#ifndef PIECEWISE_LINEAR_INTERPOLATION_FUNCTION_2D_H
#define PIECEWISE_LINEAR_INTERPOLATION_FUNCTION_2D_H


#include "function_2d.h"

class piecewise_linear_interpolation_function_2d final : public abstract_interpolation_function_2d
{
protected:
    virtual void compute_points(int nx, int ny, double a, double b, double c, double d, double* points_x, double* points_y) override;
    virtual double* allocate_coefficients(int nx, int ny) const override;
    virtual double* allocate_workspace() const override;
    virtual void compute_coefficients(
        int nx, int ny,
        const double* points_x,
        const double* points_y,
        const double* values,
        double* coeffs,
        double* workspace
    ) override;

    virtual double compute_interpolated_value(
        double x,
        double y,
        double a,
        double b,
        double c,
        double d,
        int nx,
        int ny,
        const double* points_x,
        const double* points_y,
        const double* coeffs
    ) const override;
    virtual double compute_interpolated_derivative(
        double x,
        double y,
        double a,
        double b,
        double c,
        double d,
        int nx,
        int ny,
        const double* points_x,
        const double* points_y,
        const double* coeffs
    ) const override;
};

#endif // PIECEWISE_LINEAR_INTERPOLATION_FUNCTION_2D_H

