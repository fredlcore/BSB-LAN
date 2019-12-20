#!/usr/bin/perl
# Run this script after adding entries to a language file to prevent compiler warnings
use bytes;
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
        if($defstrlen > 199) {print "$file WARNING: string length $stringname too big: $defstrlen bytes.\n";}
      }
    }
  }
  close IN;
  close OUT;
}
