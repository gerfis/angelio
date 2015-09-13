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


	$form['account']['name'] = array(
	    '#title' => t('username'),
	    '#description' => 'Wählen Sie hier einen Benutzernamen nach Ihren Wünschen, aber beachten Sie unten angeführte Regeln. Der Benutzername ist sehr wichtig für Sie und kann nicht mehr geändert werden! Einerseits benötigen Sie ihn, um sich bei angelio einzuloggen. 
Andererseits wird dieser Name verwendet, wenn Sie weitere Personen als Mitglieder anwerben, damit das System weiß, wer wen geworben hat und wir dadurch die Werbeprämie an Sie ausbezahlen können. <br><b>Regeln:</b> Der Benutzername muss zwischen 3 und 15 Zeichen lang sein und darf keine Leerzeichen, Satzzeichen und Sonderzeichen enthalten. Beispiele: RUDI1963, RudiPur, Winner1.<br>Sollte ein Benutzername bereits im System vorhanden sein, dann müssen Sie einen anderen wählen.<br>WÄHLEN SIE DEN BENUTZERNAMEN MIT BEDACHT! ER KANN SPÄTER NICHT MEHR GEÄNDERT WERDEN!',
	    '#type' => 'textfield',
	    '#required' => TRUE,
	    '#weight' => -1,
	);

	$form['benutzer'] = array(
	  '#type' => 'fieldset',
	  '#title' => t('angelio Informationen'),
	  '#weight' => 1,
	);
	
	$form['benutzer']['sponsor'] = array(
	  '#title' => t('Sponsor'),
	  '#description' => 'Der Sponsor ist jene Person, welche Sie als Mitglied zum Verein angelio anwerben möchte. Wenn das Feld leer ist, dann müssen Sie hier den Benutzernamen der Person einfügen, die Ihnen angelio empfohlen hat.',
	  '#type' => 'textfield',
	  '#element_validate' => array('angelio_sponsor_validate'),
	  '#required' => TRUE,
	  '#default_value' => $sponsor_name,
	  '#weight' => 1,
	);


	$form['personal'] = array(
	  '#type' => 'fieldset',
	  '#title' => t('Kontakt Informationen'),
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
	  '#title' => t('Alter'),
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
	  '#description' => '<p>Um Mitglied beim Verein angelio zu werden, bedarf es für Minderjährige (unter 18 Jahre) der ausdrücklichen Zustimmung eines Erziehungsberechtigten.
Wir benötigen in diesem Fall eine Einverständniserklärung, die Sie <a href="/downloads/Einverstaendniserklaerung.pdf" target="_blank">hier ausdrucken</a> können. Per Fax, E-Mail oder Post muss diese unverzüglich an uns gesendet werden.
Sollten wir die Einverständniserklärung nicht innerhalb der gesetzlichen Kündigungsfrist von 14 Tagen erhalten, dann müssen wir von uns aus eine Kündigung des minderjährigen Mitglieds durchführen.</p>',
	  '#weight' => 1,	
	);
	
	
	$form['bank'] = array(
	  '#type' => 'fieldset',
	  '#title' => t('Bankverbindung'),
	  '#description' => 'Zahlungsempfänger:<br>Verein angelio Kaufgemeinschaft<br>
Aigen 1 8<br>
A-4654 Bad Wimsbach-Neydharting<br>
<br>
Gläubiger-Identifikationsnummer: AT76ZZZ00000016804<br>
(Creditor ID)<br>',
	  '#weight' => 4,
	);

	$form['bank']['strIban_O'] = array(
	  '#type' => 'textfield',
	  '#title' => t('IBAN'),
	  '#required' => TRUE,
	  '#element_validate' => array('angelio_iban_validate'),
	  '#default_value' => 'AT131490022010010999',
	  '#weight' => 2,		
	);
	$form['bank']['strBic_O'] = array(
	  '#type' => 'textfield',
	  '#title' => t('BIC'),
	  '#required' => TRUE,	  
	  '#element_validate' => array('angelio_bic_validate'),	  
	  '#default_value' => 'RZOOAT2L510',
	  '#weight' => 3,	
	);		
	
	$form['bank']['Zahlungsintervall_O'] = array(
	  '#type' => 'select',
	  '#title' => t('Zahlungsweise'),
	  '#required' => TRUE,
	  '#options' => array('1'=>'jährlich 240€',
	  					  '2'=>'halbjährlich 120€',
	  					  '4'=>'quartalsweise 60€',
	  					  '12'=>'monatlich 20€'), 
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
	  '#title' => t('Bedingungen'),
	  '#weight' => 5,
	);
	
	$form['bedingungen']['ysnNewsletter_O'] = array(
	  '#type' => 'checkbox',
	  '#title' => t('Bitte sendet mir den angelio Newsletter zu.'),
	  '#attributes' => array('checked' => 'checked'),
	  '#weight' => 1,
	);
	
	$form['bedingungen']['AGB'] = array(
	  '#type' => 'checkbox',
	  '#title' => 'Ich habe die <a href="/agb">Allgemeinen Geschäftsbedingungen</a> gelesen und akzeptiere sie.',
	  '#element_validate' => array('angelio_agb_validate'),
	  '#weight' => 2,
	);


	$form['#submit'][] = 'angelio_user_register_form_submit';
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
		
	$form['ysnNewsletter_O'] = array(
	  '#type' => 'checkboxes',
	  '#options' => array('1' => 'Bitte sendet mir den angelio Newsletter zu.'),
	  '#default_value' => array($userdata['ysnNewsletter_O']),
	  '#title' => t('Newsletter'),	  
	  '#weight' => 10,
	);
 
 
	$form['#submit'][] = 'angelio_user_edit_form_submit';
	unset($form['contact']);

	}
}


function angelio_sponsor_validate($element, &$form_state) {
  $sponsor = $element['#value']; 
  if(!angelio_check_sponsor($sponsor)) {
    form_error($element, t('Sponsor "%s" ist unbekannt.', array('%s'=>$sponsor)));
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
    form_error($element, t('Das Geburtsjahr "%d" ist ungültig. Das Höchstalter ist 75 Jahre!',array('%d' => $geburtstag['year'])));
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
	$ysnNewsletter_O = $form_state['values']['ysnNewsletter_O'];
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
	'SponsorID_O' => $SponsorID_O,
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
		$text = "Der Benutzer wurde NICHT gespeichert.";
	}
	else {
		drupal_set_message("Der Benutzer wurde gespeichert.");
		$text = "Der Benutzer wurde gespeichert!";		
	}
}

function angelio_user_edit_form_submit($form, &$form_state) {
	$KundenID_online = $form_state['values']['KundenID_online'];
	$strEmail_O = $form_state['values']['mail'];
	$SponsorID_O = $_SESSION['sponsor_uid'];
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
	$ysnNewsletter_O = $form_state['values']['ysnNewsletter_O'][1];
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
		drupal_set_message("Der Benutzer wurde NICHT gespeichert.", 'error');
		return false;
	}
	else {
		drupal_set_message("Der Benutzer wurde gespeichert.");
	}

}
?>