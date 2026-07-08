// piecewise_linear_interpolation_function_1d.h

#ifndef PIECEWISE_LINEAR_INTERPOLATION_FUNCTION_1D_H
#define PIECEWISE_LINEAR_INTERPOLATION_FUNCTION_1D_H

#include <cassert>
#include "function_1d.h"

class piecewise_linear_interpolation_function_1d final : public abstract_interpolation_function_1d
{
protected:
  virtual void compute_points (int n, double a, double b, double *points) override;
  virtual double *allocate_coefficients (int n) const override;
  virtual double *allocate_workspace () const override;
  virtual void compute_coefficients (
      int n,
      const double *points,
      const double *values,
      double *coeffs,
      double *workspace
      ) override;

  virtual double compute_interpolated_value (
      double x,
      double a,
      double b,
      int n,
      const double *points,
      const double *coeffs
      ) const override;
 
  virtual double compute_interpolated_derivative (
      double x,
      double a,
      double b,
      int n,
      const double *points,
      const double *coeffs
      ) const override;
};

#endif // PIECEWISE_LINEAR_INTERPOLATION_FUNCTION_1D_H
