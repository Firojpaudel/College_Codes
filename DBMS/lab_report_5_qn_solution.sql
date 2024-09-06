/*
Objective:  Consider the following database and write SQL as given: 
Customer (Cno, Cname, Caddress, Ccontact)
Purchase (Cno, Pid) Product (Pid, Pname, price, quantity)

a.	Find the names of all products having price 1000. 
b.	Find the name of those customers who purchased Dell Laptop.
c.	Find the total number of products purchased by customer ‘Ram’.
d.	Increase price of all products by 5% 
e. Find total price of Apple Mobiles.
*/
CREATE DATABASE SalesDB;
USE SalesDB;

CREATE TABLE Customer (
    Cno INT PRIMARY KEY,
    Cname VARCHAR(100),
    Caddress VARCHAR(255),
    Ccontact VARCHAR(20)
);
CREATE TABLE Product (
    Pid INT PRIMARY KEY,
    Pname VARCHAR(100),
    price DECIMAL(10, 2),
    quantity INT
);

CREATE TABLE Purchase (
    Cno INT,
    Pid INT,
    FOREIGN KEY (Cno) REFERENCES Customer(Cno),
    FOREIGN KEY (Pid) REFERENCES Product(Pid)
);
-- Inserting sample data into Customer
INSERT INTO Customer (Cno, Cname, Caddress, Ccontact) VALUES
(1, 'Ram', 'Kathmandu', '9800000000'),
(2, 'Sita', 'Pokhara', '9810000000'),
(3, 'Hari', 'Biratnagar', '9820000000');

-- Inserting sample data into Product
INSERT INTO Product (Pid, Pname, price, quantity) VALUES
(101, 'Dell Laptop', 1000.00, 10),
(102, 'Apple Mobile', 1200.00, 15),
(103, 'Samsung Tablet', 500.00, 20);

-- Inserting sample data into Purchase
INSERT INTO Purchase (Cno, Pid) VALUES
(1, 101),
(1, 102),
(2, 103),
(3, 101),
(3, 102);

-- a. Find the names of all products having price 1000.
SELECT Pname
FROM Product
WHERE price = 1000;

-- b. Find the name of those customers who purchased Dell Laptop.
SELECT C.Cname
FROM Customer C
JOIN Purchase P ON C.Cno = P.Cno
JOIN Product Pr ON P.Pid = Pr.Pid
WHERE Pr.Pname = 'Dell Laptop';

-- c. Find the total number of products purchased by customer ‘Ram’.
SELECT COUNT(P.Pid) AS TotalProducts
FROM Purchase P
JOIN Customer C ON P.Cno = C.Cno
WHERE C.Cname = 'Ram';

-- d. Increase price of all products by 5%.
UPDATE Product
SET price = price * 1.05;
WHERE Pid IS NOT NULL;
-- e. Find total price of Apple Mobiles.
SELECT SUM(price * quantity) AS TotalPrice
FROM Product
WHERE Pname = 'Apple Mobile';
