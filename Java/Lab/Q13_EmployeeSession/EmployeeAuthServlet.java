import java.io.*;
import java.sql.*;
import javax.servlet.*;
import javax.servlet.http.*;

public class EmployeeAuthServlet extends HttpServlet {

    private String dbUrl = "jdbc:mysql://localhost:3306/school";
    private String dbUser = "root";
    private String dbPass = "";

    @Override
    public void init() throws ServletException {
        try {
            Class.forName("com.mysql.cj.jdbc.Driver");
            // Auto-create database & table if not exists for easy setup
            try (Connection conn = DriverManager.getConnection("jdbc:mysql://localhost:3306/", dbUser, dbPass);
                    Statement stmt = conn.createStatement()) {
                stmt.executeUpdate("CREATE DATABASE IF NOT EXISTS school");
            }

            try (Connection conn = DriverManager.getConnection(dbUrl, dbUser, dbPass);
                    Statement stmt = conn.createStatement()) {
                stmt.executeUpdate("CREATE TABLE IF NOT EXISTS employees (" +
                        "id INT AUTO_INCREMENT PRIMARY KEY, " +
                        "name VARCHAR(100), " +
                        "email VARCHAR(100), " +
                        "course VARCHAR(100), " +
                        "salary DOUBLE, " +
                        "username VARCHAR(50), " +
                        "password VARCHAR(50))");

                // Add a default user if database is empty
                ResultSet rs = stmt.executeQuery("SELECT COUNT(*) FROM employees");
                if (rs.next() && rs.getInt(1) == 0) {
                    stmt.executeUpdate("INSERT INTO employees (name, email, course, salary, username, password) " +
                            "VALUES ('Admin', 'admin@mail.com', 'IT', 75000.0, 'admin', 'admin123')");
                }
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    private Connection getConnection() throws SQLException {
        return DriverManager.getConnection(dbUrl, dbUser, dbPass);
    }

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        response.setContentType("text/html");
        PrintWriter out = response.getWriter();

        HttpSession session = request.getSession(false);
        String action = request.getParameter("action");

        // Handle logout
        if ("logout".equals(action)) {
            if (session != null) {
                session.invalidate();
            }
            out.println("<html><body>");
            out.println("<h2>Logged out successfully. Session invalidated.</h2>");
            out.println("<p><a href='login.html'>Go back to Login</a></p>");
            out.println("</body></html>");
            return;
        }

        // Check if session exists
        if (session == null || session.getAttribute("user") == null) {
            response.sendRedirect("login.html");
            return;
        }

        String loggedInUser = (String) session.getAttribute("user");

        // Handle delete action
        if ("delete".equals(action)) {
            String idStr = request.getParameter("id");
            if (idStr != null) {
                try (Connection conn = getConnection();
                        PreparedStatement ps = conn.prepareStatement("DELETE FROM employees WHERE id = ?")) {
                    ps.setInt(1, Integer.parseInt(idStr));
                    ps.executeUpdate();
                    out.println("<h3 style='color:green'>Employee deleted successfully!</h3>");
                } catch (Exception e) {
                    out.println("<h3 style='color:red'>Error deleting employee: " + e.getMessage() + "</h3>");
                }
            }
        }

        // Check if loading for edit
        int editId = -1;
        String editName = "", editEmail = "", editCourse = "", editSalary = "";
        if ("edit".equals(action)) {
            String idStr = request.getParameter("id");
            if (idStr != null) {
                try (Connection conn = getConnection();
                        PreparedStatement ps = conn.prepareStatement("SELECT * FROM employees WHERE id = ?")) {
                    ps.setInt(1, Integer.parseInt(idStr));
                    ResultSet rs = ps.executeQuery();
                    if (rs.next()) {
                        editId = rs.getInt("id");
                        editName = rs.getString("name");
                        editEmail = rs.getString("email");
                        editCourse = rs.getString("course");
                        editSalary = String.valueOf(rs.getDouble("salary"));
                    }
                } catch (Exception e) {
                    e.printStackTrace();
                }
            }
        }

        // Render dashboard
        out.println("<html>");
        out.println("<body>");
        out.println("<h2>Employee System Dashboard</h2>");
        out.println("<p>Welcome, <strong>" + loggedInUser + "</strong> (Session Active)</p>");
        out.println("<p><a href='EmployeeAuthServlet?action=logout'>Logout</a></p>");
        out.println("<hr>");

        // Search Form
        String search = request.getParameter("search");
        out.println("<h3>Search Employee / Student</h3>");
        out.println("<form method='GET' action='EmployeeAuthServlet'>");
        out.println("  Search by ID or Name: <input type='text' name='search' value='" + (search != null ? search : "")
                + "'>");
        out.println("  <input type='submit' value='Search'>");
        out.println("  <a href='EmployeeAuthServlet'>Clear</a>");
        out.println("</form>");
        out.println("<hr>");

        // Add / Update Form
        if (editId != -1) {
            out.println("<h3>Update Employee Record</h3>");
            out.println("<form method='POST' action='EmployeeAuthServlet'>");
            out.println("  <input type='hidden' name='action' value='update'>");
            out.println("  <input type='hidden' name='id' value='" + editId + "'>");
            out.println("  Name: <input type='text' name='name' value='" + editName + "' required><br><br>");
            out.println("  Email: <input type='email' name='email' value='" + editEmail + "' required><br><br>");
            out.println("  Course/Designation: <input type='text' name='course' value='" + editCourse
                    + "' required><br><br>");
            out.println("  Salary: <input type='number' step='0.01' name='salary' value='" + editSalary
                    + "' required><br><br>");
            out.println("  <input type='submit' value='Update Employee'>");
            out.println("</form>");
        } else {
            out.println("<h3>Register New Employee</h3>");
            out.println("<form method='POST' action='EmployeeAuthServlet'>");
            out.println("  <input type='hidden' name='action' value='register'>");
            out.println("  Name: <input type='text' name='name' required><br><br>");
            out.println("  Email: <input type='email' name='email' required><br><br>");
            out.println("  Course/Designation: <input type='text' name='course' required><br><br>");
            out.println("  Salary: <input type='number' step='0.01' name='salary' required><br><br>");
            out.println("  Username: <input type='text' name='username' required><br><br>");
            out.println("  Password: <input type='password' name='password' required><br><br>");
            out.println("  <input type='submit' value='Register Employee'>");
            out.println("</form>");
        }
        out.println("<hr>");

        // Display Table
        out.println("<h3>Employee Records</h3>");
        out.println("<table border='1' cellpadding='8' cellspacing='0'>");
        out.println(
                "<tr><th>ID</th><th>Name</th><th>Email</th><th>Course/Designation</th><th>Salary</th><th>Username</th><th>Actions</th></tr>");

        String query = "SELECT * FROM employees";
        boolean hasSearch = (search != null && !search.trim().isEmpty());
        if (hasSearch) {
            query = "SELECT * FROM employees WHERE id = ? OR name LIKE ?";
        }

        try (Connection conn = getConnection();
                PreparedStatement ps = conn.prepareStatement(query)) {
            if (hasSearch) {
                int searchId = -1;
                try {
                    searchId = Integer.parseInt(search.trim());
                } catch (NumberFormatException e) {
                }
                ps.setInt(1, searchId);
                ps.setString(2, "%" + search + "%");
            }
            ResultSet rs = ps.executeQuery();
            while (rs.next()) {
                int id = rs.getInt("id");
                out.println("<tr>");
                out.println("<td>" + id + "</td>");
                out.println("<td>" + rs.getString("name") + "</td>");
                out.println("<td>" + rs.getString("email") + "</td>");
                out.println("<td>" + rs.getString("course") + "</td>");
                out.println("<td>" + rs.getDouble("salary") + "</td>");
                out.println("<td>" + rs.getString("username") + "</td>");
                out.println("<td>");
                out.println("  <a href='EmployeeAuthServlet?action=edit&id=" + id + "'>Edit</a> | ");
                out.println("  <a href='EmployeeAuthServlet?action=delete&id=" + id
                        + "' onclick='return confirm(\"Are you sure?\")'>Delete</a>");
                out.println("</td>");
                out.println("</tr>");
            }
        } catch (Exception e) {
            out.println("<tr><td colspan='7'>Error fetching records: " + e.getMessage() + "</td></tr>");
        }
        out.println("</table>");
        out.println("</body>");
        out.println("</html>");
    }

    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        response.setContentType("text/html");
        PrintWriter out = response.getWriter();
        String action = request.getParameter("action");

        try (Connection conn = getConnection()) {
            if ("login".equals(action)) {
                String uname = request.getParameter("username");
                String pass = request.getParameter("password");

                try (PreparedStatement ps = conn
                        .prepareStatement("SELECT * FROM employees WHERE username = ? AND password = ?")) {
                    ps.setString(1, uname);
                    ps.setString(2, pass);
                    ResultSet rs = ps.executeQuery();

                    if (rs.next()) {
                        HttpSession session = request.getSession();
                        session.setAttribute("user", uname);
                        response.sendRedirect("EmployeeAuthServlet");
                    } else {
                        out.println("<html><body>");
                        out.println("<h2 style='color:red'>Invalid login credentials!</h2>");
                        out.println("<p><a href='login.html'>Try Again</a></p>");
                        out.println("</body></html>");
                    }
                }
            } else if ("register".equals(action)) {
                String name = request.getParameter("name");
                String email = request.getParameter("email");
                String course = request.getParameter("course");
                double salary = Double.parseDouble(request.getParameter("salary"));
                String uname = request.getParameter("username");
                String pass = request.getParameter("password");

                String sql = "INSERT INTO employees (name, email, course, salary, username, password) VALUES (?, ?, ?, ?, ?, ?)";
                try (PreparedStatement ps = conn.prepareStatement(sql)) {
                    ps.setString(1, name);
                    ps.setString(2, email);
                    ps.setString(3, course);
                    ps.setDouble(4, salary);
                    ps.setString(5, uname);
                    ps.setString(6, pass);
                    ps.executeUpdate();

                    out.println("<html><body>");
                    out.println("<h2 style='color:green'>Employee inserted successfully!</h2>");
                    out.println("<p><a href='EmployeeAuthServlet'>Back to Dashboard</a></p>");
                    out.println("</body></html>");
                }
            } else if ("update".equals(action)) {
                int id = Integer.parseInt(request.getParameter("id"));
                String name = request.getParameter("name");
                String email = request.getParameter("email");
                String course = request.getParameter("course");
                double salary = Double.parseDouble(request.getParameter("salary"));

                String sql = "UPDATE employees SET name = ?, email = ?, course = ?, salary = ? WHERE id = ?";
                try (PreparedStatement ps = conn.prepareStatement(sql)) {
                    ps.setString(1, name);
                    ps.setString(2, email);
                    ps.setString(3, course);
                    ps.setDouble(4, salary);
                    ps.setInt(5, id);
                    ps.executeUpdate();

                    out.println("<html><body>");
                    out.println("<h2 style='color:green'>Employee updated successfully!</h2>");
                    out.println("<p><a href='EmployeeAuthServlet'>Back to Dashboard</a></p>");
                    out.println("</body></html>");
                }
            }
        } catch (Exception e) {
            out.println("<html><body>");
            out.println("<h2 style='color:red'>Database Error: " + e.getMessage() + "</h2>");
            out.println("<p><a href='EmployeeAuthServlet'>Back to Dashboard</a></p>");
            out.println("</body></html>");
        }
    }
}
