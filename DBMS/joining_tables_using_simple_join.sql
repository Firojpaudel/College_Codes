/*
Objective: Create two tables Students and Course; then JOIN the tables using simple join:
*/
CREATE DATABASE lab_3;
USE lab_3;

-- Creating the Student table
CREATE TABLE Student (
    StdId INT,
    StdName VARCHAR(50),
    CourseID INT
);

INSERT INTO Student (StdId, StdName, CourseID)
VALUES
(1001, 'XYZ', 2001),
(1002, 'ABC', 2002),
(1003, 'PQR', 2003);

-- Creating the Course table
CREATE TABLE Course (
    CourseID INT,
    CourseName VARCHAR(50)
);

INSERT INTO Course (CourseID, CourseName)
VALUES
(2001, 'Database'),
(2002, 'AI'),
(2003, 'Operating System'),
(2004, 'C Programming');

-- Performing a simple left join on the CourseID column
SELECT Student.StdId, Student.StdName, Student.CourseID, Course.CourseName
FROM Student
LEFT JOIN Course
ON Student.CourseID = Course.CourseID;