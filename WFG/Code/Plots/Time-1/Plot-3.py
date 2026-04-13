import matplotlib.pyplot as plt

X = [50, 100, 150, 200, 250, 300, 350, 400, 450, 500]

Y1 = [11, 33, 66, 113, 151, 204, 258, 317, 368, 443]
Y2 = [5, 23, 53, 96, 132, 179, 239, 291, 342, 414]
Y3 = [3, 23, 56, 82, 115, 155, 213, 252, 314, 375]

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
plt.title('Objectives : 3')

# Grid for clarity
plt.grid(True, linestyle='--', alpha=0.6)

# Legend
plt.legend()

plt.tight_layout()
plt.show()