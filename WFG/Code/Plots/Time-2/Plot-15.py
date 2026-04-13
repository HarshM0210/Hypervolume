import matplotlib.pyplot as plt

# Data
X = [15, 20, 25, 30, 35, 40, 45, 50, 55, 60]

Y1 = [13, 31, 141, 234, 348, 637, 955, 1440, 2043, 4394]
Y2 = [8, 27, 124, 373, 436, 745, 1210, 2266, 2537, 6454]
Y3 = [5, 20, 127, 227, 353, 617, 909, 1397, 1963, 4332]

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
plt.title('Objectives : 15')

# Grid for clarity
plt.grid(True, linestyle='--', alpha=0.6)

# Legend
plt.legend()

plt.tight_layout()
plt.show()
