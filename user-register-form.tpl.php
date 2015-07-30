<?php

// What is in that $form var ? To check, uncomment next line
// print '<pre>' . print_r($form, 1) . '</pre>';
$sponsor_uid = '';
$sponsor_name = '';

if (isset($_SESSION['sponsor_uid'])) {
	$sponsor_uid = $_SESSION['sponsor_uid'];
}
if (isset($_SESSION['sponsor_name'])) {
	$sponsor_name = $_SESSION['sponsor_name'];	
}

drupal_set_title('angelio Anmeldung');
?>

<p><?php print render($intro_text); ?></p>
<div class="angelio-user-login-form-wrapper">
  <?php print drupal_render_children($form) ?>
</div>


<div class="register_daten">
	<?php
	/*
	// print_pre($form);
	
//	if ($sponsor_uid) {print "<b>Ihr Sponsor:</b> " . $sponsor_name;	}
	print render($form['personal']);
	print render($form['alter']);
	print render($form['bank']);
	print render($form['benutzer']);
	print render($form['name']);
	print render($form['mail']);
	print render($form['bedingungen']);
    print render($form['submit']);
  	print drupal_render($form['actions']);
	 * 
	 */
	?>
</div>