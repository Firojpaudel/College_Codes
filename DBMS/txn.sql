/* 
    Consider a banking system with the following operations:

Debit an amount from a customer's account (Account A).
Credit the same amount to another customer's account (Account B).
Write a SQL script to implement this transaction using the following table structure:


CREATE TABLE Accounts (
    AccountID INT PRIMARY KEY,
    Balance DECIMAL(10, 2) NOT NULL
);

Assume the following conditions:

- Account balances should never become negative.
- If any step in the transaction fails (e.g., insufficient balance in Account A), the entire transaction should roll back to maintain data consistency.
Tasks:

Write an SQL script to perform the transaction with proper use of BEGIN TRANSACTION, COMMIT, and ROLLBACK.
*/
-- Step 1: Create a new database
CREATE DATABASE txn;

-- Step 2: Use the database
USE txn;

-- Step 3: Create the Accounts table
CREATE TABLE Accounts (
    AccountID INT PRIMARY KEY,
    Balance DECIMAL(10, 2) NOT NULL
);

-- Step 4: Insert sample data into the Accounts table
INSERT INTO Accounts (AccountID, Balance) 
VALUES (1, 500.00), (2, 300.00);

-- Step 5: Create the stored procedure
DELIMITER //

CREATE PROCEDURE TransferAmount(
    IN fromAccount INT,
    IN toAccount INT,
    IN transferAmount DECIMAL(10, 2)
)
BEGIN
    DECLARE balanceA DECIMAL(10, 2);

    -- Start the transaction
    START TRANSACTION;

    -- Step 6: Check the balance of the source account
    SELECT Balance INTO balanceA
    FROM Accounts
    WHERE AccountID = fromAccount;

    -- Step 7: Perform the transaction if balance is sufficient
    IF balanceA >= transferAmount THEN
        -- Debit from source account
        UPDATE Accounts
        SET Balance = Balance - transferAmount
        WHERE AccountID = fromAccount;

        -- Credit to target account
        UPDATE Accounts
        SET Balance = Balance + transferAmount
        WHERE AccountID = toAccount;

        -- Commit the transaction
        COMMIT;
        SELECT 'Transaction completed successfully.' AS Message;
    ELSE
        -- Rollback the transaction if insufficient balance
        ROLLBACK;
        SELECT 'Transaction failed: Insufficient balance in the source account.' AS Message;
    END IF;
END;
//

DELIMITER ;

-- Step 6: Call the procedure to test the transaction
CALL TransferAmount(1, 2, 200.00);
