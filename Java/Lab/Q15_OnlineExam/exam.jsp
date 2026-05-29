<%@ page language="java" contentType="text/html; charset=UTF-8" pageEncoding="UTF-8"%>
<!DOCTYPE html>
<html>
<head>
    <title>Online Exam</title>
</head>
<body>
    <h2>Java Programming Exam</h2>
    <form action="result.jsp" method="POST">
        <p>1. What is the size of int in Java?</p>
        <input type="radio" name="q1" value="2" required> 2 Bytes<br>
        <input type="radio" name="q1" value="4"> 4 Bytes<br>
        <input type="radio" name="q1" value="8"> 8 Bytes<br>
        
        <p>2. Which method is the entry point in Java?</p>
        <input type="radio" name="q2" value="start" required> start()<br>
        <input type="radio" name="q2" value="main"> main()<br>
        <input type="radio" name="q2" value="init"> init()<br>
        
        <br>
        <input type="submit" value="Submit Answers">
    </form>
</body>
</html>
