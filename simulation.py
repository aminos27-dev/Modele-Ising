import matplotlib.pyplot as plt
import numpy as np

# Charge la configuration issue de la mesure P_{N,T} [cite: 84]
grille = np.loadtxt("grille.txt")

plt.figure(figsize=(6,6))
plt.imshow(grille, cmap='gray', interpolation='nearest')
plt.title("Réalisation de la mesure d'Ising P_{N,T}")
plt.axis('off')
plt.show()