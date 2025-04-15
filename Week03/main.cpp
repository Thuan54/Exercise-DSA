#include <stdio.h>
#include <string.h>
#include <iostream>
#include "sort_algo.h"

using namespace std;

int main(int argc, char const *argv[])
{
	char* type_sort = new char[50];
	char* input_path = new char[100];
	char* output_path = new char[100];
	
	for(int i = 1;i<argc - 1;i+=2){
		if(strcmp(argv[i],"-a") == 0){
			strcpy(type_sort,argv[i+1]); 
		}
		else if(strcmp(argv[i],"-i") == 0){
			strcpy(input_path,argv[i+1]);
		}
		else if(strcmp(argv[i],"-o") == 0){
			strcpy(output_path,argv[i+1]);
		}
	}
	FILE* input_file = fopen(input_path,"r");
	FILE* output_file = fopen(output_path,"w");

	if(input_file == NULL || output_file == NULL){
		cout<<"Error opening file"<<endl;
		delete[] input_path;
		delete[] type_sort;
		delete[] output_path;
		fclose(input_file);
		fclose(output_file);
		return 1;
	}

	int n;
	fscanf(input_file,"%d",&n);
	int *nums = new int[n];
	
	for(int i =0;i<n;i++){
		if(fscanf(input_file,"%d",&nums[i]) == EOF){
			cout<<"Error reading file"<<endl;
			delete[] input_path;
			delete[] type_sort;
			delete[] output_path;
			delete[] nums;
			fclose(input_file);
			fclose(output_file);
			return 1;
		}
	}

	int sortIndex = -1;
	for(int i = 0; i < nOfSort; i++){
		if(strcmp(type_sort,typeOfSortName[i]) == 0){
			sortIndex = i;
			break;
		}
	}
	
	if(sortIndex == -1){
		cout<<"Error: sort type not found"<<endl;
		delete[] nums;
		delete[] input_path;
		delete[] type_sort;
		delete[] output_path;
		fclose(input_file);
		fclose(output_file);
		return 1;
	}
	
	typeOfSort[sortIndex](nums,n);

	fprintf(output_file,"%d\n",n);
	for(int i = 0; i < n; i++){
		fprintf(output_file,"%d ",nums[i]);
	}

	delete[]input_path;
	delete[]type_sort;
	delete[]output_path;
	delete[]nums;

	fclose(input_file);
	fclose(output_file);
	return 0;
}