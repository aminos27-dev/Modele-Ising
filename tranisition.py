import pandas as pd
import matplotlib.pyplot as plt

df = pd.read_csv("transition.csv")


# 2. Création du graphique
plt.figure(figsize=(10, 6))
plt.plot(df['T'], df['Esperance'], marker='o', linestyle='-', color='b', label='Moyenne du spin central')

# 3. Ajout de la ligne théorique de transition (Tc ~ 2.269)
plt.axvline(x=2.269, color='r', linestyle='--', label='Température critique théorique ($T_c \\approx 2.27$)')

# 4. Habillage du graphique
plt.title("Transition de phase dans le modèle d'Ising (N=100)")
plt.xlabel("Température (T)")
plt.ylabel("Espérance $\mathbb{E}_{N,T}^+[\sigma(0)]$")
plt.grid(True, which='both', linestyle='--', alpha=0.5)
plt.legend()

# 5. Affichage
plt.show()