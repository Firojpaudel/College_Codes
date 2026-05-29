import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;

public class HelloServlet extends HttpServlet {
    
    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) 
            throws ServletException, IOException {
        String userName = request.getParameter("name");
        
        response.setContentType("text/html");
        PrintWriter out = response.getWriter();
        
        out.println("<html><body>");
        if(userName != null && !userName.isEmpty()) {
            out.println("<h1>Welcome, " + userName + "!</h1>");
        } else {
            out.println("<h1>Welcome, Guest! Please pass ?name=YourName in URL</h1>");
        }
        out.println("</body></html>");
    }
}
