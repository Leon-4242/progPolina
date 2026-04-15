// linear_interpolation_function_1d.cpp

#include "linear_interpolation_function_1d.h"

double *linear_interpolation_function_1d::allocate_workspace (int n) const
{
  (void)n;
  // no additional memory is required for this algorithm
  return nullptr;
}

void linear_interpolation_function_1d::compute_points (int n, double a, double b, double *points)
{
  // uniform distribution of points:
  double d = b - a;
  for (int i = 0; i < n  - 1; i++)
    points[i] = a + static_cast<double> (i) * d / static_cast<double> (n - 1);
  points[n - 1] = b;
}

double *linear_interpolation_function_1d::allocate_coefficients (int n) const
{
  // 4 values for n polynoms:
  return new double[4 * n];
}

void linear_interpolation_function_1d::compute_coefficients (
    int n,
    const double *points,
    const double *values,
    double *coeffs,
    double * /*workspace*/
    )
{
  double *coeffs_values = coeffs;
  double *coeffs_slopes = coeffs + n;
  for (int i = 0; i < n; i++)
    coeffs_values[i] = values[i];
  for (int i = 0; i < n - 1; i++)
    coeffs_slopes[i] = (values[i + 1] - values[i]) / (points[i + 1] - points[i]);
}

double linear_interpolation_function_1d::compute_interpolated_value (
    double x,
    double a,
    double b,
    int n,
    const double *points,
    const double *coeffs
    ) const
{
  const double *coeffs_values = coeffs;
  const double *coeffs_slopes = coeffs + n;
  // using that distribution is uniform:
  double step = (b - a) / (n - 1);
  int i = (int) ((x - a) / step);
  if (i < 0)
    return coeffs_values[0];
  if (i >= n - 1)
    return coeffs_values[n-1];
  else
    return coeffs_values[i] + coeffs_slopes[i] * (x - points[i]);
}
