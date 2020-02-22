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
open( IN,   $file );
open( OUT, ">LANG_C.h" );
while ( $line = <IN> ) {
    if ( !( $line =~ /^\/\// ) ) {
        if ( $line =~ /#define (.*?) / ) {
            $stringname = $1;
            $stringname1 = $1;
#            $stringname1 =~ s/_TEXT/_TXT/; # Save ~3 kB. Do not to change without discussion, please, because "_TEXT" used as marker in external interface.
            print OUT "#define $stringname \"$stringname1\"\n";
        }
        else {
            print OUT "$line";
        }
    }
    else {
        print OUT "$line";
    }
}
close IN;
close OUT;

#create UNDEF files
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
