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
    <title>PHP Form Handling - GET and POST Methods</title>
    <style>
        body {
            font-family: Arial, sans-serif;
            max-width: 800px;
            margin: 20px auto;
            padding: 20px;
        }
        .form-section {
            margin: 30px 0;
            padding: 20px;
            border: 1px solid #ddd;
            border-radius: 5px;
        }
        .form-group {
            margin-bottom: 15px;
        }
        label {
            display: block;
            margin-bottom: 5px;
        }
        input[type="text"],
        input[type="email"],
        textarea {
            width: 100%;
            padding: 8px;
            margin-bottom: 10px;
            border: 1px solid #ddd;
            border-radius: 4px;
        }
        button {
            background-color: #4CAF50;
            color: white;
            padding: 10px 20px;
            border: none;
            border-radius: 4px;
            cursor: pointer;
        }
        button:hover {
            background-color: #45a049;
        }
        .result {
            margin-top: 20px;
            padding: 15px;
            background-color: #f9f9f9;
            border-radius: 4px;
        }
    </style>
</head>
<body>
    <h1>PHP Form Handling Demo</h1>

    <!-- GET Method Form -->
    <div class="form-section">
        <h2>GET Method Form</h2>
        <p>GET method sends form data through URL parameters. Good for non-sensitive data and bookmarkable pages.</p>
        
        <form method="GET" action="<?php echo htmlspecialchars($_SERVER["PHP_SELF"]); ?>">
            <div class="form-group">
                <label for="get-name">Name:</label>
                <input type="text" id="get-name" name="name" value="<?php echo $get_name; ?>" required>
            </div>
            
            <div class="form-group">
                <label for="get-email">Email:</label>
                <input type="email" id="get-email" name="email" value="<?php echo $get_email; ?>" required>
            </div>
            
            <button type="submit">Submit (GET)</button>
        </form>

        <?php if (!empty($get_name) || !empty($get_email)): ?>
            <div class="result">
                <h3>GET Results:</h3>
                <p>Name: <?php echo $get_name; ?></p>
                <p>Email: <?php echo $get_email; ?></p>
                <p>URL Parameters: <?php echo $_SERVER['QUERY_STRING']; ?></p>
            </div>
        <?php endif; ?>
    </div>

    <!-- POST Method Form -->
    <div class="form-section">
        <h2>POST Method Form</h2>
        <p>POST method sends form data in the request body. Better for sensitive data and larger amounts of data.</p>
        
        <form method="POST" action="<?php echo htmlspecialchars($_SERVER["PHP_SELF"]); ?>">
            <div class="form-group">
                <label for="post-name">Name:</label>
                <input type="text" id="post-name" name="name" value="<?php echo $post_name; ?>" required>
            </div>
            
            <div class="form-group">
                <label for="post-email">Email:</label>
                <input type="email" id="post-email" name="email" value="<?php echo $post_email; ?>" required>
            </div>
            
            <div class="form-group">
                <label for="post-message">Message:</label>
                <textarea id="post-message" name="message" rows="4" required><?php echo $post_message; ?></textarea>
            </div>
            
            <button type="submit">Submit (POST)</button>
        </form>

        <?php if ($post_submitted): ?>
            <div class="result">
                <h3>POST Results:</h3>
                <p>Name: <?php echo $post_name; ?></p>
                <p>Email: <?php echo $post_email; ?></p>
                <p>Message: <?php echo $post_message; ?></p>
            </div>
        <?php endif; ?>
    </div>

    <!-- Comparison Section -->
    <div class="form-section">
        <h2>GET vs POST Comparison</h2>
        <table style="width: 100%; border-collapse: collapse;">
            <tr>
                <th style="border: 1px solid #ddd; padding: 8px; text-align: left;">Feature</th>
                <th style="border: 1px solid #ddd; padding: 8px; text-align: left;">GET</th>
                <th style="border: 1px solid #ddd; padding: 8px; text-align: left;">POST</th>
            </tr>
            <tr>
                <td style="border: 1px solid #ddd; padding: 8px;">Visibility</td>
                <td style="border: 1px solid #ddd; padding: 8px;">Data visible in URL</td>
                <td style="border: 1px solid #ddd; padding: 8px;">Data not visible in URL</td>
            </tr>
            <tr>
                <td style="border: 1px solid #ddd; padding: 8px;">Bookmarking</td>
                <td style="border: 1px solid #ddd; padding: 8px;">Can be bookmarked</td>
                <td style="border: 1px solid #ddd; padding: 8px;">Cannot be bookmarked</td>
            </tr>
            <tr>
                <td style="border: 1px solid #ddd; padding: 8px;">Data Length</td>
                <td style="border: 1px solid #ddd; padding: 8px;">Limited by URL length</td>
                <td style="border: 1px solid #ddd; padding: 8px;">No length limitation</td>
            </tr>
            <tr>
                <td style="border: 1px solid #ddd; padding: 8px;">Security</td>
                <td style="border: 1px solid #ddd; padding: 8px;">Less secure</td>
                <td style="border: 1px solid #ddd; padding: 8px;">More secure</td>
            </tr>
        </table>
    </div>
</body>
</html> 