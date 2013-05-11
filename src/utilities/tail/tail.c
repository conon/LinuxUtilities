#include <stdio.h>
#include <stdlib.h>

#include <getopt.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define VERSION "0.0.1"
#define POS -10

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


static void print_version()
{
    printf("tail %s\n", VERSION);
    printf("Written by Constantinos Georgiades\n");
    exit(EXIT_SUCCESS);
}


int
main(int argc, char *argv[])
{
	
	int c, i;
	int status;
    int option_index = 0;
    int fds[_SC_OPEN_MAX];
    off_t offset;
	
	while( (c = getopt_long(argc, argv, "a", long_options, &option_index)) != -1) {

		switch(c)
		{
			case 1:
				usage();
				break;
				
			case 2:
				print_version();
				break;
				
			case '?':
				printf("See tail --help for more info\n");
				exit(EXIT_FAILURE);
				break;
				
			default:
				abort();
		}
	}
	
	
	if (optind == argc) {
		/*read from stdin*/
	}
	
	for(i = 0; optind != argc; optind++, i++) {
		
		fds[i] = open(argv[optind], O_RDWR | O_CREAT, S_IRWXU | S_IRWXG | S_IRWXO);
		if (fds[i] == -1) {
			perror("open ");
			exit(EXIT_FAILURE);
		}
		
		/*first check if file is empty or has less than 10 bytes, if it has procceed,
		 *else minus 10 the offset and then procceed*/
		
		offset = lseek(fds[i], 0, SEEK_END);
		if (offset == -1) {
			perror("lseek ");
			exit(EXIT_FAILURE);
		}
		if (offset <= 10) {
			/*evaluate*/
		} else {
		
			offset = lseek(fds[i], POS, SEEK_END);
			if (offset == -1) {
				perror("lseek ");
				exit(EXIT_FAILURE);
			}
		}
	}
	
	
	return 0;
}


