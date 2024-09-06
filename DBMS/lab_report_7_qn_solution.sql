/*
Objective: Consider a banking database with three labels and primary key underlined as given below:
Customer (CustomerID , CustomerName, Address, Phone, Email) 
Borrows (CustomerID, LoanNumber ) 
Loan ( LoanNumber , LoanType, Amount )
Write both relational algebra and SQL queries: 
a.	To display name of all customers who live in “Lalitpur” in ascending order of name. 
b.	To count total number of customers having loan at the bank. 
c.	To find name of those customers who have loan amount greater than or equal to 500000. 
d.	To find average loan amount of each account type.
*/

CREATE DATABASE BankingDB;
USE BankingDB;

CREATE TABLE Customer (
    CustomerID INT PRIMARY KEY,
    CustomerName VARCHAR(100),
    Address VARCHAR(255),
    Phone VARCHAR(20),
    Email VARCHAR(100)
);

CREATE TABLE Loan (
    LoanNumber INT PRIMARY KEY,
    LoanType VARCHAR(100),
    Amount DECIMAL(15, 2)
);

CREATE TABLE Borrows (
    CustomerID INT,
    LoanNumber INT,
    FOREIGN KEY (CustomerID) REFERENCES Customer(CustomerID),
    FOREIGN KEY (LoanNumber) REFERENCES Loan(LoanNumber)
);

-- Insert sample data into Customer
INSERT INTO Customer (CustomerID, CustomerName, Address, Phone, Email) VALUES
(1, 'Amit Sharma', 'Lalitpur', '9800000000', 'amit@example.com'),
(2, 'Sita Devi', 'Kathmandu', '9810000000', 'sita@example.com'),
(3, 'Ram Bahadur', 'Lalitpur', '9820000000', 'ram@example.com'),
(4, 'Gita Rai', 'Bhaktapur', '9830000000', 'gita@example.com'),
(5, 'Hari Prasad', 'Lalitpur', '9840000000', 'hari@example.com');

-- Insert sample data into Loan
INSERT INTO Loan (LoanNumber, LoanType, Amount) VALUES
(101, 'Personal Loan', 300000.00),
(102, 'Home Loan', 700000.00),
(103, 'Auto Loan', 450000.00),
(104, 'Education Loan', 600000.00),
(105, 'Business Loan', 800000.00);

-- Insert sample data into Borrows
INSERT INTO Borrows (CustomerID, LoanNumber) VALUES
(1, 101),
(1, 102),
(3, 103),
(3, 104),
(5, 105);

-- 1. To display names of all customers who live in “Lalitpur” in ascending order of name.
SELECT CustomerName
FROM Customer
WHERE Address = 'Lalitpur'
ORDER BY CustomerName ASC;

-- 2. To count the total number of customers having a loan at the bank.
SELECT COUNT(DISTINCT CustomerID) AS TotalCustomersWithLoan
FROM Borrows;

-- 3. To find names of those customers who have loan amounts greater than or equal to 500000
SELECT DISTINCT C.CustomerName
FROM Customer C
JOIN Borrows B ON C.CustomerID = B.CustomerID
JOIN Loan L ON B.LoanNumber = L.LoanNumber
WHERE L.Amount >= 500000;

-- 4. To find the average loan amount of each loan type.
SELECT LoanType, AVG(Amount) AS AverageAmount
FROM Loan
GROUP BY LoanType;