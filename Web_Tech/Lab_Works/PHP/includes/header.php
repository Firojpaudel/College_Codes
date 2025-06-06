<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title><?php echo $page_title ?? 'My Website'; ?></title>
    <style>
        body {
            font-family: Arial, sans-serif;
            margin: 0;
            padding: 0;
            line-height: 1.6;
        }
        .header {
            background-color: #333;
            color: white;
            padding: 1rem;
        }
        .nav {
            background-color: #f4f4f4;
            padding: 1rem;
        }
        .nav a {
            color: #333;
            text-decoration: none;
            padding: 0.5rem 1rem;
            margin-right: 1rem;
        }
        .nav a:hover {
            background-color: #ddd;
            border-radius: 4px;
        }
        .container {
            max-width: 1200px;
            margin: 0 auto;
            padding: 20px;
        }
    </style>
</head>
<body>
    <div class="header">
        <div class="container">
            <h1><?php echo $page_title ?? 'My Website'; ?></h1>
        </div>
    </div>
    <div class="nav">
        <div class="container">
            <a href="index.php">Home</a>
            <a href="about.php">About</a>
            <a href="contact.php">Contact</a>
        </div>
    </div>
    <div class="container"> 