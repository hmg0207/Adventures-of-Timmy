#ifndef KERROR_H
#define KERROR_H

#include <stdio.h>
#include <stdlib.h>

#define KFALSE 0
#define KTRUE  1

static char err_str[256];

#define KERROR(...)     sprintf( err_str, __VA_ARGS__);\
						printf("\nERROR:\n\t%s: %s() - Line %d\n\t%s\n\n", __FILE__, __FUNCTION__, __LINE__, err_str );\
						exit( EXIT_FAILURE );

#define KWARNING(...)	sprintf( err_str, __VA_ARGS__);\
						printf("\nWARNING:\n\t%s: %s() - Line %d\n\t%s\n\n", __FILE__, __FUNCTION__, __LINE__, err_str );


#define KNOTICE(...)	sprintf( err_str, __VA_ARGS__);\
						printf( "NOTICE: %s(): %s\n", __FUNCTION__, err_str );

#endif /* KERROR_H */
												