#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <iostream>
#include <time.h>
#include <cstring>
#include <string>

using namespace std;

using namespace std;
#define INF 99999999
#define powtorzenia 1
int const iteracje[13] = {10, 20, 50, 100, 200, 300, 400, 500, 600, 700, 800, 900, 1000};

int saveTime(int in, double czas)
{
    FILE *file;
    char *buff;
    file = fopen("czasy.ini", "a");
    if (file == NULL)
    {
        cout << "Blad pliku 'czasy.txt'" << endl;
        return 1;
    }

    string tekst;
    tekst = "Rozmiar: " + to_string(in) + ", czas: " + to_string(czas) + "s, l. powtorzen:" + to_string(powtorzenia) +"\n";
    cout << tekst << endl;
    buff = &tekst[0];
    fputs(buff, file);
    fclose(file);
}

int main()
{
    clock_t t;
    int size = 1000;
    int **graf = new int *[size];
    for (int i = 0; i < size; ++i)
    {
        graf[i] = new int[size];
    }
    FILE *file;
    file = fopen("skierowana.txt", "r");

    if (file == NULL)
    {
        printf("Error reading file\n");
        exit(1);
    }

    int newNumber = 0;
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            {
                fscanf(file, "%d,", &newNumber);
                graf[i][j] = newNumber;
            }
        }
    }
    fclose(file);

    // cout << "Edge"
    //      << " : "
    //      << "Weight";
    // cout << endl;

    for (int it = 0; it < 13; it++)
    {
        
        t = clock();
        for (int m = 0; m < powtorzenia; m++)
        {
            int no_edge;
            int *selected = new int[iteracje[it]];
            memset(selected, false, sizeof(selected));
            no_edge = 0;
            selected[0] = true;

            int x;
            int y;

            
            while (no_edge < iteracje[it] - 1)
            {
                int min = INF;
                x = 0;
                y = 0;

                for (int i = 0; i < iteracje[it]; i++)
                {
                    if (selected[i])
                    {
                        for (int j = 0; j < iteracje[it]; j++)
                        {
                            if (!selected[j] && graf[i][j])
                            {
                                if (min > graf[i][j])
                                {
                                    min = graf[i][j];
                                    x = i;
                                    y = j;
                                }
                            }
                        }
                    }
                }
                // cout << x << " - " << y << " :  " << graf[x][y];
                // cout << endl;
                selected[y] = true;
                no_edge++;
            }
            delete[] selected;
        }
        t = clock() - t;
        double czas = ((double)t) / CLOCKS_PER_SEC;
        saveTime(iteracje[it], czas);
        
    }
    delete[] graf;
}