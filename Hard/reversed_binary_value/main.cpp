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
 1. 8 4 <number queries = 8; LRUCache capacity = 4>
 2. set 4 2
 3. set 2 7
 4. get 2
 6. set 1 8
 7. set 5 9
 8. set 6 15
 9. get 4
11. get 5

Output:
 5. 7
10. -1
12. 9
*/