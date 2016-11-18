//#include "mpi.h"

#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


int usage(char* prog_name)
{
	printf("usage: %s options\n\
		-p number\t\tnumber of openMP threads\
		-n number\t\tnumber of ceils\n\
		-m number\t\tnumber of blocks\n\
		-k number\t\tnumber of parameters in ceil\n\
		-s number\t\tsize of shadow zone\n\
		-c number\t\tcount iterations of computing\n\
		-t file\t\tinput file with grid\n",prog_name);
	return 0;
}


int check_options(int argc, char** argv, int *p, int *n, int *m, int *k, int *s, int *c, int *t, char* input_file)
{
	int opt;

	while((getopt(argc, argv, "p:n:m:k:s:c:t:")) != -1)
	{
		switch(opt)
		{
			case 'p':
				*p = atoi(optarg);
				break;
			case 'n':
				*n = atoi(optarg);
				break;
			case 'm':
				*m = atoi(optarg);
				break;
			case 'k':
				*k = atoi(optarg);
				break;
			case 's':
				*s = atoi(optarg);
				break;
			case 'c':
				*c = atoi(optarg);
				break;
			case 't':
				*t = 1;
				input_file = optarg;
				break;
		}
	}
	/*
	printf("optind=%d\n", optind); 
	
	if (optind >= argc)
	{
		fprintf(stderr, "Expected argument after options\n");
		return -1;
	}
	
	printf("name argument = %s\n", argv[optind]);
	*/
	return 0;
}


int main(int argc, char** argv)
{
	int n = 0;
	int m = 0;
	int k = 0;
	int c = 0; // count iterations
	int s = 0; // shadow zone
	int t = 0; // test mode - 1; computing - 0
	int p = 0; // count openMP threads
	char *i;
	
	if (check_options(argc, argv, n, m, k, s, c, t, i) < 0)
	{
		usage(argv[0]);
		return -1;
	}


	return 0;
}
