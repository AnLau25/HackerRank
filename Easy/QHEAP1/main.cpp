#include <cmath>
#include <sstream>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

class minHeap{
    private:
        vector<int> arr;
        int size = 0;

        void heapify (int idx){
            int smalest = idx;
            int left = 2*idx + 1;
            int right = 2*idx + 2;

            if(left<size && arr[left]<arr[smalest]){
                smalest=left;
            }
            if(right<size && arr[right]<arr[smalest]){
                smalest=right;
            }

            if (smalest!=idx){
                swap(arr[idx],arr[smalest]);
                heapify(smalest);
            }

        }

    public:
        minHeap() = default;
        minHeap(int capacity) : arr(capacity){}
        minHeap(vector<int> array) : arr(array),size(array.size()){
            for (int i = size / 2 - 1; i >= 0; --i) { 
                //Gotta heapify() for eachelement in the array Ɛ( · — ·)3
                heapify(i);
            }
        }

        void insert(int key){
            arr.push_back(key);
            size++;

            int idx = size-1;

            while (idx!=0 && key<arr[(idx-1)/2])
            {
                swap(arr[(idx-1)/2], arr[idx]);
                idx = (idx-1)/2;
            }

        }

        void remove(int key){
            if (arr.empty()) return;

            int idx = -1;

            for (int i = 0; i<size; i++){
                if(arr[i]==key){
                    idx = i;
                    break;
                }
            }

            if(idx==-1){
                cout<<"Key not found";
                return;
            }

            swap(arr[idx], arr[size-1]);
            arr.pop_back();
            size--;

            heapify(idx);         
        }

        void printMin() const{ // cause we dont modif the heap
            if(arr.empty()) return; 

            cout<<arr.front()<<endl;
        }       
};

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */

    minHeap hippy = minHeap();
    
    vector<vector<int>> cmds;
    
    int counter = 0;
    std::cin >> counter;
    std::cin.ignore();//Makes sure cin ignores next line (since it's getline) 

    while(counter-->0)
    {   
        std::string line;
        std::getline(std::cin, line); //Takes a full line of code
        std::istringstream iss(line);

        vector<int> com;
        int val;

        while (iss>>val){//Pushes the input into command
            com.push_back(val);
        }

        cmds.push_back(com);//Com to commands
    }

    for(vector<int> com : cmds)//Exhecutes the commands
    {
        if (com[0]==1){
            hippy.insert(com[1]);
        }else if (com[0]==2){
            hippy.remove(com[1]);
        }else if (com[0]==3){
            hippy.printMin();
        }   
    }
    
    return 0;
}

/* 
Input format:
1. 5    <number of coms = 5>
2. 1 4  <insert 4>
3. 1 9  <insert 9>
4. 3    <print minimum>
5. 2 4  <delete 4>
6. 3    <print minimum>

Output: 
7. 4 <print minimum at the time of command call>
8. 9
*/