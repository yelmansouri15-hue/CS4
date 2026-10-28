import os
import sqlite3
from urllib.parse import urlparse
from cs50 import SQL
from datetime import datetime, timedelta
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from werkzeug.security import check_password_hash, generate_password_hash
from functools import wraps

app = Flask(__name__)


# Accept only standard web links so resources cannot inject invalid URLs.
def is_valid_url(value):
    if not value:
        return False
    parsed = urlparse(value)
    return parsed.scheme in {"http", "https"} and bool(parsed.netloc)


# Return the Monday-Sunday window for the current week.
def current_week_bounds():
    today = datetime.now().date()
    start_of_week = today - timedelta(days=today.weekday())
    end_of_week = start_of_week + timedelta(days=6)
    return start_of_week, end_of_week


# Convert form values to integers safely instead of letting bad input crash the app.
def safe_int(value, default=None):
    try:
        return int(value)
    except (TypeError, ValueError):
        return default


# SQLite file path used for transaction-safe schedule creation.
DB_PATH = os.path.join(os.path.dirname(__file__), "classes.db")

app.config["SECRET_KEY"] = os.environ.get("SECRET_KEY", "dev-only-secret-key")
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
app.config["SESSION_COOKIE_HTTPONLY"] = True
app.config["SESSION_COOKIE_SAMESITE"] = "Lax"
Session(app)

db = SQL("sqlite:///classes.db")


# Protect routes so only authenticated users can access them.
def login_required(f):
    @wraps(f)
    def decorated_function(*args, **kwargs):
        if session.get("user_id") is None:
            return redirect("/login")
        return f(*args, **kwargs)

    return decorated_function

@app.route("/")
@login_required
def index():
    user = db.execute("SELECT * FROM users WHERE id = ?", session["user_id"])[0]
    now = datetime.now()
    current_date = now.strftime("%Y-%m-%d")
    current_time = now.strftime("%H:%M:%S")

    if session["user_role"] == "Professor":
        start_of_week, end_of_week = current_week_bounds()

        classes = db.execute("""
            SELECT schedules.*, users.username AS student_name
            FROM schedules
            JOIN users ON schedules.student_id = users.id
            WHERE teacher_id = ? AND date BETWEEN ? AND ?
            ORDER BY date, time_start
        """, session["user_id"], start_of_week.strftime("%Y-%m-%d"), end_of_week.strftime("%Y-%m-%d"))

        return render_template(
            "index_professor.html",
            classes=classes,
            username=user["username"],
            start_of_week=start_of_week,
            end_of_week=end_of_week,
        )

    classes = db.execute("""
        SELECT schedules.*, users.username AS professor_name
        FROM schedules
        JOIN users ON schedules.teacher_id = users.id
        WHERE student_id = ? AND (date > ? OR (date = ? AND time_end >= ?))
        ORDER BY date, time_start
    """, session["user_id"], current_date, current_date, current_time)
    return render_template("index_student.html", classes=classes, username=user["username"])

