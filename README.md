Projet C - ROLANDO Nathan - OSTERMANN Alexia


1. Explication du programme

Ce programme représente l'évolution des états de chaque personne dans une population. 
Les personnes peuvent prendre plusieurs états différents :
- sain
- malade
- immunisé
- mort
- zombie

Au début du programme, on crée un graphe qui représente le statut de chaque personne de la population au départ (jour 0).

Lors de la simulation, il est possible de modifier les paramètres, en particulier les probabilités de contamination, immunisation... (expliqués un peu plus loin).
On entre aussi le nombre de jours que doit réaliser la simulation. 
A la fin de celle-ci, un graphe s'affiche : il représente l'évolution des états de la population au cours du temps. 

Voici les règles de la simulation :
- Un individu sain peut devenir malade, zombie naturellement ou bien immunisé suite à une campagne de vaccination. 
- Un individu malade peut devenir zombie, mort ou immunisé. 
- Un individu immunisé peut devenir zombie et peut également tuer des zombies.
- Un individu mort reste mort.
- Un individu zombie peut devenir mort et peuvent tuer tout le monde.





2. Lancer le programme

Executer les commandes suivantes : 
gcc *.c -o main
./main

Le menu principal s'affiche : 
"

"




3. Détail du menu principal et utilisation du programme

3.1. "GENERER UN GRAPHE A PARTIR D'UN FICHIER TEXTE"

On crée un graphe à partir d'un fichier .txt dans le même format que celui vu en cours, c'est-à-dire de la même forme que "graph_10_13.txt" joint dans ce dossier. 
Le premier nombre correspond au nombre de sommets, le suivant au nombre d'arêtes. 
Ensuite, on a "sommet1 sommet2" qui représente le fait que sommet1 et sommet2 sont reliés. 

Un graphe est donc généré en fonction des paramètres entrés : on obtient un graphe contenant le statut de chaque personne au départ (jour 0). 


3.2. "GENERER UN GRAPHE GRILLE"

On crée un graphe grille d'une taille que l'on choisit. 
De même, un graphe est généré en fonction des paramètres entrés, qui déterminent le statut de chaque personne au départ (jour 0).


3.3. "LANCER LA SIMULATION"

Pour lancer la simulation, deux paramètres sont demandés :
- le nombre de jour de la simulation (exemple : 30)
- à partir de quel jour commence la campagne de vaccination (exemple : 4). En entrant "-1", on considère qu'il n'y a pas de campagne de vaccination. 


3.4. "MODIFIER LES PARAMETRES"

On accède au menu secondaire.


3.5. "QUITTER"

Sortir du programme.



4. Détails du menu secondaire

4.1. "MODIFIER LES PROBABILLITES"

Avec cette commande, on accède à un tableau de paramètres. Il est possible dans changer 8, il s'agit des probabilités permettant la simulation :
- probabilité de contamination au début de la simulation : permet de définir la situation de départ.
- probabilité de contamination par la maladie : probabilité qu'un individu sain tombe malade au contact de ses voisins malades
- probabilité de devenir zombie naturellement : un individu devient zombie sans contamination extérieure
- probabilité d'immunisation : après avoir été contaminé par la maladie, l'individu peut être immunisé
- probabilité de devenir zombie : probabilité qu'un individu devienne zombie après avoir été mordu par un zombie voisin
- probabilité d'être mort : probabilité qu'un individu meurt après avoir été contaminé par la maladie
- probabilté d'être immunisé après avoir été vacciné
- probabilité de tuer un zombie : probabilité qu'un zombie meurt après avoir été tué par un individu immunisé


4.2. "ACTIVER/DESACTIVER LE MODE ZOMBIE"



4.3. "ACTIVER/DESACTIVER LA CAMPAGNE DE VACCINATION"




4.4. "REINITIALISER LES PARAMETRES"

Les paramètres que nous avons établis par défaut sont entrés dans le tableau des probabilités.


4.5. "RETOUR AU MENU PRINCIPAL"
Permet de revenir au menu principal.




































