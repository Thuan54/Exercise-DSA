void swap(int &a, int &b);
void heapify(int nums[], int n, int i, unsigned long long &countCompare);
void merge(int nums[], int left, int mid, int right, unsigned long long &countCompare);
void merge_sort_recursive(int nums[], int left, int right, unsigned long long &countCompare);
void quick_sort_recursive(int nums[], int left, int right, unsigned long long &countCompare);
void counting_sort_for_radix(int nums[], int n, int exp, int base, unsigned long long &countCompare);
int getBucketId(int nums[], int i, int min, int max, int m);