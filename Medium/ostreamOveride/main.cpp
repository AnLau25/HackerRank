#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>  // for ltrim, rtrim
#include <sstream>    // for split
#include <compare>    // for spaceship operator (C++20)
#include <iomanip> 
using namespace std;

class Person {
public:
    Person(const string& first_name, const string& last_name) : first_name_(first_name), last_name_(last_name) {}
    const string& get_first_name() const {
      return first_name_;
    }
    const string& get_last_name() const {
      return last_name_;
    }
private:
    string first_name_;
    string last_name_;
};

// Enter your code here.
std::ostream& operator<<(std::ostream& os, const Person& p) {
    os  << "first_name=" << p.get_first_name() 
        << ",last_name=" << p.get_last_name()
        << "";
    return os;
}
// The person class has getters, but had it not, we'd have to declare ostream as a friend:
// friend std::ostream& operator<<(std::ostream& os, const Person& p);
// Then we'd be hable to call the variable sform the outside


int main() {
    string first_name, last_name, event;
    cin >> first_name >> last_name >> event;
    auto p = Person(first_name, last_name);
    cout << p << " " << event << endl;
    return 0;
}

/* 
Input format:
1. aabbcd <string to test>

Output:
2. NO <not a valid Sherlock Holmes>
*/