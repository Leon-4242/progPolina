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

    arr = new double[n];

    for (int i = 0; i < n; ++i) 
    {
        in >> arr[i];
    }
    in.close();

    function(arr, n);

    std::ofstream out("output.txt");
    if (!out.is_open()) 
    {
        std::cerr << "Error output\n";
        delete[] arr;
        return -3;
    }

    for (int i = 0; i < n; ++i) 
    {
        out << arr[i] << " ";
    }

    out.close();
    delete[] arr;
    return 0;
}

void function(double* arr, int n) 
{
    double tmp = 0;

    tmp = arr[n - 1];
    for (int i = n - 1; i > 0; --i) 
    {
        arr[i] = arr[i - 1];
    }

    arr[0] = tmp;

}