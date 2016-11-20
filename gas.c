//#include "mpi.h"

#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>

#include <map>
#include <vector>

using namespace std;

int usage(char*);
int parse_args(int, char**, int *, int *, int *, int *, int *, int *, int *, char*);
int check_options(int, int, int, int, int, int, int, char*);

int generate_data();
int read_test_file(char*);

int main(int argc, char** argv)
{
	int p = 0; // count openMP threads
	int n = 0; // ceils count
	int m = 0; // blocks count
	int k = 0; // parameters count
	int c = 0; // count iterations
	int s = 0; // shadow zone
	int t = 0; // test mode - 1; computing - 0
	char *test_file;
	
	if (parse_args(argc, argv, &p, &n, &m, &k, &s, &c, &t, test_file) < 0 || 
		check_options(p, n, m, k, s, c, t, test_file) < 0)
	{
		usage(argv[0]);
		return -1;
	}
	
	map<int, vector < vector < vector < vector <double> > > > > blocks();
	
	if (t == 1)
		read_test_file(test_file);
	else
		generate_data();
	
	return 0;
}


int usage(char* prog_name)
{
	printf("usage: %s options\n\
		-p number\t\tnumber of openMP threads\n\
		-n number\t\tnumber of ceils\n\
		-m number\t\tnumber of blocks\n\
		-k number\t\tnumber of parameters in ceil\n\
		-s number\t\tsize of shadow zone\n\
		-c number\t\tcount iterations of computing\n\
		-t filename\t\tinput file with grid\n", prog_name);
	return 0;
}


int parse_args(int argc, char** argv, int *p, int *n, int *m, int *k, int *s, int *c, int *t, char* input_file)
{
	int opt;
	unsigned int check(0);

	while((opt = getopt(argc, argv, "p:n:m:k:s:c:t:")) != -1)
	{
		switch(opt)
		{
			case 'p':
				check += (1 << 0);
				*p = atoi(optarg);
				break;
			case 'n':
				check += (1 << 1);
				*n = atoi(optarg);
				break;
			case 'm':
				check += (1 << 2);
				*m = atoi(optarg);
				break;
			case 'k':
				check += (1 << 3);
				*k = atoi(optarg);
				break;
			case 's':
				check += (1 << 4);
				*s = atoi(optarg);
				break;
			case 'c':
				check += (1 << 5);
				*c = atoi(optarg);
				break;
			case 't':
				*t = 1;
				input_file = optarg;
				break;
		}
	}
	
	if (optind < argc)
	{
		//fprintf(stderr, "Expected argument after options\n");
		return -1;
	}
	
	if (check < pow(2, 5) - 1)
		return -1;
	
	return 0;
}

int check_options(int p, int n, int m, int k, int s, int c, int t, char* input_file)
{
	double fractpart(0), intpart(0);
	int i;
	
	fractpart = modf(cbrt(n), &intpart);
	if (fractpart != 0 || n < 0)
	{
		printf("n - must be a cube of a natural number (n > 0)\n\tExample: 64, 512, etc.\n");
		return -1;
	}
	
	fractpart = modf(cbrt(m), &intpart);
	if (fractpart != 0 || m < 0)
	{
		printf("m - must be a cube of a natural number (m > 0)\n\tFor n = %d m must be in: ", n);
		
		i = 2;
		while(i <= sqrt(n))
		{
			if(n % i == 0)
			{
				fractpart = modf(cbrt(i), &intpart);
				if (fractpart == 0)
					printf("%d ", i);
				
				if (i != (n / i))
				{
					fractpart = modf(cbrt(n / i), &intpart);
					if (fractpart == 0)
						printf("%d ", n / i);
				}
			}
			i++;
		}
		
		return -1;
	}
	
	
	return 0;
}

int read_test_file(char* test_file)
{
	
	
	return 0;
}

int generate_data()
{
	return 0;
}