#!/bin/bash

gcc exercise_2.c -lgsl -lgslcblas -lm && ./a.out $(cat input) && python plots.py && zathura plots_exercise_2.pdf