@app.route("/classes", methods=["GET", "POST"])
@login_required
def classes():
    if session["user_role"] != "Professor":
        return redirect("/")

    if request.method == "POST":
        action = request.form.get("action")

        if action == "add":
            # Read and validate the form inputs before we do any database work.
            student_id_raw = request.form.get("student_id")
            try:
                student_id = int(student_id_raw)
                day_of_week = int(request.form.get("day_of_week"))  # 0 = Monday, 6 = Sunday
                weeks_count = int(request.form.get("weeks_count", 4))  # Default 4 weeks
            except (TypeError, ValueError):
                flash("Invalid schedule data.", "danger")
                return redirect("/classes")

            time_start = request.form.get("time_start")
            time_end = request.form.get("time_end")
            price = request.form.get("price")

            if not student_id_raw or day_of_week is None or not time_start or not time_end or not price:
                flash("Must complete all fields.", "danger")
                return redirect("/classes")

            try:
                datetime.strptime(time_start, "%H:%M")
                datetime.strptime(time_end, "%H:%M")
            except ValueError:
                flash("Invalid time format.", "danger")
                return redirect("/classes")

            if time_start >= time_end:
                flash("Start time must be before end time", "danger")
                return redirect("/classes")

            if weeks_count < 1 or weeks_count > 52:
                flash("Invalid number of weeks.", "danger")
                return redirect("/classes")

            try:
                price_value = float(price)
            except (TypeError, ValueError):
                flash("Please enter a valid price.", "danger")
                return redirect("/classes")

            if price_value < 0:
                flash("Price cannot be negative.", "danger")
                return redirect("/classes")

            valid_student = db.execute("SELECT id FROM users WHERE id = ? AND role = 'Student'", student_id)
            if not valid_student:
                flash("Selected student is invalid.", "danger")
                return redirect("/classes")

            roster_entry = db.execute("SELECT id FROM rosters WHERE teacher_id = ? AND student_id = ?", session["user_id"], student_id)
            if not roster_entry:
                flash("This student is not in your roster.", "danger")
                return redirect("/classes")

            # Pick the first class date in the upcoming week and move it forward if needed.
            today = datetime.now().date()
            current_time = datetime.now().strftime("%H:%M")
            days_ahead = day_of_week - today.weekday()

            if days_ahead < 0 or (days_ahead == 0 and time_start < current_time): 
                days_ahead += 7 # Target day already passed this week, move to next week

            first_class_date = today + timedelta(days=days_ahead)

            # Check every generated date for overlaps before inserting anything.
            conflicts = []
            dates_to_schedule = []

            # Build the recurring schedule list for the requested number of weeks.
            for i in range(weeks_count):
                current_class_date = (first_class_date + timedelta(weeks=i)).strftime("%Y-%m-%d")
                dates_to_schedule.append(current_class_date)

                # Check if the teacher or student already has a class that conflicts with this schedule.
                overlap = db.execute("""
                    SELECT id FROM schedules 
                    WHERE (teacher_id = ? OR student_id = ?)
                    AND date = ?
                    AND time_start < ?
                    AND time_end > ?
                """, session["user_id"], student_id, current_class_date, time_end, time_start)

                if overlap:
                    conflicts.append(current_class_date)

            # If there are conflicts, we abort the creation of the entire series and notify
            if conflicts:   
                conflict_dates = ", ".join(conflicts)
                flash(f"Schedule conflict detected on dates: {conflict_dates}. The professor or student is already busy at this time.", "warning")
                return redirect("/classes")

            # Insert the full recurring set atomically so the schedule is not left half-created.
            try:
                with sqlite3.connect(DB_PATH) as connection:
                    connection.execute("BEGIN")
                    for date_str in dates_to_schedule:
                        connection.execute(
                            """
                            INSERT INTO schedules (teacher_id, student_id, date, time_start, time_end, price)
                            VALUES (?, ?, ?, ?, ?, ?)
                            """,
                            (session["user_id"], student_id, date_str, time_start, time_end, price_value),
                        )
                    connection.commit()
            except sqlite3.Error:
                flash("An error occurred while creating the schedule. Please try again.", "danger")
                return redirect("/classes")

            flash("Classes scheduled successfully!", "success")
            return redirect("/")

        elif action == "cancel_single":
            # Cancel only one specific class
            schedule_id = safe_int(request.form.get("schedule_id"))
            if schedule_id is None:
                flash("Invalid class selected.", "danger")
                return redirect("/")

            db.execute("DELETE FROM schedules WHERE id = ? AND teacher_id = ?", schedule_id, session["user_id"])

            flash("Class cancelled.", "info")
            return redirect("/")

        elif action == "cancel_series":
            # Cancel all future recurring classes for this student at this time slot
            student_id = safe_int(request.form.get("student_id"))
            time_start = request.form.get("time_start")
            class_date = request.form.get("date")
            today_str = datetime.now().date().strftime("%Y-%m-%d")

            if student_id is None or not time_start or not class_date:
                flash("Invalid class series selected.", "danger")
                return redirect("/")

            db.execute("""
                DELETE FROM schedules 
                WHERE student_id = ? 
                  AND time_start = ? 
                  AND date >= ? 
                  AND teacher_id = ?
                  AND strftime('%w', date) = strftime('%w', ?)
                """, student_id, time_start, today_str, session["user_id"], class_date)

            flash("Class series cancelled.", "info")
            return redirect("/")

    students = db.execute("""
        SELECT users.id, users.username 
        FROM users 
        JOIN rosters ON users.id = rosters.student_id 
        WHERE teacher_id = ?
    """, session["user_id"])
    return render_template("classes.html", students=students)    

