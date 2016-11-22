#include "includes.h"
#include "functions.h"
#include "calculate.h"

int main(int argc, char** argv)
{
	int rank(0);
	int size(1);
	
	/// Initialize mpi
	/// get rank
	/// get size
	
	int p = 0; // count openMP threads
	int n = 0; // ceils count
	int m = 0; // blocks count
	int k = 0; // parameters count
	int c = 0; // count iterations
	int s = 0; // shadow zone
	int t = 0; // test mode - 1; computing - 0
	char *test_file = NULL;
	char *out_file = NULL;
	
	if (parse_args(argc, argv, &p, &n, &m, &k, &s, &c, &t, &test_file, &out_file) < 0 || 
		check_options(size, p, n, m, k, s, c, t, test_file) < 0)
	{
		usage(argv[0]);
		return -1;
	}
	
	map<int, vector < vector < vector < vector <double> > > > > blocks;
	set_size(&blocks, n, m, k, size, rank);
	
	if (t == 1)
		read_test_file(test_file, &blocks, rank, n, m, k);
	else
		generate_data(&blocks);
	
	write_file(&blocks, out_file);
	
	calculate();
	
	if (test_file != NULL)
		delete test_file;
	if (out_file != NULL)
		delete out_file;
	
	/// Finalize mpi
	
	return 0;
}