#include <string.h> 
#include <stdlib.h>
#include <stdbool.h>

#include <unistd.h>

#include "pathr.h"

#define BUF _PC_PATH_MAX

static char *tpath;
static bool flag = false;

int
initPathR(const char *path)
{
	
	if (path == NULL)
		return EMPTYSTRING;
	
	tpath = malloc(BUF);
	strncpy(tpath, path, BUF);
	
	flag = true;

    return 0;
	
}


char*
pathR(const char *path)
{
	static char *spath;
	static char *pch;
	int ma;
	
	if (flag) {
		spath = tpath;
		flag = false;
		return tpath;
	} else {
		pch = strrchr(tpath, '/');
		if (pch == NULL) {
			free(spath);
			return NULL;
		}
		
		ma = pch - spath;
		tpath[ma] = 0;

		return tpath;
	}
		
}
