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

void printArray(vector<int> &arr)
{
    for (int i = 0; i < arr.size(); i++)
        cout << i + 1 << ". " << arr[i] << endl;
    cout << "\n";
}

void zapis(vector<int> &arr)
{
    FILE *fwrite;
    int i = 0;
    char *num;
    time_t rawtime;
    struct tm *info;
    char buffer1[80];
    char buffer2[80];

    if (asprintf(&num, "%d", N) == -1)
    {
        perror("asprintf");
    }
    else
    {
        strcat(strcpy(buffer2, name), num);
        printf("%s\n", buffer2);
        free(num);
    }

    name = buffer2;
    time(&rawtime);
    info = localtime(&rawtime);
    strftime(buffer1, 80, "-%Y-%m-%d-%H-%M-%S", info);
    strcat(name, buffer1);
    strcat(name, ".ini");

    fwrite = fopen(name, "w");
    if (fwrite == NULL)
    {
        printf("Blad odczytu!");
        exit(1);
    }
    for (i = 0; i < N; i++)
    {
        fprintf(fwrite, "%d, ", array[i]);
    }
    fclose(fwrite);
    system("cls");
    printf("Zapisano do pliku: %s\n", name);
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
    t = clock();
    countSort(liczby);
    t = clock() - t;
    double czas = ((double)t) / CLOCKS_PER_SEC;
    printf("Czas wykonania: %f\n", czas);

    // printArray(liczby);
    char x;
    cout << "Posortowano" << endl
         << "Zapisac do pliku? < T / N > ";
    cin >> x;
    if (x == 'T')
    {
        zapis();
    }
    {
        /* code */
    }

    return 0;
}
