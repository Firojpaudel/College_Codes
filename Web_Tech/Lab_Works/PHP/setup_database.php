<?php
require_once 'includes/config.php';
require_once 'includes/db_connect.php';

// Set up the database and tables
setupDatabase();

// Create a sample user
try {
    $conn = getDB();
    
    // Check if admin user exists
    $stmt = $conn->prepare("SELECT id FROM users WHERE username = 'admin'");
    $stmt->execute();
    
    if ($stmt->rowCount() == 0) {
        // Create admin user
        $password_hash = password_hash('admin123', PASSWORD_DEFAULT);
        $stmt = $conn->prepare("INSERT INTO users (username, password, email) VALUES (?, ?, ?)");
        $stmt->execute(['admin', $password_hash, 'admin@example.com']);
        echo "<p>Admin user created successfully</p>";
        
        // Create some sample posts
        $admin_id = $conn->lastInsertId();
        $sample_posts = [
            [
                'title' => 'First Blog Post',
                'content' => 'This is the content of our first blog post. It demonstrates the CRUD functionality.'
            ],
            [
                'title' => 'Second Blog Post',
                'content' => 'Another example post to show how the blog system works.'
            ]
        ];
        
        $stmt = $conn->prepare("INSERT INTO posts (title, content, user_id) VALUES (?, ?, ?)");
        foreach ($sample_posts as $post) {
            $stmt->execute([$post['title'], $post['content'], $admin_id]);
        }
        echo "<p>Sample posts created successfully</p>";
    } else {
        echo "<p>Admin user already exists</p>";
    }
    
} catch(PDOException $e) {
    die("Error creating sample data: " . $e->getMessage());
}

echo "<p>Database setup completed. You can now proceed to the <a href='crud.php'>CRUD Demo</a></p>";
?> 