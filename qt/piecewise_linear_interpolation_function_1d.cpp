// piecewise_linear_interpolation_function_1d.cpp

#include "piecewise_linear_interpolation_function_1d.h"

double *piecewise_linear_interpolation_function_1d::allocate_workspace () const
{
  // no additional memory is required for this algorithm
  return nullptr;
}

void piecewise_linear_interpolation_function_1d::compute_points (int n, double a, double b, double *points)
{
  // uniform distribution of points:
  double d = b - a;
  for (int i = 0; i < n  - 1; i++)
    points[i] = a + static_cast<double> (i) * d / static_cast<double> (n - 1);
  points[n - 1] = b;
}

double *piecewise_linear_interpolation_function_1d::allocate_coefficients (int n) const
{
  // n values + (n - 1) slopes:
  return new double[4 * (n - 1)];
}

void piecewise_linear_interpolation_function_1d::compute_coefficients (
    int n,
    const double *points,
    const double *values,
    double *coeffs,
    double * /*workspace*/
    )

{
  double *coeffs_values = coeffs;
  double diff = 0;
  for (int i = 0; i < n-1; i++) {
    coeffs_values[4*i] = values[i];
    coeffs_values[4*i+1] = values[i+n];
	diff = (values[i+1]-values[i])/(points[i+1]-points[i]);
    coeffs_values[4*i+2] = (3*diff -2*values[i+n]-values[i+n+1])/ (points[i+1]-points[i]);
	coeffs_values[4*i+3] = (values[i+n]+values[i+n+1]-2*diff)/((points[i+1]-points[i])*(points[i+1]-points[i]));
  }
}



double piecewise_linear_interpolation_function_1d::compute_interpolated_value (
    double x,
    double a,
    double b,
    int n,
    const double *points,
    const double *coeffs
    ) const
{
  const double *coeffs_values = coeffs;
  // using that distribution is uniform:
  double step = (b - a) / (n - 1);
  int i = (int) ((x - a) / step);
  if (i < 0)
    return coeffs_values[0];
  if (i >= n - 1)
    return coeffs_values[4*(n-1)];
  else
    return coeffs[4 * i] + (x - points[i]) * (coeffs[4 * i + 1] + ((x - points[i]) * (coeffs[4 * i + 2] + (x - points[i]) * coeffs[4 * i + 3])));
}

double piecewise_linear_interpolation_function_1d::compute_interpolated_derivative (
      double ,
      double ,
      double ,
      int ,
      const double *,
      const double *
      ) const
{
	assert(false);
	return 0;
}
