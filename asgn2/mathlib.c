#include "mathlib.h"
#include <stdio.h>

#include <math.h>

#define EPSILON 1e-14

// credit to Eugene Lab section 1/19/21
double static inline Abs(double x) {
    return x < 0 ? -x : x;
}

// credit to Eugene Lab section 1/19/21
double Sin(double x) {
    x = fmod(x, 2.0 * M_PI);
    double numerator = x;
    double denominator = 1.0;
    double sum = numerator / denominator; // x/1 = x
    double term = numerator / denominator;
    for (double k = 3.0; Abs(term) > EPSILON; k += 2.0) {

        // raising old numerator by 2
        numerator = numerator * -x * x;

        //old denominator is previous factorial
        denominator = denominator * (k - 1) * k;
        term = numerator / denominator;
        sum += term;
    }
    return sum;
}

// inspired by Eugene lab section 1/19/21
double Cos(double x) {
    //normalizing input
    x = fmod(x, 2.0 * M_PI);
    double numerator = 1.0; // x^0
    double denominator = 1.0; // 0!
    double sum = numerator / denominator;
    double term = numerator / denominator;
    for (double k = 2.0; Abs(term) > EPSILON; k += 2) {
        numerator = numerator * -x * x;
        denominator = denominator * (k - 1.0) * k;
        term = numerator / denominator;
        sum += term;
    }

    return sum;
}

// credit to Eugene Lab section 1/19/21
double Tan(double x) {
    x = fmod(x, 2.0 * M_PI);
    return Sin(x) / Cos(x);
}

// credit to Eugene Lab section 1/19/21
double Exp(double x) {
    //starting at x^0
    double term = 1.0;
    double sum = term;
    for (double k = 1.0; Abs(term) > EPSILON; k += 1.0) {
        term = (x / k) * term;
        sum += term;
    }
    return sum;
}

// credit to Eugene Lab section 1/19/21
double Log(double x) {
    double y = 1.0;
    double p = Exp(y);
    while (Abs(x - p) > EPSILON) {
        y = y + ((x - p) / p);
        p = Exp(y);
    }

    return y;
}
