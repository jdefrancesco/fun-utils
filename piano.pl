# piano.pl
# By: Joey DeFrancesco 
# Year: 2005
# Needs Audio::Beep, and Term::ReadKey to work..
# Usage: perl piano.pl
#!/usr/bin/perl

use strict;
use Audio::Beep;
use Term::ReadKey;

# Frequencies and notes found on Wikipedia
my($DUR, $freq, $k) = (250, undef, undef);
my @notes = (440, 494, 262, 294, 330, 349, 392);

# need to set cbreak so each keyboard press is read individually and unbuffered
ReadMode 3;

while(($k = ReadKey(0)) ne "\n"){
	if($k =~ /[a-z]/){
		$freq = $notes[ord($k) - ord('a')];
	}elsif($k =~ /[A-Z]/){
		$freq = $notes[ord($k) - ord('A')] * 1.05946;
	}
	print "Key: $k\r";
	beep($freq, $DUR); 
}

# set read mode back to its default setting
ReadMode 0;
exit(0);
#EOF
