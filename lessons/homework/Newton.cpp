

#include "Newton_interpolation_function_1d.h"

double *Newton_interpolation_function_1d::allocate_workspace (int n) const
{
  (void)n;
  return nullptr;
}

void Newton_interpolation_function_1d::compute_points (int n, double a, double b, double *points)
{
  double d = b - a;
  for (int i = 0; i < n  - 1; i++)
    points[i] = a + static_cast<double> (i) * d / static_cast<double> (n - 1);
  points[n - 1] = b;
}

double *Newton_interpolation_function_1d::allocate_coefficients (int n) const
{
  return new double[n];
}

void Newton_interpolation_function_1d::compute_coefficients (
    int n,
    const double *points,
    const double *values,
    double *coeffs,
    double * /*workspace*/
    )
{
  for (int i = 0; i < n; i++)
  {
    coeffs[i] = values[i];
  }

  for (int i = 1; i < n; i++)
  {
    for (int j = n - 1; j >= i; j--)
    {
      coeffs[j] = (coeffs[j] - coeffs[j - 1]) / (points[j] - points[j - i]);
    }
  }
}

double Newton_interpolation_function_1d::compute_interpolated_value (
    double x,
    double a,
    double b,
    int n,
    const double *points,
    const double *coeffs
    ) const
  {
  double result = coeffs[n - 1];

  for (int i = n - 2; i >= 0; i--)
  {
    result = coeffs[i] + (x - points[i]) * result;
  }

  return result;
}