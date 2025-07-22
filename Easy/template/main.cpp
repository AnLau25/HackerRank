#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <cassert>
using namespace std;

/*Write the class AddElements here*/
template <class T>
class AddElements{
    T element;
    
    public:
    AddElements(T _element){
        element = _element;
    }
    
    T add(T other_element){
        return element+other_element;
    }
    
    T concatenate(T other_element){
        return element+other_element;
    }
    
};

int main () {
  int n,i;
  cin >> n;
  for(i=0;i<n;i++) {
    string type;
    cin >> type;
    if(type=="float") {
        double element1,element2;
        cin >> element1 >> element2;
        AddElements<double> myfloat (element1);
        cout << myfloat.add(element2) << endl;
    }
    else if(type == "int") {
        int element1, element2;
        cin >> element1 >> element2;
        AddElements<int> myint (element1);
        cout << myint.add(element2) << endl;
    }
    else if(type == "string") {
        string element1, element2;
        cin >> element1 >> element2;
        AddElements<string> mystring (element1);
        cout << mystring.concatenate(element2) << endl;
    }
  }
  return 0;
}

/* 
Input format:
1. 7 <length of array>
2. 1 2 1 2 1 3 2 <space separated array>

Output:
3. 2 <pairs of socks, because 3 socks are without pair>
*/