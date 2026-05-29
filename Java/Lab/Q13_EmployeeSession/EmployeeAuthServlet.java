import java.io.*;
import java.sql.*;
import javax.servlet.*;
import javax.servlet.http.*;

public class EmployeeAuthServlet extends HttpServlet {
    
    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response) 
            throws ServletException, IOException {
        String action = request.getParameter("action");
        PrintWriter out = response.getWriter();
        response.setContentType("text/html");
        
        if ("login".equals(action)) {
            String uname = request.getParameter("username");
            String pass = request.getParameter("password");
            
            // Dummy check, in real scenario check DB
            if ("employee".equals(uname) && "emp123".equals(pass)) {
                HttpSession session = request.getSession();
                session.setAttribute("user", uname);
                out.println("<h2>Login successful! Session created for " + uname + "</h2>");
                out.println("<a href='EmployeeAuthServlet?action=logout'>Logout</a>");
            } else {
                out.println("<h2>Login failed.</h2>");
            }
        } 
        
        if ("logout".equals(action)) {
            HttpSession session = request.getSession(false);
            if (session != null) {
                session.invalidate();
                out.println("<h2>Logged out successfully. Session invalidated.</h2>");
            } else {
                out.println("<h2>No active session found.</h2>");
            }
        }
    }
    
    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) 
            throws ServletException, IOException {
        doPost(request, response);
    }
}
