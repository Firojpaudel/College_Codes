<?php
// Configuration and setup
$page_title = 'Contact Us';

require_once 'includes/config.php';
include 'includes/header.php';

// Initialize variables
$message = '';
$message_type = '';

// Process form submission
if ($_SERVER['REQUEST_METHOD'] === 'POST') {
    $name = sanitize($_POST['name'] ?? '');
    $email = sanitize($_POST['email'] ?? '');
    $subject = sanitize($_POST['subject'] ?? '');
    $message_text = sanitize($_POST['message'] ?? '');
    
    // Simple validation
    if (empty($name) || empty($email) || empty($subject) || empty($message_text)) {
        $message = 'Please fill in all fields';
        $message_type = 'error';
    } elseif (!filter_var($email, FILTER_VALIDATE_EMAIL)) {
        $message = 'Please enter a valid email address';
        $message_type = 'error';
    } else {
        // In a real application, you would send the email here
        $message = 'Thank you for your message. We will get back to you soon!';
        $message_type = 'success';
    }
}
?>

<h2>Contact Us</h2>

<div class="content">
    <?php if ($message): ?>
        <div class="message <?php echo $message_type; ?>" style="padding: 10px; margin-bottom: 20px; border-radius: 4px; <?php echo $message_type === 'error' ? 'background-color: #ffebee;' : 'background-color: #e8f5e9;'; ?>">
            <?php echo $message; ?>
        </div>
    <?php endif; ?>

    <form method="POST" action="<?php echo htmlspecialchars($_SERVER["PHP_SELF"]); ?>" style="max-width: 600px;">
        <div class="form-group" style="margin-bottom: 15px;">
            <label for="name">Name:</label>
            <input type="text" id="name" name="name" required 
                   style="width: 100%; padding: 8px; margin-top: 5px; border: 1px solid #ddd; border-radius: 4px;">
        </div>

        <div class="form-group" style="margin-bottom: 15px;">
            <label for="email">Email:</label>
            <input type="email" id="email" name="email" required
                   style="width: 100%; padding: 8px; margin-top: 5px; border: 1px solid #ddd; border-radius: 4px;">
        </div>

        <div class="form-group" style="margin-bottom: 15px;">
            <label for="subject">Subject:</label>
            <input type="text" id="subject" name="subject" required
                   style="width: 100%; padding: 8px; margin-top: 5px; border: 1px solid #ddd; border-radius: 4px;">
        </div>

        <div class="form-group" style="margin-bottom: 15px;">
            <label for="message">Message:</label>
            <textarea id="message" name="message" rows="5" required
                      style="width: 100%; padding: 8px; margin-top: 5px; border: 1px solid #ddd; border-radius: 4px;"></textarea>
        </div>

        <button type="submit" style="background-color: #4CAF50; color: white; padding: 10px 20px; border: none; border-radius: 4px; cursor: pointer;">
            Send Message
        </button>
    </form>

    <div class="section" style="margin-top: 30px;">
        <h3>Other Ways to Contact Us</h3>
        <p>You can also reach us through:</p>
        <ul>
            <li>Email: info@example.com</li>
            <li>Phone: (123) 456-7890</li>
            <li>Address: 123 Main St, City, Country</li>
        </ul>
    </div>
</div>

<?php
include 'includes/footer.php';
?> 