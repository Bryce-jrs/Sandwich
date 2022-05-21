#include <stdio.h>
#include <stdlib.h>
#include "global.h"
#include "rule.h"



struct couple{
  int x;
  int y;
};

struct rule
{
  int (*match)(const struct world*, unsigned int, unsigned int); 
  int new_center_color[MAX_CHANGES];          //liste des changements possible ; liste de couleur donc   
  struct couple deplacement[MAX_CHANGES];     //tableau des déplacements (dx,dy) liés aux couleurs de new_center_color
  int nb_of_changes;
};

struct rule rules[MAX_RULES];
int NB_RULES;

void fill_voisins(int* v, int i, int j)
{
  int m = 0;
  for(int k=-1; k<=1; k++){
    for(int l=-1; l<=1; l++){
      int i2 = i+k;
      int j2 = j+l;
      if(i2<0)
	i2+=HEIGHT;
      if(i2>=HEIGHT)
	i2-=HEIGHT;
      if(j2<0)
	j2+=WIDTH;
      if(j2>=WIDTH)
	j2-=WIDTH;
      v[m] = indexes(i2, j2);
      m += 1;
    }
  }
}

int nombre_voisins_vivants(const struct world*w, unsigned int i, unsigned int j)
{

  int voisin[9];
  fill_voisins(voisin,i,j);
  int k = 0;
  int compteur = 0; 
  for(k=0; k< 9; ++k)
    {
      if ( w->t[voisin[k]] == WHITE )
	compteur +=1;
    }
  return compteur;
}


// implémentation des règles du jeu de la vie 

int match_rule1_gol(const struct world*w, unsigned int i, unsigned int j)
{
  if((nombre_voisins_vivants(w,i,j)== 3) && w->t[indexes(i,j)]==BLACK)
    return 1;
  return 0;
}

 

int match_rule2_gol(const struct world*w, unsigned int i, unsigned int j)
{
  if( w->t[indexes(i,j)]!=WHITE)
    return 0;
  else
    {
      switch (nombre_voisins_vivants(w,i,j))
	{
	case 1:
	case 2:
	case 5:
	case 6:
	case 7:
	case 8:
	case 9:
	  return 1;
	  break;
	default:
	  break;
	}
    }
  return 0;
}



void rules_init_game_of_life()
{
  struct rule rule1;
  struct rule rule2;

  rule1.match = &match_rule1_gol;
  rule2.match = &match_rule2_gol;
  rule1.new_center_color[0]= WHITE;
  rule2.new_center_color[0]= BLACK;
  rule1.nb_of_changes =1;
  rule2.nb_of_changes =1;
  (rule1.deplacement[0]).x = 0;
  (rule1.deplacement[0]).y = 0;
  (rule2.deplacement[0]).x = 0;
  (rule2.deplacement[0]).y = 0;

  rules[0]=rule1;
  rules[1]=rule2;

  NB_RULES =2;
  

}

int match_rule_incompressibilite(const struct world*w, unsigned int i, unsigned int j)
{
  if(w->t[indexes(i,j)]==WHITE){
    return 1;
  }
  return 0;
}



void rules_test_incompressibilite()
{
  struct rule rule1;

  rule1.match = &match_rule_incompressibilite;
  rule1.new_center_color[0] = WHITE;
  rule1.new_center_color[1] = WHITE;
  rule1.new_center_color[2] = WHITE;
  rule1.new_center_color[3] = WHITE;

  rule1.nb_of_changes = 4;
  
  (rule1.deplacement[0]).x = 1;
  (rule1.deplacement[0]).y = 5;
  (rule1.deplacement[1]).x = 2;
  (rule1.deplacement[1]).y = 1;
  (rule1.deplacement[2]).x = -1;
  (rule1.deplacement[2]).y = 7;
  (rule1.deplacement[3]).x = -3;
  (rule1.deplacement[3]).y = 0;

  rules[0]=rule1;
 
  NB_RULES =1;
}

   
// implémentaion de la règle pour la tombée de sable


int match_rule1_fs(const struct world*w, unsigned int i, unsigned int j)
{
  if((w->t[indexes(i,j)+WIDTH]== GREY)&& w->t[indexes(i,j)]== OR)
    {
      return 1;
    }
  return 0;
}

int match_rule2_fs(const struct world*w, unsigned int i, unsigned int j)
{
  if((w->t[indexes(i,j)+WIDTH]== BLACK)&& w->t[indexes(i,j)]== OR)
    { 
      return 1;
    }
  return 0;
}

void rules_init_falling_sand()
{
  struct rule rule1;
  struct rule rule2;

  rule1.match = &match_rule1_fs;
  rule2.match = &match_rule2_fs;
  rule1. new_center_color[0]= OR;
  rule2. new_center_color[0]= OR;
  rule1.nb_of_changes =1;
  rule2.nb_of_changes =1;
  (rule1.deplacement[0]).x = 0;
  (rule1.deplacement[0]).y = 0;
  (rule2.deplacement[0]).x = 1;
  (rule2.deplacement[0]).y = 0;

  rules[0]=rule1;
  rules[1]=rule2;

  NB_RULES =2;
}





// fonctions de manipulations des rules 


void rules_init()
{

  rules_init_game_of_life();

}


int rule_match(const struct world* w, const struct rule* r,unsigned int i, unsigned int j)
{
  return(r->match(w,i,j));
}

unsigned int rules_count()
{
  return NB_RULES;
}

struct rule * rule_get(unsigned int i)
{
  return &rules[i];
}

unsigned int rule_num_changes(const struct rule* r)
{
  return (*r).nb_of_changes; 
}

unsigned int rule_change_to(const struct rule* r, unsigned int idx)
{
  return r->new_center_color[idx];
}


int rule_change_dx(const struct rule* r, unsigned int idx)
{
  return ((r->deplacement)[idx]).x;
}

int rule_change_dy(const struct rule* r, unsigned int idx)
{
  return ((r->deplacement)[idx]).y;
}
