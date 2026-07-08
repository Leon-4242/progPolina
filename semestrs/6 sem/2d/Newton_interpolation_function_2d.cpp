#include "Newton_interpolation_function_2d.h"
#include <assert.h>

double* Newton_interpolation_function_2d::allocate_workspace() const
{
    return nullptr;
}

static void compute_points_1d_uniform(int n, double a, double b, double* points)
{
    assert(n > 1);
    double step = (b - a) / static_cast<double>(n - 1);

    for (int i = 0; i < n - 1; i++)
        points[i] = a + i * step;

    points[n - 1] = b;
}

void Newton_interpolation_function_2d::compute_points(
    int nx, int ny, double a, double b, double c, double d,
    double* points_x, double* points_y)
{
    compute_points_1d_uniform(nx, a, b, points_x);
    compute_points_1d_uniform(ny, c, d, points_y);
}

double* Newton_interpolation_function_2d::allocate_coefficients(int nx, int ny) const
{

    return new double[nx * ny];
}

void Newton_interpolation_function_2d::compute_coefficients(
    int nx, int ny,
    const double* points_x,
    const double* points_y,
    const double* values_in,
    double* coeffs,
    double* /*workspace*/
)
{

    for (int i = 0; i < nx * ny; i++) {
        coeffs[i] = values_in[i];
    }


    for (int j = 0; j < ny; j++) {
        for (int i = 1; i < nx; i++) {
            for (int k = nx - 1; k >= i; k--) {
                int curr = k * ny + j;
                int prev = (k - 1) * ny + j;
                coeffs[curr] = (coeffs[curr] - coeffs[prev]) / (points_x[k] - points_x[k - i]);
            }
        }
    }


    for (int i = 0; i < nx; i++) {
        for (int j = 1; j < ny; j++) {
            for (int k = ny - 1; k >= j; k--) {
                int curr = i * ny + k;
                int prev = i * ny + (k - 1);
                coeffs[curr] = (coeffs[curr] - coeffs[prev]) / (points_y[k] - points_y[k - j]);
            }
        }
    }
}

double Newton_interpolation_function_2d::compute_interpolated_value(
    double x, double y,
    double /*a*/, double /*b*/, double /*c*/, double /*d*/,
    int nx, int ny,
    const double* points_x,
    const double* points_y,
    const double* coeffs
) const
{

    double Pf = 0.0;

    for (int i = 0; i < nx; i++)
    {
        for (int j = 0; j < ny; j++)
        {

            double product_x = 1.0;
            for (int k = 0; k < i; k++) {
                product_x *= (x - points_x[k]);
            }

            double product_y = 1.0;
            for (int l = 0; l < j; l++) {
                product_y *= (y - points_y[l]);
            }

            double f = coeffs[i * ny + j];

            Pf += f * product_x * product_y;
        }
    }

    return Pf;
}
double Newton_interpolation_function_2d::compute_interpolated_derivative(
    double, double, double, double, double, double,
    int, int, const double*, const double*, const double*
) const
{
    assert(false);
    return 0;
}
