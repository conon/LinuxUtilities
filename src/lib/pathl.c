#include <string.h>
#include <stdlib.h>

#include "pathl.h"

#define	BUF 4096

static char *pch;

int
initPathL(const char *path)
{
	char *tpath;
	
	if (path == NULL)
		return EMPTYSTRING;
	
	tpath = malloc(BUF);
	strncpy(tpath, path, BUF);
	pch = strtok (tpath, "/");
	free(tpath);

    return 0;
	
}

char*
pathL()
{
	static char re[BUF];
	
	while (pch != NULL) {
		
		if (strcmp(pch, ".") == 0) {
			strcat(re, "./");
		} else if (strcmp(pch, "..") == 0) {
			strcat(re, "../");
		} else {
			strncat(re, pch, strlen(pch));
			strcat(re, "/");
			break;
		}
		
		pch = strtok(NULL, "/");
    }
    
    if (pch == NULL)
		return NULL;

    pch = strtok(NULL, "/");

    return re;
}
