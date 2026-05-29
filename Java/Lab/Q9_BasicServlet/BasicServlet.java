import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;

public class BasicServlet extends HttpServlet {
    
    @Override
    public void init() throws ServletException {
        System.out.println("Servlet is being initialized...");
    }
    
    @Override
    protected void service(HttpServletRequest request, HttpServletResponse response) 
            throws ServletException, IOException {
        System.out.println("Processing request in service()...");
        response.setContentType("text/html");
        PrintWriter out = response.getWriter();
        out.println("<html><body><h1>Basic Servlet Lifecycle Example</h1></body></html>");
    }
    
    @Override
    public void destroy() {
        System.out.println("Servlet is being destroyed...");
    }
}
