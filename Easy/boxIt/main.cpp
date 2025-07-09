#include <iostream>
#include <vector>
#include <string>
#include <algorithm>  // for ltrim, rtrim
#include <sstream>    // for split
#include <compare>    // for spaceship operator (C++20)
#include <iomanip> 
using namespace std;

//Implement the class Box  
//l,b,h are integers representing the dimensions of the box

// The class should have the following functions : 

// Constructors: 
// Box();
// Box(int,int,int);
// Box(Box);


// int getLength(); // Return box's length
// int getBreadth (); // Return box's breadth
// int getHeight ();  //Return box's height
// long long CalculateVolume(); // Return the volume of the box

//Overload operator < as specified
//bool operator<(Box& b)

//Overload operator << as specified
//ostream& operator<<(ostream& out, Box& B)

class Box{

    private:
        int l = 0, b = 0, h = 0;
    
    public:
        Box() = default;
        Box(int _l, int _b, int _h){
            l = _l;
            b = _b;
            h = _h;
        }
        Box(Box& other_box){
            l = other_box.getLength();
            b = other_box.getBreadth();
            h = other_box.getHeight();
        }
        
        int getLength(){
            return l;
        }
        
        int getBreadth(){
            return b;
        }
        
        int getHeight(){
            return h;
        }
        
        long long CalculateVolume(){
            return 1LL*l*b*h;
        }
        
        bool operator<(Box& other_box){
            int _l = other_box.getLength();
            int _b = other_box.getBreadth();
            int _h = other_box.getHeight();
            
            if (l<_l){
                return true;
            }
            
            if (b<_b && l==_l){
                return true;
            }
            
            if (h<_h && b==_b && l==_l){
                return true;
            }
            
            return false;
        }
        
        friend ostream& operator<<(ostream& os, const Box& box);
  
};

ostream& operator<<(ostream& os, Box& box){

    os<<box.getLength()<<" "<<box.getBreadth()<<" "<<box.getHeight()<<" ";
            
    return os;
}


void check2()
{
	int n;
	cin>>n;
	Box temp;
	for(int i=0;i<n;i++)
	{
		int type;
		cin>>type;
		if(type ==1)
		{
			cout<<temp<<endl;
		}
		if(type == 2)
		{
			int l,b,h;
			cin>>l>>b>>h;
			Box NewBox(l,b,h);
			temp=NewBox;
			cout<<temp<<endl;
		}
		if(type==3)
		{
			int l,b,h;
			cin>>l>>b>>h;
			Box NewBox(l,b,h);
			if(NewBox<temp)
			{
				cout<<"Lesser\n";
			}
			else
			{
				cout<<"Greater\n";
			}
		}
		if(type==4)
		{
			cout<<temp.CalculateVolume()<<endl;
		}
		if(type==5)
		{
			Box NewBox(temp);
			cout<<NewBox<<endl;
		}

	}
}

int main()
{
	check2();
}

/* 
Input format:
1. 6 <number of Boxes>
2. 2 1039 3749 8473 <box dimentions preceded by a query number>
3. 4
4. 3 1456 3836 283
5. 3 729 3749 272
6. 2 4839 283 273

*/