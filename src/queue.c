#include <stdio.h>
#include <stdlib.h>
#include "global.h"
#include "queue.h"

// elle prend les coordonnées de la cellule  et le déplacement et retourne sa case d'arrivée

int nouvelle_case(int i,int j, int dx, int dy)
{
  int x = (i + dx + HEIGHT)%HEIGHT;
  int y = (j + dy + WIDTH)%WIDTH;

  return indexes(x,y);
  
}

// on crée une structure de queue contenant deux tableaux du nombre de case présente  dans le monde multiplié par le nombre de règles. le premier qui va contenir les règles et le deuxième les cases correspondantes. Les indices définissent les des cases que l'on va considérer pour notre structure file

struct queue *queue_init(struct queue *q)
{
  q -> indice_debut = 0;
  q -> indice_fin = 0;
  return q;
}


/* elle ajoute une cellule dans la queue   
*/
void queue_append( struct queue *queue, struct rule *regle, int i, int j)
{
  struct cell cellule;
  unsigned int ind_couleur = indice_couleur(regle);
  int dx = rule_change_dx( regle, ind_couleur);
  int dy = rule_change_dy( regle, ind_couleur);

  cellule.couleur =  rule_change_to(regle, ind_couleur);
  cellule.cases = indexes(i,j);
  cellule.arrival = nouvelle_case(i,j, dx, dy );
  cellule.booleen = 0;

  queue -> file [queue->indice_fin] = cellule;
  queue -> indice_fin += 1;
}



void queue_pop( struct queue *queue)
{
  queue -> indice_debut += 1;
}

// retourne  l'indices de la premiere occurence de la valeur dans le tableau 
   
int first_occurence(int valeur,int tableau[],int taille)
{
  int i=0;
  for(i=0;i<taille;i++)
    {
      if(tableau[i]==valeur)
	break; 
    }
  return i;
}

// nombre d'occurence de la case d'arrivée  dans un tableau quelconque 

int nbre_occurence(int valeur ,int tableau[], int taille)
{
  int i=0;
  int compteur=0;
   for(i=0;i<taille;i++)
    {
      if(tableau[i] == valeur)
	compteur+=1; 
    }
   return compteur;
}

/* cette fonction a été implémentée avec comme objectif de déterminer le nombre d'occurence d'arrivée c'est-à-dire si oui ou non elle est la case d'arrivée de plusieurs cellule
 */ 
int nbre_occurence_arrival(int valeur , struct cell tableau[], int taille)
{
  int i=0;
  int compteur=0;
   for(i=0;i<taille;i++)
    {
      if((tableau[i]).arrival == valeur)
	compteur+=1; 
    }
   return compteur;
}

/* Cette fonction a été implémentée avec comme objectif de choisir aléatoirement une cellule parmi toutes celles qui ont comme destination une case d'arrivée       donnée
   la méthode consiste pour une case d'arrivée donnée de trouver toutes les cellules prétendantes et  à  mettre leur indice dans un tableau temporaire
   ensuite on va choisir alétoirement une valeur dans ce tableau et on va la retourner 
*/ 
int choix_aleatoire( int valeur, struct cell tableau[], int taille)
{
  int j=0;
  int n=0;
  int i=0;
  int tableau_temporaire[WIDTH*HEIGHT]={0};

  for(i=0; i<taille; i++)
    {
      if( (tableau[i]).arrival == valeur )
	{
	  tableau_temporaire[j] = i;
	  j+=1;
	}
    }

  n = tableau_temporaire[rand()%j];
  return n;
}


void remplir_tableau(int valeur, int tableau[],int taille)
{
  int i=0;
  for(i=0;i<taille; ++i)
    tableau[i]=valeur;
}


int test_incompressibilite( struct world *world, int taille )
{
  int compteur=0;
  int i=0;
  for(i=0; i< taille; i++)
    {
      if(world->t[i]== WHITE)
	compteur +=1;
    }
  return compteur;
}

int indice_couleur(struct rule *regle)
{
  if(rule_num_changes(regle)==0)
    return 0;
  else
    return rand() % rule_num_changes(regle);
}
