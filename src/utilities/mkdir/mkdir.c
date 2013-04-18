#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <getopt.h>
#include <sys/stat.h>
#include <sys/types.h>

#include "bitsmode.h"
#include "pathl.h"

#define VERSION "0.01"

static struct option long_options[] = 
{
    {"help", no_argument, NULL, 1},
    {"version", no_argument, NULL, 2},
	{"verbose", no_argument, NULL, 'v'},
	{"parent", no_argument, NULL, 'p'},
	{"mode", required_argument, NULL, 'm'},
    {NULL, 0, NULL, 0}
};


static void
usage()
{
	fputs("Usage: mkdir [OPTION(S)] [DIRECTORY(IES)]\n\n"
	"OPTIONS:\n"
	"  -v, --verbose      print a message for every created directory\n"
	"  -m, --mode         set file mode(only octal representation)\n"
	"  -p, --parents      make parents directories, no errors on existing directories\n"
	"    --help           print this message and exit\n"
	"    --version        print version and exit\n", stdout);

	exit(EXIT_SUCCESS);
}


static void
print_version()
{
	printf("mkdir %s\n", VERSION);
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
    bool fparent = false;
    bool fverbose = false;
    char *temp_path;
    char *s_mode = NULL;
    mode_t o_mode;
    
    while((c = getopt_long(argc, argv, "pvm:", long_options, &option_index)) != -1) {
    
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
				
			case 'm':
				s_mode = optarg;
				break;
			
			case 'p':
				fparent = true;
				break;
			
			case '?':
				printf("See mkdir --help for more info\n");
				exit(EXIT_FAILURE);
				break;
				
			default:
				abort();

		}
	}
		
		
	if (optind == argc) {
		printf("Missing operand\n");
		printf("See mkdir --help for more info\n");
		exit(EXIT_FAILURE);
	}
	
	if (s_mode == NULL) {
		o_mode = S_IRWXU | S_IRWXG | S_IRWXO;
	} else {
		/*turn off system umask and convert user mode to octal bits*/
		o_mode = turn_off_umask();
		
		o_mode = str_to_octals(s_mode);
		if (o_mode == EXCEEDED_ERROR || o_mode == DIGITS_ERROR || o_mode == RANGE_ERROR) {
			fprintf(stderr, "mkdir: invalid mode\n");
			exit(EXIT_FAILURE);
		}
		
	}

	if (fparent) {
		while (optind != argc) {
			
			temp_val = optind++;
			
			initPathL(argv[temp_val]);
			while ((temp_path = pathL()) != NULL) {
				
				status = mkdir(temp_path, o_mode);
				if (status == 0 && fverbose) {
					printf("mkdir: directory was created '%s'\n", temp_path);
				}
				
			}
			
		}
	} else {
		while (optind != argc) {
			
			temp_val = optind++;
			
			status = mkdir(argv[temp_val], o_mode);
			if (status == -1 && fverbose) {
				printf("mkdir: directory exists '%s'\n", argv[temp_val]);
				continue;
			}
			if (status == -1) {
				perror("mkdir: ");
				exit(EXIT_FAILURE);
			}
			if (status == 0 && fverbose) {
				printf("mkdir: directory was created '%s'\n", argv[temp_val]);
			}
			
		}
	}

	return 0;
}
