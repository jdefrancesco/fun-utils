/* me.c - IRC /me for your command-line if you are lonely and
 * or interested in expressing your emotions to a lifeless 
 * machine.
 * 
 * License: MIT
 * NOTE: If you want to use it without a dot-slash prefix it needs to be
 *     	 in your root directory (/). It is a safe program, but do so
 *       at your own risk.
 * Written : Joey DeFrancesco
 * Year: 2005
 * Usage: /me YOUR_TEXT
 */

#include <stdio.h>
#include <stdlib.h>

void printu(){
	char *uname;

	/* Get username for printing */
	uname = getenv("USER");
	if(uname == NULL){
		fprintf(stderr, "[!] Error grabbing $USER environment variable. Is it set?\n");
		exit(1);
	}
	
	/* Blueish star, green username, white output text */
	printf("\x1b\x5b\x33\x33\x6d* \x1b\x5b\x33\x32\x6d%s\x1b\x5b\x33\x39\x6d ", uname);
}

int main(int argc, char **argv){

	int i = 1;
	
	if(argc < 2)
		goto out;

	/* Output user name */
	printu();
	/* Display arguments */
	for(; i < argc; i++)
		printf("%s ", argv[i]);

	puts("");
	return 0;

	/* If we get here something didn't go so smooth */ 
	out:
	printu();
	puts("");
	exit(1);
}
	
