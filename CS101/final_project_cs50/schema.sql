-- Table of users (professors and students)
CREATE TABLE users (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    username TEXT NOT NULL UNIQUE,
    hash TEXT NOT NULL,
    role TEXT NOT NULL CHECK(role IN ('Professor', 'Student'))
);

-- Table of schedules/classes
CREATE TABLE schedules (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    teacher_id INTEGER NOT NULL,
    student_id INTEGER NOT NULL,
    date TEXT NOT NULL,       -- Format: YYYY-MM-DD
    time_start TIME NOT NULL, -- Format: HH:MM
    time_end TIME NOT NULL,   -- Format: HH:MM
    price REAL NOT NULL,
    status TEXT CHECK(status IN ('Pending', 'Revision', 'Paid')) DEFAULT ('Pending'),
    payment_proof TEXT,
    FOREIGN KEY(teacher_id) REFERENCES users(id),
    FOREIGN KEY(student_id) REFERENCES users(id)
);

-- Table of resources (exercices, links)
CREATE TABLE resources (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    teacher_id INTEGER NOT NULL,
    student_id INTEGER NOT NULL,
    title TEXT NOT NULL,
    url_link TEXT NOT NULL,
    FOREIGN KEY(teacher_id) REFERENCES users(id),
    FOREIGN KEY(student_id) REFERENCES users(id)
);

CREATE TABLE rosters (
    id INTEGER PRIMARY KEY AUTOINCREMENT,
    teacher_id INTEGER NOT NULL,
    student_id INTEGER NOT NULL,
    FOREIGN KEY(teacher_id) REFERENCES users(id),
    FOREIGN KEY(student_id) REFERENCES users(id),
    UNIQUE(teacher_id, student_id)
);

CREATE INDEX idx_schedules_teacher ON schedules(teacher_id, date);
CREATE INDEX idx_schedules_student ON schedules(student_id, date);
CREATE INDEX idx_resources_student ON resources(student_id);