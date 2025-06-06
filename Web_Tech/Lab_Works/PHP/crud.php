<?php
require_once 'includes/config.php';
require_once 'includes/db_connect.php';

session_start();

// Initialize variables
$message = '';
$message_type = '';
$posts = [];
$editing_post = null;

// Handle form submissions
if ($_SERVER['REQUEST_METHOD'] === 'POST') {
    $conn = getDB();
    
    // Create new post
    if (isset($_POST['action']) && $_POST['action'] === 'create') {
        try {
            $stmt = $conn->prepare("INSERT INTO posts (title, content, user_id) VALUES (?, ?, 1)");
            $stmt->execute([
                $_POST['title'],
                $_POST['content']
            ]);
            $message = "Post created successfully!";
            $message_type = "success";
        } catch(PDOException $e) {
            $message = "Error creating post: " . $e->getMessage();
            $message_type = "error";
        }
    }
    
    // Update existing post
    if (isset($_POST['action']) && $_POST['action'] === 'update') {
        try {
            $stmt = $conn->prepare("UPDATE posts SET title = ?, content = ? WHERE id = ?");
            $stmt->execute([
                $_POST['title'],
                $_POST['content'],
                $_POST['post_id']
            ]);
            $message = "Post updated successfully!";
            $message_type = "success";
        } catch(PDOException $e) {
            $message = "Error updating post: " . $e->getMessage();
            $message_type = "error";
        }
    }
    
    // Delete post
    if (isset($_POST['action']) && $_POST['action'] === 'delete') {
        try {
            $stmt = $conn->prepare("DELETE FROM posts WHERE id = ?");
            $stmt->execute([$_POST['post_id']]);
            $message = "Post deleted successfully!";
            $message_type = "success";
        } catch(PDOException $e) {
            $message = "Error deleting post: " . $e->getMessage();
            $message_type = "error";
        }
    }
}

// Handle edit request
if (isset($_GET['edit'])) {
    try {
        $conn = getDB();
        $stmt = $conn->prepare("SELECT * FROM posts WHERE id = ?");
        $stmt->execute([$_GET['edit']]);
        $editing_post = $stmt->fetch(PDO::FETCH_ASSOC);
    } catch(PDOException $e) {
        $message = "Error fetching post: " . $e->getMessage();
        $message_type = "error";
    }
}

// Fetch all posts
try {
    $conn = getDB();
    $stmt = $conn->query("SELECT * FROM posts ORDER BY created_at DESC");
    $posts = $stmt->fetchAll(PDO::FETCH_ASSOC);
} catch(PDOException $e) {
    $message = "Error fetching posts: " . $e->getMessage();
    $message_type = "error";
}

$page_title = "CRUD Demo - Blog Posts";
include 'includes/header.php';
?>

<div class="container">
    <h2>Blog Posts Management</h2>
    
    <?php if ($message): ?>
        <div class="alert <?php echo $message_type; ?>" style="padding: 10px; margin: 10px 0; border-radius: 4px; <?php echo $message_type === 'error' ? 'background-color: #ffebee;' : 'background-color: #e8f5e9;'; ?>">
            <?php echo $message; ?>
        </div>
    <?php endif; ?>

    <!-- Create/Edit Form -->
    <div class="form-section" style="margin: 20px 0; padding: 20px; border: 1px solid #ddd; border-radius: 4px;">
        <h3><?php echo $editing_post ? 'Edit Post' : 'Create New Post'; ?></h3>
        <form method="POST" action="crud.php">
            <input type="hidden" name="action" value="<?php echo $editing_post ? 'update' : 'create'; ?>">
            <?php if ($editing_post): ?>
                <input type="hidden" name="post_id" value="<?php echo $editing_post['id']; ?>">
            <?php endif; ?>
            
            <div class="form-group" style="margin-bottom: 15px;">
                <label for="title">Title:</label>
                <input type="text" id="title" name="title" required
                       value="<?php echo $editing_post ? htmlspecialchars($editing_post['title']) : ''; ?>"
                       style="width: 100%; padding: 8px; margin-top: 5px; border: 1px solid #ddd; border-radius: 4px;">
            </div>
            
            <div class="form-group" style="margin-bottom: 15px;">
                <label for="content">Content:</label>
                <textarea id="content" name="content" rows="4" required
                          style="width: 100%; padding: 8px; margin-top: 5px; border: 1px solid #ddd; border-radius: 4px;"
                ><?php echo $editing_post ? htmlspecialchars($editing_post['content']) : ''; ?></textarea>
            </div>
            
            <button type="submit" style="background-color: #4CAF50; color: white; padding: 10px 20px; border: none; border-radius: 4px; cursor: pointer;">
                <?php echo $editing_post ? 'Update Post' : 'Create Post'; ?>
            </button>
            
            <?php if ($editing_post): ?>
                <a href="crud.php" style="display: inline-block; padding: 10px 20px; margin-left: 10px; text-decoration: none; color: #666; border: 1px solid #ddd; border-radius: 4px;">
                    Cancel
                </a>
            <?php endif; ?>
        </form>
    </div>

    <!-- Posts List -->
    <div class="posts-section">
        <h3>All Posts</h3>
        <?php if (empty($posts)): ?>
            <p>No posts found.</p>
        <?php else: ?>
            <?php foreach ($posts as $post): ?>
                <div class="post" style="margin: 20px 0; padding: 15px; border: 1px solid #ddd; border-radius: 4px;">
                    <h4 style="margin: 0 0 10px 0;"><?php echo htmlspecialchars($post['title']); ?></h4>
                    <p style="margin: 10px 0;"><?php echo htmlspecialchars($post['content']); ?></p>
                    <div class="post-meta" style="color: #666; font-size: 0.9em;">
                        Created: <?php echo date('F j, Y, g:i a', strtotime($post['created_at'])); ?>
                    </div>
                    <div class="post-actions" style="margin-top: 10px;">
                        <a href="?edit=<?php echo $post['id']; ?>" style="color: #2196F3; text-decoration: none; margin-right: 15px;">Edit</a>
                        <form method="POST" action="crud.php" style="display: inline;">
                            <input type="hidden" name="action" value="delete">
                            <input type="hidden" name="post_id" value="<?php echo $post['id']; ?>">
                            <button type="submit" onclick="return confirm('Are you sure you want to delete this post?');"
                                    style="background: none; border: none; color: #f44336; cursor: pointer; padding: 0;">
                                Delete
                            </button>
                        </form>
                    </div>
                </div>
            <?php endforeach; ?>
        <?php endif; ?>
    </div>
</div>

<?php include 'includes/footer.php'; ?> 