#include <iostream>
#include <fstream>

void function(double* arr, int n);

int main() 
{
    int n = 0;
    double* arr;

    std::ifstream in("input.txt");
    if (!in.is_open()) 
    {
        std::cerr << "Error input\n";
        return -1;
    }

    
    if (!(in >> n)) 
    {
        std::cerr << "Empty file\n";
        in.close();
        return -2;
    }

    arr = new double[n + 1];

    function(arr, n);

    std::ofstream out("output.txt");
    if (!out.is_open()) 
    {
        std::cerr << "Error output\n";
        delete[] arr;
        return -3;
    }

    for (int i = 0; i < n + 1; ++i) 
    {
        out << arr[i] << " ";
    }

    out.close();
    delete[] arr;
    return 0;
}

void function(double* arr, int n) 
{
    arr[0] = 1;
    for (int k = 1; k <= n; ++k) 
    {
        arr[k] = arr[k - 1] * (n - k + 1) / k;
    }
}
