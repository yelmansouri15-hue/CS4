document.addEventListener("DOMContentLoaded", function () {
    const toggleBtn = document.getElementById("togglePaidBtn");
    if (!toggleBtn) {
        return;
    }

    const rows = document.querySelectorAll(".class-row");
    let isHidingPaid = false;

    toggleBtn.addEventListener("click", function () {
        isHidingPaid = !isHidingPaid;

        if (isHidingPaid) {
            toggleBtn.textContent = "Show Paid Classes";
            toggleBtn.classList.replace("btn-outline-secondary", "btn-secondary");
        } else {
            toggleBtn.textContent = "Hide Paid Classes";
            toggleBtn.classList.replace("btn-secondary", "btn-outline-secondary");
        }

        rows.forEach((row) => {
            if (row.getAttribute("data-status") === "Paid") {
                row.style.display = isHidingPaid ? "none" : "";
            }
        });
    });
});
