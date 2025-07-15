#include <iostream>
#include <deque> 
#include <algorithm>
using namespace std;

void printKMax(int arr[], int n, int k){
    //Write your code here.
    int max = 0;
    deque<int> dq;
    
    for (int i = 0; i < n; ++i) {
        // Remove indices from the back while arr[i] >= arr[dq.back()]
        while (!dq.empty() && arr[i] >= arr[dq.back()])
            dq.pop_back();

        dq.push_back(i);

        // Remove front if it's outside the window
        if (dq.front() <= i - k)
            dq.pop_front();

        // Print max only when the first window is fully traversed
        if (i >= k - 1)
            cout << arr[dq.front()] << " ";
    }
    cout<<endl;
}

int main(){
  
	int t;
	cin >> t;
	while(t>0) {
		int n,k;
    	cin >> n >> k;
    	int i;
    	int arr[n];
    	for(i=0;i<n;i++)
      		cin >> arr[i];
    	printKMax(arr, n, k);
    	t--;
  	}
  	return 0;
}
