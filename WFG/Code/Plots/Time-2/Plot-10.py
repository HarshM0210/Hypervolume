import matplotlib.pyplot as plt

# Data
X = [15, 20, 25, 30, 35, 40, 45, 50, 55, 60]

Y1 = [6, 15, 28, 46, 78, 131, 196, 384, 625, 847]
Y2 = [6, 8, 30, 44, 87, 156, 245, 652, 976, 970]
Y3 = [3, 5, 21, 36, 68, 124, 168, 350, 612, 763]

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
plt.ylabel('Time In Milliseconds')
plt.title('Objectives : 10')

# Grid for clarity
plt.grid(True, linestyle='--', alpha=0.6)

# Legend
plt.legend()

plt.tight_layout()
plt.show()
