#include <iostream>
#include <fstream>

void quick_sort(double* arr, int left, int right);
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
        std::cerr << "Empty or invalid file\n";
        in.close();
        return -2;
    }

    arr = new double[n];

    for (int i = 0; i < n; ++i) 
    {
        in >> arr[i];
    }
    in.close();

    quick_sort(arr, 0, n - 1);

    function(arr, &n);

    std::ofstream out("output.txt");
    if (!out.is_open()) 
    {
        std::cerr << "Error output\n";
        delete[] arr;
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

void quick_sort(double* arr, int left, int right) 
{
    int i = left;
    int j = right;
    double temp = 0;
    double pivot = arr[left + (right - left) / 2];

    while (i <= j) 
    {
        while (arr[i] < pivot) 
        i++;
        while (arr[j] > pivot) 
        j--;

        if (i <= j) 
        {

            temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;

            i++;
            j--;
        }
    }

    if (left < j) 
    {
        quick_sort(arr, left, j);
    } 
    if (i < right)
    {
        quick_sort(arr, i, right);
    } 
}

void function(double* arr, int* n) 
{

    int k = 0;

    for (int i = 0; i < *n - 1; ++i) 
    {
        if (arr[i] == arr[i+1]) 
        {
            continue;
            
        }

        arr[k++] = arr[i];
    }
    arr[k++] = arr[*n - 1];
    *n = k; 
}
