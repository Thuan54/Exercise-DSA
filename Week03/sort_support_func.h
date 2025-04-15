void swap(int &a, int &b);
void heapify(int nums[], int n, int i);
void merge(int nums[], int left, int mid, int right);
void merge_sort_recursive(int nums[], int left, int right);
void quick_sort_recursive(int nums[], int left, int right);
void counting_sort_for_radix(int nums[], int n, int exp, int base);
int getBucketId(int nums[], int i, int min, int max, int m);