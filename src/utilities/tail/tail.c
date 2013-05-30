#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#include <getopt.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


#define TRUE 1
#define FALSE 0
#define VERSION "0.0.1"
#define POS -10
#define DEFAULT_POS 10

static struct option long_options[] = 
{
    {"help", no_argument, NULL, 1},
    {"version", no_argument, NULL, 2},
	{"verbose", no_argument, NULL, 'v'},
	{"bytes", required_argument, NULL, 'b'},
    {NULL, 0, NULL, 0}
};


static void
usage()
{
	fputs("Usage: tail  [OPTION] [FILE]\n\n"
	"OPTIONS:\n"
	"  -v, --verbose      print a message for every created directory\n"
	"  -b  --bytes=[number of bytes]      print the last bytes. Use c [number of bytes]"
	"    --help           print this message and exit\n"
	"    --version        print version and exit\n", stdout);

	exit(EXIT_SUCCESS);
}


static void 
print_version()
{
    printf("tail %s\n", VERSION);
    printf("Written by Constantinos Georgiades\n");
    exit(EXIT_SUCCESS);
}


static void
output_bytes(int byts)
{
}


static void
read_bytes(int fd, int bytes_num)
{
    ssize_t bytes_read;
	off_t offset;
	int neg_num;
	char buf[20];
	
	offset = lseek(fd, 0, SEEK_END);
	neg_num = bytes_num * (-1);
	
	if (offset <= bytes_num) {
		offset = lseek(fd, 0, SEEK_SET);
		if (offset == -1) {
			perror("lseek ");
			exit(EXIT_FAILURE);
		}
	} else {
		offset = lseek(fd, neg_num, SEEK_END);
		if (offset == -1) {
			perror("lseek ");
			exit(EXIT_FAILURE);
		}
	}
	
	bytes_read = read(fd, buf, (size_t)offset);
	if (bytes_read == -1) {
		perror("read");
		exit(EXIT_FAILURE);
	}
	buf[bytes_read] = '\0';
	printf("%s", buf);
	
}

int
main(int argc, char *argv[])
{
	
	int c, i;
	int status;
    int option_index = 0;
    int fds[_SC_OPEN_MAX];
    int bytes_bool = FALSE;
    int bytes_num;
    
   
	while( (c = getopt_long(argc, argv, "ab:", long_options, &option_index)) != -1) {

		switch(c)
		{
			case 1:
				usage();
				break;
				
			case 2:
				print_version();
				break;
				
			case 'b':
				bytes_bool = TRUE;
				bytes_num = atoi(optarg);
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
		
		fds[i] = open(argv[optind], O_RDONLY);
		if (fds[i] == -1) {
			perror("open ");
			exit(EXIT_FAILURE);
		}
		
		
		if (bytes_bool)
			read_bytes(fds[i], bytes_num);
		
	}
	
	
	return 0;
}


