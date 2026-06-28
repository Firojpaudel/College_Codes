<%@ page language="java" contentType="text/html; charset=UTF-8" pageEncoding="UTF-8"%>
<%@ page import="java.sql.*" %>
<%
    // Check if session has timed out before calculations
    if (session == null || session.getAttribute("student") == null) {
        response.sendRedirect("login.jsp?msg=Session+timed+out!+Your+answers+could+not+be+saved.");
        return;
    }
    String student = (String) session.getAttribute("student");
%>
<!DOCTYPE html>
<html>
<head>
    <title>Exam Result</title>
</head>
<body>
    <h2>Exam Results</h2>
    
    <%
        int score = 0;
        String ans1 = request.getParameter("q1");
        String ans2 = request.getParameter("q2");
        
        if ("4".equals(ans1)) score++;
        if ("main".equals(ans2)) score++;
        
        out.println("<p>Student Name: <strong>" + student + "</strong></p>");
        out.println("<p>Your answers: Q1 = " + ans1 + ", Q2 = " + ans2 + "</p>");
        out.println("<h3>Your score is: " + score + " / 2</h3>");
        
        String dbUrl = "jdbc:mysql://localhost:3306/school";
        String dbUser = "root";
        String dbPass = "";

        // Database Storage
        try {
            Class.forName("com.mysql.cj.jdbc.Driver");
            try (Connection connSetup = DriverManager.getConnection("jdbc:mysql://localhost:3306/", dbUser, dbPass);
                 Statement stmtSetup = connSetup.createStatement()) {
                stmtSetup.executeUpdate("CREATE DATABASE IF NOT EXISTS school");
            }
            try (Connection connSetup = DriverManager.getConnection(dbUrl, dbUser, dbPass);
                 Statement stmtSetup = connSetup.createStatement()) {
                stmtSetup.executeUpdate("CREATE TABLE IF NOT EXISTS exam_results (" +
                        "id INT AUTO_INCREMENT PRIMARY KEY, " +
                        "username VARCHAR(100), " +
                        "score INT, " +
                        "exam_time TIMESTAMP DEFAULT CURRENT_TIMESTAMP)");
            }

            try (Connection conn = DriverManager.getConnection(dbUrl, dbUser, dbPass);
                 PreparedStatement pstmt = conn.prepareStatement("INSERT INTO exam_results (username, score) VALUES (?, ?)")) {
                pstmt.setString(1, student);
                pstmt.setInt(2, score);
                pstmt.executeUpdate();
                out.println("<p style='color:green;'>Result successfully saved to the database.</p>");
            }
        } catch (SQLException e) {
            out.println("<p style='color:red;'>SQL Exception: " + e.getMessage() + "</p>");
        } catch (Exception e) {
            out.println("<p style='color:red;'>Exception: " + e.getMessage() + "</p>");
        }

        // Invalidate session now that the exam is finished
        session.invalidate();
    %>

    <hr>
    <h3>All Stored Exam Results</h3>
    <table border="1" cellpadding="8" cellspacing="0">
        <tr>
            <th>ID</th>
            <th>Student</th>
            <th>Score</th>
            <th>Exam Date/Time</th>
        </tr>
        <%
            try (Connection conn = DriverManager.getConnection(dbUrl, dbUser, dbPass);
                 Statement stmt = conn.createStatement();
                 ResultSet rs = stmt.executeQuery("SELECT * FROM exam_results ORDER BY exam_time DESC")) {
                while (rs.next()) {
        %>
        <tr>
            <td><%= rs.getInt("id") %></td>
            <td><%= rs.getString("username") %></td>
            <td><%= rs.getInt("score") %> / 2</td>
            <td><%= rs.getTimestamp("exam_time") %></td>
        </tr>
        <%
                }
            } catch (SQLException e) {
                out.println("<tr><td colspan='4' style='color:red;'>SQL Exception: " + e.getMessage() + "</td></tr>");
            }
        %>
    </table>

    <br>
    <a href="login.jsp">Take Exam Again</a>
</body>
</html>
