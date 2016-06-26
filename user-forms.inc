<?php


function angelio_form_alter(&$form, &$form_state, $form_id) {
global $user;	
// ******** user_register

    if ($form_id == 'user_register_form') {

	$sponsor_name = '';
	if (isset($_COOKIE['sponsor_name'])) {
		$sponsor_name = $_COOKIE['sponsor_name']; 
	} else if (isset($_SESSION['sponsor_name'])){
		$sponsor_name = $_SESSION['sponsor_name'];
	} 



	// hilfe öffnen link:
	$form['account']['script'] = array(
		'#markup' => '<script>

(function ($) {
  Drupal.behaviors.angelio = {
    attach: function (context, settings) {
		$(".form_expand", context).click(function () {
    $header = $(this);
    //getting the next element
    $content = $header.next();
    //open up the content needed - toggle the slide- if visible, slide up, if not slidedown.
    $content.slideToggle(300, function () {
        //execute this after slideToggle is done
        //change text of header based on visibility of content div
        $header.html(function () {
            //change text based on condition
            return $content.is(":visible") ? "<span class=\"form_hilfe\">Hilfe schließen...</span>" : "<span class=\"form_hilfe\">Hilfe öffnen...</span>";
        });
    });

	});
      }}})(jQuery);
</script>',
		
	);

	$form['account']['name'] = array(
	    '#title' => 'Benutzername aussuchen',
	    '#description' => '<div class="form_expand"><span class="form_hilfe">Hilfe öffnen...</span></div><div class="form_collapse">Wählen Sie hier einen Benutzernamen nach Ihren Wünschen, aber beachten Sie unten angeführte Regeln. Der Benutzername ist sehr wichtig für Sie und kann nicht mehr geändert werden! Einerseits benötigen Sie ihn, um sich bei angelio einzuloggen. 
Andererseits wird dieser Name verwendet, wenn Sie weitere Personen als Mitglieder anwerben, damit das System weiß, wer wen geworben hat und wir dadurch die Werbeprämie an Sie ausbezahlen können. <br><b>Regeln:</b> Der Benutzername muss zwischen 3 und 15 Zeichen lang sein und darf keine Umlaute, Leerzeichen, Satzzeichen und Sonderzeichen enthalten. Beispiele: RUDI1963, RudiPur, Winner1.<br>Sollte ein Benutzername bereits im System vorhanden sein, dann müssen Sie einen anderen wählen.<br>WÄHLEN SIE DEN BENUTZERNAMEN MIT BEDACHT! ER KANN SPÄTER NICHT MEHR GEÄNDERT WERDEN!</div>',
	    '#type' => 'textfield',
	    '#required' => TRUE,
	    '#element_validate' => array('angelio_username_validate'),
	    '#weight' => 2,
	);
	
	$form['account']['mail']['#description'] = '<div class="form_expand"><span class="form_hilfe">Hilfe öffnen...</span></div><div class="form_collapse">Eine gültige E-Mail-Adresse. Alle E-Mails der Website werden an diese Adresse geschickt. Die Adresse wird nicht veröffentlicht und wird nur verwendet, wenn Sie ein neues Passwort anfordern oder wenn Sie einstellen, bestimmte Informationen oder Benachrichtigungen per E-Mail zu erhalten.</div>';
	
	$form['benutzer'] = array(
	  '#type' => 'fieldset',
	  '#weight' => 1,
	);
	
	$form['benutzer']['sponsor'] = array(
	  '#title' => 'Wer hat dir den Verein angelio empfohlen?',
	  '#description' => '<div class="form_expand"><span class="form_hilfe">Hilfe öffnen...</span></div><div class="form_collapse">Wenn das Feld leer ist, dann müssen Sie hier den Benutzernamen der Person einfügen, die Ihnen angelio empfohlen hat.</div>',
	  '#type' => 'textfield',
	  '#element_validate' => array('angelio_sponsor_validate'),
	  '#required' => TRUE,
	  '#autocomplete_path' => 'user/autocomplete',
	  '#default_value' => $sponsor_name,
	  '#weight' => 1,
	);

//	if (isset($_GET['wunsch'])) {
		$form['benutzer']['upline'] = array(
		  '#title' => 'Wunschlinie in der Matrix',
		  '#description' => '<div class="form_expand"><span class="form_hilfe">Hilfe öffnen...</span></div><div class="form_collapse">In welcher Linie der 3x9 Matrix soll der Benutzer platziert werden? Bitte nur ausf&uuml;llen, wenn Du schon eine Downline hast.</div>',
		  '#type' => 'textfield',
          '#autocomplete_path' => 'user/autocomplete',		  
		  '#element_validate' => array('angelio_upline_validate'),
		  '#weight' => 2,
		);
//	}
	 
	$form['personal'] = array(
	  '#type' => 'fieldset',
	  '#title' => '<strong>' . t('Kontakt Informationen') . '</strong>',
	  '#weight' => 2,
	);
	$form['personal']['strTitel_O'] = array(
	  '#type' => 'textfield',
	  '#title' => t('Titel'),
	  '#required' => FALSE,
	  '#weight' => 1,
	);
	
	$form['personal']['strVName_O'] = array(
	  '#type' => 'textfield',
	  '#title' => t('Vorname'),
	  '#required' => TRUE,
	  '#weight' => 2,	 
	);	
	$form['personal']['strNName_O'] = array(
	  '#type' => 'textfield',
	  '#title' => t('Nachname'),
	  '#required' => TRUE,
	  '#weight' => 3,	  
	);
	$form['personal']['strAnschrift_O'] = array(
	  '#type' => 'textfield',
	  '#title' => t('Strasse'),
	  '#required' => TRUE,	  
	  '#weight' => 4,	 
	);
	$form['personal']['strPLZ_O'] = array(
	  '#type' => 'textfield',
	  '#title' => t('PLZ'),
	  '#required' => TRUE,
	  '#weight' => 5,	  
	);
	$form['personal']['strOrt_O'] = array(
	  '#type' => 'textfield',
	  '#title' => t('Ort'),
	  '#required' => TRUE,
	  '#weight' => 6,	  
	);
	$form['personal']['strLand_O'] = array(
	  '#type' => 'select',
	  '#title' => t('Land'),
	  '#options' => array('' => '', 'AT' => 'Österreich','DE' => 'Deutschland'),
	  '#required' => TRUE,
	  '#weight' => 7,	  
	);
	$form['personal']['strBeruf_O'] = array(
	  '#type' => 'textfield',
	  '#title' => t('Beruf'),
	  '#required' => TRUE,
	  '#weight' => 8,	  
	);
	$form['personal']['strTelefon_O'] = array(
	  '#type' => 'textfield',
	  '#title' => t('Telefon'),
	  '#required' => TRUE,
	  '#weight' => 9,	
	);

	$form['alter'] = array(
	  '#type' => 'fieldset',
	  '#title' => '<strong>' . t('Alter') . '</strong>',
	  '#weight' => 3,
	);
	
	$form['alter']['datGeburt_O'] = array(
	  '#title' => t('Geburtstag'),
	  '#type' => 'date',
	  '#default_value' => array(
	    'month' => format_date(time(), 'custom', 'n'), 
	    'day' => format_date(time(), 'custom', 'j'), 
	    'year' => format_date(time(), 'custom', 'Y'),
	  ),
	  '#required' => TRUE,  
	  '#element_validate' => array('angelio_geburtstag_validate'),
	  '#description' => '<div class="form_expand"><span class="form_hilfe">Hilfe öffnen...</span></div><div class="form_collapse"><p>Um Mitglied beim Verein angelio zu werden, bedarf es für Minderjährige (unter 18 Jahre) der ausdrücklichen Zustimmung eines Erziehungsberechtigten.
Wir benötigen in diesem Fall eine Einverständniserklärung, die Sie <a href="/downloads/Einverstaendniserklaerung.pdf" target="_blank">hier ausdrucken</a> können. Per Fax, E-Mail oder Post muss diese unverzüglich an uns gesendet werden.
Sollten wir die Einverständniserklärung nicht innerhalb der gesetzlichen Kündigungsfrist von 14 Tagen erhalten, dann müssen wir von uns aus eine Kündigung des minderjährigen Mitglieds durchführen.<br>ACHTUNG: Personen &uuml;ber 74 Jahre bekommen die Unfallversicherung als Rente ausbezahlt!</div>',
	  '#weight' => 1,	
	);
	
	
	$form['bank'] = array(
	  '#type' => 'fieldset',
	  '#title' => '<strong>' . t('Bankverbindung') . '</strong>',
	  '#weight' => 4,
	);

	$form['bank']['strIban_O'] = array(
	  '#type' => 'textfield',
	  '#title' => t('IBAN'),
	  '#required' => TRUE,
	  '#element_validate' => array('angelio_iban_validate'),
	  //'#default_value' => 'AT131490022010010999',
	  '#weight' => 2,		
	);
	$form['bank']['strBic_O'] = array(
	  '#type' => 'textfield',
	  '#title' => t('BIC'),
	  '#required' => TRUE,	  
	  '#element_validate' => array('angelio_bic_validate'),	  
	  //'#default_value' => 'RZOOAT2L510',
	  '#description' => '<div class="form_expand"><span class="form_hilfe">Hilfe öffnen...</span></div><div class="form_collapse">Zahlungsempfänger:<br>Verein angelio Kaufgemeinschaft<br>
Aigen 1<br>
A-4654 Bad Wimsbach-Neydharting<br>
<br>
Gläubiger-Identifikationsnummer: AT76ZZZ00000016804<br>
(Creditor ID)<br></div>',	  
	  '#weight' => 3,	
	);		
	
	$form['bank']['Zahlungsintervall_O'] = array(
	  '#type' => 'select',
	  '#title' => t('Zahlungsweise'),
	  '#required' => TRUE,
	  '#options' => array('1'=>'jährlich 264€ (22€/Mon.)',
	  					  '2'=>'halbjährlich 138€ (23€/Mon.)',
	  					  '4'=>'quartalsweise 72€ (24€/Mon.)',
	  					  '12'=>'monatlich 25€'), 
	  '#weight' => 4,	
	);

	$form['bank']['Beitrag'] = array(
	  '#type' => 'checkbox',
	  '#title' => '<span class="description">Ich ermächtige/Wir ermächtigen den Verein angelio Kaufgemeinschaft, Zahlungen von meinem/unserem Konto mittels Lastschrift einzuziehen. Zugleich weise ich 
mein/weisen wir unser Kreditinstitut an, die vom Verein angelio Kaufgemeinschaft auf mein/unser Konto gezogenen Lastschriften einzulösen.
Ich kann/Wir können innerhalb von acht Wochen, beginnend mit dem Belastungsdatum, die Erstattung des belasteten Betrages verlangen. Es gelten dabei die mit 
meinem/unserem Kreditinstitut vereinbarten Bedingungen.</span>
	  ',
	  '#element_validate' => array('angelio_beitrag_validate'),
	  '#weight' => 5,
	);
	
		
	$form['bedingungen'] = array(
	  '#type' => 'fieldset',
	  '#title' => '<strong>' . t('Bedingungen') . '</strong>',
	  '#weight' => 5,
	);
	
	/*
	$form['bedingungen']['ysnNewsletter_O'] = array(
	  '#type' => 'checkbox',
	  '#title' => t('Bitte sendet mir den angelio Newsletter zu.'),
	  '#attributes' => array('checked' => 'checked'),
	  '#weight' => 1,
	);
	*/
	
	$form['bedingungen']['AGB'] = array(
	  '#type' => 'checkbox',
	  '#title' => 'Ich habe die <a target="_blank" href="/agb">Allgemeinen Geschäftsbedingungen</a> gelesen und akzeptiere sie.',
	  '#element_validate' => array('angelio_agb_validate'),
	  '#weight' => 2,
	);

  //$form['submit'] = array('#type' => 'submit','#value' => 'Registrierung absenden...', );

	$form['#submit'][] = 'angelio_user_register_form_submit';
	//$form['actions']['submit']['#submit'][] = 'angelio_user_register_form_submit';
	
    } 

// ******** user_profile_form

	if ($form_id == 'user_profile_form') {
	$account_id = arg(1);
	$account = user_load($account_id);
	$user_id = $account->uid;
	$user_name = $account->name;
	$userdata = angelio_get_userdata($user_id);
	$ysnNewsletter_O = ($userdata['ysnNewsletter_O'] == 0x01) ? '1' : '0';
	$ysnNewsletter_O = ord($userdata['ysnNewsletter_O']);
	
	$form['KundenID_online'] = array(
		'#type' => 'hidden', 
		'#value' => $user_id,
	);
	
	$form['personal'] = array(
	  '#type' => 'fieldset',
	  '#title' => 'Kontakt Informationen',
	  '#weight' => 1,
	);
	$form['personal']['strTitel_O'] = array(
	  '#type' => 'textfield',
	  '#title' => t('Titel'),
	  '#required' => FALSE,
	  '#default_value' => $userdata['strTitel_O'],
	  '#weight' => 1,
	);
	$form['personal']['strVName_O'] = array(
	  '#type' => 'textfield',
	  '#title' => t('Vorname'),
	  '#required' => TRUE,
	  '#default_value' => $userdata['strVName_O'],	  
	  '#weight' => 2,	 
	);	
	$form['personal']['strNName_O'] = array(
	  '#type' => 'textfield',
	  '#title' => t('Nachname'),
	  '#required' => TRUE,
	  '#default_value' => $userdata['strNName_O'],	  
	  '#weight' => 3,	  
	);
	$form['personal']['strAnschrift_O'] = array(
	  '#type' => 'textfield',
	  '#title' => t('Strasse'),
	  '#required' => TRUE,	 
	  '#default_value' => $userdata['strAnschrift_O'],	   
	  '#weight' => 4,	 
	);
	$form['personal']['strPLZ_O'] = array(
	  '#type' => 'textfield',
	  '#title' => t('PLZ'),
	  '#required' => TRUE,
	  '#default_value' => $userdata['strPLZ_O'],	  
	  '#weight' => 5,	  
	);
	$form['personal']['strOrt_O'] = array(
	  '#type' => 'textfield',
	  '#title' => t('Ort'),
	  '#required' => TRUE,
	  '#default_value' => $userdata['strOrt_O'],	  
	  '#weight' => 6,	  
	);
	$form['personal']['strLand_O'] = array(
	  '#type' => 'select',
	  '#title' => t('Land'),
	  '#options' => array('' => '', 'AT' => 'Österreich','DE' => 'Deutschland'),
	  '#required' => TRUE,
	  '#default_value' => $userdata['strLand_O'],	  
	  '#weight' => 7,	  
	);
	$form['personal']['strBeruf_O'] = array(
	  '#type' => 'textfield',
	  '#title' => t('Beruf'),
	  '#required' => TRUE,
	  '#default_value' => $userdata['strBeruf_O'],	  
	  '#weight' => 8,	  
	);
	$form['personal']['strTelefon_O'] = array(
	  '#type' => 'textfield',
	  '#title' => t('Telefon'),
	  '#required' => TRUE,
	  '#default_value' => $userdata['strTelefon_O'],	  
	  '#weight' => 9,	
	);
/*
	$form['personal']['strMobil_O'] = array(
	  '#type' => 'textfield',
	  '#title' => t('Mobil'),
	  '#default_value' => $userdata['strMobil_O'],	  
	  '#weight' => 10,
	);
*/
	$form['personal']['datGeburt_O'] = array(
	  '#title' => t('Geburtstag'),
	  '#type' => 'date',
	  '#default_value' => array(
	    'month' => fdate($userdata['datGeburt_O'],'n'), 
	    'day' => fdate($userdata['datGeburt_O'],'d'), 
	    'year' => fdate($userdata['datGeburt_O'],'Y'),
	  ),
	  '#required' => TRUE,  
	  '#element_validate' => array('angelio_geburtstag_validate'),
	  '#weight' => 11,	
	);
	
	$form['bank'] = array(
	  '#type' => 'fieldset',
	  '#title' => t('Bankverbindung'),
	  '#weight' => 2,
	);
/*
	$form['bank']['strBank_O'] = array(
	  '#type' => 'textfield',
	  '#title' => t('Bankinstitut'),
	  '#required' => TRUE,
	  '#default_value' => $userdata['strBank_O'],	  
	  '#weight' => 1,	
	);
 */	
	$form['bank']['strIban_O'] = array(
	  '#type' => 'textfield',
	  '#title' => t('IBAN'),
	  '#required' => TRUE,
	  '#element_validate' => array('angelio_iban_validate'),
	  '#default_value' => $userdata['strIban_O'],	  
	  '#weight' => 2,		
	);
    
	$form['bank']['strBic_O'] = array(
	  '#type' => 'textfield',
	  '#title' => t('BIC'),
	  '#required' => TRUE,	  
	  '#element_validate' => array('angelio_bic_validate'),
	  '#default_value' => $userdata['strBic_O'],	  
	  '#weight' => 3,	
	);		
	$form['bank']['Zahlungsintervall_O'] = array(
	  '#type' => 'select',
	  '#title' => t('Zahlungsweise'),
	  '#required' => TRUE,
	  '#options' => array('1'=>'jährlich','2'=>'halbjährlich','4'=>'quartalsweise','12'=>'monatlich'),	  
	  '#default_value' => $userdata['Zahlungsintervall_O'],
	  '#weight' => 4,	
	);
		
	/*
	$form['ysnNewsletter_O'] = array(
	  '#type' => 'checkboxes',
	  '#options' => array('1' => 'Bitte sendet mir den angelio Newsletter zu.'),
	  '#default_value' => array($userdata['ysnNewsletter_O']),
	  '#title' => t('Newsletter'),	  
	  '#weight' => 10,
	);
 */
 
	$form['#submit'][] = 'angelio_user_edit_form_submit';
	unset($form['contact']);

	}
}

