<%@ page language="java" contentType="text/html; charset=UTF-8" pageEncoding="UTF-8"%>
<!DOCTYPE html>
<html>
<head>
    <title>Student Login - Exam</title>
</head>
<body>
    <h2>Online Exam - Student Login</h2>
    <%
        String msg = request.getParameter("msg");
        if (msg != null) {
            out.println("<p style='color:red'>" + msg + "</p>");
        }
    %>
    <form action="login.jsp" method="POST">
        Enter Username: <input type="text" name="username" required><br><br>
        <input type="submit" value="Start Exam">
    </form>

    <%
        if (request.getMethod().equalsIgnoreCase("POST")) {
            String username = request.getParameter("username");
            if (username != null && !username.trim().isEmpty()) {
                // Start session and store username
                session.setAttribute("student", username.trim());
                // Set session timeout to 2 minutes (120 seconds) for demonstration
                session.setMaxInactiveInterval(120);
                
                response.sendRedirect("exam.jsp");
            }
        }
    %>
</body>
</html>
