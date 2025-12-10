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


/*
Input:
 1. 2 <number of test cases>
 2. 5 2 <n integers in array, k intergers in window>
 3. 3 4 6 3 4 <array>
 4. 7 4
 5. 3 4 5 8 1 4 10

Output:
 6. 4 6 6 4 <local maxima per window of size k>
 7. 8 8 8 10

Note:
 The actual goal is more to 𝘬𝘦𝘦𝘱 𝘵𝘩𝘦 𝘮𝘢𝘹 𝘢𝘵 𝘵𝘩𝘦 𝘧𝘳𝘰𝘯𝘵 rather than finding the max
 We use a deque to maintain the indices of the elements in the current window
 Basicaly a sliding window maximum problem
*/