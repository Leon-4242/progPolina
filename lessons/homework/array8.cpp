#include <iostream>
#include <fstream>

void function(double* arr, int* n);

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

    function(arr, &n);

    std::ofstream out("output.txt");
    if (!out.is_open()) 
    {
        std::cerr << "Error output\n";
        return -3;
    }

    out << n << "\n";
    for (int i = 0; i < n; ++i) 
    {
        out << arr[i] << " ";
    }

    out.close();
    delete[] arr;
    return 0;
}

void function(double* arr, int* n) 
{

    int new_n = 0;
    int i = 0, j = 0;

    for (i = 0; i < *n; ++i) 
    {
        
        for (j = 0; j < i; ++j) 
        {
            if (arr[i] == arr[j]) 
            {
                break;
            }
        }

        if (j == i) 
        {
            arr[new_n] = arr[i];
            new_n++;
        }
    }

    *n = new_n;
}