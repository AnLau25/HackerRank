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
    for(i=0;i<N;i++)
    {
        value=arr[i];
        j=i-1;
        while(j>=0 && value<arr[j])
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
 1. 5         <length of array>
 2. 2 4 6 8 3 <array with unsorted element at the end>

Output:
 3. 2 4 6 8 8 <steps of sorting>
 4. 2 4 6 6 8 
 5. 2 4 4 6 8 
 6. 2 3 4 6 8 
*/