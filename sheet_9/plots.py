import matplotlib.pyplot as plt
import numpy as np
import math
from matplotlib.backends.backend_pdf import PdfPages

grid_points = list(range(0, 340))
methods = ["exact", "ftcs", "lax", "upwind1", "upwind2", "lax_w"]
endfile = "end"

with PdfPages("plots_exercise_1.pdf") as pdf:
    with open("output.txt", 'r') as f:
        init_fig = 1
        i = 0
        j = 0
        tot = 0
        check_last = 0
        print_1 = 0
        for line in f:
            if (init_fig == 1):
                init_fig = 0
                n_plots = float(line)
                fig, ax = plt.subplots(math.ceil((n_plots + 1) / 2), 2, squeeze=False)

            line = line.strip()
            j = tot % 2
            i = math.floor(tot / 2)
            if (line == endfile):
                break;
            if line in methods:
                if (check_last == 1):
                    print_1 = 1
                    check_last = 0
                else:
                    header = line
            else:
                if (len(line.split()) == 1):
                    t = float(line)
                else:
                    grid = [float(x) for x in line.split()]
                    check_last = 1

            if (print_1 == 1):
                ax[i, j].plot(grid_points, grid, lw = 0.1)
                ax[i, j].set_title(header, fontsize = 7)
                ax[i, j].tick_params(axis="both", labelsize=7)
                print_1 = 0
                header = line
                tot += 1

        ax[i, j].plot(grid_points, grid, lw = 0.1)
        ax[i, j].set_title(header, fontsize = 7)
        ax[i, j].tick_params(axis="both", labelsize=7)

    fig.suptitle(f"Results at time {t}", fontsize = 11)
    fig.subplots_adjust(hspace = 0.6, wspace = 0.4, top = 0.85)
    pdf.savefig(fig)
    plt.close(fig)
    f.close()

    with open("output.txt", 'r') as f:
        init_fig = 1
        init_fig_1 = 2
        i = 0
        j = 0
        tot = -1
        cont = 0
        print_1 = 0
        l_type = "solid"
        for line in f:
            if (init_fig_1 == 1):
                init_fig_1 = 0
                print_line = int(line)
            if (init_fig == 1):
                init_fig = 0
                n_plots = float(line)
                fig, ax = plt.subplots(math.ceil((n_plots + 1) / 2), 2, squeeze=False)
                init_fig_1 -= 1

            line = line.strip()
            if (line == endfile):
                break;
            if line in methods:
                header = line
                cont = 0
                tot += 1
            else:
                if (len(line.split()) == 1):
                    t = float(line)
                else:
                    grid = [float(x) for x in line.split()]
                    cont += 1
                    if (cont % print_line == 0):
                        print_1 = 1                 
            j = tot % 2
            i = math.floor(tot / 2)

            if (print_1 == 1):
                if (l_type == (0, (16, 12))):
                    l_type = "solid"
                else:
                    l_type = (0, (16, 12))
                ax[i, j].plot(grid_points, grid, lw = 0.1, label = t, linestyle = l_type)
                ax[i, j].set_title(header, fontsize = 7)
                ax[i, j].legend(title = "time", title_fontsize = 6, fontsize = 4, loc = "upper left", bbox_to_anchor = (1.01, 1.0))
                ax[i, j].tick_params(axis="both", labelsize = 7)
                print_1 = 0

    fig.suptitle("Results at different times", fontsize = 11)
    fig.subplots_adjust(hspace = 0.6, wspace = 0.4, top = 0.85)
    pdf.savefig(fig)
    plt.close(fig)
