<%@ page language="java" contentType="text/html; charset=UTF-8" pageEncoding="UTF-8"%>
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
        
        out.println("<p>Your score is: " + score + " / 2</p>");
        // Here you can insert the score into the database via JDBC
    %>
    <a href="exam.jsp">Retake Exam</a>
</body>
</html>
