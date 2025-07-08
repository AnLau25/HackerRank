#include <iostream>
#include <vector>
#include <string>
#include <algorithm>  // for ltrim, rtrim
#include <sstream>    // for split
#include <compare>    // for spaceship operator (C++20)
#include <iomanip> 
using namespace std;

class Student{
    
    public:
        vector<int> scores;
        
        void input(){
            string scrlst;
            do {
                getline(cin, scrlst);
            } while (scrlst.find_first_not_of(" \t\r\n") == string::npos);
            stringstream ss(scrlst);
            
            int grade;
            
            while (ss>>grade) {
                scores.push_back(grade);
            }
            
        }
        
        int calculateTotalScore(){
            int sum = 0;
            
            for(int num : scores){
                sum+=num;
            }
            
            return sum;
        }
    
};


int main() {
    int n; // number of students
    cin >> n;
    Student *s = new Student[n]; // an array of n students
    
    for(int i = 0; i < n; i++){
        s[i].input();
    }

    // calculate kristen's score
    int kristen_score = s[0].calculateTotalScore();

    // determine how many students scored higher than kristen
    int count = 0; 
    for(int i = 1; i < n; i++){
        int total = s[i].calculateTotalScore();
        if(total > kristen_score){
            count++;
        }
    }

    // print result
    cout << count;
    
    return 0;
}

/*
Intput:
 1. 3 <number of students>
 2. 30 40 45 10 10 <space separated 5 grades by student>
 3. 40 40 40 10 10
 4. 50 20 30 10 10

Output:
 5. 1 <number of student where Student grades>Student 0 grades >
*/