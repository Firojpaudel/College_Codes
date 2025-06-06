<?php
// Database configuration (example)
define('DB_HOST', 'localhost');
define('DB_USER', 'root');
define('DB_PASS', '');
define('DB_NAME', 'mywebsite');

// Site configuration
define('SITE_NAME', 'My Website');
define('SITE_URL', 'http://localhost/mywebsite');

// Error reporting
error_reporting(E_ALL);
ini_set('display_errors', 1);

// Time zone
date_default_timezone_set('UTC');

// Session start
session_start();

// Utility functions
function sanitize($str) {
    return htmlspecialchars(trim($str), ENT_QUOTES, 'UTF-8');
}

function redirect($url) {
    header("Location: $url");
    exit();
}

// Global variables
$site_name = SITE_NAME;
$current_year = date('Y');
?> 