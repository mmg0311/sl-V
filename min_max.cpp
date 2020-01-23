#include<iostream>
#include<stdlib.h>
#include<time.h>
using namespace std;

struct ele{
	int m0,m1;
};


struct ele min1(int *a,int n,int l,int r){
	struct ele m;
	if(l == r){
		m.m0 = a[l];
		m.m1 = a[l];
		return m;
	}
	else{
		int mid = (l+r-1)/2;
		m.m0 = min(min1(a,n,l,mid).m0,min1(a,n,mid+1,r).m0 );
		m.m1 = max(min1(a,n,l,mid).m1,min1(a,n,mid+1,r).m1);
	}
	return m;
}

int main(){
	int *arr;
	clock_t start, end;
     	double cpu_time_used;
	struct ele e;
	int n,j=0,k=0;
	cout << "ENTER THE SIZE OF ARRAY : " ;
	cin >> n;
	arr = new int[n];
	cout << "ENTER ARRAY ELEMENTS : \n";
	start = clock();
	for(int i = 0 ; i < n ; i++){
		cout << "Array[" << i << "]: " ; 
		cin >> arr[i];
		if(i != 0){
			if(arr[i] >= arr[i-1]){
				j++;
			}else if(arr[i] < arr[i-1] ){
				k++;
			}
		}
		
	}
	end = clock();
	cpu_time_used = ((double)end-start)/CLOCKS_PER_SEC;
	cout << "TIME TAKEN BY FOR LOOP :" << cpu_time_used << endl;
	if(j == n-1){
		cout << "min :" << arr[0] << "\tmax :" << arr[n-1] << endl;
	}
	else if( k == n-1 ){
		cout << "min :" << arr[n-1] << "\tmax :" << arr[0] << endl;
	}else{ 
		start = clock();
		e = min1(arr,n,0,n-1); 
		end = clock();
		cpu_time_used = ((double)end-start)/CLOCKS_PER_SEC;
		cout << "min :" << e.m0 << "\tmax :" << e.m1 << "\ttime :" << cpu_time_used << endl;
	}
}
