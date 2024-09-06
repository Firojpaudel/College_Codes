/*
Objective:  Retrive the TName, SName, SPhone for “ABC” school using SQL from given relation    as below:
TEACHER (TID, TName, TAddress, TQualification) 
SCHOOL (SID, SName, SAddress, SPhone)
SCHOOL_TEACHER (SID, TID, No_of Period)
*/

CREATE TABLE TEACHER (
    TID INT PRIMARY KEY,
    TName VARCHAR(100),
    TAddress VARCHAR(255),
    TQualification VARCHAR(100)
);

CREATE TABLE SCHOOL (
    SID INT PRIMARY KEY,
    SName VARCHAR(100),
    SAddress VARCHAR(255),
    SPhone VARCHAR(20)
);

CREATE TABLE SCHOOL_TEACHER (
    SID INT,
    TID INT,
    No_of_Period INT,
    FOREIGN KEY (SID) REFERENCES SCHOOL(SID),
    FOREIGN KEY (TID) REFERENCES TEACHER(TID)
);

-- Insert sample data into TEACHER
INSERT INTO TEACHER (TID, TName, TAddress, TQualification) VALUES
(1, 'John Doe', '123 Elm Street', 'MSc in Mathematics'),
(2, 'Jane Smith', '456 Oak Avenue', 'MSc in Physics'),
(3, 'Emily Johnson', '789 Pine Road', 'MSc in Chemistry'),
(4, 'Michael Brown', '101 Maple Lane', 'MSc in Biology'),
(5, 'Sarah Davis', '202 Birch Blvd', 'MSc in Computer Science');

-- Insert sample data into SCHOOL
INSERT INTO SCHOOL (SID, SName, SAddress, SPhone) VALUES
(1, 'ABC School', '12 School St', '555-1234'),
(2, 'XYZ Academy', '34 Academy Rd', '555-5678'),
(3, 'DEF Institute', '56 Institute Ave', '555-8765'),
(4, 'GHI School', '78 School Blvd', '555-4321');

-- Insert sample data into SCHOOL_TEACHER
INSERT INTO SCHOOL_TEACHER (SID, TID, No_of_Period) VALUES
(1, 1, 10),
(1, 2, 15),
(1, 3, 20),
(2, 4, 12),
(2, 5, 18),
(3, 1, 14),
(3, 3, 16),
(4, 2, 13);

SELECT T.TName, S.SName, S.SPhone
FROM TEACHER T
JOIN SCHOOL_TEACHER ST ON T.TID = ST.TID
JOIN SCHOOL S ON ST.SID = S.SID
WHERE S.SName = 'ABC School';
