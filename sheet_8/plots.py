import matplotlib.pyplot as plt
import numpy as np
import glob

n_plots = len(glob.glob("data_*.txt"))

for i in range (n_plots):
    with open(f"data_{i+1}.txt", 'r') as f:
        header = f.readline().strip()
        data = np.loadtxt(f)
        time = data[:, 0]
        a_t = data[:, 1]
        plt.plot(time, a_t, lw = 0.1, label = header)
    f.close()

plt.xlabel("t [Gyr]")
plt.ylabel("a(t)")
plt.legend()

plt.savefig("fig_1.pdf")
