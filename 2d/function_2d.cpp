
#include "function_2d.h"

#include <assert.h>
#include <math.h>

#include "common_defs.h"


double compute_infinity_norm(
    const abstract_function_2d* func, double a, double b, double c, double d, int n_steps_x, int n_steps_y)
{
    double len_x = b - a;
    double len_y = d - c;
    double norm = fabs(func->evaluate(b, d));
    double step_x = len_x / static_cast<double> (n_steps_x);
    double step_y = len_y / static_cast<double> (n_steps_y);
    for (int i = 0; i < n_steps_x; i++)
    {
        for (int j = 0; j < n_steps_y; j++)
        {
            double z = fabs(func->evaluate(a + i * step_x, c + j * step_y));
            if (z > norm)
                norm = z;
        }
    }
    return norm;
}


double compute_derivative_x_infinity_norm(
    const abstract_function_2d* func, double a, double b, double c, double d, int n_steps_x, int n_steps_y)
{
    double len_x = b - a;
    double len_y = d - c;
    double norm = fabs(func->derivative_x(b, d));
    double step_x = len_x / static_cast<double> (n_steps_x);
    double step_y = len_y / static_cast<double> (n_steps_y);
    for (int i = 0; i < n_steps_x; i++)
    {
        for (int j = 0; j < n_steps_y; j++)
        {
            double z = fabs(func->derivative_x(a + i * step_x, c + j * step_y));
            if (z > norm)
                norm = z;
        }
    }
    return norm;
}

double compute_derivative_y_infinity_norm(
    const abstract_function_2d* func, double a, double b, double c, double d, int n_steps_x, int n_steps_y)
{
    double len_x = b - a;
    double len_y = d - c;
    double norm = fabs(func->derivative_y(b, d));
    double step_x = len_x / static_cast<double> (n_steps_x);
    double step_y = len_y / static_cast<double> (n_steps_y);
    for (int i = 0; i < n_steps_x; i++)
    {
        for (int j = 0; j < n_steps_y; j++)
        {
            double z = fabs(func->derivative_y(a + i * step_x, c + j * step_y));
            if (z > norm)
                norm = z;
        }
    }
    return norm;
}


function_2d::function_2d(int k)
{
    set_k(k);
}

const char* function_2d::get_function_name() const
{
    switch (m_k)
    {
    case function_id_t::constant:
        return "1.0";
    case function_id_t::linear_x:
        return "x";
    case function_id_t::linear_y:
        return "y";
    case function_id_t::linear:
        return "x + y";
    case function_id_t::radial:
        return "sqrt (x^2 + y^2)";
    case function_id_t::quadratic:
        return "x^2 + y^2";
    case function_id_t::exponent_quadratic:
        return "e^{x^2 - y^2}";
    case function_id_t::cauchy:
        return "1.0 / (25.0 * (x^2 + y^2) + 1)";
    case function_id_t::COUNT:
        assert(false);
        return "";
    }

    assert(false);
    return "";
}


double function_2d::evaluate(double x, double y) const
{
    switch (m_k)
    {
    case function_id_t::constant:
        return 1.0;
    case function_id_t::linear_x:
        return x;
    case function_id_t::linear_y:
        return y;
    case function_id_t::linear:
        return x + y;
    case function_id_t::radial:
        return sqrt(x * x + y * y);
    case function_id_t::quadratic:
        return x * x + y * y;
    case function_id_t::exponent_quadratic:
        return exp(x * x - y * y);
    case function_id_t::cauchy:
        return 1.0 / (25.0 * (x * x + y * y) + 1);
    case function_id_t::COUNT:
        assert(false);
        return 0.0;
    }

    assert(false);
    return 0.0;
}

double function_2d::derivative_x(double x, double y) const
{
    switch (m_k)
    {
    case function_id_t::constant:
        return 0.0;
    case function_id_t::linear_y:
        return 0.0;
    case function_id_t::linear_x:
        return 1.0;
    case function_id_t::linear:
        return 1.0;
    case function_id_t::radial:
    {
        double r = sqrt(x * x + y * y);
        if(x*x+y*y >= EPSILON_FOR_DIVISION)
            return x / r;
        else
            return 0;
    }
    case function_id_t::quadratic:
        return 2.0 * x;
    case function_id_t::exponent_quadratic:
        return 2.0 * x * exp(x * x - y * y);
    case function_id_t::cauchy:
    {
        return -50.0 * x / ((25.0 * (x * x + y * y) + 1.0) * (25.0 * (x * x + y * y) + 1.0));
    }
    case function_id_t::COUNT:
        assert(false);
        return 0.0;
    }
    assert(false);
    return 0.0;
}

