<?php
session_start();

// Check if user is not logged in
if (!isset($_SESSION['user_id'])) {
    header("Location: login.php");
    exit();
}
?>
<!DOCTYPE html>
<html>
<head>
    <title>Dashboard</title>
</head>
<body>
    <h2>Welcome, <?php echo htmlspecialchars($_SESSION['username']); ?>!</h2>
    
    <div>
        <p>This is your dashboard. You are successfully logged in.</p>
        <p>Current time: <?php echo date('Y-m-d H:i:s'); ?></p>
    </div>
    
    <p><a href="logout.php">Logout</a></p>
</body>
</html> 