@app.route("/login", methods=["GET", "POST"])
def login():

    if request.method == "POST":
        # Clear stale session state before validating the new login attempt.
        session.clear()

        username = request.form.get("username")
        password = request.form.get("password")

        if not username:
            flash("Must provide username.", "danger")
            return render_template("login.html")
        elif not password:
            flash("Must provide password.", "danger")
            return render_template("login.html")
        
        rows = db.execute("SELECT * FROM users WHERE username = ?", username)

        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], password):
            flash("Invalid username and/or password.", "danger")
            return render_template("login.html")

        session["user_id"] = rows[0]["id"]
        session["user_role"] = rows[0]["role"]

        flash(f"Welcome back, {rows[0]['username']}!", "success")
        return redirect("/")

    return render_template("login.html")

@app.route("/logout")
def logout():
    session.clear()
    return redirect("/")

@app.route("/register", methods=["GET", "POST"])
def register():
    if request.method == "POST":
        username = request.form.get("username").strip()
        password = request.form.get("password")
        role = request.form.get("role")
        confirmation = request.form.get("confirmation")

        # Basic validations for required registration data and role selection.
        if not username or not password or not role:
            flash("Must complete all the fields", "danger")
            return render_template("register.html")

        if role not in {"Professor", "Student"}:
            flash("Invalid role selected.", "danger")
            return render_template("register.html")

        # Encrypt the password
        hash_pw = generate_password_hash(password)

        try:
            db.execute("INSERT INTO users (username, hash, role) VALUES (?, ?, ?)", username, hash_pw, role)
            user_id = db.execute("SELECT id FROM users WHERE username = ?", username)

            session["user_id"] = user_id[0]["id"]
            session["user_role"] = role

        except sqlite3.IntegrityError:
            flash("The username already exists", "danger")
            return render_template("register.html")

        return redirect("/login")
        
    return render_template("register.html")

@app.route("/roster", methods=["GET", "POST"])
@login_required
def roster():
    if session.get("user_role") != "Professor":
        return redirect("/")
    
    if request.method == "POST":
        action = request.form.get("action")
        student_id = request.form.get("student_id")
        
        if action == "add":
            # Prevent invalid IDs from reaching the database and ensure roster entries are unique.
            student_id = safe_int(request.form.get("student_id"))
            if student_id is None:
                flash("Please select a student.", "danger")
                return redirect("/roster")

            check = db.execute("SELECT * FROM rosters WHERE teacher_id = ? AND student_id = ?", session["user_id"], student_id)
            if check:
                flash("Student is already in your roster.", "warning")
                return redirect("/roster")

            try:
                db.execute("INSERT INTO rosters (teacher_id, student_id) VALUES (?, ?)", session["user_id"], student_id)
                flash("Student added to your roster.", "success")
            except sqlite3.IntegrityError:
                flash("Student is already in your roster.", "warning")
                
        elif action == "remove":
            student_id = safe_int(request.form.get("student_id"))
            if student_id is None:
                flash("Invalid student selected.", "danger")
                return redirect("/roster")

            db.execute("DELETE FROM rosters WHERE teacher_id = ? AND student_id = ?", session["user_id"], student_id)
            flash("Student removed from roster.", "info")
            
        return redirect("/roster")
        
    # GET: Load the professor's specific students
    my_students = db.execute("""
        SELECT users.id, users.username 
        FROM users 
        JOIN rosters ON users.id = rosters.student_id 
        WHERE rosters.teacher_id = ?
    """, session["user_id"])
    
    # Load students NOT currently in the roster so they can be added
    other_students = db.execute("""
        SELECT id, username FROM users 
        WHERE role = 'Student' AND id NOT IN (
            SELECT student_id FROM rosters WHERE teacher_id = ?
        )
    """, session["user_id"])
    
    return render_template("roster.html", my_students=my_students, other_students=other_students)

