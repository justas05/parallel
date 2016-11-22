#include "includes.h"
#include "functions.h"

using namespace std;

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

int parse_args(int argc, char** argv, int *p, int *n, int *m, int *k, int *s, int *c, int *t, char** input_file, char** out_file)
{
	int opt;
	unsigned int check(0);

	while((opt = getopt(argc, argv, "p:n:m:k:s:c:t:o:")) != -1)
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
				*input_file = new char[strlen(optarg)];
				strcpy(*input_file, optarg);
				break;
			case 'o':
				*out_file = new char[strlen(optarg)];
				strcpy(*out_file, optarg);
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

inline bool is_equal(double x, double y)
{
	double epsilon = 0.0000000001;
	return abs(x - y) <= epsilon * abs(x);
}

int check_options(int size, int p, int n, int m, int k, int s, int c, int t, char* input_file)
{
	double fractpart(0), intpart(0);
	int i;
	
	fractpart = modf(cbrt(n), &intpart);
	if (!is_equal(fractpart, 0.0) || n < 0)
	{
		printf("n - must be a cube of a natural number (n > 0)\n\tExample: 64, 512, etc.\n");
		return -1;
	}
	
	fractpart = modf(cbrt(m), &intpart);
	if (!is_equal(fractpart, 0.0) || m < 0)
	{
		printf("m - must be a cube of a natural number (m > 0)\n\tFor n = %d m must be in: ", n);
		
		i = 2;
		while(i <= sqrt(n))
		{
			if(n % i == 0)
			{
				fractpart = modf(cbrt(i), &intpart);
				if (is_equal(fractpart, 0.0))
					printf("%d ", i);
				
				if (i != (n / i))
				{
					fractpart = modf(cbrt(n / i), &intpart);
					if (is_equal(fractpart, 0.0))
						printf("%d ", n / i);
				}
			}
			i++;
		}
		
		printf("\n");
		
		return -1;
	}
	
	if (n % m != 0)
	{
		printf("m must devide n\n");
		return -1;
	}
	
	if ((m % size) != 0)
	{
		printf("np - must devide m (np > 0)\n\tFor m = %d np must be in: ", m);
		
		i = 2;
		while(i <= sqrt(size))
		{
			if(n % i == 0)
			{
				printf("%d ", i);
				
				if (i != (n / i))
					printf("%d ", n / i);
			}
			i++;
		}
		printf("\n");
		
		return -1;
	}
	
	if (p < 0)
	{
		printf("p must be a positive integer (p > 0)\n");
		return -1;
	}
	if (k < 0)
	{
		printf("k must be a positive integer (k > 0)\n");
		return -1;
	}
	if (s < 0)
	{
		printf("s must be a positive integer (0 < s < %f)\n", cbrt(n));
		return -1;
	}
	if (c < 0)
	{
		printf("c must be a positive integer (c > 0)\n");
		return -1;
	}
	
	if (t == 1 && access(input_file, F_OK) < 0)
	{
		printf("File %s doesn't exists\n", input_file);
		return -1;
	}
	
	return 0;
}

int set_size(map<int, vector < vector < vector < vector <double> > > > > *blocks, int n, int m, int k, int size, int rank)
{
	int i(rank * (m / size));
	int block_side(cbrt(n / m));
	
	for (; i < (rank + 1) * (m / size); ++i)
	{
		blocks->insert(pair<int, vector < vector < vector < vector <double> > > > >(i,
			vector < vector < vector < vector <double> > > > (block_side,
						vector < vector < vector <double> > > (block_side,
									vector < vector <double> >(block_side,
														vector <double>(k))))));
	}
	
	return 0;
}

int read_test_file(char* test_file, map<int, vector < vector < vector < vector <double> > > > > *blocks, int rank, int n, int m, int k)
{
	
	
	return 0;
}

int write_file(map<int, vector < vector < vector < vector <double> > > > > *blocks, char* out_file)
{
	ofstream ofs(out_file);
	
	for (auto& pair : *blocks)
		for (auto& grid : pair.second)
		{
			for (auto& plane : grid)
			{
				for (auto& ceil : plane)
				{
					for (auto& param : ceil)
						ofs << param << " ";
					ofs << "\t";
				}
				ofs << endl;
			}
			
			ofs << endl << endl;
		}
	ofs.close();
	
	return 0;
}

int generate_data(map<int, vector < vector < vector < vector <double> > > > > *blocks)
{
	srand(time(NULL));
	
	for (auto& pair : *blocks)
		for (auto& grid : pair.second)
			for (auto& plane : grid)
				for (auto& ceil : plane)
					for (auto& param : ceil)
						param = (double)rand() / rand();
	
	return 0;
}