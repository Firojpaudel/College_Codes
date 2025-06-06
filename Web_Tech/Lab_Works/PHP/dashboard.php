<?php
require_once 'includes/config.php';
require_once 'includes/db_connect.php';

session_start();

// Check if user is not logged in
if (!isset($_SESSION['user_id'])) {
    header("Location: login.php");
    exit();
}

$page_title = "Dashboard";
include 'includes/header.php';

// Fetch user's posts
try {
    $conn = getDB();
    $stmt = $conn->prepare("SELECT * FROM posts WHERE user_id = ? ORDER BY created_at DESC");
    $stmt->execute([$_SESSION['user_id']]);
    $posts = $stmt->fetchAll(PDO::FETCH_ASSOC);
} catch(PDOException $e) {
    $error = "Error fetching posts: " . $e->getMessage();
}
?>

<div class="container">
    <div class="dashboard-header" style="display: flex; justify-content: space-between; align-items: center; margin-bottom: 20px;">
        <h2>Welcome, <?php echo htmlspecialchars($_SESSION['username']); ?>!</h2>
        <a href="logout.php" style="background-color: #f44336; color: white; padding: 8px 16px; text-decoration: none; border-radius: 4px;">
            Logout
        </a>
    </div>

    <div class="dashboard-stats" style="display: grid; grid-template-columns: repeat(auto-fit, minmax(200px, 1fr)); gap: 20px; margin-bottom: 30px;">
        <div class="stat-card" style="background-color: #f5f5f5; padding: 20px; border-radius: 4px; text-align: center;">
            <h3 style="margin: 0 0 10px 0;">Total Posts</h3>
            <p style="font-size: 24px; margin: 0;"><?php echo count($posts); ?></p>
        </div>
        
        <div class="stat-card" style="background-color: #f5f5f5; padding: 20px; border-radius: 4px; text-align: center;">
            <h3 style="margin: 0 0 10px 0;">Last Login</h3>
            <p style="font-size: 16px; margin: 0;"><?php echo date('F j, Y, g:i a'); ?></p>
        </div>
    </div>

    <div class="dashboard-actions" style="margin-bottom: 30px;">
        <h3>Quick Actions</h3>
        <div style="display: flex; gap: 10px;">
            <a href="crud.php" style="background-color: #2196F3; color: white; padding: 10px 20px; text-decoration: none; border-radius: 4px;">
                Manage Posts
            </a>
            <a href="#" style="background-color: #4CAF50; color: white; padding: 10px 20px; text-decoration: none; border-radius: 4px;">
                Create New Post
            </a>
        </div>
    </div>

    <div class="recent-posts">
        <h3>Your Recent Posts</h3>
        <?php if (empty($posts)): ?>
            <p>You haven't created any posts yet.</p>
        <?php else: ?>
            <div style="display: grid; gap: 20px;">
                <?php foreach (array_slice($posts, 0, 5) as $post): ?>
                    <div class="post" style="background-color: white; padding: 15px; border: 1px solid #ddd; border-radius: 4px;">
                        <h4 style="margin: 0 0 10px 0;"><?php echo htmlspecialchars($post['title']); ?></h4>
                        <p style="margin: 0 0 10px 0;"><?php echo substr(htmlspecialchars($post['content']), 0, 150) . '...'; ?></p>
                        <div style="color: #666; font-size: 0.9em;">
                            Posted on <?php echo date('F j, Y', strtotime($post['created_at'])); ?>
                        </div>
                    </div>
                <?php endforeach; ?>
            </div>
        <?php endif; ?>
    </div>
</div>

<?php include 'includes/footer.php'; ?> 