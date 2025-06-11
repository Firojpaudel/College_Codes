<?php
$name = "Alice";
$age = 20;
$height = 5.6;
$fruits = ["apple", "banana", "orange"];
?>
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>PHP Variables Demo</title>
    <style>
        body { font-family: Arial, sans-serif; max-width: 400px; margin: 40px auto; background: #fafafa; padding: 20px; border-radius: 8px; box-shadow: 0 2px 8px #eee; }
        h2 { color: #333; }
        .var { margin-bottom: 10px; }
        pre { background: #f4f4f4; padding: 8px; border-radius: 4px; }
    </style>
</head>
<body>
    <h2>PHP Variables & Print</h2>
    <div class="var">Name: <?php echo $name; ?></div>
    <div class="var">Age: <?php echo $age; ?></div>
    <div class="var">Height: <?php print $height; ?></div>
    <div class="var">Fruits: <pre><?php print_r($fruits); ?></pre></div>
</body>
</html> 