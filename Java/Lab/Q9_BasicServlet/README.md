# Q9: Basic Servlet Application & Lifecycle

This laboratory task demonstrates a basic Java Servlet application showcasing the Servlet lifecycle (init, service, and destroy).

## Compile Command
Compile the servlet from the 'Java' directory:
```powershell
javac -cp "lib/javax.servlet-api-4.0.1.jar" -d Lab/Q9_BasicServlet Lab/Q9_BasicServlet/BasicServlet.java
```

## Deployment Structure
Deploy files inside Tomcat's webapps directory (e.g., C:\xampp\tomcat\webapps):
```text
C:\xampp\tomcat\webapps\basic-app\
└── WEB-INF/
    ├── web.xml
    └── classes/
        └── BasicServlet.class
```

## Running
1. Copy web.xml to C:\xampp\tomcat\webapps\basic-app\WEB-INF\
2. Copy BasicServlet.class to C:\xampp\tomcat\webapps\basic-app\WEB-INF\classes\
3. Start Tomcat using XAMPP Control Panel or C:\xampp\tomcat\bin\startup.bat
4. Access in browser: http://localhost:8080/basic-app/basic
5. Check the console or logs to see the lifecycle output (init, service, destroy).
