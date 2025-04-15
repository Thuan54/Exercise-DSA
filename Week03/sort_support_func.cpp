void swap(int &a, int &b){
    int temp = a;
    a = b;
    b = temp;
}
void heapify(int nums[], int n, int i){
	int  largest = i;
	int left = 2*i+1;
	int right = 2*i+2;
	if(left<n&&nums[left]>nums[largest])
		largest = left;
	if(right<n&&nums[right]>nums[largest])
		largest = right;
	if(largest!=i){
		swap(nums[i],nums[largest]);
		heapify(nums,n,largest);
	}
}
void merge(int nums[], int left, int mid, int right){
    int* temp = new int[right - left + 1];
    int k = 0, i = left, j = mid + 1;
    while(i <= mid && j <= right){
        if(nums[i] < nums[j]){
            temp[k++] = nums[i++];
        }
        else{
            temp[k++] = nums[j++];
        }
    }
    while(i <= mid) temp[k++] = nums[i++];
    while(j <= right) temp[k++] = nums[j++];
    for(i = left, k = 0; i <= right; i++,k++){
        nums[i] = temp[k];
    }
    delete[] temp;
}
void merge_sort_recursive(int nums[], int left, int right){
    if(left < right){
        int mid = left + (right - left)/2;
        merge_sort_recursive(nums,left,mid);
        merge_sort_recursive(nums,mid+1,right);
        merge(nums,left,mid,right);
    }
}
int partition(int nums[], int left, int right){
    int pi = left + (right - left)/2;
    int i = left, j = left-1;

    swap(nums[pi],nums[right]);
    pi = right;
    
    for(;i < right;i++){
        if(nums[i] <= nums[pi]){
            j++;
            swap(nums[i],nums[j]);
        }
    }
    swap(nums[j+1],nums[pi]);
    return j+1;
}
void quick_sort_recursive(int nums[], int left, int right){
	if(left<right){
		int pi = partition(nums,left,right);
		quick_sort_recursive(nums,left,pi-1);
		quick_sort_recursive(nums,pi+1,right);
	}
}
void counting_sort_for_radix(int nums[], int n, int exp, int base){
    int* output = new int[n];
    int* count = new int[base]();

    for(int i = 0; i < n; i++){
        int index = (nums[i]/exp)%base;
        count[index]++;
    }
    for(int i = 1; i < base; i++){
        count[i] += count[i - 1];
    }
    for(int i = n - 1; i >= 0; i--){
        int index = (nums[i]/exp)%base;
        output[count[index] - 1] = nums[i];
        count[index]--;
    }
    for(int i = 0; i < n; i++){
        nums[i] = output[i];
    }
    delete[] output;
    delete[] count;
}
int getBucketId(int nums[], int i, int min, int max, int m){
    float border = (float)(m -1)/(max - min);
    return (int)((nums[i] - min)*border);
}