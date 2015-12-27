<pre><?php // print_r($userdata); ?></pre>
<?php $date_anlage = date_create($userdata['datAbschluss']); ?>
<h3>angelio schützt Dich weltweit im Beruf und in der Freizeit, 24 Stunden</h3>

<p></p><b>Versicherungsbest&auml;tigungsnummer:</b> <?php print $userdata['Polizzennummer']; ?></p>
<p></p><b>Produkt:</b> <?php print $userdata['strProduktbeschreibung']; ?></p>

<p>Der Verein angelio bestätigt hiermit folgenden Versicherungsschutz für das Vereinsmitglied:</p>

<p>Bleibende körperliche Beeinträchtigungen bis zu Euro 300.000,- ab dem 1. Prozent lt. AUVB 2005<br />
(Grundversicherungssumme: Euro 100.000,- mit 300% Progression)</p>
<table>
<tr><td>Unfalltod:&nbsp;</td><td>Euro 5.000,-</td></tr>
</table> 
<?php if(date_format($date_anlage, 'm') <> '12') { ?>
<p><b>Versicherungsbeginn:</b> <?php print date("m.d.Y",mktime(0, 0, 0, 1, date_format($date_anlage, 'm')+1, date_format($date_anlage, 'Y'))); ?><br>
<b>Versicherungsablauf:</b> <?php print date("m.d.Y",mktime(0, 0, 0, 1, date_format($date_anlage, 'm')+1, date_format($date_anlage, 'Y')+1)); ?> – automatische Verlängerung, wenn nicht innerhalb von 1 Monat vor Versicherungsablauf eine schriftliche Kündigung erfolgt.</p>
<?php } else { ?>
<p><b>Versicherungsbeginn:</b> <?php print date("m.d.Y",mktime(0, 0, 0, 1, '01', date_format($date_anlage, 'Y')+1)); ?><br>
<b>Versicherungsablauf:</b> <?php print date("m.d.Y",mktime(0, 0, 0, 1, '01', date_format($date_anlage, 'Y')+2)); ?> – automatische Verlängerung, wenn nicht innerhalb von 1 Monat vor Versicherungsablauf eine schriftliche Kündigung erfolgt.</p>	
<?php } ?>

<h3>Vereinsmitglied = versicherte Person</h3>
<table>
<tr><td><b>Mitgliedsnummer:</b>&nbsp;</td><td><?php print $userdata['KundenID_online']; ?></td></tr>
<tr><td><b>Name:</b> </td><td><?php print $userdata['strTitel_O'] . " " . $userdata['strVName_O'] . " " . $userdata['strNName_O']; ?></td></tr>
<tr><td><b>Geburtsdatum:</b> </td><td><?php print date_format(date_create($userdata['datGeburt_O']), 'd.m.Y'); ?></td></tr>
<tr><td><b>Adresse:</b> </td><td><?php print $userdata['strAnschrift_O'] . ", " . $userdata['strPLZ_O'] . " " . $userdata['strOrt_O'] . ", " . $userdata['strLand_O']; ?></td></tr>
<tr><td><b>Beruf:</b> </td><td><?php print $userdata['strBeruf_O']; ?></td></tr>
</table>
<p><b>Vertragsgrundlagen:</b> Alle ordentlichen Mitglieder des Vereins „angelio Kaufgemeinschaft (ZVR-Zahl: 198313517)“ welche zum Zeitpunkt ihres Unfalls ihren vollen Mitgliedsbeitrag bezahlt haben, sind über einen Rahmenvertrag, der mit der AIG (AIG Europe Limited Direktion für Österreich, Mariahilfer Straße 17, 1060 Wien) abgeschlossen wurde, für das oben genannte Risiko versichert.
Der Versicherungsschutz, alle Rechte und Pflichten sind in den allgemeinen Unfall-Versicherungsbedingungen AUVB 2005 und den besonderen Bedingungen festgelegt.  Zusätzlich gelten die Vereinsstatuten und die besonderen Bedingungen von angelio.</p>

<p>Vorchdorf, am <?php print date_format(date_create($userdata['datAbschluss']), 'd.m.Y'); ?></p>
	
<p>Rudolf Pürimayr, MTD<br>
Vereinsobmann</p>

<p>Anhang:</p>
<p>
- <a href="http://www.angelio.at/downloads/AIG_AUVB_2005_extern.pdf">AUVB 2005 mit Gliedertaxe</a><br>
- <a href="http://www.angelio.at/downloads/AIG_Progressionstabelle.pdf">Progressionstabelle AIG</a><br>
- <a href="http://www.angelio.at/downloads/Datenschutzrichtlinie.pdf">Datenschutzrichtlinie</a></p>

<p><a href="/print/polizze/<?php print $userdata['KundenID_online']; ?>/<?php print $userdata['Polizzennummer_O']; ?>" target="_blank">Druckversion</a>&nbsp;|&nbsp;<a href="/printpdf/polizze/<?php print $userdata['KundenID_online']; ?>/<?php print $userdata['Polizzennummer_O']; ?>" target="_blank">PDF Drucken</a></p>

