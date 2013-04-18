#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <errno.h>

#include <unistd.h>
#include <getopt.h>
#include <pwd.h>
#include <grp.h>

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
	fputs("Usage: chown [OPTION] OWNER[:[GROUP]] FILE\n\n"
	"OPTIONS:\n"
	"  -v, --verbose      print a message for every created directory\n"
	"    --help           print this message and exit\n"
	"    --version        print version and exit\n", stdout);

	exit(EXIT_SUCCESS);
}


static void
print_version()
{
	printf("chown %s\n", VERSION);
	printf("Written by Constantinos Georgiades\n");
	exit(EXIT_SUCCESS);
}


int
main(int argc, char *argv[])
{
    int c;
    int option_index = 0;
    int status;
    bool fverbose = false;
    char *owgr, *pch;
    char *end;
    char *temp_path;
    struct passwd *pwd_st;
    struct group *grp_st;
    uid_t own;
    gid_t grp;
    
    
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
				printf("See chown --help for more info\n");
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
	
	owgr = argv[optind++];
	
	/**
	 * At first search if field has ':', if it has that mean that probably a 
	 * new group requested,
	 * */
	
	pch = strchr(owgr, ':');
	if (pch != NULL) {
		
		/* for owner*/
		pch = strtok(owgr, ":");
		if (strlen(pch) > _SC_LOGIN_NAME_MAX-1) {
			fprintf(stderr, "owner name is longer than system can handle\n");
			exit(EXIT_FAILURE);
		}
		/** 
		 * Try to convert owner(and group) argument to integer(uid), if conversion 
		 * wasnt made try getting uid from name with getpwnam(). 
		 * Set errno to zero, if getownam() return a NULL value and errno 
		 * is still 0 that means that the owner doesnt exist else if getownam() 
		 * return a NULL and errno isnt zero that means tha getownnam() failed .
		 * */
		
		own = strtol(pch, &end, 10); 
		 
		if (end != NULL) {
			errno = 0;
			pwd_st = getpwnam(pch);
			if (pwd_st == NULL) {
				if (errno == 0) {
					fprintf(stderr, "chown: owner requested does not exists\n");
					exit(EXIT_FAILURE);
				} else {
					perror("getpwnam ");
					exit(EXIT_FAILURE);
				}
			}
			
			own = pwd_st->pw_uid;
		}
		
		
		/*for group*/
		pch = strtok(NULL, ":");
		if (pch != NULL) {
			
			if (strlen(pch) > _SC_GETGR_R_SIZE_MAX-1) {
				fprintf(stderr, "group name is longer than system can handle\n");
				exit(EXIT_FAILURE);
			}
			
			grp = strtol(pch, &end, 10);
			if (end != NULL) { /*if end equals null means that ':' was alone*/
				errno = 0;
				grp_st = getgrnam(pch);
				if (grp_st == NULL) {
					if (errno == 0) {
						fprintf(stderr, "chown: owner requested does not exists\n");
						exit(EXIT_FAILURE);
					} else {
						perror("getpwnam ");
						exit(EXIT_FAILURE);
					}
				}
				
				grp = grp_st->gr_gid;
			}
		}
		
		while (optind != argc) {
			
			temp_path = argv[optind++];
			
			status = chown(temp_path, own, grp);
			if (status == -1) {
				perror("chown ");
				exit(EXIT_FAILURE);
			}
			if (status == 0 && fverbose) {
				printf("chown: %s -> %s:%s\n", temp_path , owgr, (pch != NULL ? pch : "") );
			}
			
		}
		
	} else {
		/*only owner*/
		if (strlen(owgr) > _SC_LOGIN_NAME_MAX-1) {
			fprintf(stderr, "owner name is longer than system can handle\n");
			exit(EXIT_FAILURE);
		}
		
		own = strtol(owgr, &end, 10);
		if (end != NULL) {
			errno = 0;
			pwd_st = getpwnam(owgr);
			if (pwd_st == NULL) {
				if (errno == 0) {
					fprintf(stderr, "chown: owner requested does not exists\n");
					exit(EXIT_FAILURE);
				} else {
					perror("getpwnam ");
					exit(EXIT_FAILURE);
				}
			}
			
			own = pwd_st->pw_uid;
			
		}
		
		while (optind != argc) {
			
			temp_path = argv[optind++];
			
			status = chown(temp_path, own, -1);
			if (status == -1) {
				perror("chown ");
				exit(EXIT_FAILURE);
			}
			if (status == 0 && fverbose) {
				printf("chown: %s -> %s\n", temp_path , owgr);
			}
			
		}
		
	}
	
	return 0;
	
}
