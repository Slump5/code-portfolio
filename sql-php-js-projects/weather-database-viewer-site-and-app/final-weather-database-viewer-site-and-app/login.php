<!DOCTYPE html>
<!-- Thomas Hoerger - Copyright © 2025 Skyview Weather Database Viewer Site-App Final Build -->
<html>
<head>
    <title>Skyview Login</title>
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <style>
    	body {
        	font-family: Arial, sans-serif;
        	background: #e0f7fa;
        	margin: 0;
        	padding: 0;
    	}

    	.login-box {
        	max-width: 400px;
        	margin: 10vh auto;
        	background: white;
        	padding: 20px;
        	border-radius: 8px;
        	box-shadow: 0px 4px 10px rgba(0,0,0,0.1);
    	}

    	input, button {
        	width: 100%;
        	padding: 10px;
        	margin: 8px 0;
        	font-size: 16px;
        	border-radius: 5px;
        	border: 1px solid #ccc;
    	}

    	button {
        	background-color: #007BFF;
        	color: white;
        	border: none;
    	}

    	button:hover {
        	background-color: #0056b3;
    	}

    	@media screen and (max-width: 480px) {
        	.login-box {
            		margin: 5vh 10px;
        	}
    	}
    </style>

</head>
<body>
    <div class="login-box">
        <h2>Login to Skyview Weather</h2>
        <form method="POST" action="auth.php">
            <input type="email" name="email" placeholder="Email" required><br>
            <input type="password" name="password" placeholder="Password" required><br>
            <button type="submit">Login</button>
        </form>
	<p style="margin: 15px 0; font-weight: bold; text-align: center;">— OR —</p>
        <a href="google-login.php"><button>Login with Google</button></a>
    </div>
</body>
</html>
