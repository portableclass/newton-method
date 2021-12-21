#include "Equation.h"

// 0. The local functions:
void IterReport(const unsigned int& iter, const double& x_new, const double& delta)
{
	std::printf("\nIteration %i\nx_new = %1.15e\ndelta = %1.15e\n", iter, x_new, delta);
};

// 1.1. The Newton's method:
double solveNewton(const double& x_start, double (*fun)(const double), double (*D1fun)(const double), DataVector& x_data, DataVector& delta_data, const double delta_max, const int iter_max)
{
	// 0. It is reset of data vectors:
	if ((x_data.size() != 0) || (delta_data.size() != 0))
	{
		x_data.setEmpty();
		delta_data.setEmpty();
	}

	// 1. It is zero's iteration:
	double x_new = x_start - fun(x_start) / D1fun(x_start);
	double delta = std::max(std::abs(x_new - x_start), std::abs(fun(x_start)));
	unsigned int iter = 0;
	double x_0 = x_new;

	x_data.push_back(x_new);
	delta_data.push_back(delta);

	// 2. It is other iterations:
	while ((delta > delta_max) && (++iter < iter_max))
	{
		x_new = x_0 - fun(x_0) / D1fun(x_0);
		delta = std::max(std::abs(x_new - x_0), std::abs(fun(x_new)));

		x_data.push_back(x_new);
		delta_data.push_back(delta);

		x_0 = x_new;
		
		IterReport(iter, x_new, delta);
	}

	// 3. It is result return:
	return x_new;
};
double solveNewton(const double& x_start, double (*fun)(const double&), double (*D1fun)(const double&), DataVector& x_data, DataVector& delta_data, const double delta_max, const int iter_max)
{
	// 0. It is reset of data vectors:
	if ((x_data.size() != 0) || (delta_data.size() != 0))
	{
		x_data.setEmpty();
		delta_data.setEmpty();
	}

	// 1. It is zero's iteration:
	double x_new = x_start - fun(x_start) / D1fun(x_start);
	double delta = std::max(std::abs(x_new - x_start), std::abs(fun(x_start)));

	x_data.push_back(x_new);
	delta_data.push_back(delta);

	unsigned int iter = 0;
	double x_0 = x_new;

	// 2. It is other iterations:
	while ((delta > delta_max) && (++iter < iter_max))
	{
		x_new = x_0 - fun(x_0) / D1fun(x_0);
		delta = std::max(std::abs(x_new - x_0), std::abs(fun(x_new)));

		x_data.push_back(x_new);
		delta_data.push_back(delta);

		x_0 = x_new;

		IterReport(iter, x_new, delta);
	}

	// 3. It is result return:
	return x_new;
};

// 1.2. The finite form of the Newton's method:
double solveNewtonFinite(const double& x_start, double (*fun)(const double), DataVector& x_data, DataVector& delta_data, const double delta_max, const int iter_max, const double step)
{
	if ((x_data.size() != 0) || (delta_data.size() != 0))
	{
		x_data.setEmpty();
		delta_data.setEmpty();
	}

	double x_new = x_start - fun(x_start) / D1(x_start, fun, step);
	double delta = std::max(std::abs(x_new - x_start), std::abs(fun(x_new)));
	unsigned int iter = 0;
	double x_0 = x_new;

	x_data.push_back(x_new);
	delta_data.push_back(delta);

	while ((delta > delta_max) && (++iter < iter_max))
	{
		x_new = x_0 - fun(x_0) / D1(x_0, fun, step);
		delta = std::max(std::abs(x_new - x_0), std::abs(fun(x_new)));

		x_data.push_back(x_new);
		delta_data.push_back(delta);

		x_0 = x_new;
		
		IterReport(iter, x_new, delta);
	}

	return x_new;
};
double solveNewtonFinite(const double& x_start, double (*fun)(const double&), DataVector& x_data, DataVector& delta_data, const double delta_max, const int iter_max, const double step)
{
	if ((x_data.size() != 0) || (delta_data.size() != 0))
	{
		x_data.setEmpty();
		delta_data.setEmpty();
	}

	double x_new = x_start - fun(x_start) / D1(x_start, fun, step);
	double delta = std::max(std::abs(x_new - x_start), std::abs(fun(x_new)));
	unsigned int iter = 0;
	double x_0 = x_new;

	x_data.push_back(x_new);
	delta_data.push_back(delta);

	while ((delta > delta_max) && (++iter < iter_max))
	{
		x_new = x_0 - fun(x_0) / D1(x_0, fun, step);
		delta = std::max(std::abs(x_new - x_0), std::abs(fun(x_new)));

		x_data.push_back(x_new);
		delta_data.push_back(delta);

		x_0 = x_new;
		
		IterReport(iter, x_new, delta);
	}

	return x_new;
};

double D1(const double& x_start, double (*fun)(const double), const double& step)
{
	return (fun(x_start + step) - fun(x_start - step)) / (2.0 * step);
};
double D1(const double& x_start, double (*fun)(const double&), const double& step)
{
	return (fun(x_start + step) - fun(x_start - step)) / (2.0 * step);
};