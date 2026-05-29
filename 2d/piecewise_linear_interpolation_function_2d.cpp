
#include "piecewise_linear_interpolation_function_2d.h"
#include <assert.h>

double* piecewise_linear_interpolation_function_2d::allocate_workspace() const
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

void piecewise_linear_interpolation_function_2d::compute_points(
    int nx, int ny, double a, double b, double c, double d,
    double* points_x, double* points_y)
{
    compute_points_1d_uniform(nx, a, b, points_x);
    compute_points_1d_uniform(ny, c, d, points_y);
}

double* piecewise_linear_interpolation_function_2d::allocate_coefficients(int nx, int ny) const
{
    return new double[16 * (nx - 1) * (ny - 1)];
}

void piecewise_linear_interpolation_function_2d::compute_coefficients(
    int nx, int ny,
    const double* points_x,
    const double* points_y,
    const double* values,
    double* coeffs,
    double* /*workspace*/
)
{

    const double* f = values;
    const double* fx = values + nx * ny;
    const double* fy = values + 2 * nx * ny;
    const double* fxy = values + 3 * nx * ny;

    for (int i = 0; i < nx - 1; i++) {
        double hx = points_x[i + 1] - points_x[i];

        for (int j = 0; j < ny - 1; j++) {
            double hy = points_y[j + 1] - points_y[j];

            int i0j0 = i * ny + j;
            int i1j0 = (i + 1) * ny + j;
            int i0j1 = i * ny + (j + 1);
            int i1j1 = (i + 1) * ny + (j + 1);

            double A[16] = {
              1.0,                  0.0,              0.0,                   0.0,
              0.0,                  1.0,                    0.0,                   0.0,
              -3.0 / (hx * hx),     -2.0 / hx,        3.0 / (hx * hx),       -1.0 / hx,
              2.0 / (hx * hx * hx), 1.0 / (hx * hx),  -2.0 / (hx * hx * hx), 1.0 / (hx * hx)
            };

            double F[16] = {
              f[i0j0],  fy[i0j0],  f[i0j1],  fy[i0j1],
              fx[i0j0], fxy[i0j0], fx[i0j1], fxy[i0j1],
              f[i1j0],  fy[i1j0],  f[i1j1],  fy[i1j1],
              fx[i1j0], fxy[i1j0], fx[i1j1], fxy[i1j1]
            };

            double tmp[16] = { 0.0 };

            for (int row = 0; row < 4; row++) {
                for (int col = 0; col < 4; col++) {
                    double sum = 0.0;
                    for (int k = 0; k < 4; k++) {
                        sum += A[4 * row + k] * F[4 * k + col];
                    }
                    tmp[4 * row + col] = sum;
                }
            }

            A[0] = 1.0;  A[1] = 0.0;    A[2] = -3.0 / (hy * hy); A[3] = 2.0 / (hy * hy * hy);
            A[4] = 0.0;  A[5] = 1.0;    A[6] = -2.0 / hy;        A[7] = 1.0 / (hy * hy);
            A[8] = 0.0;  A[9] = 0.0;    A[10] = 3.0 / (hy * hy); A[11] = -2.0 / (hy * hy * hy);
            A[12] = 0.0; A[13] = 0.0;   A[14] = -1.0 / hy;       A[15] = 1.0 / (hy * hy);

            int index = 16 * (i * (ny - 1) + j);

            for (int row = 0; row < 4; row++) {
                for (int col = 0; col < 4; col++) {
                    double sum = 0.0;
                    for (int k = 0; k < 4; k++) {
                        sum += tmp[4 * row + k] * A[4 * k + col];
                    }
                    coeffs[index + 4 * row + col] = sum;
                }
            }

        }
    }
}
static int find(double x, const double* points, int n)
{
    if (x <= points[0]) return 0;
    if (x >= points[n-1]) return n-2;
            for (int k = 0; k < n-1; k++) {
                if(x >= points[k] && x <= points[k+1] ) return k;
    }
            return 0;
}

double piecewise_linear_interpolation_function_2d::compute_interpolated_value(
    double x, double y,
    double /*a*/, double /*b*/, double /*c*/, double /*d*/,
    int nx, int ny,

    const double *points_x,
    const double *points_y,
    const double *coeffs
) const
{
    int i = find(x, points_x, nx);
    int j = find(y, points_y, ny);
    int index = 16 * (i * (ny - 1) + j);

    double Pf = 0.0;

    double product_x = 1.0;
    for (int k = 0; k < 4; k++) {
        double product_y = 1.0;
        for (int l = 0; l < 4; l++) {
            double gamma = coeffs[index + 4 * k + l];

            Pf += gamma * product_x * product_y;

            product_y *= y - points_y[j];
        }
        product_x *= x - points_x[i];
    }

    return Pf;
}

double piecewise_linear_interpolation_function_2d::compute_interpolated_derivative(
    double, double, double, double, double, double,
    int, int, const double*, const double*, const double*
) const
{
    assert(false);
    return 0;
}
