<%@ page language="java" contentType="text/html; charset=UTF-8" pageEncoding="UTF-8"%>
<%@ page import="java.sql.*" %>
<!DOCTYPE html>
<html>
<head>
    <title>JSP Student Registration</title>
</head>
<body>
    <h2>Register Student</h2>
    <form action="register.jsp" method="POST">
        Name: <input type="text" name="name"><br><br>
        Email: <input type="text" name="email"><br><br>
        <input type="submit" value="Submit">
    </form>

    <% 
        String name = request.getParameter("name");
        String email = request.getParameter("email");
        
        String dbUrl = "jdbc:mysql://localhost:3306/school";
        String dbUser = "root";
        String dbPass = ""; // Matches default XAMPP config

        // Initialize driver and database/table
        try {
            Class.forName("com.mysql.cj.jdbc.Driver");
            try (Connection connSetup = DriverManager.getConnection("jdbc:mysql://localhost:3306/", dbUser, dbPass);
                 Statement stmtSetup = connSetup.createStatement()) {
                stmtSetup.executeUpdate("CREATE DATABASE IF NOT EXISTS school");
            }
            try (Connection connSetup = DriverManager.getConnection(dbUrl, dbUser, dbPass);
                 Statement stmtSetup = connSetup.createStatement()) {
                stmtSetup.executeUpdate("CREATE TABLE IF NOT EXISTS students (" +
                        "id INT AUTO_INCREMENT PRIMARY KEY, " +
                        "name VARCHAR(100), " +
                        "email VARCHAR(100))");
            }
        } catch (Exception e) {
            out.println("<p style='color:red'>Database Initialization Error: " + e.getMessage() + "</p>");
        }

        // Process POST registration
        if (request.getMethod().equalsIgnoreCase("POST")) {
            // Validate empty fields
            if (name == null || email == null || name.trim().isEmpty() || email.trim().isEmpty()) {
                out.println("<p style='color:red'>Validation Error: Name and Email fields cannot be empty!</p>");
            } else {
                // Insert record
                try (Connection conn = DriverManager.getConnection(dbUrl, dbUser, dbPass);
                     PreparedStatement pstmt = conn.prepareStatement("INSERT INTO students (name, email) VALUES (?, ?)")) {
                    pstmt.setString(1, name.trim());
                    pstmt.setString(2, email.trim());
                    int rows = pstmt.executeUpdate();
                    
                    if (rows > 0) {
                        out.println("<p style='color:green'>Record inserted successfully!</p>");
                        out.println("<h3>Last Entered Details:</h3>");
                        out.println("<p><strong>Name:</strong> " + name + "</p>");
                        out.println("<p><strong>Email:</strong> " + email + "</p>");
                    }
                } catch (SQLException e) {
                    out.println("<p style='color:red'>SQL Exception: " + e.getMessage() + "</p>");
                }
            }
        }
    %>

    <hr>
    <h3>All Stored Students</h3>
    <table border="1" cellpadding="8" cellspacing="0">
        <tr>
            <th>ID</th>
            <th>Name</th>
            <th>Email</th>
        </tr>
        <% 
            try (Connection conn = DriverManager.getConnection(dbUrl, dbUser, dbPass);
                 Statement stmt = conn.createStatement();
                 ResultSet rs = stmt.executeQuery("SELECT * FROM students")) {
                while (rs.next()) {
        %>
        <tr>
            <td><%= rs.getInt("id") %></td>
            <td><%= rs.getString("name") %></td>
            <td><%= rs.getString("email") %></td>
        </tr>
        <% 
                }
            } catch (SQLException e) {
                out.println("<tr><td colspan='3' style='color:red'>SQL Exception while loading: " + e.getMessage() + "</td></tr>");
            }
        %>
    </table>
</body>
</html>
