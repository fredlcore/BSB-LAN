#!/usr/bin/perl

# Run this script after adding entries to a language file to prevent compiler warnings

@files = `ls LANG*.h`;
foreach $file (@files) {
  chomp ($file);
  print "$file\n";
  open (IN, $file);
  open (OUT, ">UNDEF_$file");
  while ($line = <IN>) {
    if (!($line =~ /^\/\//)) {
      if ($line =~ /#define (.*?) /) {
        print OUT "#undef $1\n";
      }
    }
  }
  close IN;
  close OUT;
}
