import matplotlib.pyplot as plt
import numpy as np

# Given points
points = np.array([
    (3, 8, 2),
    (2, 9, 2),
    (4, 7, 1),
    (1, 7, 3)
])

# Extract coordinates
x = points[:, 0]
y = points[:, 1]
z = points[:, 2]

# Create distinct colors
colors = plt.cm.tab20(np.linspace(0, 1, len(points)))

# Create 3D scatter plot
fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')

ax.scatter(x, y, z, c=colors, s=100,  edgecolors='black')


ax.set_xlabel("X-axis")
ax.set_ylabel("Y-axis")
ax.set_zlabel("Z-axis")

# Reference point R
xr, yr, zr = 0, 6, 0 

# Extract point coordinates (excluding R if included)
x_vals = [p[0] for p in points]
y_vals = [p[1] for p in points]
z_vals = [p[2] for p in points]

# Bounding box limits
x_min = xr
y_min = yr
z_min = zr

x_max = max(x_vals)
y_max = max(y_vals)
z_max = max(z_vals)

xp, yp, zp = 3, 8, 2

def draw_cuboid(x0, x1, y0, y1, z0, z1):
    corners = [
        (x0,y0,z0), (x1,y0,z0), (x1,y1,z0), (x0,y1,z0),
        (x0,y0,z1), (x1,y0,z1), (x1,y1,z1), (x0,y1,z1)
    ]
    
    edges = [
        (0,1),(1,2),(2,3),(3,0),
        (4,5),(5,6),(6,7),(7,4),
        (0,4),(1,5),(2,6),(3,7)
    ]
    
    for i,j in edges:
        xs = [corners[i][0], corners[j][0]]
        ys = [corners[i][1], corners[j][1]]
        zs = [corners[i][2], corners[j][2]]
        ax.plot(xs, ys, zs, color='black', linewidth=1)

# Split intervals using pivot
x_intervals = [(x_min, xp), (xp, x_max)]
y_intervals = [(y_min, yp), (yp, y_max)]
z_intervals = [(z_min, zp), (zp, z_max)]

# Draw all 8 hyperoctants
for xi in x_intervals:
    for yi in y_intervals:
        for zi in z_intervals:
            draw_cuboid(xi[0], xi[1], yi[0], yi[1], zi[0], zi[1])

ax.scatter(xp, yp, zp, s=120, marker='*')
ax.text(xp, yp, zp, '  P', fontsize=14)
ax.scatter(xr, yr, zr, s=120, marker='o')
ax.text(xr, yr, zr, '  R(0,6,0)', fontsize=14)

plt.title("3D Scatter Plot of 4 Points")
plt.show()