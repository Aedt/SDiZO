#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <algorithm>
#include <iostream>
#include <vector>
#include <time.h>
#include <string>
using namespace std;

#define N 1000000

void countSort(vector<int> &arr)
{
    int max = *max_element(arr.begin(), arr.end());
    int min = *min_element(arr.begin(), arr.end());
    int range = max - min + 1;

    vector<int> count(range), output(arr.size());
    for (int i = 0; i < arr.size(); i++)
        count[arr[i] - min]++;

    for (int i = 1; i < count.size(); i++)
        count[i] += count[i - 1];

    for (int i = arr.size() - 1; i >= 0; i--)
    {
        output[count[arr[i] - min] - 1] = arr[i];
        count[arr[i] - min]--;
    }

    for (int i = 0; i < arr.size(); i++)
        arr[i] = output[i];
}

void heapify(std::vector<int> &arr, int size, int i)
{
    int max = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    if (left < size && arr[left] > arr[max])
        max = left;
    if (right < size && arr[right] > arr[max])
        max = right;
    if (max != i)
    {
        int temp = arr[i];
        arr[i] = arr[max];
        arr[max] = temp;
        heapify(arr, size, max);
    }
}

void heapSort(std::vector<int> &arr)
{
    int size = arr.size();

    for (int i = size / 2 - 1; i >= 0; i--)
    {
        heapify(arr, size, i);
    }

    for (int i = size - 1; i >= 0; i--)
    {
        int temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;

        heapify(arr, i, 0);
    }
}

void zapis(vector<int> &arr, string name, int iter)
{
    FILE *fwrite;
    int i = 0;
    char *num;
    string liczb;
    time_t rawtime;
    struct tm *info;
    char buffer1[80];
    char buffer2[80];

    liczb = to_string(iter);
    name = name + liczb;
    time(&rawtime);
    info = localtime(&rawtime);
    strftime(buffer1, 80, "-%Y-%m-%d-%H-%M-%S", info);

    name = name + buffer1 + ".ini";
    const char *str = name.c_str();

    fwrite = fopen(str, "w");
    if (fwrite == NULL)
    {
        printf("Blad odczytu!");
        exit(1);
    }
    for (i = 0; i < iter; i++)
    {
        fprintf(fwrite, "%d, ", arr[i]);
    }
    fclose(fwrite);
    // cout << "Zapis: " << name << endl;
}

template <typename T>
vector<T> slice(vector<T> const &v, int m, int n)
{
    auto first = v.cbegin() + m;
    auto last = v.cbegin() + n + 1;
    vector<T> vec(first, last);
    return vec;
}

int main(int argc, char const *argv[])
{
    clock_t t;
    FILE *file = fopen("liczby.txt", "r");
    if (file == NULL)
    {
        cout << "Blad odczytu pliku" << endl;
    }
    int nn, i;
    vector<int> liczby;

    for (i = 0; i < N; i++)
    {
        fscanf(file, "%d, ", &nn);
        liczby.push_back(nn);
    }

    int testy[] = {1000, 2000, 5000, 10000, 20000, 50000, 100000, 200000, 500000, 1000000};

    cout << "Sortowanie przez zliczanie:" << endl;
    for (int i = 0; i < 10; i++)
    {
        vector<int> sub_vec = slice(liczby, 0, testy[i]);
        t = clock();
        countSort(sub_vec);
        t = clock() - t;
        double czas = ((double)t) / CLOCKS_PER_SEC;
        zapis(sub_vec, "Zliczanie-N", testy[i]);
        cout << "Czas wykonania dla N=" << testy[i] << ": " << czas << endl;
    }

    cout << endl << "Sortowanie przez kopcowanie" << endl;
    for (int i = 0; i < 10; i++)
    {
        vector<int> sub_vec = slice(liczby, 0, testy[i]);
        t = clock();
        heapSort(sub_vec);
        t = clock() - t;
        double czas = ((double)t) / CLOCKS_PER_SEC;
        zapis(sub_vec, "Kopcowanie-N", testy[i]);
        cout << "Czas wykonania dla N=" << testy[i] << ": " << czas << endl;
    }
    getchar();
    
    return 0;
}
