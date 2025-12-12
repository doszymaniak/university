import numpy as np
import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation

def count_alive_neighbours(data, i, j, n):
    x_dir = [0, 1, 1, 1, 0, -1, -1, -1]
    y_dir = [-1, -1, 0, 1, 1, 1, 0, -1]
    cnt = 0
    for k in range(8):
        (x, y) = (x_dir[k], y_dir[k])
        new_y = i + y
        new_x = j + x
        if (new_y < 0 or new_y >= n) or (new_x < 0 or new_x >= n):
            continue
        if data[new_y][new_x]:
            cnt += 1
    return cnt

def step(data, n):
    next_state = np.zeros((n, n))
    for i in range (n):
        for j in range (n):
            alive_neighbours = count_alive_neighbours(data, i, j, n)
            if data[i][j]:
                if alive_neighbours == 2 or alive_neighbours == 3:
                    next_state[i][j] = 1
                else:
                    next_state[i][j] = 0
            else:
                if alive_neighbours == 3:
                    next_state[i][j] = 1
                else:
                    next_state[i][j] = 0
    return next_state

def update(frame):
    global data
    data = step(data, n)
    grid.set_data(data)
    return [grid]

n = 100
data = np.random.choice([0, 1], size=(n, n), p=(0.8, 0.2))
fig, ax = plt.subplots()
grid = plt.imshow(data, cmap="binary")
plt.xticks([])
plt.yticks([])
animation = FuncAnimation(fig, update, interval=100)
plt.show()