#include "queue.h"


struct world create_empty_world();

struct world create_random_world();

void world_disp(struct world* w);

struct world world_init();

void world_apply_rule(struct world* w, struct queue *queue, int indice);
