import matplotlib.pyplot as plt

X = [50, 100, 150, 200, 250, 300, 350, 400, 450, 500]

Y1 = [4, 34, 73, 110, 153, 194, 242, 290, 341, 396]
Y2 = [4, 24, 58, 96, 137, 180, 229, 280, 337, 396]
Y3 = [4, 26, 63, 102, 144, 189, 244, 287, 339, 394]

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
plt.title('Objectives : 2')

# Grid for clarity
plt.grid(True, linestyle='--', alpha=0.6)

# Legend
plt.legend()

plt.tight_layout()
plt.show()