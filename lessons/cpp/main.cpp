#include <iostream>
#include <fstream>
#include <cmath>

#define EPS 1e-15

bool function(std::ifstream &in, double x);

int main() 
{
    double x = 0;

    std::cout << "Enter x:\n";
    if (!(std::cin >> x)) 
    {
        std::cout << "Incorrect data\n";
        return -1;
    }

    std::ifstream in("input.txt");
    if (!in.is_open()) 
    {
        std::cerr << "Error input\n";
        return -2;
    }
    std::ofstream out("output.txt");
    if (!out.is_open()) 
    {
        std::cout << "Error output\n";
        return -3;
    }

	out << (function(in, x) ? "YES" : "NO") << "\n";

    in.close();
    out.close();
    return 0;
}

bool function(std::ifstream &in, double x) 
{
    double a = 0;
    
    while (in >> a) 
    {
        if (std::fabs(a - x) < EPS) 
        {
            return true;
        }
    }
    
    return false;
}
