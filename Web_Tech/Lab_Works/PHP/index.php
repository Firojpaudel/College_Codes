<?php
// Configuration and setup
$page_title = 'Home - Include and Require Demo';

// Required files (will cause fatal error if not found)
require_once 'includes/config.php';  // This will generate an error since we haven't created it yet

// Included files (will only generate a warning if not found)
include 'includes/header.php';
?>

<h2>Welcome to the Include and Require Demo</h2>

<div class="content">
    <h3>Understanding Include vs Require</h3>
    
    <div class="section">
        <h4>Include Statement</h4>
        <ul>
            <li>Uses the <code>include</code> keyword</li>
            <li>Generates a warning if file is not found</li>
            <li>Continues script execution if file is missing</li>
            <li>Good for optional includes</li>
        </ul>
        
        <?php
        // Example of include with a non-existent file
        include 'includes/sidebar.php';  // This will generate a warning but continue execution
        ?>
    </div>
    
    <div class="section">
        <h4>Require Statement</h4>
        <ul>
            <li>Uses the <code>require</code> keyword</li>
            <li>Generates a fatal error if file is not found</li>
            <li>Stops script execution if file is missing</li>
            <li>Good for mandatory includes</li>
        </ul>
    </div>
    
    <div class="section">
        <h4>Include_once and Require_once</h4>
        <ul>
            <li>Checks if the file has already been included</li>
            <li>Prevents multiple inclusions of the same file</li>
            <li>Useful for preventing duplicate function definitions</li>
        </ul>
        
        <?php
        // Example of include_once
        include_once 'includes/header.php';  // This won't include the file again
        ?>
    </div>
</div>

<?php
include 'includes/footer.php';
?> 