/**
 * This is path handler currently used only for rmdir.
 * It will return the path from right to left separated by '/'.
 * For example if "/abc/../po/.lk" is supplied pathR will return
 * /abc/../po/.lk -> /abc/../po/ -> /abc/../ -> /abc/ 
 * */

#ifndef PATHR_H
#define PATHR_H

#define EMPTYSTRING 1

/**
 * Initialize path handler.
 * 
 * @param path			the path to proccess
 * @return 				EMPTYSTRING ( 1 ) if path supplied was empty
 * @return				0 if initialization was successful
 * */
int initPathR(const char *path);


/**
 * Retrieve a substring by '/' field of path each time
 * 
 * @return			a field of the passed path (NULL if paths's fields are exhausted) 
 * */
char* pathR();



#endif
