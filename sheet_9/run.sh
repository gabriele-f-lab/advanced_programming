#!/bin/bash
gcc exercise_1.c -lm && ./a.out $(cat input) && python plots.py && zathura plots_exercise_1.pdf
