#ifndef SORTS_H
#define SORTS_H

void bubble_sort(int nums[], int n, unsigned long long &countCompare);
void selection_sort(int nums[], int n, unsigned long long &countCompare);
void insertion_sort(int nums[], int n, unsigned long long &countCompare);
void quick_sort(int nums[], int n, unsigned long long &countCompare);
void merge_sort(int nums[], int n, unsigned long long &countCompare);
void heap_sort(int nums[], int n, unsigned long long &countCompare);
void shell_sort(int nums[], int n, unsigned long long &countCompare);
void counting_sort(int nums[], int n, unsigned long long &countCompare);
void radix_sort(int nums[], int n, unsigned long long &countCompare);
void shaker_sort(int nums[], int n, unsigned long long &countCompare);
void flash_sort(int nums[], int n, unsigned long long &countCompare);

extern void (*typeOfSort[])(int nums[], int n, unsigned long long &countCompare);
extern const int nOfSort;
extern const char *typeOfSortName[];

#endif
