#include "mathlib.h"

#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <unistd.h>

#define OPTIONS "asctel"

// credit to Eugene Lab section 1/19/21
int main(int argc, char **argv) {
    int opt = 0;
    bool do_sin, do_cos, do_tan, do_exp, do_log;
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
        case 'a':
            do_sin = true;
            do_cos = true;
            do_tan = true;
            do_exp = true;
            do_log = true;
            break;
        case 's': do_sin = true; break;
        case 'c': do_cos = true; break;
        case 't': do_tan = true; break;
        case 'e': do_exp = true; break;
        case 'l': do_log = true; break;
        default: fprintf(stderr, "Usage: %s -[asctel]\n", argv[0]);
        }
    }

    if (do_sin) {
        puts("  x            Sin              Library        Difference");
        puts("  -            ---              -------        ----------");
        for (double i = -2 * M_PI; i < 2 * M_PI; i = i + 0.1) {
           // printf(" %7.4lf % 16.8lf % 16.8lf % 16.10lf\n", i, Sin(i), sin(i), Sin(i) - sin(i));
	   printf(" % 16.8lf, ", Sin(i));
	 
        }
    }
    if (do_cos) {
        puts("  x            Cos              Library        Difference");
        puts("  -            ---              -------        ----------");
        for (double i = -2 * M_PI; i < 2 * M_PI; i = i + 0.1) {
           // printf(" %7.4lf % 16.8lf % 16.8lf % 16.10lf\n", i, Cos(i), cos(i), Cos(i) - cos(i));
	    printf("% 16.8lf, ", Cos(i));
        }
    }

    if (do_tan) {
        puts("  x            Tan                Library      Difference");
        puts("  -            ---                ------       ----------");
        for (double i = -M_PI / 3; i < M_PI / 3; i = i + 0.1) {
           // printf(" %7.4lf % 16.8lf % 16.6lf % 16.10lf\n", i, Tan(i), tan(i), Tan(i) - tan(i));
	    printf(" %7.4lf, ", (i));
        }
    }

    if (do_exp) {
        puts("  x            Exp                Library      Difference");
        puts("  -            ---                -------      ----------");
        for (double i = 1.0; i < 10; i = i + 0.1) {
           // printf(" %7.4lf % 16.8lf % 16.6lf % 16.10lf\n", i, Exp(i), exp(i), Exp(i) - exp(i));
	    printf(" %16.8lf, ", Exp(i));
        }
    }

    if (do_log) {
        puts("  x            Log                Library      Difference");
        puts("  -            ---                -------      ----------");
        for (double i = 1.0; i < 10; i = i + 0.1) {
           // printf(" %7.4lf % 16.8lf %16.6lf % 16.10lf\n", i, Log(i), log(i), Log(i) - log(i));
	   printf(" % 16.8lf, ", Log(i));
        }
    }
}
