#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#include <unistd.h>
#include <getopt.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


#define VERSION "0.01"
#define TRUE 1
#define FALSE 0

static struct option long_options[] = 
{
    {"help", no_argument, NULL, 1},
    {"version", no_argument, NULL, 2},
    {"append", no_argument, NULL, 'a'},
    {NULL, 0, NULL, 0}
};


static void
usage()
{
    fputs("Usage: tee [OPTION(S)]  [FILE] \n\n"
    "OPTIONS:\n"
    "-a, --append         append to the given FILEs, do not overwrite\n"
    "    --help           print this message and exit\n"
    "    --version        print version and exit\n", stdout);

    exit(EXIT_SUCCESS);
}


static void print_version()
{
    printf("tee %s\n", VERSION);
    printf("Written by Constantinos Georgiades\n");
    exit(EXIT_SUCCESS);
}


int
main(int argc, char *argv[])
{
	int c, i;
    int status;
    int option_index = 0;
    int append = FALSE;
    int cl, fd, numRead, numWritten;
    int fds[_SC_OPEN_MAX]; //defined in unistd.h
    char buf[BUFSIZ]; // defined in stdio.h
    
    while( (c = getopt_long(argc, argv, "a", long_options, &option_index)) != -1) {

	switch(c)
	{
			case 1:
				usage();
				break;
				
			case 2:
				print_version();
				break;
				
			case 'a':
				append = TRUE;
				break;
				
			case '?':
                printf("See tee --help for more info\n");
				exit(EXIT_FAILURE);
				break;
				
            default:
                abort();
		}
	}
	
	// open requested files, if no files are specified fds first element will be
	// assigned to -1 
	if (append) {
		for(i = 0; optind != argc; optind++, i++) {
			fds[i] = open(argv[optind],  O_RDWR | O_CREAT | O_APPEND, S_IRWXU | 
			S_IRWXG | S_IRWXO);
			if (fds[i] == -1) {
				perror("open ");
				exit(EXIT_FAILURE);
			}
		}
		
	} else {
		for(i = 0; optind != argc; optind++, i++) {
			fds[i] = open(argv[optind],  O_RDWR | O_CREAT | O_EXCL, S_IRWXU | 
			S_IRWXG | S_IRWXO);
			if (fds[i] == -1) {
				perror("open ");
				exit(EXIT_FAILURE);
			}
		}
	}
	fds[i] = -1;
	
	
	while(1) {
		
		// read from standard input
		numRead = read(STDIN_FILENO, buf, BUFSIZ);
		if (numRead == -1) {
			perror("read ");
			exit(EXIT_FAILURE);
		}
		buf[numRead] = '\0';
		
		// write to files if requested
		for(i = 0; fds[i] != -1; i++) {
			numWritten = write(fds[i], buf, numRead);
			if (numWritten == -1) {
				perror("write ");
				exit(EXIT_FAILURE);
			}
		}
		
		// write to standard output
		numWritten = write(STDOUT_FILENO, buf, numRead);
		if (numWritten == -1) {
			perror("write ");
			exit(EXIT_FAILURE);
		}
		
	}
	
	// it will never execute
	for(i = 0; fds[i] != -1; i++) {
		cl = close(fds[i]);
		if (cl == -1) {
			perror("close ");
			exit(EXIT_FAILURE);
		}
	}
	
	return 0;
    
}



