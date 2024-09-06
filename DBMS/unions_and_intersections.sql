/*
    Objective: Execute the following SQL statements and display the output tables along with the SQL scripts:
*/
--
CREATE DATABASE SchoolDB;
USE SchoolDB;
---1.	Using CREATE, create a Table with name ‘std1’ and INSERT data into std1:---
CREATE TABLE std1
(
    std_id INT PRIMARY KEY,
    std_name VARCHAR(50),
    fee DECIMAL
);

INSERT INTO std1 (std_id, std_name, fee) 
VALUES 
(1001, 'Ram', 20000),
(1002, 'Hari', 25000),
(1003, 'Sita', 30000),
(1004, 'Laxman', 35000);

---2.	Using CREATE, create a Table with name ‘std2’ and INSERT data into std2:---
Create table std2
(
std_id int primary key,
std_name varchar(30),
fee decimal
);

INSERT INTO std2 (std_id, std_name, fee) 
VALUES 
(1001, 'Ram', 20000),
(2001, 'Shyam', 50000),
(2002, 'Radha', 75000);

---3.	Perform Union and Intersect Operations:---

                ---i.	Union:---
select * from firoj.std1 
union
select * from firoj.std2;

                ---ii.	Intersection:---
select * from firoj.std1 
intersect
select * from firoj.std2;

---4.	Rename Table std1 to Student; displaying content of student table:---
alter table std1

rename to Student;
select * from Student;

 