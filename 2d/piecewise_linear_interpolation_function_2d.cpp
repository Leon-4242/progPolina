// piecewise_linear_interpolation_function_2d.cpp

#include <math.h>
#include <assert.h>

#include "piecewise_linear_interpolation_function_2d.h"

double *piecewise_linear_interpolation_function_2d::allocate_workspace () const
{
  return nullptr;
}

static void compute_points_1d_uniform (int n, double a, double b, double *points)
{
  assert (n > 1);

  double step = (b - a) / static_cast<double>(n - 1);

  for (int i = 0; i < n - 1; i++)
    points[i] = a + i * step;

  points[n - 1] = b;
}

void piecewise_linear_interpolation_function_2d::compute_points (
    int nx, int ny, double a, double b, double c, double d,
    double *points_x, double *points_y)
{
  compute_points_1d_uniform (nx, a, b, points_x);
  compute_points_1d_uniform (ny, c, d, points_y);
}

double *piecewise_linear_interpolation_function_2d::allocate_coefficients (int nx, int ny) const
{
  // values [(nx - 1) * (ny - 1)]
  // slopes_x [(nx - 1) * (ny - 1)]
  // slopes_y [(nx - 1) * (ny - 1)]
  // slopes_xy [(nx - 1) * (ny - 1)]

  return new double[4 * (nx - 1) * (ny - 1)];
}

void piecewise_linear_interpolation_function_2d::compute_coefficients (
    int nx, int ny,
    const double *points_x,
    const double *points_y,
    const double *values_in,
    double *coeffs,
    double * /*workspace*/
    )
{
  int n_blocks_x = nx - 1;
  int n_blocks_y = ny - 1;
  int n_blocks   = n_blocks_x * n_blocks_y;

  double *values    = coeffs;
  double *slopes_x  = coeffs + n_blocks;
  double *slopes_y  = coeffs + 2 * n_blocks;
  double *slopes_xy = coeffs + 3 * n_blocks;

  for (int j = 0; j < n_blocks_y; j++)
    {
      double dy = points_y[j + 1] - points_y[j];

      for (int i = 0; i < n_blocks_x; i++)
        {
          double dx = points_x[i + 1] - points_x[i];

          int k = j * n_blocks_x + i;

          double f_ij = values_in[j * nx + i];
          double f_Ij = values_in[j * nx + i + 1];
          double f_iJ = values_in[(j + 1) * nx + i];
          double f_IJ = values_in[(j + 1) * nx + i + 1];

          values[k] = f_ij;
          slopes_x[k] = (f_Ij - f_ij) / dx;
          slopes_y[k] = (f_iJ - f_ij) / dy;
          slopes_xy[k] = (f_IJ - f_Ij - f_iJ + f_ij) / (dx * dy);
        }
    }
}

static int get_index_by_point_for_uniform_distribution (
    double x,
    double a,
    double b,
    int n)
{
  double inv_step = static_cast<double> (n - 1) / (b - a);

  int i = static_cast<int> (floor((x - a) * inv_step));

  if (i < 0)
    return 0;

  if (i >= n - 1)
    return n - 2;

  return i;
}

double piecewise_linear_interpolation_function_2d::compute_interpolated_value (
    double x, double y,
    double a, double b, double c, double d,
    int nx, int ny,
    const double *points_x,
    const double *points_y,
    const double *coeffs
    ) const
{
  int i = get_index_by_point_for_uniform_distribution (x, a, b, nx);
  int j = get_index_by_point_for_uniform_distribution (y, c, d, ny);

  int n_blocks_x = nx - 1;
  int n_blocks_y = ny - 1;
  int n_blocks   = n_blocks_x * n_blocks_y;

  int k = j * n_blocks_x + i;

  const double *values    = coeffs;
  const double *slopes_x  = coeffs + n_blocks;
  const double *slopes_y  = coeffs + 2 * n_blocks;
  const double *slopes_xy = coeffs + 3 * n_blocks;

  double x_offset = x - points_x[i];
  double y_offset = y - points_y[j];

  return values[k] +
         slopes_x[k] * x_offset +
         slopes_y[k] * y_offset +
         slopes_xy[k] * x_offset * y_offset;
}