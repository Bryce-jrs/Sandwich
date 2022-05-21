
#include "../src/rule.h"
#include "../src/queue.h"
#include "../src/test.h"
#include "../src/processus.h"
#include <assert.h>
#include <stdio.h>


int main()
{
  struct world w = create_planeur();
  rules_init_game_of_life();
  for(unsigned int regle = 0; regle<rules_count(); regle++){
    assert(rule_match(&w, rule_get(regle), 1, 2)==0); //test sur la case blanche centrale du planneur, normalement aucune règle ne s'applique à cette case
  }
  struct queue q1;
  struct queue q2;
  struct queue *queue1 = queue_init(&q1);
  struct queue *queue2 = queue_init(&q2);
  queue_append(queue1, rule_get(0), 1, 4);
  queue_append(queue1, rule_get(1), 1, 5);
  queue_append(queue2, rule_get(1), 1, 5);
  queue_pop(queue1);
  //tests avec des arguments arbitraires sur le fonctionnement de la struct queue et les fonctions primitives du type défini
  assert(queue1->file[queue1->indice_debut].cases == queue2->file[queue2->indice_debut].cases);
  assert(queue1->file[queue1->indice_fin].cases == queue2->file[queue2->indice_fin].cases);
  
  
  //execution de l'algorithme principal sur 500 tours avec des règles et un monde précis en testant si le nombre de cases vivantes au début est bien le même que le nombre de cases vivantes à l'arrivée
  struct world w1 = create_world_test_conflit();
  int cases_vivantes_debut = test_incompressibilite(&w1,WIDTH*HEIGHT);
  rules_test_incompressibilite();
  struct queue queue;
  for(int i=0; i<500; ++i){
    struct queue *q = queue_init(&queue);
    queue_fill(q, &w1);
    gestion_conflits(q,&w1);
    application_regles(q,&w1);
    }
  int cases_vivantes_fin = test_incompressibilite(&w1,WIDTH*HEIGHT);
  assert(cases_vivantes_debut == cases_vivantes_fin);
  return 0;
}

