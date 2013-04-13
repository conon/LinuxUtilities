/**
 * This is a path handler currently used only for mkdir.
 * It will return path slipted by '/' from left to right 
 * ignoring dots and double dots. 
 * 
 * For example if you pass "/abc/../po/.lk" it will return 
 * /abc/ -> /abc/../po -> /abc/../po/.lk
 * */

#ifndef PATHL_H
#define PATHL_H

#define EMPTYSTRING 1

 
/**
 * Initialize path handler.
 * 
 * @param path			the path to proccess
 * @return				EMPTYSTRING ( 1 ) if path passed was empty
 * @return				0 if initPathL was initialized succesfully
 * */
int initPathL(const char *path);



/**
 * Retrieve a slited by '/' field of path each time
 * 
 * @return			a field of the passed path (NULL if paths's fields are exhausted)
 * */
char* pathL();

#endif
