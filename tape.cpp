#include <bits/stdc++.h>
using namespace std;

int main(){
	vector<int> c;
	vector<int>l;
	vector<int>sum;
	vector<int>::iterator ptr; 
	int n = 0,m = 0,count=0,temp,rr=0,j=0;
	double mrt;
	cout << "ENTER N(no. of paradigms) :" ;
	cin >> n;
	cout << "ENTER M(no. of tapes) :" ;
	cin >> m;
	cout << "ENTER THE PARADIGMS :";
	for(int i = 0 ; i < n ; i++){
		cin >> temp;
		l.push_back(temp);
	}
	cout << "ENTER THE CAPACITIES :";
	for(int i = 0 ; i < m ; i++){
		cin >> temp;
		c.push_back(temp);
	}
	cout << "IS IT A ROUND ROBIN IF YES(ENTER 1) IF NO(ENTER 0) : " ;
	cin >> rr;
	sort(l.begin(),l.end());
	sum.push_back(0);
	for(int i = 0 ; i < n ; i++){
		if(rr == 1){
			//ROUND ROBIN
			j = i%m;
			cout << j << endl;
		}
		else{
			ptr = sum.end()-1;
			if((*ptr + l[i]) <= c[j]){
				sum.push_back(*ptr + l[i]);
				count++;
			}else{
				j++;
				temp = accumulate(sum.begin(),sum.end(),0);
				cout << "count : " << count << " sum : " << temp << endl ;
				mrt = temp/(double)count;
				cout << "MRT = " << mrt << endl;
				sum.clear();
				count = 1;
				sum.push_back(l[i]);
				if(m <= j){
					break;
				}
			}
		}
	}
	
}