@app.route("/payments", methods=["GET", "POST"])
@login_required
def payments():
    current_date = datetime.now().strftime("%Y-%m-%d")
    current_time = datetime.now().strftime("%H:%M:%S")

    if request.method == "POST":
        # Payment submissions are only valid when a real class ID and proof are present.
        action = request.form.get("action")
        schedule_id = safe_int(request.form.get("schedule_id"))

        if session.get("user_role") == "Student" and action == "pay":
            proof = (request.form.get("payment_proof") or "").strip()
            if not proof or schedule_id is None:
                flash("The proof of payment has not been submitted.", "danger")
                return redirect("/payments")

            db.execute("UPDATE schedules SET status = 'Revision', payment_proof = ? WHERE id = ? AND student_id = ?", proof, schedule_id, session["user_id"])
            flash("Payment submitted for revision.", "success")

        elif session.get("user_role") == "Professor":
            if action == "confirm":
                db.execute("UPDATE schedules SET status = 'Paid' WHERE id = ? AND teacher_id = ?", schedule_id, session["user_id"])
                flash("Payment confirmed.", "success")
            elif action == "delete":
                db.execute("DELETE FROM schedules WHERE id = ? AND teacher_id = ?", schedule_id, session["user_id"])
                flash("Class marked as not held and deleted.", "info")

        return redirect("/payments")

    role_column = "teacher_id" if session.get("user_role") == "Professor" else "student_id"
    join_column = "student_id" if session.get("user_role") == "Professor" else "teacher_id"
    name_alias = "student_name" if session.get("user_role") == "Professor" else "professor_name"

    past_classes = db.execute(f"""
        SELECT schedules.*, users.username AS {name_alias} 
        FROM schedules 
        JOIN users ON schedules.{join_column} = users.id 
        WHERE {role_column} = ? AND (date < ? OR (date = ? AND time_end < ?)) 
        ORDER BY date DESC, time_start DESC
    """, session["user_id"], current_date, current_date, current_time)

    return render_template("payments.html", classes=past_classes)

@app.route("/resources", methods=["GET", "POST"])
@login_required
def resources():

    if session.get("user_role") == "Professor":

        if request.method == "POST":
            action = request.form.get("action")

            # Professors may add resources only for students they actually manage.
            if action == "add":
                student_id = safe_int(request.form.get("student_id"))
                title = (request.form.get("title") or "").strip()
                url_link = (request.form.get("url_link") or "").strip()

                if student_id is None or not title or not url_link:
                    return "Must complete all fields", 400

                if not is_valid_url(url_link):
                    flash("Please provide a valid http or https link.", "danger")
                    return redirect("/resources")

                check = db.execute("SELECT * FROM rosters WHERE teacher_id = ? AND student_id = ?", session["user_id"], student_id)
                if not check:
                    flash("Error: This student is not in your roster.", "danger")
                    return redirect("/resources")

                db.execute("INSERT INTO resources (teacher_id, student_id, title, url_link) VALUES (?, ?, ?, ?)",
                        session["user_id"], student_id, title, url_link)

            # Delete an existing resource
            elif action == "delete":
                resource_id = request.form.get("resource_id")
                
                if resource_id:
                    # Ensure the professor only deletes their own resources
                    db.execute("DELETE FROM resources WHERE id = ? AND teacher_id = ?", resource_id, session["user_id"])

            # Redirect using GET to avoid form resubmission on page refresh
            return redirect("/resources")

        # If GET method: load the page data
        # 1. Fetch all resources created by this professor
        resources = db.execute("""
            SELECT resources.*, users.username AS student_name 
            FROM resources 
            JOIN users ON resources.student_id = users.id 
            WHERE teacher_id = ?
            ORDER BY resources.id DESC
        """, session["user_id"])

        # 2. Fetch all students to populate the form dropdown
        students = db.execute("""
                SELECT users.id, users.username 
                FROM users 
                JOIN rosters ON users.id = rosters.student_id 
                WHERE teacher_id = ?
            """, session["user_id"])

        return render_template("resources.html", resources=resources, students=students)

    else:
        # Students see the professor who assigned each resource, not the student record itself.
        resources = db.execute("""
            SELECT resources.*, users.username AS professor_name
            FROM resources
            JOIN users ON resources.teacher_id = users.id
            WHERE student_id = ?
            ORDER BY resources.id DESC
        """, session["user_id"])

        professors = db.execute("SELECT id, username FROM users WHERE role = 'Professor'")

        return render_template("resources.html", resources=resources, professors=professors)

if __name__ == '__main__':
    app.run(debug=False)
