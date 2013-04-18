#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <getopt.h>

static struct option long_options[] = 
{
    {"help", no_argument, NULL, 1},
    {"version", no_argument, NULL, 2},
	{"verbose", no_argument, NULL, 'v'},
    {NULL, 0, NULL, 0}
};


static void
usage()
{
	fputs("Usage: tail  [OPTION] [FILE]\n\n"
	"OPTIONS:\n"
	"  -v, --verbose      print a message for every created directory\n"
	"    --help           print this message and exit\n"
	"    --version        print version and exit\n", stdout);

	exit(EXIT_SUCCESS);
}
