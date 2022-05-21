#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "queue.h"
#include "world.h"



//retourne l'indice de la case (i,j) dans le tableau unidimensionnel de la struct world
int indexes(int i, int j) 
{
  return WIDTH*i+j;
}


//crée un monde vide et le renvoie
struct world create_empty_world()
{
  struct world empty_world;
  for(int i=0; i<(WIDTH*HEIGHT); i++){
    empty_world.t[i] = 0;
  }
  return empty_world;
}

//crée un monde de couleurs aléatoires et le renvoie
struct world create_random_world()
{
  struct world random_world;
  for(int i=0; i<(WIDTH*HEIGHT); i++){
    random_world.t[i] = rand();
  }
  return random_world;
}

//crée un monde aléatoire en noir et blanc adapté au jeu de la vie et le renvoie
struct world create_game_of_life()
{
  struct world game_of_life;
  for(int i=0; i<(WIDTH*HEIGHT); i++){
    game_of_life.t[i] = WHITE * (rand()%2);
  }
  return game_of_life;
}


//crée un monde avec un planeur (jeu de la vie), utilisé pour tester notre procédure pour le jeu de la vie
struct world create_planeur()
{
  struct world planeur = create_empty_world();
  planeur.t[indexes(0,2)]=WHITE;
  planeur.t[indexes(1,1)]=WHITE;
  planeur.t[indexes(2,1)]=WHITE;
  planeur.t[indexes(2,2)]=WHITE;
  planeur.t[indexes(2,3)]=WHITE;
  return planeur;
}

struct world create_world_test_conflit()
{
  struct world collision= create_empty_world();
  int i=0;
  for(i=0; i<WIDTH*HEIGHT; ++i)
    {
      int compteur =rand()%100;
      if(compteur > 70)
	collision.t[i]=WHITE;
    }
  return collision;
}

struct world create_conflit_rouge_et_bleu()
{
  struct world conflit = create_empty_world();
  conflit.t[indexes(5,5)]=RED;
  conflit.t[indexes(5,13)]=BLUE;
  conflit.t[indexes(5,9)]=WHITE;
  return conflit;
}



struct world create_simple_game_of_life()
{
  struct world simple = create_empty_world();
  simple.t[indexes(5,5)]=WHITE;
  simple.t[indexes(5,6)]=WHITE;
  simple.t[indexes(5,7)]=WHITE;
  return simple;
}

struct world create_falling_sand()
{
  struct world sand = create_empty_world();
  int i=0;
  for(i=0; i< WIDTH; i++)
    {
    sand.t[indexes(HEIGHT-1,i)]= GREY;
    }
  sand.t[indexes(2,30)]=OR;
  sand.t[indexes(3,10)]=OR;
  sand.t[indexes(4,30)]=OR;
  sand.t[indexes(6,30)]=OR;
  sand.t[indexes(8,30)]=OR;
  sand.t[indexes(10,30)]=OR;
  sand.t[indexes(5,100)]=OR;
  sand.t[indexes(11,10)]=OR;
  sand.t[indexes(7,10)]=OR;
  sand.t[indexes(9,10)]=OR;
  sand.t[indexes(14,10)]=OR;
  sand.t[indexes(13,10)]=OR;
  sand.t[indexes(16,15)]=OR;
  sand.t[indexes(22,15)]=OR;
  sand.t[indexes(19,15)]=OR;
  sand.t[indexes(25,15)]=OR;
  sand.t[indexes(15,15)]=OR;
  sand.t[indexes(19,15)]=OR;
  sand.t[indexes(21,15)]=OR;

  
  sand.t[indexes(10,5)]=GREY;
  sand.t[indexes(11,6)]=GREY;
  sand.t[indexes(12,7)]=GREY;
  sand.t[indexes(13,8)]=GREY;
  sand.t[indexes(HEIGHT-1,30)]=BLACK;
  sand.t[indexes(HEIGHT-1,31)]=BLACK;
  sand.t[indexes(HEIGHT-1,32)]=BLACK;
  sand.t[indexes(HEIGHT-1,33)]=BLACK;
  sand.t[indexes(HEIGHT-1,34)]=BLACK;
  sand.t[indexes(HEIGHT-1,35)]=BLACK;
  sand.t[indexes(20,30)]=GREY;
  sand.t[indexes(20,31)]=GREY;
  sand.t[indexes(20,32)]=GREY;


  return sand;
}
//affiche le monde avec les couleurs dans chaque case

void world_disp(struct world* w)
{
  printf("#\n");
  for(int i=1; i<HEIGHT+1; i++){
    for(int j=1; j<WIDTH; j++){
      printf("%d ", w->t[WIDTH*(i-1)+j-1]);
    }
    printf("%d\n", w->t[WIDTH*i-1]);
  }
}


//initialise le monde pour être ensuite appelé dans project.c
struct world world_init()
{
  struct world w = create_game_of_life();
  return w;
}



//effectue les changements liés à la règle à la position indice dans la queue

void world_apply_rule(struct world* w, struct queue *queue, int indice)
{ 
  w->t[ (queue ->file[indice]).cases] = BLACK;
  w->t[ (queue -> file[indice]).arrival] = (queue -> file[indice]).couleur;
}

