Ce projet implémente une simulation de physique statistique utilisant les méthodes Monte-Carlo par Chaîne de Markov (MCMC). L'objectif est d'étudier le comportement d'un matériau ferromagnétique afin de simuler sa mesure stationnaire et d'identifier sa température de transition de phase.


Structure du Projet

Le projet se compose de deux parties complémentaires :

    Calcul (C) : Effectue les milliers d'itérations nécessaires pour que la chaîne de Markov converge (loi stationnaire π).

    Analyse et Visualisation (Python) : Traite les données exportées pour tracer l'évolution et visualiser les résultats.

Utilisation :

1. Compilation du simulateur

Compilez le code source C avec l'option mathématique :

Bash

gcc simulation.c -o simulation -lm

2. Exécution du balayage de température

Lancez le programme pour générer le fichier transition.csv. Le programme teste T de 1.0 à 4.0.

Bash

./simulation

3. Visualisation des résultats

Générez le graphique de l'espérance du spin central :

Bash

python3 simulation.py
python3 transition.py

RÉSULTATS ATTENDUS

Température Critique (Tc​)

Sur le graphique généré, vous observerez une chute de l'espérance aux alentours de T≈2.27.

    Phase Ordonnée (T<Tc​) : Le spin central reste proche de +1. L'influence des bords se propage à travers toute la grille, même pour N=100.

    Phase Désordonnée (T>Tc​) : L'agitation thermique domine. Le centre devient indépendant des bords et l'aimantation moyenne tombe à 0.

Visualisation de la Mesure de Gibbs

    À basse température, les amas sont massifs et uniformes.

    À haute température, le système est très aléatoire, signe que la corrélation entre les sites est devenue faible.



