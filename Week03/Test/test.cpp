#include <bits/stdc++.h>
#include "sort_algo.h"
#include "DataGenerator.h"
using namespace std;

int main()
{
    int dataSize[] = {10000,30000,50000,100000};
    int dataOrder[] = {0, 1, 2, 3};
    const char dataOrderName[][20] = {"Random", "Sorted", "Reverse Sorted", "Almost Sorted"};
    int nOfDataSize = sizeof(dataSize) / sizeof(dataSize[0]);
    int nOfDataOrder = sizeof(dataOrder) / sizeof(dataOrder[0]);

    FILE *statisticFile = fopen("statistic2.txt", "w");
    if (statisticFile == NULL)
    {
        cout << "Error opening file" << endl;
        return 1;
    }

    for (int i = 0; i < nOfDataOrder; i++)
    {
        fprintf(statisticFile, "Data Order: %s\n", dataOrderName[i]);
        fprintf(statisticFile, "Data Size,Sort Type,Time Taken,Number of Comparisons\n");
        for (int j = 0; j < nOfDataSize; j++)
        {
            int n = dataSize[j];
            int *nums = new int[n];
            GenerateData(nums, n, dataOrder[i]);
            int *numsCopy = new int[n];
            for (int k = 0; k < nOfSort; k++)
            {

                for (int l = 0; l < n; l++)
                {
                    numsCopy[l] = nums[l];
                }
                unsigned long long countCompare = 0;
                clock_t start = clock();
                typeOfSort[k](numsCopy, n, countCompare);
                clock_t end = clock();
                double timeTaken = (double)(end - start) / CLOCKS_PER_SEC;

                fprintf(statisticFile, "%d,%s,%f,%llu\n", n, typeOfSortName[k], timeTaken, countCompare);
            }
            delete[] numsCopy;
            delete[] nums;
        }
        fprintf(statisticFile, "\n");
    }
    fclose(statisticFile);
    return 0;
}
