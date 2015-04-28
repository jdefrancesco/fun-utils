/* penistime.c
 * Desc: ASCII penis grows as uptime becomes longer
 * Written By: Joey, and dlab - modifications
 */
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


static void die(char *str)
{
	perror(str);
	exit(1);
}


static char *strrep(char ch, int len)
{
	static char foo[2][100];
	static int bar = 0;


	if(bar == 2)
		bar = 0;

	if(len > (int)sizeof(foo[0]) - 1)
		len = (int)sizeof(foo[0]) - 1;

	memset(foo[bar], ch, len);
	foo[bar][len] = 0;

	return foo[bar++];
}


static int parse_uptime_days(const char *str)
{
	char *up, *s;


	up = strstr(str, " up ");
	if(up == NULL)
	{
		fprintf(stderr, "parse_uptime_days() failed on str: %s\n", str);
		return 0;
	}

	up += 4;
	while(*up == ' ') up++;

	s = up;

	while(*s >= '0' && *s <= '9') s++;

	if(*s != ' ')
		return 0;

	while(*s == ' ') s++;

	if(strncmp(s, "day", 3) != 0)
		return 0;

	return atoi(up);
}


static char *get_uptime_str(void)
{
	static char buf[128];
	FILE *fd;


	setenv("LC_ALL", "C", 1);
	setenv("LANG", "C", 1);
	setenv("LANGUAGE", "C", 1);

	fd = popen("uptime", "r");
	if(fd == NULL)
		die("fopen");

	if(!fgets(buf, sizeof(buf), fd))
		die("fgets");

	fclose(fd);

	if(strlen(buf) == 0)
		die("strlen == 0");

	if(buf[strlen(buf) - 1] == '\n')
		buf[strlen(buf) - 1] = 0;

	return buf;
}


int main(void)
{
	int penis_length;
	int penis_thickness = 0;
	int n;
	char *uptime_str;


	/* exec /bin/uptime and return the first line */
	uptime_str = get_uptime_str();

	/* left trim spaces */
	while(*uptime_str == ' ')
		uptime_str++;

	/* calculate penis length based on uptime */
	penis_length = parse_uptime_days(uptime_str);

	if(penis_length > 7)
	{
		penis_length /= 28;
		penis_thickness = 1;
	}

	/* print head */
	if(penis_thickness > 0)
	{
		printf("%s%s\n",
			strrep(' ', penis_length + 2),
			strrep('_', penis_thickness)
			);
	}
	if(penis_length > 0)
	{
		printf("%s/%s)\n",
			strrep(' ', penis_length + 1),
			strrep(' ', penis_thickness)
			);
	}
	else
	{
		printf(" /%s)_ %s\n",
			strrep(' ', penis_thickness),
			uptime_str
			);
	}

	/* print shaft */
	for(n=0; n<penis_length; n++)
	{
		char *space = strrep(' ', penis_length - n);
		char *thick = strrep(' ', penis_thickness);

		if(n == penis_length - 1)
		{
			printf("%s/%s/_ %s\n", space, thick, uptime_str);
		}
		else
		{
			printf("%s/%s/\n", space, thick);
		}
	}
	/* print balls */
	printf("(%s)_)\n",
		strrep('_', penis_thickness + 1)
		);


	return 0;
}
