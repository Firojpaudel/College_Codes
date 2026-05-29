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
        Name: <input type="text" name="name" required><br><br>
        Email: <input type="email" name="email" required><br><br>
        <input type="submit" value="Submit">
    </form>

    <% 
        String name = request.getParameter("name");
        String email = request.getParameter("email");
        
        if (name != null && email != null && !name.isEmpty() && !email.isEmpty()) {
            Connection conn = null;
            PreparedStatement pstmt = null;
            try {
                Class.forName("com.mysql.cj.jdbc.Driver");
                conn = DriverManager.getConnection("jdbc:mysql://localhost:3306/school", "root", "root");
                
                String sql = "INSERT INTO students (name, email) VALUES (?, ?)";
                pstmt = conn.prepareStatement(sql);
                pstmt.setString(1, name);
                pstmt.setString(2, email);
                int rows = pstmt.executeUpdate();
                
                if (rows > 0) {
                    out.println("<p style='color:green'>Record inserted successfully!</p>");
                }
            } catch (Exception e) {
                out.println("<p style='color:red'>Database Error: " + e.getMessage() + "</p>");
            } finally {
                if(pstmt != null) pstmt.close();
                if(conn != null) conn.close();
            }
        }
    %>
</body>
</html>
