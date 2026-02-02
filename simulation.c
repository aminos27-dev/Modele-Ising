#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define N 100
#define SIZE (2 * N + 1)
#define N_ITER 10000

int spins[SIZE][SIZE];

// Calcule la différence d'énergie si on inverse le spin au site (i, j)
double delta_H (int i, int j)
{
  int s = spins[i][j];
  int neighbors = 0;
  if (i > 0)
    neighbors += spins[i - 1][j];
  if (i < SIZE - 1)
    neighbors += spins[i + 1][j];
  if (j > 0)
    neighbors += spins[i][j - 1];
  if (j < SIZE - 1)
    neighbors += spins[i][j + 1];

  // H = - sum sigma_x * sigma_y. Delta H = 2 * sigma_i * sum(neighbors)
  return 2.0 * s * neighbors;
}

void simulation_step (double T)
{
  // n = 0; Répéter jusqu'à n = N_ITER
  for (int n = 0; n < N_ITER; n++)
    {
      // 1. Choisir j (une configuration voisine)
      int x = rand () % SIZE;
      int y = rand () % SIZE;

      // On ne touche pas aux bords pour les conditions de bords positives
      if (x == 0 || x == SIZE - 1 || y == 0 || y == SIZE - 1) continue;

      // 2. Calculer Delta H pour obtenir rho
      // Dans le code, on utilise souvent Delta H car rho = exp(-DeltaH / T)
      double dh = delta_H (x, y);
      double rho = exp (-dh / T);

      // 3. Logique d'acceptation (Si rho >= 1 ou U < rho)
      if (dh <= 0)
	{
	  // Équivalent à rho >= 1
	  spins[x][y] *= -1;
	}
      else
	{
	  // choisir U uniformément sur (0,1)
	  double U = (double) rand () / RAND_MAX;
	  if (U < rho)
	    {
	      spins[x][y] *= -1;	// X = j
	    }
	}
    }
}

// Initialisation (0 pour bords négatifs, 1 pour bords positifs)
void initialisation_bords(int p) {
    if (p == 0) {
      for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            spins[i][j] = -1; // On part de x0 avec bords +1
        }
      }
    }
    else {
      for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            spins[i][j] = 1; // On part de x0 avec bords -1
        }
      }
    }
}

void enregistrer_grille() {
    FILE *f = fopen("grille.txt", "w");
    if (f == NULL) return;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            fprintf(f, "%d ", spins[i][j]);
        }
        fprintf(f, "\n");
    }
    fclose(f);
}

int main() {
    srand(time(NULL));
    double T = 3.0; // Température
    double somme_spin_central = 0;
    int nb_mesures = 10000;
    int bord;

    printf("Saisir 1 pour initialiser avec bords positifs, 0 pour bords négatifs : ");
    scanf("%d",&bord);

    initialisation_bords(bord);

    printf("Enregistrement de la configuration...\n");
    enregistrer_grille();

    for (int i = 0; i < nb_mesures; i++) {
      simulation_step(T); // On laisse la chaîne évoluer
      somme_spin_central += spins[N][N]; // On cumule la valeur du spin au centre (0,0)
    }

    double esperance = somme_spin_central / nb_mesures;
    printf("Pour T = %f, l'espérance au centre est : %f\n", T, esperance);

    printf("Enregistrement de la configuration...\n");
    enregistrer_grille();

    // Partie simulation de la température de transition de phase
    FILE *f_csv = fopen("transition.csv", "w");
    fprintf(f_csv, "T,Esperance\n");

    bord = 1; // On utilise les bords positifs par défaut pour la Question 2
    nb_mesures = 1000;

    for (double T = 1.0; T <= 4.0; T += 0.1) {
        initialisation_bords(bord);

        // On laisse la chaîne évoluer longtemps avant de mesurer
        for (int i = 0; i < 500; i++) {
            simulation_step(T);
        }

        // 2. Phase de Mesure (Loi des Grands Nombres)
        double somme_spin_central = 0;
        for (int i = 0; i < nb_mesures; i++) {
            simulation_step(T);
            somme_spin_central += spins[N][N]; // Observation du centre sigma(0)
        }

        double esperance = somme_spin_central / nb_mesures;
        fprintf(f_csv, "%.1f,%f\n", T, esperance);
    }

    fclose(f_csv);
    printf("Résultats enregistrés dans transition.csv\n");

    return 0;
}
