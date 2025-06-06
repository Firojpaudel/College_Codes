<?php
// Configuration and setup
$page_title = 'About Us';

require_once 'includes/config.php';
include 'includes/header.php';
?>

<h2>About Us</h2>

<div class="content">
    <p>This is a demonstration website showing how to use PHP include and require statements to create a modular website structure.</p>
    
    <div class="section">
        <h3>Benefits of Include/Require</h3>
        <ul>
            <li>Code reusability</li>
            <li>Easier maintenance</li>
            <li>Better organization</li>
            <li>Consistent layout across pages</li>
        </ul>
    </div>
    
    <div class="section">
        <h3>File Structure</h3>
        <pre>
project/
├── includes/
│   ├── config.php
│   ├── header.php
│   └── footer.php
├── index.php
├── about.php
└── contact.php
        </pre>
    </div>
</div>

<?php
include 'includes/footer.php';
?> 