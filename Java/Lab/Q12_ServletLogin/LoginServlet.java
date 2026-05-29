import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;

public class LoginServlet extends HttpServlet {
    
    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response) 
            throws ServletException, IOException {
        String user = request.getParameter("username");
        String pass = request.getParameter("password");
        
        response.setContentType("text/html");
        PrintWriter out = response.getWriter();
        
        if("admin".equals(user) && "admin123".equals(pass)) {
            out.println("<h2 style='color:green'>Login Successful!</h2>");
            out.println("<p>Welcome, " + user + "</p>");
        } else {
            out.println("<h2 style='color:red'>Login Failed! Invalid username or password.</h2>");
        }
    }
}
