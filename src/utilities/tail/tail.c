#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#include <getopt.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


#define TRUE 1
#define FALSE 0
#define VERSION "0.0.1"
#define DEFAULT_POS 10

static struct option long_options[] = 
{
    {"help", no_argument, NULL, 1},
    {"version", no_argument, NULL, 2},
	{"verbose", no_argument, NULL, 'v'},
	{"bytes", required_argument, NULL, 'c'},
	{"lines", required_argument, NULL, 'n'},
    {NULL, 0, NULL, 0}
};


static void
usage()
{
	fputs("Usage: tail  [OPTION] [FILE]\n\n"
	"OPTIONS:\n"
	"  -v, --verbose		print a message for every created directory\n"
	"  -c  --bytes=[number of bytes]      print the last bytes. Use c [number of bytes]"
	"  -n  --lines=[number of lines]	  print the last lines, Use n [number of bytes]"
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
read_bytes(int fd, int bytes_num)
{
    ssize_t bytes_read, bytes_written;
	off_t offset;
	int neg_num, size;
	size_t len;
	char *buf, *buf_temp, *temp;
	
	if (fd == STDIN_FILENO) {
		
		/*temporary storage*/
		buf_temp = malloc(sizeof(char) * BUFSIZ + sizeof(char));
		if (buf_temp == NULL) {
			perror("malloc");
			exit(EXIT_FAILURE);
		}
		
		/*the buffer for data to be stored*/
		buf = malloc(sizeof(char) * BUFSIZ + sizeof(char));
		if (buf == NULL) {
			perror("malloc");
			exit(EXIT_FAILURE);
		}
		
		size = BUFSIZ;
		
		while(1) {
			bytes_read = read(fd, buf_temp, size);
			if (bytes_read == -1) {
				perror("read");
				exit(EXIT_FAILURE);
			}
			if (bytes_read == 0)
				break;
				
			buf_temp[bytes_read] = '\0';
			
			
			strncat(buf, buf_temp, bytes_read);
		
			if (bytes_read == BUFSIZ) { /* reallocate */
				size += BUFSIZ;
				temp = realloc(buf, size + sizeof(char));
				if (temp == NULL) {
					perror("realloc");
					free(buf);
					exit(EXIT_FAILURE);
				}
				buf = temp;
			}
		}
		
		free(buf_temp);
		
		temp = buf;
		
		len = strlen(buf) - bytes_num; /* point to the last bytes */
		
		buf += len;
	
	} else {
		
		buf = malloc(sizeof(char) * bytes_num);
		if (buf == NULL) {
			perror("malloc");
			exit(EXIT_FAILURE);
		}
	
		offset = lseek(fd, 0, SEEK_END);
		neg_num = bytes_num * (-1); /* convert it to negative */
	
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
	
		
		bytes_read = read(fd, buf, bytes_num);
		if (bytes_read == -1) {
			perror("read");
			exit(EXIT_FAILURE);
		}
		
	
	}
	
	close(fd);
	
	bytes_written = write(STDOUT_FILENO, buf, bytes_num);
	if (bytes_written == -1) {
		perror("write");
		exit(EXIT_FAILURE);
	}
	if (bytes_written < bytes_num) {
		fprintf(stderr, "Less than requested bytes written\n");
	}
	
	
	if (fd == STDIN_FILENO)
		free(temp);
	else
		free(buf);
	
}


static void
read_lines(int fd, int lines_num)
{
	FILE *pFile;
	char *buf, *buf_temp, *temp;
	size_t num_read;
	int i;
	long int size;
	long int lines = 0;
	long int offset = 0;
	
	pFile = fdopen(fd, "r");
	if (pFile == NULL) {
		perror("fdopen");
		exit(EXIT_FAILURE);
	}
	
	
	if (fd == STDIN_FILENO) {
		
		/*temporary storage*/
		buf_temp = malloc(sizeof(char) * BUFSIZ + sizeof(char));
		if (buf_temp == NULL) {
			perror("malloc");
			exit(EXIT_FAILURE);
		}
		
		/*the buffer for data to be stored*/
		buf = malloc(sizeof(char) * BUFSIZ + sizeof(char));
		if (buf == NULL) {
			perror("malloc");
			exit(EXIT_FAILURE);
		}
		
		size = BUFSIZ;
		
		while(1) {
			num_read = fread(buf_temp, sizeof(char), BUFSIZ, stdin);
			buf_temp[num_read] = '\0';
		
			strncat(buf, buf_temp, num_read);
		
			if (feof(stdin))
				break;
			if (num_read == BUFSIZ) { /* reallocate */
				size += BUFSIZ + sizeof(char);
				temp = realloc(buf, size);
				if (temp == NULL) {
					perror("realloc");
					free(buf);
					exit(EXIT_FAILURE);
				}
				buf = temp;
			}
		}
		
		free(buf_temp);
		
	} else {
	
		fseek(pFile, 0 ,SEEK_END);
		size = ftell(pFile);
		rewind(pFile);
		
		buf = malloc(size);
		if (buf == NULL) {
			perror("malloc");
			exit(EXIT_FAILURE);
		}
		
		num_read = fread(buf, 1, size, pFile);
	
		fclose(pFile);
		
	}
		
	for(i = size-1; i >= 0; i--) {
		if (buf[i] == '\n') {
			lines++;
			if (lines == lines_num + 1) { /* search for +1 to get one more '\n' because we need the data after it*/
				offset = i; /* store current offset */
				break;
			}
		}
	}
	/* lines requested were more than file contained */
	if (lines_num > lines)
		offset = 0;
	
	offset++; /* we do not need the last '\n' only the data after it*/
	
	temp = buf;
	buf = buf + offset;
	
	fputs(buf, stdout);

	free(temp);
	
}


int
main(int argc, char *argv[])
{
	
	int c, i;
    int option_index = 0;
    int fds[_SC_OPEN_MAX];
    int bytes_bool = FALSE;
    int bytes_num;
    int lines_num = DEFAULT_POS;
    
   
	while( (c = getopt_long(argc, argv, "ac:n:", long_options, &option_index)) != -1) {

		switch(c)
		{
			case 1:
				usage();
				break;
				
			case 2:
				print_version();
				break;
				
			case 'c':
				bytes_bool = TRUE;
				bytes_num = atoi(optarg);
				// some catchs when converting to int
				break;
				
			case 'n':
				lines_num = atoi(optarg);
				// some catchs when converting to int
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
		if (bytes_bool)
			read_bytes(STDIN_FILENO, bytes_num);
		else
			read_lines(STDIN_FILENO, lines_num);
	} else {
		/*read from regular files*/
		for(i = 0; optind != argc; optind++, i++) {
		
			fds[i] = open(argv[optind], O_RDONLY);
			if (fds[i] == -1) {
				perror("open ");
				exit(EXIT_FAILURE);
			}
		
			if (bytes_bool)
				read_bytes(fds[i], bytes_num);
			else
				read_lines(fds[i], lines_num);
		}
	}
	
	return 0;
}


