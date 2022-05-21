# Dépôt pour les projets S5 (PR103)

- Lien vers le sujet du projet :

        <https://www.labri.fr/perso/renault/working/teaching/projets/2021-22-S5-Sandwich.php>

- Lien vers le projet sur la forge :

        <https://thor.enseirb-matmeca.fr/ruby/projects/projetss5>

- Lien vers la documentation sur l'utilisation de git :

        <https://thor.enseirb-matmeca.fr/ruby/docs/repository/git>

les tags à considérer pour chaque achievement est le dernier dans l'ordre lexicographique, les autres comportent souvent des problèmes ou ne sont pas complets. Notamment vous pouvez consulter ces tags suivants:

achievement 0.2.2
achievement 1.2
achievement 2.1
achievement 3.2
achievement 4.4

achievement 0:

vous pouvez compiler le test avec make test et l'executer avec un ./test, le fichier teste uniquement les fonctions sur les quelles nous avions des doutes mais le reste fonctionne. Pour tester notre jeu de la vie nous avons codé un monde contenant un planeur car il utilise toutes les règles du jeu de la vie, et en lançant project avec un planeur le comportement du monde est celui attendu. On peut changer l'initialisation du monde à partir du fichier world.c , en mettant soit le planeur soit le monde aléatoire en noir et blanc dans la fonction world init. Ici nous avons commit avec le jeu de la vie. 
Certaines fonctions correspondant aux achievements 1 et 2 sont déjà présentes dans le code car nous avons avancé avant d'avoir terminé les changements de l'achievement 0. 

achievement 2:

cet achievement concerne l'implémentation des déplacements de cases avant une vraie gestion de conflits. Nous avons mis le tag sur cet achievement puis nous avons du revenir en arrière sur les achievements 0 et 1 car nous avions oublié d'ajouter les options et les tests, les tests sur la forge ne passaient pas tous en vert. Nous nous sommes rendus compte au dernier moment que nous avons oublié d'ajouter les tests dans l'achievement 2 et de le tag à nouveau. Par conséquent, il est possible que certains tests passent au rouge sur cet achievement, alors que le système de déplacement de cases fonctionne. Nous ne pouvons plus le tag désormais car le code a beaucoup évolué depuis et nous avons amélioré la gestion de conflits donc il est compliqué de retourner à une version naive des conflits à présent.


rules et world:

Pour choisir différents règles et mondes, il faut modifier directement les mondes et règles choisis dans les fonctions rules_init() et world_init() d'initialisation des règles et des mondes 


