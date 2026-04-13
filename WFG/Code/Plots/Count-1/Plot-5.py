import matplotlib.pyplot as plt

X = [50, 100, 150, 200, 250, 300, 350, 400, 450, 500]

Y1 = [2111, 7317, 14734, 24735, 34713, 41224, 53109, 61374, 96922, 84917]
Y2 = [4237, 15717, 43898, 91931, 138729, 145639, 225000, 222010, 337544, 380235]
Y3 = [2120, 7366, 15092, 24714, 34321, 41120, 53017, 61221, 76977, 85319]

plt.figure(figsize=(10, 6))

# Plot with distinct styles
plt.plot(X, Y1, marker='o', linewidth=2.5, label='Original Population')
plt.plot(X, Y2, marker='s', linestyle='--', linewidth=2.5, label='Randomly Shuffled Population')
plt.plot(X, Y3, marker='^', linestyle='-.', linewidth=2.5, label='Standard Deviation Shuffled Population')

# Force all X points to be visible
plt.xticks(X)

# Improve Y scaling (tight margins)
y_min = min(min(Y1), min(Y2), min(Y3))
y_max = max(max(Y1), max(Y2), max(Y3))
plt.ylim(y_min - 20, y_max + 20)

# Labels and title
plt.xlabel('Number Of Points')
plt.ylabel('Times hypervolume() Function Is Called')
plt.title('Objectives : 5')

# Grid for clarity
plt.grid(True, linestyle='--', alpha=0.6)

# Legend
plt.legend()

plt.tight_layout()
plt.show()