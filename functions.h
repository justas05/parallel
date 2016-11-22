#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "includes.h"

int usage(char*);
int parse_args(int, char**, int *, int *, int *, int *, int *, int *, int *, char**, char**);
int check_options(int, int, int, int, int, int, int, int, char*);

int set_size(map<int, vector < vector < vector < vector <double> > > > > *, int, int, int, int, int);

int generate_data(map<int, vector < vector < vector < vector <double> > > > > *blocks);
int read_test_file(char*, map<int, vector < vector < vector < vector <double> > > > >*, int, int, int, int);
int write_file(map<int, vector < vector < vector < vector <double> > > > > *blocks, char*);

#endif