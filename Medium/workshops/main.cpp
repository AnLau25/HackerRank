#include<bits/stdc++.h>

using namespace std;

//Define the structs Workshops and Available_Workshops.
//Implement the functions initialize and CalculateMaxWorkshops
struct Workshop{
    int starttime = 0 , duration = 0, endtime = 0;
    
    Workshop(int _startime, int _duration){
        starttime = _startime;
        duration = _duration;
        endtime = _startime + _duration;
    }
    
};

struct Available_Workshops{
    int len = 0;
    vector<Workshop> workshops;
    
    Available_Workshops(int _len, vector<Workshop> _workshops){
        len=_len;
        workshops=_workshops;
    }

};


Available_Workshops* initialize(int* startime, int* duration, int n){
    vector<Workshop> workshops;
        
    for (int i = 0; i<n; i++) {
        workshops.emplace_back(startime[i], duration[i]);      
    }
        
    return new Available_Workshops(n, workshops);
}

int CalculateMaxWorkshops(Available_Workshops* ptr){
    int current_end = 0, scheduled = 0;

    vector<Workshop> workshops = ptr->workshops;
    
    sort(workshops.begin(), workshops.end(), [](const Workshop& a, const Workshop& b) {
        return a.endtime < b.endtime;
    });
    
    for (Workshop& w : workshops){
        if (w.starttime >= current_end) {
            scheduled++;
            current_end = w.endtime;
        }
    }
    
    return scheduled;
}


int main(int argc, char *argv[]) {
    int n; // number of workshops
    cin >> n;
    // create arrays of unknown size n
    int* start_time = new int[n];
    int* duration = new int[n];

    for(int i=0; i < n; i++){
        cin >> start_time[i];
    }
    for(int i = 0; i < n; i++){
        cin >> duration[i];
    }

    Available_Workshops * ptr;
    ptr = initialize(start_time,duration, n);
    cout << CalculateMaxWorkshops(ptr) << endl;
    return 0;
}


/* 
Input format:
 1. 6 <number of workshops>
 2. 1 3 0 5 5 8 <array of workshop star time>
 3. 1 1 6 2 4 1 <array of workshop durations>

Output:
 4. 4 <workshops that don't interfere with eachother>

Note:
 - Struct=> Public by default
 - Class=> Private by default
 - Otherwise Struct == Class 
*/