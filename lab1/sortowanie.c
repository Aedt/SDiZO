#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define N 1000000

void swap(int *a, int *b)
{
    int t = *a;
    *a = *b;
    *b = t;
}

int partition(int array[], int low, int high)
{

    int pivot = array[high];

    int i = (low - 1);
    int j;

    for (j = low; j < high; j++)
    {
        if (array[j] <= pivot)
        {
            i++;
            swap(&array[i], &array[j]);
        }
    }
    swap(&array[i + 1], &array[high]);

    return (i + 1);
}

void quickSort(int array[], int low, int high)
{
    if (low < high)
    {
        int pi = partition(array, low, high);
        quickSort(array, low, pi - 1);
        quickSort(array, pi + 1, high);
    }
}

void zapisz(char name[], int array[])
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

int main()
{
    clock_t t;
    char *bubbleName = "bubbleSort-N";
    char *insertName = "insertSort-N";
    char *quickSortName = "quickSort-N";
    char *filename = "liczby.txt";
    FILE *fp = fopen(filename, "r");
    int *liczby = malloc(N * sizeof(*liczby));
    int *liczby_sort = malloc(N * sizeof(*liczby_sort));
    // int n_liczb = 1000;
    int i, j, k, temp, key;

    if (fp == NULL)
    {
        printf("Blad odczytu pliku.\n");
        exit(1);
    }

    int nowaLiczba;

    for (i = 0; i < N; i++)
    {
        fscanf(fp, "%d, ", &nowaLiczba);
        liczby[i] = nowaLiczba;
    }

    fclose(fp);

    // MENU

    char menu_option, menu_option2, menu_option3;

    do
    {

        for (k = 0; k < N; k++)
        {
            liczby_sort[k] = liczby[k];
        }
        fseek(stdin, 0, SEEK_END);
        system("cls");
        printf("Liczba wczytanych danych: %d\n\nMetody sortowania:\n\n",N);
        printf("a. babelkowe.\n");
        printf("b. przez wstawianie.\n");
        printf("c. quick sort.\n");
        // printf("d. przez scalanie.\n");
        printf("e. wyjscie z programu.\n\n");
        printf("Wybierz opcje: ");
        scanf("%c", &menu_option);

        switch (menu_option)
        {
        case 'a':
            system("cls");
            t = clock();
            for (i = 0; i < N; i++)
            {
                for (j = 0; j < N - 1; j++)
                {
                    if (liczby_sort[j] > liczby_sort[j + 1])
                    {
                        temp = liczby_sort[j];
                        liczby_sort[j] = liczby_sort[j + 1];
                        liczby_sort[j + 1] = temp;
                        // swap(&liczby_sort[j], &liczby_sort[j + 1]);
                    }
                }
            }
            t = clock() - t;
            double czas = ((double)t) / CLOCKS_PER_SEC;
            printf("Czas wykonania: %f\n", czas);

            do
            {
                fseek(stdin, 0, SEEK_END);
                printf("a. zapisz posortowane dane\n");
                printf("e. wroc do menu\n");
                scanf("%c", &menu_option2);
                switch (menu_option2)
                {
                case 'a':
                    zapisz(bubbleName, liczby_sort);
                    break;
                default:
                    printf("blad\n");
                    break;
                }
            } while (menu_option2 != 'e');

            break;

        // WSTAWIANIE
        case 'b':
            system("cls");
            t = clock();
            for (i = 1; i < N; i++)
            {
                key = liczby_sort[i];
                j = i - 1;
                while (j >= 0 && liczby_sort[j] > key)
                {
                    liczby_sort[j + 1] = liczby_sort[j];
                    j = j - 1;
                }
                liczby_sort[j + 1] = key;
            }
            t = clock() - t;
            double czas2 = ((double)t) / CLOCKS_PER_SEC;
            printf("Czas wykonania: %f\n", czas2);

            do
            {
                fseek(stdin, 0, SEEK_END);
                printf("a. zapisz posortowane dane\n");
                printf("e. wroc do menu\n");
                scanf("%c", &menu_option2);
                switch (menu_option2)
                {
                case 'a':
                    zapisz(insertName, liczby_sort);
                    break;
                default:
                    printf("blad\n");
                    break;
                }
            } while (menu_option2 != 'e');
            break;
        case 'c':
            system("cls");
            t = clock();
            quickSort(liczby_sort, 0, N - 1);
            t = clock() - t;
            double czas3 = ((double)t) / CLOCKS_PER_SEC;
            printf("Czas wykonania: %f\n", czas3);

            do
            {
                fseek(stdin, 0, SEEK_END);
                printf("a. zapisz posortowane dane\n");
                printf("e. wroc do menu\n");
                scanf("%c", &menu_option3);
                switch (menu_option3)
                {
                case 'a':
                    zapisz(quickSortName, liczby_sort);
                    break;
                default:
                    printf("blad\n");
                    break;
                }
            } while (menu_option3 != 'e');

            break;
            // case 'd':
            //     printf("brak");
            //     getch();
            //     break;

        default:
            // printf("blad\n");
            break;
        }

    } while (menu_option != 'e');
    free(liczby);
    free(liczby_sort);
}