function angelio_username_validate($element, &$form_state) {
  $username = $element['#value']; 
  if(!angelio_validate_url($username)) {
    form_error($element, t('Der Benutzername "%s" ist ung&uuml;ltig. Bitte keine Umlaute, Leerzeichen, Satzzeichen und Sonderzeichen verwenden.', array('%s'=>$username)));
  }
}

function angelio_sponsor_validate($element, &$form_state) {
  $sponsor = $element['#value']; 
  if(!angelio_check_sponsor($sponsor)) {
    form_error($element, t('Sponsor "%s" ist unbekannt.', array('%s'=>$sponsor)));
  }
}

function angelio_upline_validate($element, &$form_state) {
  $upline = $element['#value']; 
  if ($upline<>"") {
	  if(!user_load_by_name($upline)) {
	    form_error($element, t('Upline "%s" ist unbekannt.', array('%s'=>$upline)));
	  }
  }
}


function angelio_password_validate($element, &$form_state) {
  $password = $element['#value'];
  $password1 = $form_state['values']['password1'];
  if($password != $password1) {
    form_error($element, 'Passwörter sind nicht gleich!');
  }
}

function angelio_geburtstag_validate($element, &$form_state) {
  $geburtstag = $element['#value']; 
  if(date('Y',time()) - $geburtstag['year'] < 1) {
    form_error($element, t('Das Geburtsjahr "%d" ist ungültig. Das Mindestalter ist 1 Jahr!',array('%d' => $geburtstag['year'])));
  }
  if(date('Y',time()) - $geburtstag['year'] > 74) {
    drupal_set_message("ACHTUNG: Sie sind &uuml;ber 75 Jahre alt und bekommen die Unfallversicherung als Rente ausbezahlt!","warning");
  }  
}

