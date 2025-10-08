#include <iostream>
#include <vector>
#include <string>
#include <algorithm>  // for ltrim, rtrim
#include <sstream>    // for split
#include <compare>    // for spaceship operator (C++20)
#include <iomanip> 
using namespace std;

string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);

/*
 * In the InsertionSort code below, there is an error. Can you fix it? 
 * Print the array only once, when it is fully sorted.
 */

void insertionSort(int N, int arr[]) {
    int i,j;
    int value;
    for(i=0;i<N;i++) //Mistake 1, i=0 instead of i=1
    {
        value=arr[i];
        j=i-1;
        while(j>=0 && value<arr[j]) //Mistake 2, j>=0 rather than j>0
        {
            arr[j+1]=arr[j];
            j=j-1;
        }
        arr[j+1]=value;
    }
    for(j=0;j<N;j++)
    {
        printf("%d",arr[j]);
        printf(" ");
    }
}
int main(void) {

    int N;
    scanf("%d", &N);
    int arr[N], i;
    for(i = 0; i < N; i++) {
        scanf("%d", &arr[i]);
    }

    insertionSort(N, arr);

    return 0;
}

/* 
Input format:
 1. 6           <length of array>
 2. 7 4 3 5 6 2 <array with unsorted element at the end>

Output:
 3. 2 3 4 5 6 7 <sorted array>
*/