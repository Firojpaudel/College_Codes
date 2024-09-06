/*
Objective:  Write SQL Query to perform cartesian product between the tables.
*/
CREATE DATABASE lab_4;
USE lab_4;

CREATE TABLE Students (
    std_id INT PRIMARY KEY,
    student_name VARCHAR(50),
    streamm VARCHAR(50)
);

CREATE TABLE Courses (
    course_id INT PRIMARY KEY,
    course_name VARCHAR(50)
);

INSERT INTO Students (std_id, student_name, streamm)
VALUES
(1, 'Student A', 'Science'),
(2, 'Student B', 'Humanities'),
(3, 'Student C', 'Science'),
(4, 'Student D', 'Humanities');

INSERT INTO Courses (course_id, course_name)
VALUES
(1, 'NM'),
(2, 'CA'),
(3, 'DSA'),
(4, 'History'),
(5, 'Sociology'),
(6, 'Psychology');
CREATE TABLE StudentCourses (
    std_id INT,
    course_id INT,
    semester INT,
    PRIMARY KEY (std_id, course_id, semester),
    FOREIGN KEY (std_id) REFERENCES Students(std_id),
    FOREIGN KEY (course_id) REFERENCES Courses(course_id)
);
CREATE TABLE StudentSemester (
    std_id INT,
    semester INT,
    PRIMARY KEY (std_id, semester),
    FOREIGN KEY (std_id) REFERENCES Students(std_id)
);

INSERT INTO StudentSemester (std_id, semester)
VALUES
(1, 3),
(2, 3),
(3, 2),
(4, 1);

INSERT INTO StudentCourses (std_id, course_id, semester)
SELECT s.std_id, c.course_id, ss.semester
FROM Students s
JOIN StudentSemester ss ON s.std_id = ss.std_id
JOIN Courses c ON (
    (s.streamm = 'Science' AND c.course_name IN ('NM', 'CA', 'DSA')) OR
    (s.streamm = 'Humanities' AND c.course_name IN ('History', 'Sociology', 'Psychology'))
);

CREATE VIEW StudentCourseDetails AS
SELECT 
    s.std_id,
    s.student_name,
    sc.semester,
    s.streamm,
    c.course_name
FROM 
    Students s
JOIN 
    StudentCourses sc ON s.std_id = sc.std_id
JOIN 
    Courses c ON sc.course_id = c.course_id;

SELECT * FROM StudentCourseDetails;
