<?php
try {
    // First connect without database selected
    $conn = new PDO("mysql:host=localhost", "root", "");
    
    // Create database if it doesn't exist
    $conn->exec("CREATE DATABASE IF NOT EXISTS blog");
    $conn->exec("USE blog");
    
    // Create posts table if it doesn't exist
    $conn->exec("CREATE TABLE IF NOT EXISTS posts (
        id INT AUTO_INCREMENT PRIMARY KEY,
        title VARCHAR(255) NOT NULL,
        content TEXT NOT NULL,
        created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP
    )");
} catch(PDOException $e) {
    die("Connection failed: " . $e->getMessage());
}

// Create
if (isset($_POST['create'])) {
    $sql = "INSERT INTO posts (title, content) VALUES (?, ?)";
    $stmt = $conn->prepare($sql);
    $stmt->execute([$_POST['title'], $_POST['content']]);
    header("Location: " . $_SERVER['PHP_SELF']);
    exit();
}

// Delete
if (isset($_GET['delete'])) {
    $sql = "DELETE FROM posts WHERE id = ?";
    $stmt = $conn->prepare($sql);
    $stmt->execute([$_GET['delete']]);
    header("Location: " . $_SERVER['PHP_SELF']);
    exit();
}

// Update
if (isset($_POST['update'])) {
    $sql = "UPDATE posts SET title = ?, content = ? WHERE id = ?";
    $stmt = $conn->prepare($sql);
    $stmt->execute([$_POST['title'], $_POST['content'], $_POST['id']]);
    header("Location: " . $_SERVER['PHP_SELF']);
    exit();
}

// Read
$edit = null;
if (isset($_GET['edit'])) {
    $stmt = $conn->prepare("SELECT * FROM posts WHERE id = ?");
    $stmt->execute([$_GET['edit']]);
    $edit = $stmt->fetch();
}

$posts = $conn->query("SELECT * FROM posts ORDER BY created_at DESC")->fetchAll();
?>

<!DOCTYPE html>
<html>
<head>
    <title>Simple Blog</title>
    <style>
        body {
            font-family: Arial, sans-serif;
            max-width: 800px;
            margin: 20px auto;
            padding: 0 20px;
            line-height: 1.6;
        }
        form {
            background: #f5f5f5;
            padding: 20px;
            border-radius: 8px;
            margin-bottom: 30px;
        }
        input, textarea {
            width: 100%;
            padding: 8px;
            margin-bottom: 10px;
            border: 1px solid #ddd;
            border-radius: 4px;
            box-sizing: border-box;
        }
        textarea {
            min-height: 100px;
        }
        button {
            background: #4CAF50;
            color: white;
            padding: 10px 20px;
            border: none;
            border-radius: 4px;
            cursor: pointer;
        }
        button:hover {
            background: #45a049;
        }
        .post {
            background: white;
            padding: 20px;
            margin-bottom: 20px;
            border: 1px solid #ddd;
            border-radius: 8px;
        }
        .post h3 {
            margin-top: 0;
            color: #333;
        }
        .actions {
            margin-top: 15px;
        }
        .actions a {
            text-decoration: none;
            padding: 5px 10px;
            margin-right: 10px;
            border-radius: 3px;
            font-size: 14px;
        }
        .edit-link {
            background: #2196F3;
            color: white;
        }
        .delete-link {
            background: #f44336;
            color: white;
        }
    </style>
</head>
<body>
    <h1>Simple Blog</h1>
    
    <!-- Create/Edit Form -->
    <form method="post">
        <?php if ($edit): ?>
            <input type="hidden" name="id" value="<?= $edit['id'] ?>">
        <?php endif; ?>
        <input name="title" value="<?= $edit ? htmlspecialchars($edit['title']) : '' ?>" placeholder="Enter title" required>
        <textarea name="content" placeholder="Enter content" required><?= $edit ? htmlspecialchars($edit['content']) : '' ?></textarea>
        <button name="<?= $edit ? 'update' : 'create' ?>"><?= $edit ? 'Update Post' : 'Create Post' ?></button>
        <?php if ($edit): ?>
            <a href="<?= $_SERVER['PHP_SELF'] ?>" style="margin-left: 10px;">Cancel</a>
        <?php endif; ?>
    </form>

    <!-- List Posts -->
    <?php foreach ($posts as $post): ?>
        <div class="post">
            <h3><?= htmlspecialchars($post['title']) ?></h3>
            <p><?= nl2br(htmlspecialchars($post['content'])) ?></p>
            <div class="actions">
                <a href="?edit=<?= $post['id'] ?>" class="edit-link">Edit</a>
                <a href="?delete=<?= $post['id'] ?>" class="delete-link" onclick="return confirm('Delete this post?')">Delete</a>
            </div>
        </div>
    <?php endforeach; ?>
</body>
</html> 