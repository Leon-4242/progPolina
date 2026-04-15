// piecewise_linear_interpolation_function_1d.cpp

#include "piecewise_linear_interpolation_function_1d.h"

double *piecewise_linear_interpolation_function_1d::allocate_workspace (int n) const
{
  // additional memory for derivative:
  return new double[n];
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
  // 4 values for n-1 polynoms:
  return new double[4 * (n-1)];
}

void piecewise_linear_interpolation_function_1d::compute_coefficients (
    int n,
    const double *points,
    const double *values,
    double *coeffs,
    double *workspace
    )
{
  double *coeffs_values = coeffs;
  double diff = 0;
  for (int i = 0; i < n-1; i++) {
    coeffs_values[4*i] = values[i];
    coeffs_values[4*i+1] = workspace[i];
	diff = (values[i+1]-values[i])/(points[i+1]-points[i]);
    coeffs_values[4*i+2] = (3*diff -2*workspace[i]-workspace[i+1])/ (points[i+1]-points[i]);
	coeffs_values[4*i+3] = (workspace[i]+workspace[i+1]-2*diff)/((points[i+1]-points[i])*(points[i+1]-points[i]));
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
    return coeffs[0];
  if (i >= n - 1)
    return coeffs_values[4*(n-2)];
  else {
	double x0 = x-points[i];
	const double *coeffs_values = coeffs+i*4;
	return x0*(x0*(x0*coeffs_values[3]+coeffs_values[2])+coeffs_values[1])+coeffs_values[0];
  }
}

void piecewise_linear_interpolation_function_1d::set_points (
    int n, double a, double b, int p, double norm, const function_1d *func)
{
  clear ();
  m_n = n;
  m_a = a;
  m_b = b;
  m_p = p;
  m_norm = norm;
  m_points = new double[n];
  m_coeffs = allocate_coefficients (n);

  compute_points (n, a, b, m_points);

  double *workspace = allocate_workspace (n);
  std::string name = func->get_function_name();
  if (name == "1.0")
	for (int i = 0; i < n; i++)
	  workspace[i] = 0.0;
  else if (name == "x")
	for (int i = 0; i < n; i++)
	  workspace[i] = 1.0;
  else if (name == "x^2")
	for (int i = 0; i < n; i++)
	  workspace[i] = 2*m_points[i];
  else if (name == "x^3")
	for (int i = 0; i < n; i++)
	  workspace[i] = 3*m_points[i]*m_points[i];
  else if (name == "x^4")
    for (int i = 0; i < n; i++)
	  workspace[i] = 4*m_points[i]*m_points[i]*m_points[i];
  else if (name == "e^x")
    for (int i = 0; i < n; i++)
	  workspace[i] = m_points[i];
  else if (name == "1 / (25x^2 + 1)")
    for (int i = 0; i < n; i++)
	  workspace[i] = 50*m_points[i] / ((25*m_points[i]*m_points[i]+1)*(25*m_points[i]*m_points[i]+1));
  else
    assert (false);

  double *values = new double[n];
  int permutated_index = n / 2;
  for (int i = 0; i < n; i++)
    {
      values[i] = func->evaluate (m_points[i]);
      if (i == permutated_index)
        values[i] += p * 0.1 * m_norm;
    }

  compute_coefficients (m_n, m_points, values, m_coeffs, workspace);

  delete [] values;
  delete [] workspace;
}