function angelio_iban_validate($element, &$form_state) {
  $iban = $element['#value'];
  if (!verify_iban($iban)) {
    form_error($element, t('IBAN ist ungültig.'));
  }
}

function angelio_bic_validate($element, &$form_state) {
	
	if(!preg_match("/^([a-zA-Z]){4}([a-zA-Z]){2}([0-9a-zA-Z]){2}([0-9a-zA-Z]{3})?$/", $element['#value'])) {
		form_error($element, t('BIC ist ungültig.'));
	} 
}

function angelio_agb_validate($element, &$form_state) {
  if(empty($element['#value'])) {
    form_error($element, t('Sie müssen den Allgemeinen Geschäftsbedingungen zustimmen!'));
  }
}

function angelio_beitrag_validate($element, &$form_state) {
  if(empty($element['#value'])) {
    form_error($element, t('Sie müssen dem Einzugsverfahren zustimmen!'));
  }
}

function angelio_user_register_form_submit($form, &$form_state) {
		
	$username = $form_state['values']['name'];
    $userinfo = db_query("SELECT * FROM {users} WHERE name='" . $username . "'")->fetchAssoc();
	
	$KundenID_online = $userinfo['uid'];
	$strUsername_O = $username;
	$strEmail_O = $form_state['values']['mail'];
	$SponsorID_O = $_SESSION['sponsor_uid'];
	if (isset($form_state['values']['upline'])) {
		$upline = $form_state['values']['upline'];
	} else {
		$upline = "";
	}
	
	$KundenID_offline = '';
	$strNName_O = $form_state['values']['strNName_O'];
	$strVName_O = $form_state['values']['strVName_O'];
	$strTitel_O = $form_state['values']['strTitel_O'];
	$strAnschrift_O = $form_state['values']['strAnschrift_O'];
	$strPLZ_O = $form_state['values']['strPLZ_O'];
	$strOrt_O = $form_state['values']['strOrt_O'];
	$strLand_O = $form_state['values']['strLand_O'];
	$strBeruf_O = $form_state['values']['strBeruf_O'];
	$datGeburt = $form_state['values']['datGeburt_O'];
	$datGeburt_O = $datGeburt['year'] . '-' . $datGeburt['month'] . '-' . $datGeburt['day'];  
	$strTelefon_O = $form_state['values']['strTelefon_O'];
	$strMobil_O = '';
	$strBank_O = '';
	$strBic_O = $form_state['values']['strBic_O'];
	$strIban_O = $form_state['values']['strIban_O'];
	//$ysnNewsletter_O = $form_state['values']['ysnNewsletter_O'];
	$ysnNewsletter_O = '0';
	$Polizzennummer_O = date("ym") . sprintf("%07d", $KundenID_online) . "0101";
	$Zahlungsintervall_O = $form_state['values']['Zahlungsintervall_O'];
	$ysnInaktiv = 0;
	$now = date("Y-m-d H:i:s", time());

	db_set_active('angelio_daten');

    $success = db_insert('tbl_Kunden_Online')
	->fields(array(
	'KundenID_online' => $KundenID_online,
	'strUsername_O' => $strUsername_O,
	'strEmail_O' => $strEmail_O,
	'ReferrerID_O' => $SponsorID_O,
	'strNName_O' => $strNName_O,
	'strVName_O' => $strVName_O,
	'strTitel_O' => $strTitel_O,
	'strAnschrift_O' => $strAnschrift_O,
	'strPLZ_O' => $strPLZ_O,
	'strOrt_O' => $strOrt_O,
	'strLand_O' => $strLand_O,
	'strBeruf_O' => $strBeruf_O,
	'datGeburt_O' => $datGeburt_O,
	'strTelefon_O' => $strTelefon_O,
	'strMobil_O' => $strMobil_O,
	'strBank_O' => $strBank_O,
	'strBic_O' => $strBic_O,
	'strIban_O' => $strIban_O,
	'ysnNewsletter_O' => $ysnNewsletter_O,
	'Polizzennummer_O' => $Polizzennummer_O,
	'Zahlungsintervall_O' => $Zahlungsintervall_O,
	'datAnlageInternet_O' => $now,
	'datLastAbgleich_O' => $now,
	'ysnInaktiv' => $ysnInaktiv
	))->execute();
  
  	db_set_active();
	
	if (!$success) {
		drupal_set_message("Der Benutzer wurde NICHT gespeichert.", 'error');
	}
	else {
		
	 	// Member in Matrix platzieren:
	    $member = angelio_get_userobject($userinfo['uid']);
		if ($upline<>"") {
			// Wunschlinie gesetzt
			$upline_user = user_load_by_name($upline);
			$upline_id = $upline_user->uid;
			angelio_inMatrix($member->member_id, $upline_id);
		} else {
			angelio_inMatrix($member->member_id, $member->sponsor_id);
		}
		
	    // Benutzer Rolle setzen
		if ($role = user_role_load_by_name('BRONCE')) {
			// Funktioniert einfach nicht...
			  
	        user_multiple_role_edit(array($member->member_id), 'add_role', $role->rid);

	        /* auch nicht
	        $user = user_load($member->member_id);
			$user->roles = $user->roles + array($role->rid => $role->name);
			user_save($user);
			*/
			
			db_set_active('angelio_daten');
			// Dem Member die host_id eintragen
			db_update('tbl_Kunden_Online')
				->fields(array('bonuslevel' => 2))
				->condition('KundenID_online', $member->member_id, '=')
				->execute();
			db_set_active();
			
			drupal_set_message("Willkommen bei angelio!");
	      }  
		
		
		$member = angelio_get_userobject($userinfo['uid']); // jetzt erst ist die Upline gesetzt!
		angelio_mail2upline($userinfo['uid']);
        
        
        /*
        // Benutzeradresse im Shop anlegen:
        
        db_set_active('angelio_shop');
    
        
        $sql = "INSERT INTO {users} (uid, name, pass, mail, mode, sort, threshold, theme, signature, signature_format, created, access, login, status, timezone, language, picture, init, data, timezone_name) 
        VALUES (
        " . $user['uid'] . ", 
        '" . $user['name'] . "', 
        '" . $user['pass'] . "', 
        '" . $user['mail'] . "', 
        " . $user['mode'] . ", 
        " . $user['sort'] . ", 
        " . $user['threshold'] . ", 
        '" . $user['theme'] . "', 
        '" . $user['signature'] . "', 
        " . $user['signature_format'] . ", 
        " . $user['created'] . ", 
        " . $user['access'] . ", 
        " . $user['login'] . ", 
        " . $user['status'] . ", 
        '" . $user['timezone'] . "', 
        '" . $user['language'] . "', 
        '" . $user['picture'] . "', 
        '" . $user['init'] . "', 
        '" . $user['data'] . "', 
        '" . $user['timezone_name'] . "'
        )";
    
        $success = db_query($sql);
        if (!$success) {
            drupal_set_message("Fehler beim Export von " . $uid, 'error');
        } else {
            drupal_set_message("Der Benutzer wurde im angelio Shop angelegt");
        }
            
        $uid = $KundenID_online;
        $first_name = $strVName_O;
        $last_name = $strNName_O;
        $phone = $strTelefon_O;
        $company = '';
        $street1 = $strAnschrift_O;
        $street2 = '';
        $city = $strOrt_O;
        $zone = '0';
        $postal_code = $strPLZ_O;
        if ($strLand_O == 'AT') {$country = '40';}
        if ($strLand_O == 'DE') {$country = '276';} 
        $address_name = 'angelio';
        $default_shipping = '1';
        $default_billing= '1';
        $created = 'NOW()';
        $modified  = 'NOW()';
        $title = '';
        $surname_prefix = '';
        $house_number = '';
        $sql = "INSERT INTO {uc_addresses} (uid,first_name,last_name,phone,company,street1,street2,city,zone,postal_code,country,address_name,default_shipping,default_billing,created,modified,title,surname_prefix,house_number)";
        $sql .= " VALUES ('$uid','$first_name','$last_name','$phone','$company','$street1','$street2','$city',$zone,'$postal_code',$country,'$address_name',$default_shipping,$default_billing,$created,$modified,'$title','$surname_prefix','$house_number')";
    
        $success = db_query($sql);
        if (!$success) {
            drupal_set_message("Fehler beim Import von " . $uid, 'error');
        } else {
            drupal_set_message("Die Benutzeradresse wurde im angelio Shop hinterlegt");
        }
    
        db_set_active('');          
         * 
         */
         
		// Alles Ok
		drupal_set_message("Hallo " . $member->first_name . "! Willkommen bei angelio! Sie wurden in der Matrix platziert.");
		drupal_set_message("Ihr Sponsor: " . $_SESSION['sponsor_name']);
		drupal_set_message("Ihre Matrix-Upline: " . $member->upline_first_name . " " . $member->upline_last_name . " (" . $member->upline . ")");
	}
	
	drupal_goto("user");
}

