#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <getopt.h>
#include <sys/stat.h>

#include "bitsmode.h"

#define VERSION "0.01"

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
    fputs("Usage: rmdir [OPTION(S)] OCTAL-MODE FILE\n\n"
    "OPTIONS:\n"
	"  -v, --verbose      print a message for every touched FILE\n"
    "    --help           print this message and exit\n"
    "    --version        print version and exit\n", stdout);

    exit(EXIT_SUCCESS);
}


static void print_version()
{
    printf("chmod %s\n", VERSION);
    printf("Written by Constantinos Georgiades\n");
    exit(EXIT_SUCCESS);
}


int
main(int argc, char *argv[])
{
    int c;
    int option_index = 0;
    int status;
    int temp_val;
    bool fverbose = false;
    char *s_mode;
    mode_t o_mode;
    
    
    while((c = getopt_long(argc, argv, "v", long_options, &option_index)) != -1) {
		
		switch(c)
		{
			case 1:
				usage();
				break;
				
			case 2:
				print_version();
				break;
				
			case 'v':
				fverbose = true;
				break;
				
			case '?':
                printf("See rmdir --help for more info\n");
				exit(EXIT_FAILURE);
				break;
				
            default:
                abort();
		}
	}
	

	if (optind == argc) {
		printf("Missing operand\n");
		printf("See chmod --help for more info\n");
		exit(EXIT_FAILURE);
	}
	
	s_mode = argv[optind++]; // get mode from arguments
	
	/*turn off system umask and convert user mode to octal bits*/
	o_mode = turn_off_umask();
	
	o_mode = str_to_octals(s_mode);
	if (o_mode == EXCEEDED_ERROR || o_mode == DIGITS_ERROR || o_mode == RANGE_ERROR) {
		fprintf(stderr, "chmod: invalid mode\n");
		exit(EXIT_FAILURE);
	}
	
	while (optind != argc) {
	
		temp_val = optind++;
	
		status = chmod(argv[temp_val], o_mode);
		if (status == -1) {
			perror("chmod");
			exit(EXIT_FAILURE);
		}
		if (status == 0 && fverbose) {
			printf("chmod: '%s', mode: '%s'\n", argv[temp_val], s_mode);
		}
	
	}
    
    return 0;
    
}


