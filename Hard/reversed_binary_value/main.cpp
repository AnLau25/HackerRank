#include <iostream>
using namespace std;

// Enter your code for reversed_binary_value<bool...>()
template<bool...bits>
int reversed_binary_value(){
    
    bool binary[] = {bits...};
    int dec = 0, base = 1;
    
    for(bool bit : binary){
        dec += bit*base;
        base*=2;
    }
    
    return dec;
}



template <int n, bool...digits>
struct CheckValues {
  	static void check(int x, int y)
  	{
    	CheckValues<n-1, 0, digits...>::check(x, y);
    	CheckValues<n-1, 1, digits...>::check(x, y);
  	}
};

template <bool...digits>
struct CheckValues<0, digits...> {
  	static void check(int x, int y)
  	{
    	int z = reversed_binary_value<digits...>();
    	std::cout << (z+64*y==x);
  	}
};

int main()
{
  	int t; std::cin >> t;

  	for (int i=0; i!=t; ++i) {
		int x, y;
    	cin >> x >> y;
    	CheckValues<6>::check(x, y);
    	cout << "\n";
  	}
}

/* 
Input format: 
 1. 2 <number of test cases>
 2. 65 1 <x=65, 65-64=1>
 3. 10 0 


Output:
 4. 0100000000000000000000000000000000000000000000000000000000000000
 5. 0000000000100000000000000000000000000000000000000000000000000000

Notes:
 - you can, straight up, multiply by bools
 - it'll give you the binary 
*/