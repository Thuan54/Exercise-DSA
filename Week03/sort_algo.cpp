#include "sort_support_func.h"
#include "sort_algo.h"

void (*typeOfSort[])(int nums[], int n) = {
    bubble_sort,
    selection_sort,
    insertion_sort,
    quick_sort,
    merge_sort,
    heap_sort,
    shell_sort,
    counting_sort,
    radix_sort,
    shaker_sort,
    flash_sort
};

const char* typeOfSortName[] = {
    "bubble-sort",
    "selection-sort",
    "insertion-sort",
    "quick-sort",
    "merge-sort",
    "heap-sort",
    "shell-sort",
    "counting-sort",
    "radix-sort",
    "shaker-sort",
    "flash-sort"
};

const int nOfSort = sizeof(typeOfSort)/sizeof(typeOfSort[0]);

void selection_sort(int nums[],int n){
	for(int i =0;i<n;i++){
		int min_pos = i;
		for(int j = i+1;j<n;j++){
			if(nums[j]<nums[min_pos]){
				min_pos = j;
			}
		}
		swap(nums[i],nums[min_pos]);
	}
}
void insertion_sort(int nums[], int n){
	for(int i =1;i<n;i++){
		int temp = nums[i];
		int j = i;
		while(j>0&&temp<nums[j-1]){
			nums[j] = nums[j-1];
			--j;
		}
		nums[j] = temp;
	}
}
void bubble_sort(int nums[], int n){
	for(int i =0;i<n-1;i++){
		bool swapped = false;
		for(int j = 0;j<n-i-1;j++){
			if(nums[j]>nums[j+1]){
				swap(nums[j],nums[j+1]);
				swapped = true;
			}
		}
		if(!swapped)
			break;
	}
}

void shaker_sort(int nums[], int n){
	int left = 0;
	int right = n - 1;
	int k = 0;
	while(left<right){
		for(int i = left;i<right;i++){
			if(nums[i]>nums[i+1]){
				swap(nums[i],nums[i+1]);
				k = i;
			}
		}
		right = k;
		for(int i = right;i>left;i--){
			if(nums[i]<nums[i-1]){
				swap(nums[i],nums[i-1]);
				k = i;
			}
		}
		left = k;
	}
}
void shell_sort(int nums[], int n) {
    for (int gap = n / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; i++) {
            int temp = nums[i];
            int j;
            for (j = i; j >= gap && nums[j - gap] > temp; j -= gap) {
                nums[j] = nums[j - gap];
            }
            nums[j] = temp;
        }
    }
}

void heap_sort(int nums[],int n){
	for(int i = n/2 - 1;i>=0;i--){
		heapify(nums,n,i);
	}
	for(int i =n-1;i>=0;i--){
		swap(nums[i],nums[0]);
		heapify(nums,i,0);
	}
}
void merge_sort(int nums[], int n){
    int l = 0;
    int r = n -1;
    merge_sort_recursive(nums, l, r);
}
void quick_sort(int nums[], int n){
    int l = 0;
    int r = n-1;
    quick_sort_recursive(nums, l, r);
}
void counting_sort(int nums[], int n){
    int max = nums[0];
    for(int i = 1; i<n;i++){
        max = max > nums[i] ? max : nums[i];
    }
    int *count = new int[max + 1]();

    for(int i = 0; i < n; i++){
        count[nums[i]]++;
    }
    for(int i = 1; i <= max; i++){
        count[i] += count[i - 1];
    }
    int *output = new int[n];
    for(int i = n - 1; i >= 0; i--){
        output[count[nums[i]] - 1] = nums[i];
        count[nums[i]]--;
    }
    for(int i = 0; i < n; i++){
        nums[i] = output[i];
    }
    delete[] count;
    delete[] output;
}
void radix_sort(int nums[], int n){
    int max = nums[0];
    for(int i = 1; i<n;i++){
        max = max > nums[i] ? max : nums[i];
    }
    int base = 10;
    for(int exp = 1; max/exp > 0; exp *= base){
        counting_sort_for_radix(nums, n, exp, base);
    }
}
void flash_sort(int nums[], int n){
    int max = nums[0];
    int min = nums[0];
    for(int i = 1; i<n;i++){
        max = max > nums[i] ? max : nums[i];
        min = min < nums[i] ? min : nums[i];
    }
    int m = (int)(0.45*n);
    if(m < 1) m = 1;
    
    int* buckets = new int[m]();
    for(int i = 0; i < n; i++){
        int b_id = getBucketId(nums, i, min, max, m);
        buckets[b_id]++;
    }
    for(int i = 1; i < m; i++){
        buckets[i] += buckets[i - 1];
    }

    int* bucket_starts = new int[m];
    bucket_starts[0] = 0;
    for(int i = 1; i < m; i++){
        bucket_starts[i] = buckets[i - 1];
    }

    for(int b_id_curr = m - 2; b_id_curr >= 0; b_id_curr--){
        for(int i = bucket_starts[b_id_curr]; i < buckets[b_id_curr]; i++){
            int b_id = getBucketId(nums, i, min, max, m);
            while(b_id != b_id_curr){
                int idx = buckets[b_id] - 1;
                buckets[b_id]--;
                swap(nums[i],nums[idx]);
                b_id = getBucketId(nums, i, min, max, m);
            }
        }
    }

    insertion_sort(nums, n);
    delete[] bucket_starts;
    delete[] buckets;
}