// linear_interpolation_function_1d.h

#ifndef LINEAR_INTERPOLATION_FUNCTION_1D_H
#define LINEAR_INTERPOLATION_FUNCTION_1D_H

#include "function_1d.h"

class linear_interpolation_function_1d final : public abstract_interpolation_function_1d
{
protected:
  virtual void compute_points (int n, double a, double b, double *points) override;
  virtual double *allocate_coefficients (int n) const override;
  virtual double *allocate_workspace (int n) const override;
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
};

#endif // LINEAR_INTERPOLATION_FUNCTION_1D_H