function angelio_user_edit_form_submit($form, &$form_state) {
	$KundenID_online = $form_state['values']['KundenID_online'];
	$strEmail_O = $form_state['values']['mail'];
	$strNName_O = $form_state['values']['strNName_O'];
	$strVName_O = $form_state['values']['strVName_O'];
	$strTitel_O = $form_state['values']['strTitel_O'];
	$strAnschrift_O = $form_state['values']['strAnschrift_O'];
	$strPLZ_O = $form_state['values']['strPLZ_O'];
	$strOrt_O = $form_state['values']['strOrt_O'];
	$strLand_O = $form_state['values']['strLand_O'];
	$strBeruf_O = $form_state['values']['strBeruf_O'];
	$datGeburt = $form_state['values']['datGeburt_O'];
	$datGeburt_O = $datGeburt['year'] . '-' . $datGeburt['month'] . '-' . $datGeburt['day'];  
	$strTelefon_O = $form_state['values']['strTelefon_O'];
	$strMobil_O = '';
	$strBank_O = '';
	$strBic_O = $form_state['values']['strBic_O'];
	$strIban_O = $form_state['values']['strIban_O'];
	//$ysnNewsletter_O = $form_state['values']['ysnNewsletter_O'][1];
	$ysnNewsletter_O = '0';
	$Zahlungsintervall_O = $form_state['values']['Zahlungsintervall_O'];	
	$now = date("Y-m-d H:i:s", time());
	
	db_set_active('angelio_daten');
    $success = db_update('tbl_Kunden_Online')
	->fields(array( 
	'strEmail_O' => $strEmail_O,
	'strNName_O' => $strNName_O,
	'strVName_O' => $strVName_O,
	'strTitel_O' => $strTitel_O,
	'strAnschrift_O' => $strAnschrift_O,
	'strPLZ_O' => $strPLZ_O,
	'strOrt_O' => $strOrt_O,
	'strLand_O' => $strLand_O,
	'strBeruf_O' => $strBeruf_O,
	'datGeburt_O' => $datGeburt_O,
	'strTelefon_O' => $strTelefon_O,
	'strMobil_O' => $strMobil_O,
	'strBank_O' => $strBank_O,
	'strBic_O' => $strBic_O,
	'strIban_O' => $strIban_O,
	'ysnNewsletter_O' => $ysnNewsletter_O,
	'Zahlungsintervall_O' => $Zahlungsintervall_O,))
	->condition('KundenID_online',$KundenID_online,'=')
	->execute();

	db_set_active();
	
	if (!$success) {
		drupal_set_message("Die Benutzerdaten wurde NICHT ge&auml;ndert.", 'warining'); 
		return false;
	}
	else {
		drupal_set_message("Der Benutzer wurde gespeichert.");
	}
    angelio_mail2office($KundenID_online);
}
?>