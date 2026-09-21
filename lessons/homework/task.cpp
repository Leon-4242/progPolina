#include <iostream>
#include <vector>
#include <cmath>
#include <limits>  // эпсилон с++
#include <fstream> // для записи в файл

const double EPS = std::numeric_limits<double>::epsilon();

typedef double (*func)(double); // для правой части уравнения
double f1(double); 
double f2(double);
std::vector<double> vector_u(int, double, double, func); // вычисляем вектор u
double trapez_formula(int, double, double, func); // приближение интеграла
std::vector<double> solve(int, double, double&, func); // ищем u1

double f1(double x) 
{
    return std::exp(x); 
}

double f2(double x) 
{
    return std::exp(x * x); 
}

std::vector<double> vector_u(int N, double h, double u1, func f) 
{
    std::vector<double> u(N + 1);
    u[0] = 0;
    u[1] = u1;

    for (int i = 1; i < N; i++) 
    {
        double x = i * h;
        u[i + 1] = (2 + h * h * std::cos(x * x)) * u[i] - u[i-1] - h * h * f(x);
    }
    return u;
}

double trapez_formula(int N, double h, double u1, func f) 
{
    std::vector<double> u = vector_u(N, h, u1, f);
    
    double sum = 0;
    double phi = 0;
    for (int i = 1; i < N; i++) 
    {
        sum += u[i];
    }
    
    phi = (sum + u[N]/2) * h;
    return phi;
}

std::vector<double> solve(int N, double h, double & u1, func f)
{
    double a = 0;
    double b = h;
    double phi_u1 = 0;
    double phi_a = trapez_formula(N, h, a, f);
    double phi_b = trapez_formula(N, h, b, f);

    while ((b - a) > EPS)
    {
        u1 = (a + b) / 2;
        phi_u1 = trapez_formula(N, h, u1, f);

        if (std::abs(phi_u1) < EPS)
        {
            break;
        }

        if (phi_a * phi_u1 < 0)
        {
            b = u1;
            phi_b = phi_u1;
        }
        else
        {
            a = u1;
            phi_a = phi_u1;
        }
    }

    return vector_u(N, h, u1, f);
}

int main()
{
    int N = 0;
    int number = 0;
    double h = 0; 
    double u1 = 0;
    func f;

    std::cout << "Enter N: ";
    std::cin >> N;

    h = 1.0 / N;

    std::cout << "Choose f(x):\n1: exp(x)\n2: exp(x^2)\nEnter 1 or 2: ";
    std::cin >> number;

    f = (number == 1) ? f1 : f2;


    std::vector<double> u = solve(N, h, u1, f);

    std::ofstream out("data.txt");
    if (out.is_open()) 
    {
        for (int i = 0; i <= N; i++) 
        {
            double x = i * h;
            out << x << " " << u[i] << "\n";
        }
        out.close();
    }

    return 0;
}
