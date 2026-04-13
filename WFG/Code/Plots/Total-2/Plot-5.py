import matplotlib.pyplot as plt

# Data
X = [15, 20, 25, 30, 35, 40, 45, 50, 55, 60]

Y1 = [294, 519, 814, 1267, 1873, 1945, 2699, 3306, 4621, 6345]
Y2 = [325, 579, 1031, 1959, 3395, 4232, 6626, 7729, 8639, 13212]
Y3 = [279, 530, 819, 1334, 1831, 1936, 2871, 3325, 4705, 6422]

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
plt.ylabel('Total Number Of Points With Which hypervolume() Function Is Called')
plt.title('Objectives : 5')

# Grid for clarity
plt.grid(True, linestyle='--', alpha=0.6)

# Legend
plt.legend()

plt.tight_layout()
plt.show()
