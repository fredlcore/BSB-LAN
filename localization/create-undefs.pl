#!/usr/bin/perl
# Run this script after adding entries to a language file to prevent compiler warnings
use bytes;

# Extract the variable size of buffer via BUFLEN from BSB_lan.ino
# Can probably be written shorter/nicer/more effective?
@Ino = `cat ../BSB_lan.ino`;
@size = grep(/#define BUFLEN /, @Ino);
$size[0] =~ /#define BUFLEN (.*)/;
$size = $1-1;

# Create LANG_C.h: language-independed definitions, based on German language
$file = "LANG_DE.h";
chomp($file);
open(IN, $file );
open(OUT, ">LANG_C.h" );
while ($line = <IN>) {
  if (!($line =~ /^\/\//)) {
    if ($line =~ /#define (.*?) /) {
      $stringname = $1;
      $stringname1 = $1;
#     $stringname1 =~ s/_TEXT/_TXT/; # Save ~3 kB. Do not to change without discussion, please, because "_TEXT" used as marker in external interface.
      print OUT "#define $stringname \"$stringname1\"\n";
    } else {
      print OUT "$line";
    }
  } else {
    print OUT "$line";
  }
}
close IN;
close OUT;

# Create UNDEF files
@files = `ls LANG*.h`;
foreach $file (@files) {
  chomp ($file);
  print "$file\n";
  open (IN, $file);
  open (OUT, ">UNDEF_$file");
  while ($line = <IN>) {
    if (!($line =~ /^\/\//)) {
      if ($line =~ /#define (.*?) /) {
        $stringname = $1;
        print OUT "#undef $stringname\n";
        my @def =  ($line =~ /\"(.*?)\"/g);
        $defstrlen = length($def[0]);
        if($defstrlen > $size) {print "$file WARNING: string length $stringname too big: $defstrlen bytes.\n";}
      }
    }
  }
  close IN;
  close OUT;
}

# Create JavaScript language files for Web-AJAX infterface in www subdir.
@files = `ls LANG*.h`;
open(LANGLIST, ">www/languages.js");
print LANGLIST "//From https://en.wikipedia.org/wiki/List_of_ISO_639-1_codes\n";
foreach $file (@files) {
  chomp($file);
  $languageNameFound = 0;
  if ($file ne "LANG_C.h") {
    open(IN, $file);
    my @file1 = ((lc $file) =~ /(.*?)\.h/g);
    print "$file1[0].js\n";
    open(OUT, ">www/$file1[0].js");
    while ($line = <IN>) {
      if (!($line =~ /^\/\//)) {
        if ($line =~ /#define (.*?) \"(.*?)\"/) {
          $stringname = $1;
          print OUT "UIStrings[\"$stringname\"] = \"$2\";\n";
          if (!$languageNameFound && ($stringname eq "LANGUAGENAME_TEXT")) {
            $languageNameFound = 1;
            $langName = $2;
            @langname = ((lc $file) =~ /lang_(.*?)\.h/g);
            print LANGLIST "langList[\"$langname[0]\"] = \"$langName\";\n";
          }
        } else {
          print OUT "$line";
        }
      } else {
        print OUT "$line";
      }
    }
    if (!$languageNameFound) {
      @langname = ((lc $file) =~ /lang_(.*?)\.h/g);
      print LANGLIST "langList[\"$langname[0]\"] = \"$langname[0]\";\n";
    }
    close IN;
    close OUT;
    system ("gzip -n -9 -k -N -f www/${file1[0]}.js");
    if ( $? != 0 ) {print "Can't gzip file ${file1[0]}.js\n";}
  }
}
close LANGLIST;
