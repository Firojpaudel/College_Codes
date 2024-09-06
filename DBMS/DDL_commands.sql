/* Objective: To practice and implement data definition language commands and constraints.
    DDL commands: CREATE, ALTER, DROP, TRUNCATE
    Constraints: NOT NULL, NULL, DROP, ENTITY CONSTRAINT (PRIMARY KEY), REFERENTIAL CONSTRAINT (FOREIGN KEY)
*/
CREATE DATABASE SchoolDB;
USE SchoolDB;
---1.	Using CREATE:---
-- Creating tables
CREATE TABLE Students(
    StudentID INT PRIMARY KEY,
    FirstName VARCHAR(50) NOT NULL, 
    LastName VARCHAR(50) NOT NULL, 
    Email VARCHAR(100) UNIQUE, 
    EnrollmentDate DATE
);

CREATE TABLE Courses(
    CourseID INT PRIMARY KEY, 
    CourseName VARCHAR(50) NOT NULL
);

---2.	Using ALTER:---
-- Manipulating the table created
ALTER TABLE Students
-- Adding the column DOB in table Students 
ADD COLUMN DOB DATE;

---3.	Using DROP:---
ALTER TABLE Students
-- Removing Email column from table Students 
DROP COLUMN Email;

---4.	Using TRUNCATE:---
CREATE TABLE Enrollments (
    EnrollmentID INT PRIMARY KEY,
    StudentID INT, 
    CourseID INT, 
    FOREIGN KEY (StudentID) REFERENCES Students(StudentID),
    FOREIGN KEY (CourseID) REFERENCES Courses(CourseID)
);

-- Inserting data into tables
INSERT INTO Students (StudentID, FirstName, LastName, EnrollmentDate, DOB) 
VALUES 
(1, 'John', 'Doe', '2020-09-01', '2002-01-15'),
(2, 'Jane', 'Smith', '2021-09-01', '2001-05-21');

INSERT INTO Courses (CourseID, CourseName) 
VALUES 
(101, 'Mathematics'),
(102, 'Physics');

INSERT INTO Enrollments (EnrollmentID, StudentID, CourseID)
VALUES 
(1, 1, 101),
(2, 2, 102);

-- Performing queries to show outputs
SELECT * FROM Students;

SELECT * FROM Courses;

SELECT * FROM Enrollments;

-- Truncating all filled values inside a table 
TRUNCATE TABLE Students; 