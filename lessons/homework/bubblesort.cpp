#include <iostream>
#include <fstream>

void bubble_sort(double* arr, int n);

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

    bubble_sort(arr, n);

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

void bubble_sort(double* arr, int n) 
{
    double temp = 0;
    for (int i = 0; i < n - 1; ++i) 
    {
        for (int j = 0; j < n - i - 1; ++j) 
        {
            if (arr[j] > arr[j + 1]) 
            {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}