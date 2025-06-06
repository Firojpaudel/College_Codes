<?php
require_once 'includes/config.php';
require_once 'includes/db_connect.php';

session_start();

// Check if user is already logged in
if (isset($_SESSION['user_id'])) {
    header("Location: dashboard.php");
    exit();
}

$message = '';
$message_type = '';

// Handle login form submission
if ($_SERVER['REQUEST_METHOD'] === 'POST') {
    $username = $_POST['username'] ?? '';
    $password = $_POST['password'] ?? '';
    
    if (empty($username) || empty($password)) {
        $message = "Please fill in all fields";
        $message_type = "error";
    } else {
        try {
            $conn = getDB();
            $stmt = $conn->prepare("SELECT id, username, password FROM users WHERE username = ?");
            $stmt->execute([$username]);
            $user = $stmt->fetch(PDO::FETCH_ASSOC);
            
            if ($user && password_verify($password, $user['password'])) {
                // Set session variables
                $_SESSION['user_id'] = $user['id'];
                $_SESSION['username'] = $user['username'];
                
                // Redirect to dashboard
                header("Location: dashboard.php");
                exit();
            } else {
                $message = "Invalid username or password";
                $message_type = "error";
            }
        } catch(PDOException $e) {
            $message = "Error: " . $e->getMessage();
            $message_type = "error";
        }
    }
}

$page_title = "Login";
include 'includes/header.php';
?>

<div class="container">
    <div class="login-form" style="max-width: 400px; margin: 40px auto; padding: 20px; border: 1px solid #ddd; border-radius: 4px;">
        <h2>Login</h2>
        
        <?php if ($message): ?>
            <div class="alert <?php echo $message_type; ?>" style="padding: 10px; margin: 10px 0; border-radius: 4px; <?php echo $message_type === 'error' ? 'background-color: #ffebee;' : 'background-color: #e8f5e9;'; ?>">
                <?php echo $message; ?>
            </div>
        <?php endif; ?>
        
        <form method="POST" action="<?php echo htmlspecialchars($_SERVER["PHP_SELF"]); ?>">
            <div class="form-group" style="margin-bottom: 15px;">
                <label for="username">Username:</label>
                <input type="text" id="username" name="username" required
                       style="width: 100%; padding: 8px; margin-top: 5px; border: 1px solid #ddd; border-radius: 4px;">
            </div>
            
            <div class="form-group" style="margin-bottom: 15px;">
                <label for="password">Password:</label>
                <input type="password" id="password" name="password" required
                       style="width: 100%; padding: 8px; margin-top: 5px; border: 1px solid #ddd; border-radius: 4px;">
            </div>
            
            <button type="submit" style="width: 100%; background-color: #4CAF50; color: white; padding: 10px; border: none; border-radius: 4px; cursor: pointer;">
                Login
            </button>
        </form>
        
        <p style="margin-top: 20px; text-align: center;">
            Default credentials:<br>
            Username: admin<br>
            Password: admin123
        </p>
    </div>
</div>

<?php include 'includes/footer.php'; ?> 