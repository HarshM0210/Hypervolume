import matplotlib.pyplot as plt

# Data
X = [15, 20, 25, 30, 35, 40, 45, 50, 55, 60]

Y1 = [1081, 1722, 8414, 12152, 23128, 41713, 53976, 125240, 186373, 253532]
Y2 = [1084, 2782, 13538, 16579, 31102, 60014, 68801, 234914, 336067, 303931]
Y3 = [1072, 1666, 8741, 12573, 23333, 42370, 55227, 122161, 185805, 260014]

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
plt.title('Objectives : 10')

# Grid for clarity
plt.grid(True, linestyle='--', alpha=0.6)

# Legend
plt.legend()

plt.tight_layout()
plt.show()
