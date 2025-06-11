<?php
// Initialize variables to store form data
$get_name = $_GET['name'] ?? '';
$get_email = $_GET['email'] ?? '';
$post_name = $_POST['name'] ?? '';
$post_email = $_POST['email'] ?? '';
$post_message = $_POST['message'] ?? '';

// Function to sanitize input
function sanitize_input($data) {
    $data = trim($data);
    $data = stripslashes($data);
    $data = htmlspecialchars($data);
    return $data;
}

// Process POST form
$post_submitted = false;
if ($_SERVER["REQUEST_METHOD"] == "POST") {
    $post_submitted = true;
    $post_name = sanitize_input($post_name);
    $post_email = sanitize_input($post_email);
    $post_message = sanitize_input($post_message);
}
?>
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>PHP Form Handling - Minimal</title>
</head>
<body>
    <h2>GET Method Form</h2>
    <form method="GET" action="<?php echo htmlspecialchars($_SERVER["PHP_SELF"]); ?>">
        <label>Name: <input type="text" name="name" value="<?php echo $get_name; ?>" required></label><br>
        <label>Email: <input type="email" name="email" value="<?php echo $get_email; ?>" required></label><br>
        <button type="submit">Submit (GET)</button>
    </form>
    <?php if (!empty($get_name) || !empty($get_email)): ?>
        <div>
            <strong>GET Results:</strong><br>
            Name: <?php echo $get_name; ?><br>
            Email: <?php echo $get_email; ?><br>
            URL Parameters: <?php echo $_SERVER['QUERY_STRING']; ?><br>
        </div>
    <?php endif; ?>
    <hr>
    <h2>POST Method Form</h2>
    <form method="POST" action="<?php echo htmlspecialchars($_SERVER["PHP_SELF"]); ?>">
        <label>Name: <input type="text" name="name" value="<?php echo $post_name; ?>" required></label><br>
        <label>Email: <input type="email" name="email" value="<?php echo $post_email; ?>" required></label><br>
        <label>Message:<br><textarea name="message" rows="3" required><?php echo $post_message; ?></textarea></label><br>
        <button type="submit">Submit (POST)</button>
    </form>
    <?php if ($post_submitted): ?>
        <div>
            <strong>POST Results:</strong><br>
            Name: <?php echo $post_name; ?><br>
            Email: <?php echo $post_email; ?><br>
            Message: <?php echo $post_message; ?><br>
        </div>
    <?php endif; ?>
</body>
</html> 