#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "world_extended.h"
#include "options.h"
#include "processus.h"


int main(int argc, char* argv[])
{
  struct options opt;
  remplir_struct(&opt, argc, argv);
  srand(get_s(&opt));
  struct world w = world_init();
  rules_init();
  printf("%d %d\n", WIDTH, HEIGHT);
  struct queue queue;
  world_disp(&w);
  for(int i=0; i<get_m(&opt); ++i){
    struct queue *q = queue_init(&queue);
    queue_fill(q, &w);
    gestion_conflits(q,&w);
    application_regles(q,&w);   
    world_disp(&w);
  }
}
