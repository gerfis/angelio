<?php

define('NUMERAL_SIGN', 'minus');
define('NUMERAL_HUNDREDS_SUFFIX', 'hundert');
define('NUMERAL_TENNER_SUFFIX', 'zig');
define('NUMERAL_INFIX', 'und');

function num2text($number) {
 global $numeral;

 $prefix = '';
 if ($number == 0) return $numeral[0]; // null
 if ($number < 0) $prefix = NUMERAL_SIGN . ' '; // minus …
 return $prefix . num2text_group(abs($number));
}


function num2text_group($number, $group_level = 0) {
$numeral = array('null', 'ein', 'zwei', 'drei', 'vier',
                  'fünf', 'sechs', 'sieben', 'acht', 'neun',
                  'zehn', 'elf', 'zwölf', 'drei~', 'vier~',
                  'fünf~', 'sech~', 'sieb~', 'acht~', 'neun~');
$tenner = array('', '', 'zwan~', 'dreißig', 'vier~',
                'fünf~', 'sech~', 'sieb~', 'acht~', 'neun~');

$group_suffix[0][0] = '';
$group_suffix[0][1] = '';
$group_suffix[1][0] = 'tausend ';
$group_suffix[1][1] = 'tausend ';
$group_suffix[2][0] = 'e Million ';
$group_suffix[2][1] = ' Millionen ';
$group_suffix[3][0] = 'e Milliarde ';
$group_suffix[3][1] = ' Milliarden ';
 

 // Ende der Rekursion erreicht, wenn Zahl gleich Null
 if ($number == 0) return '';

 // Zahlengruppe dieser Runde bestimmen
 $group_number = $number % 1000;


 if ($group_number == 1) {

  // Zahl der Gruppe ist Eins
  $res = $numeral[1] . $group_suffix[$group_level][0]; // eine Milliarde

 } elseif ($group_number > 1) {

  // Zahlwort der Hunderter
  $fst_digit = floor($group_number / 100);
  if ($fst_digit) $res = $numeral[$fst_digit] . NUMERAL_HUNDREDS_SUFFIX; // fünfhundert

  // Zahlwort der Zehner und Einer
  $lst_digits = $group_number % 100;
  $snd_digit = floor($lst_digits / 10);
  $trd_digit = $lst_digits % 10;

  if ($lst_digits == 0) $res .= ''; // null
  elseif ($lst_digits == 1) $res .= $numeral[1] . 's'; // eins
  elseif ($lst_digits <= 19) $res .= str_replace('~', $numeral[10], $numeral[$lst_digits]); // dreizehn
  else {
   if ($trd_digit) $res .= $numeral[$trd_digit] . NUMERAL_INFIX; // sechsund…
   $res .= str_replace('~', NUMERAL_TENNER_SUFFIX, $tenner[$snd_digit]); // (…)achtzig
  }

  // Suffix anhängen
  $res .= $group_suffix[$group_level][1]; // Millionen
 }

 // Nächste Gruppe auswerten und Zahlwort zurückgeben
 $number = floor($number / 1000);
 $group_level++;

 return num2text_group($number, $group_level) . $res;
}

?>