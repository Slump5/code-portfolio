<?php
// Thomas Hoerger - Copyright © 2025 Skyview Weather Database Viewer Final Build
session_start();           // Start the current session
session_destroy();         // Destroy all session data
header("Location: login.php");  // Redirect back to login page
exit();
?>
