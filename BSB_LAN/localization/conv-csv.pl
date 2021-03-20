#!/usr/bin/perl

# After use, please change back to chmod 644 to prevent unintentional overwriting!

@skip = (501, 521, 541, 561, 642, 643, 5978, 6800, 6803, 6805, 6806, 6810, 6813, 6815, 6816, 6820);
@categories = ("00", "03", "04", "05", "06", "08", "09", "0b", "0d", "0f", "13", "19", "1b", "1c", "1d", "1e", "1f", "20", "21", "24", "26", "27", "28", "-1", "-1"); 

@files = `ls LANG_*.csv`;
foreach $file (@files) {
  $file =~ /LANG_(..).csv/;
  $lang = $1;
  open (OUT, ">LANG_$lang.h");
  print "$lang - $file\n";
  $cat = 0;
  $cat_text = "";
  $param_text = "";
  open (CSV, $file);
  while ($line = <CSV>) {
    ($param_no, $desc, $p3, $p4, $p5) = split(";", $line);
    if ($param_no ge " " && $desc eq "" && $p3 eq "" && $p4 eq "" && $p5 eq "") {
      if ($categories[$cat] >= 0) {
        $cat_text .= "#define ENUM_CAT_$categories[$cat]_TEXT \"$param_no\"\n";
      }
      $cat++;
    }  
    $skip_this = 0;
    for ($x=0; $x<scalar(@skip); $x++) {
      if ($param_no == $skip[$x]) {
        $skip_this = 1;
      }
    }
    if ($skip_this == 1) {
      next;
    }
    if ($param_no =~ /^\d+$/) {
      $param_text .= "#define STR$param_no\_TEXT \"$desc\"\n";
    }
  }
  print OUT $cat_text . $param_text;
  close OUT;
  close CSV;
}
