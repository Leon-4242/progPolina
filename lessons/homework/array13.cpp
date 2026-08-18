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
    double prev = 0, curr = 0;
    if (n < 3)
    {
        return;
    }

    prev = arr[0];

    for (int i = 1; i < n - 1; ++i) 
    {
        curr = arr[i];
        arr[i] = (prev + arr[i + 1]) / 2;
        prev = curr;
    }
}