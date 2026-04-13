import matplotlib.pyplot as plt

# Data
X = [15, 20, 25, 30, 35, 40, 45, 50, 55, 60]

Y1 = [201, 369, 579, 899, 1326, 1769, 1910, 2341, 2985, 3034]
Y2 = [205, 412, 733, 1391, 2403, 3493, 4708, 5478, 6922, 6051]
Y3 = [210, 377, 583, 947, 1302, 1788, 2033, 2356, 2853, 3034]

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
