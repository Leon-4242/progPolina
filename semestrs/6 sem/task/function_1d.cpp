// function_1d.cpp

#include "function_1d.h"

#include <assert.h>
#include <math.h>

double compute_infinity_norm (
    const abstract_function_1d *func, double a, double b, int n_steps)
{
  double len = b - a;
  double norm = fabs (func->evaluate (b));
  double step = len / static_cast<double> (n_steps);
  for (int i = 0; i < n_steps; i++)
    {
      double y = fabs (func->evaluate (a + i * step));
      if (y > norm)
        norm = y;
    }
  return norm;
}

function_1d::function_1d (int k)
{
  set_k (k);
}

const char *function_1d::get_function_name () const
{
  switch (m_k)
  {
  case function_id_t::constant:
    return "1.0";
  case function_id_t::linear:
    return "x";
  case function_id_t::quadratic:
    return "x^2";
  case function_id_t::cubic:
    return "x^3";
  case function_id_t::fourth_degree:
    return "x^4";
  case function_id_t::exponent:
    return "e^x";
  case function_id_t::cauchy:
    return "1 / (25x^2 + 1)";
  case function_id_t::COUNT:
    assert (false);
    return "";
  }

  assert (false);
  return "";
}

double function_1d::evaluate (double x) const
{
  switch (m_k)
  {
  case function_id_t::constant:
    return 1.0;
  case function_id_t::linear:
    return x;
  case function_id_t::quadratic:
    return x * x;
  case function_id_t::cubic:
    return x * x * x;
  case function_id_t::fourth_degree:
    return x * x * x * x;
  case function_id_t::exponent:
    return exp (x);
  case function_id_t::cauchy:
    return 1.0 / (25.0 * x * x + 1);
  case function_id_t::COUNT:
    assert (false);
    return 0.0;
  }

  assert (false);
  return 0.0;
}

abstract_interpolation_function_1d::~abstract_interpolation_function_1d ()
{
  clear ();
}

double abstract_interpolation_function_1d::evaluate (double x) const
{
  return compute_interpolated_value (x, m_a, m_b, m_n, m_points, m_coeffs);
}

void abstract_interpolation_function_1d::set_points (
    int n, double a, double b, int p, double norm, const abstract_function_1d *func)
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

void abstract_interpolation_function_1d::clear ()
{
  delete [] m_points;
  delete [] m_coeffs;
}


residual_function_1d::residual_function_1d (
    const abstract_function_1d *func, const abstract_function_1d *approx)
{
  m_func = func;
  m_approx = approx;
}

double residual_function_1d::evaluate (double x) const
{
  return m_func->evaluate (x) - m_approx->evaluate (x);
}

