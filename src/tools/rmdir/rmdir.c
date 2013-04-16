#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <unistd.h>
#include <getopt.h>

#include "pathr.h"

#define VERSION "0.01"


static struct option long_options[] = 
{
    {"help", no_argument, NULL, 1},
    {"version", no_argument, NULL, 2},
    {"verbose", no_argument, NULL, 'v'},
    {"parents", no_argument, NULL, 'p'},
    {0, 0, 0, 0}
};


static void
usage()
{
    fputs("Usage: rmdir [OPTION(S)] [DIRECTORY]\n\n"
    "OPTIONS:\n"
    "  -v, --verbose      print a message for every created directory\n"
    "  -p, --parents      remove DIRECTORY and its parents\n"
    "    --help           print this message and exit\n"
    "    --version        print version and exit\n", stdout);

    exit(EXIT_SUCCESS);
}


static void print_version()
{
    printf("rmdir %s\n", VERSION);
    printf("Written by Constantinos Georgiades\n");
}


int
main(int argc, char *argv[])
{
    int c;
    int option_index = 0;
    int temp_val;
    int status;
    bool fverbose = false;
    bool fparents = false;
    char *temp_path;


    while ((c = getopt_long(argc, argv, "vp", long_options, &option_index)) != -1) {

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
				
			case 'p':
				fparents = true;
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
		printf("See rmdir --help for more info\n");
		exit(EXIT_FAILURE);
	}
	
	
	if (fparents) {
		
		while (optind != argc) {
			
			temp_val = optind++;
			
			initPathR(argv[temp_val]);
			while ((temp_path = pathR()) != NULL) {
				
				status = rmdir(temp_path);
				if (status == 0 && fverbose) {
					printf("rmdir: directory was removed '%s'\n", temp_path);
				}
				
			}
			
		}
	} else {
	
		while (optind != argc) {
			
			temp_val = optind++;
			
			status = rmdir(argv[temp_val]);
			if (status == -1) {
				perror("rmdir");
				exit(EXIT_FAILURE);
			}
			if (status == 0 && fverbose) {
				printf("rmdir: directory was removed '%s'\n", argv[temp_val]);
			}
			
		}
	}	
	
	return 0;
	
}



