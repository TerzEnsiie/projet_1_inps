import matplotlib.pyplot as plt
import numpy as np

# Read the 'output.log' file
file_path = 'output.txt'
with open(file_path, 'r') as file:
    lines = file.readlines()

x_min = float(lines[0].strip())  # Line 1 : min x value
x_max = float(lines[1].strip())  # Line 2 : max x value
num_points = int(lines[2].strip())  # Line 3 : nb of points
num_graphs = int(lines[3].strip())  # Line 4 : nb of graph to plut

# Read the data for [num_graphs] lines and [num_points] points each line
data = [list(map(float, line.strip().split())) for line in lines[4:4+num_graphs]]

# Create a subplot for each line
fig, axes = plt.subplots(num_graphs, 1, figsize=(10, 10))

# If there's only one line, convert the type of axes
if num_graphs == 1:
    axes = [axes]

x_values = np.linspace(x_min, x_max, num_points)

colors = ['blue', 'purple', 'red', 'orange', 'yellow', 'green', 'cyan']

# Print the graphs
for i, ax in enumerate(axes):
    ax.plot(x_values, data[i], color=colors[i % len(colors)])
    ax.fill_between(x_values, data[i], color=colors[i % len(colors)], alpha=0.3)
    ax.set_xlim(x_min, x_max)
    ax.set_title(f'Graphe Psi{i}(x)')
    ax.grid(True)

# Ajust size of each plot
plt.tight_layout()

# Save the plot
plt.savefig('output_graph.png')