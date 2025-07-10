#include <iostream>
#include <vector>
#include <string>
#include <algorithm>  // for ltrim, rtrim
#include <sstream>    // for split
#include <compare>    // for spaceship operator (C++20)
#include <iomanip> 
using namespace std;

class Person{
    protected:
        string name = "";
        int age = 0;
    
    public:
        Person() = default;
        Person(string _name, int _age) : name(_name), age(_age){}
        
        virtual void getdata() = 0;
        virtual void putdata() = 0;
};

class Professor : public Person{
    
    private:
        int pubs = 0, cur_Id = 0;
    
    public:
        static int counter;
        Professor() {
            counter++;
            cur_Id = counter;
        }
        
        void getdata() override{
            cin >> name >> age >> pubs;
        }
        
        void putdata() override{
            cout << name << " " << age << " " << pubs << " " << cur_Id << endl;
        }
};
int Professor::counter = 0;

class Student : public Person{
    
    private:
        vector<int> marks;
        int cur_Id = 0;
    
    public:
        static int counter;
        Student(){
            counter++;
            cur_Id = counter;
        }
    
        void getdata() override{
            cin >> name >> age;
            int mark;
            for (int i = 0; i < 6; i++) {
                cin >> mark;
                marks.push_back(mark);
            }
        }
        
        void putdata() override{
            int sum = 0;
            
            for(int i : marks){
                sum+=i;
            }
            cout << name << " " << age << " " << sum << " " << cur_Id << endl;
        }
};
int Student::counter = 0;

int main(){

    int n, val;
    cin>>n; //The number of objects that is going to be created.
    Person *per[n];

    for(int i = 0;i < n;i++){

        cin>>val;
        if(val == 1){
            // If val is 1 current object is of type Professor
            per[i] = new Professor;

        }
        else per[i] = new Student; // Else the current object is of type Student

        per[i]->getdata(); // Get the data from the user.

    }

    for(int i=0;i<n;i++)
        per[i]->putdata(); // Print the required output for each object.

    return 0;

}

/*
Intput:
 1. 3
 2. Peter
 3. Me
 4. Arxwwz

Output:
 5. Valid
 6. Too short: 2
 7. Invalid
*/

/*
Try catch example:

try{
    long long C;
    Server serve;
    C = serve.compute(A, B);
    cout<<C<<endl;
} catch(invalid_argument& e){
    cout<<"Exception: "<<e.what()<<endl;
} catch(bad_alloc& e){
    cout<<"Not enough memory"<<endl;
} catch(exception& e){ //catch general c++ exceptions 
    cout<<"Exception: "<<e.what()<<endl;
} catch (...){ //catch any other exception
    cout<<"Other Exception"<<endl;            
}

*/