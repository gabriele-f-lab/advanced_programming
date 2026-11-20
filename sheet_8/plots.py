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
        a_t_ad = data[:, 2]
        diff = data[:, 3]
        first_plot = plt.plot(time, a_t_ad, lw = 0.1, label = f"{header} Runge-Kutta")
        c = first_plot[0].get_color()
        plt.plot(time, a_t_ad, ls = 'dashed', lw = 0.1, label = f"{header} RK4/5 (adaptive timestep)", color = c)
    f.close()

plt.xlabel(r"$t$ [Gyr]")
plt.ylabel(r"$a(t)$")
plt.legend(fontsize = 6)

plt.savefig("plots_exercise_2.pdf")
