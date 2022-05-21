#include "world_extended.h"
#include <stdio.h>
#include <stdlib.h>


void queue_fill(struct queue *q, struct world *w)
{
  for(int ligne = 0; ligne<HEIGHT; ++ligne){
    for(int colonne = 0; colonne<WIDTH; ++colonne){
      for(unsigned int regle = 0; regle<rules_count(); ++regle){
	if (rule_match(w, rule_get(regle), ligne, colonne)) {
	  queue_append(q, rule_get(regle), ligne, colonne);             
	}
      }
    }
  }
}

void gestion_conflits(struct queue *q, struct world *w)
{
  int m=0;
  int k = q->indice_debut;
  int tableau_de_suivi_des_arrivees[WIDTH*HEIGHT];
  remplir_tableau( WIDTH*HEIGHT, tableau_de_suivi_des_arrivees, WIDTH*HEIGHT);
  while(k< q->indice_fin) // on parcourt la file                            
    {
      if (nbre_occurence((q-> file [k]).arrival ,tableau_de_suivi_des_arrivees,WIDTH*HEIGHT) == 0){// si la case d'arrivée n'a pas été traitée 
	tableau_de_suivi_des_arrivees[m]= (q->file[k]).arrival; // on la marque comme traitée
	m=m+1;
	if (w->t[(q-> file [k]).arrival] == BLACK ){ // si la case d'arrivée est vide
	  if( nbre_occurence_arrival((q -> file[k]).arrival, q->file, q->indice_fin-q->indice_debut) == 1){ // si c'est le seul prétendant vers cette case
	    (q->file[k]).booleen =1;   // on active la règle                              
	  }
	  else{ // En cas de conflit
	    int index_mod = choix_aleatoire((q->file[k]).arrival, q->file ,q->indice_fin-q->indice_debut); //on choisit aléatoirement une transformation de la file  
	    (q -> file[index_mod]).booleen =1;  // on active la règle                    
	  }
	}
	if(((w->t)[(q-> file [k]).arrival] != BLACK) && ((q->file[k]).arrival = (q->file[k]).cases)){
	  (q->file[k]).booleen = 1;
	}
      }
      k=k+1; 
    }
}


void application_regles(struct queue *q, struct world *w)
{
  while((q->indice_debut - q->indice_fin) != 0)   
    {
      if ((q -> file[q->indice_debut].booleen) == 1)       
	{
	  world_apply_rule(w, q, q -> indice_debut);
	  queue_pop(q);
	}
      else                                       
	queue_pop(q);
    }
}