double function_2d::derivative_y(double x, double y) const
{
    switch (m_k)
    {
    case function_id_t::constant:
        return 0.0;
    case function_id_t::linear_x:
        return 0.0;
    case function_id_t::linear_y:
        return 1.0;
    case function_id_t::linear:
        return 1.0;
    case function_id_t::radial:
    {
        return y / sqrt(x * x + y * y);
    }
    case function_id_t::quadratic:
        return 2.0 * y;
    case function_id_t::exponent_quadratic:
        return -2.0 * y * exp(x * x - y * y);
    case function_id_t::cauchy:
    {
        return -50.0 * y / ((25.0 * (x * x + y * y) + 1.0 )* (25.0 * (x * x + y * y) + 1.0));
    }
    case function_id_t::COUNT:
        assert(false);
        return 0.0;
    }
    assert(false);
    return 0.0;
}

double function_2d::derivative_xy(double x, double y) const
{
    switch (m_k)
    {
    case function_id_t::constant:
        return 0.0;
    case function_id_t::linear_x:
        return 0.0;
    case function_id_t::linear_y:
        return 0.0;
    case function_id_t::linear:
        return 0.0;
    case function_id_t::quadratic:
        return 0.0;
    case function_id_t::radial:
    {
        return -x * y / (sqrt(x * x + y * y) * sqrt(x * x + y * y) * sqrt(x * x + y * y));
    }
    case function_id_t::exponent_quadratic:
        return -4.0 * x * y * exp(x * x - y * y);
    case function_id_t::cauchy:
    {
        return 2500.0 * x * y / ((25.0 * (x * x + y * y) + 1.0) * (25.0 * (x * x + y * y) + 1.0) * (25.0 * (x * x + y * y) + 1.0));
    }
    case function_id_t::COUNT:
        assert(false);
        return 0.0;
    }
    assert(false);
    return 0.0;
}


abstract_interpolation_function_2d::~abstract_interpolation_function_2d()
{
    clear();
}

double abstract_interpolation_function_2d::evaluate(double x, double y) const
{
    return compute_interpolated_value(x, y, m_a, m_b, m_c, m_d, m_nx, m_ny, m_points_x, m_points_y, m_coeffs);
}

double abstract_interpolation_function_2d::derivative_x(double x, double y) const
{
    FIX_UNUSED (x);
    FIX_UNUSED (y);

    assert(false);
    return 0;


}

double abstract_interpolation_function_2d::derivative_y(double x, double y) const
{
    FIX_UNUSED (x);
    FIX_UNUSED (y);

    assert(false);
    return 0;

}

double abstract_interpolation_function_2d::derivative_xy(double x, double y) const
{
    FIX_UNUSED (x);
    FIX_UNUSED (y);

    assert(false);
    return 0;
}

void abstract_interpolation_function_2d::set_points(
    int nx, int ny, double a, double b, double c, double d, int p, double norm, const abstract_function_2d* func)
{
    clear();
    m_nx = nx;
    m_ny = ny;
    m_a = a;
    m_b = b;
    m_c = c;
    m_d = d;
    m_p = p;
    m_norm = norm;
    m_points_x = new double[nx];
    m_points_y = new double[ny];
    m_coeffs = allocate_coefficients(nx, ny);

    compute_points(nx, ny, a, b, c, d, m_points_x, m_points_y);

    double* workspace = allocate_workspace();

   
    double* values = new double[4 * nx * ny];

    int permutated_index_x = nx / 2;
    int permutated_index_y = ny / 2;

    for (int i = 0; i < nx; i++)
    {
        for (int j = 0; j < ny; j++)
        {
           
            values[i * ny + j] = func->evaluate(m_points_x[i], m_points_y[j]);
            values[i * ny + j + nx * ny] = func->derivative_x(m_points_x[i], m_points_y[j]);
            values[i * ny + j + 2 * nx * ny] = func->derivative_y(m_points_x[i], m_points_y[j]);
            values[i * ny + j + 3 * nx * ny] = func->derivative_xy(m_points_x[i], m_points_y[j]);

           
            if (i == permutated_index_x && j == permutated_index_y)
            {
                values[i * ny + j] += p * 0.1 * m_norm;
               
            }
        }
    }

    compute_coefficients(m_nx, m_ny, m_points_x, m_points_y, values, m_coeffs, workspace);

    delete[] values;
    delete[] workspace;
}

void abstract_interpolation_function_2d::clear()
{
    delete[] m_points_x;
    delete[] m_points_y;
    delete[] m_coeffs;
}


residual_function_2d::residual_function_2d(
    const abstract_function_2d* func, const abstract_function_2d* approx)
{
    m_func = func;
    m_approx = approx;
}

double residual_function_2d::evaluate(double x, double y) const
{
    return m_func->evaluate(x, y) - m_approx->evaluate(x, y);
}

double residual_function_2d::derivative_x(double x, double y) const
{
    return m_func->derivative_x(x, y) - m_approx->derivative_x(x, y);
}

double residual_function_2d::derivative_y(double x, double y) const
{
    return m_func->derivative_y(x, y) - m_approx->derivative_y(x, y);
}

double residual_function_2d::derivative_xy(double x, double y) const
{
    return m_func->derivative_xy(x, y) - m_approx->derivative_xy(x, y);
}
