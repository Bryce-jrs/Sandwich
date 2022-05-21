#include <stdio.h>
#include <stdlib.h>
#include "options.h"
#include <unistd.h>
#include <getopt.h>
#include <time.h>


void remplir_struct(struct options* opt, int argc, char* argv[])
{
  int option;
  opt->m = 10;
  opt->s = time(NULL);
  while ((option = getopt(argc, argv, "m:s:")) != -1) {
    switch (option) {
    case 'm':
      opt->m = atoi(optarg);
      break;
    case 's':
      opt->s = atoi(optarg);
      break;
    default: 
      break;
    }
  }
}


int get_m(struct options *opt)
{
  return opt->m;
}

int get_s(struct options *opt)
{
  return opt->s;
}
