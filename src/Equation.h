#pragma once
#include "DataVector.h"

// 1.1. The Newton's method:
double solveNewton(const double&, double (*)(const double), double (*)(const double), DataVector&, DataVector&, const double = 1e-5, const int = 5);
double solveNewton(const double&, double (*)(const double&), double (*)(const double&), DataVector&, DataVector&, const double = 1e-5, const int = 5);

// 1.2. The finite form of the Newton's method:
double solveNewtonFinite(const double& , double (*)(const double), DataVector&, DataVector&, const double = 1e-5, const int = 5, const double = 1e-2);
double solveNewtonFinite(const double&, double (*)(const double&), DataVector&, DataVector&, const double = 1e-5, const int = 5, const double = 1e-2);

double D1(const double&, double (*)(const double), const double&);
double D1(const double&, double (*)(const double&), const double&);