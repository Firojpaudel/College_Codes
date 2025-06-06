<?php
// Basic PHP Variables and Print Statements Demo

// 1. Variable Declaration and Basic Types
$string_var = "Hello World";
$integer_var = 42;
$float_var = 3.14;
$boolean_var = true;
$null_var = null;
$array_var = ["apple", "banana", "orange"];
$associative_array = [
    "name" => "John Doe",
    "age" => 25,
    "city" => "New York"
];

// 2. Different Ways to Print
?>
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>PHP Variables and Print Statements</title>
    <style>
        body {
            font-family: Arial, sans-serif;
            max-width: 800px;
            margin: 20px auto;
            padding: 20px;
        }
        .section {
            margin: 20px 0;
            padding: 15px;
            border: 1px solid #ddd;
            border-radius: 5px;
        }
        code {
            background: #f4f4f4;
            padding: 2px 5px;
            border-radius: 3px;
        }
    </style>
</head>
<body>
    <h1>PHP Variables and Print Statements Demo</h1>

    <div class="section">
        <h2>1. Using echo</h2>
        <?php
        echo "<p>String variable: $string_var</p>";
        echo '<p>Integer variable: ' . $integer_var . '</p>';
        echo "<p>Float variable: $float_var</p>";
        echo "<p>Boolean variable: " . ($boolean_var ? 'true' : 'false') . "</p>";
        echo "<p>Null variable: " . ($null_var ?? 'null') . "</p>";
        ?>
    </div>

    <div class="section">
        <h2>2. Using print</h2>
        <?php
        print "<p>Using print statement: $string_var</p>";
        ?>
    </div>

    <div class="section">
        <h2>3. Using print_r for Arrays</h2>
        <pre><?php print_r($array_var); ?></pre>
        <pre><?php print_r($associative_array); ?></pre>
    </div>

    <div class="section">
        <h2>4. Using var_dump (Detailed Information)</h2>
        <pre><?php var_dump($string_var); ?></pre>
        <pre><?php var_dump($array_var); ?></pre>
    </div>

    <div class="section">
        <h2>5. String Concatenation</h2>
        <?php
        $first_name = "John";
        $last_name = "Doe";
        
        // Using dot operator
        echo "<p>Using dot operator: " . $first_name . " " . $last_name . "</p>";
        
        // Using double quotes
        echo "<p>Using double quotes: $first_name $last_name</p>";
        ?>
    </div>

    <div class="section">
        <h2>6. Variable Variables</h2>
        <?php
        $animal = "dog";
        $$animal = "Buddy";  // Creates variable $dog
        echo "<p>Animal: $animal</p>";
        echo "<p>Pet name: $dog</p>";
        ?>
    </div>

    <div class="section">
        <h2>7. Constants</h2>
        <?php
        define("PI", 3.14159);
        const MAX_USERS = 100;
        echo "<p>Value of PI: " . PI . "</p>";
        echo "<p>Maximum users: " . MAX_USERS . "</p>";
        ?>
    </div>
</body>
</html> 