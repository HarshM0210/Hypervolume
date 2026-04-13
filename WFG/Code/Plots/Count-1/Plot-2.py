import matplotlib.pyplot as plt

X = [50, 100, 150, 200, 250, 300, 350, 400, 450, 500]

Y1 = [100, 200, 300, 400, 500, 600, 700, 800, 900, 1000]
Y2 = [217, 455, 723, 958, 1205, 1455, 1723, 1967, 2202, 3439]
Y3 = [100, 200, 300, 400, 500, 600, 700, 800, 900, 1000]

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
plt.title('Objectives : 2')

# Grid for clarity
plt.grid(True, linestyle='--', alpha=0.6)

# Legend
plt.legend()

plt.tight_layout()
plt.show()