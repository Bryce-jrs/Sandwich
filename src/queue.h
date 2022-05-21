#include "rule.h"
#include "global.h"
struct cell
{
 int couleur;
 int cases;
 int arrival;
 int booleen;
};

struct queue 
{
  int indice_debut;
  int indice_fin;
  struct cell file[WIDTH*HEIGHT*MAX_RULES];
};


struct queue *queue_init(struct queue *q);

void queue_append( struct queue *queue, struct rule *regle, int i, int j);

void queue_pop( struct queue *queue);

int first_occurence(int valeur, int tableau[],int taille);

int nbre_occurence(int valeur ,int tableau[], int taille);

int nbre_occurence_arrival(int valeur , struct cell tableau[], int taille); 

int choix_aleatoire(int valeur, struct cell tableau[], int taille);

void remplir_tableau( int valeur, int tableau[], int taille);

int test_incompressibilite(struct world *world, int taille );

int indice_couleur(struct rule *regle);
