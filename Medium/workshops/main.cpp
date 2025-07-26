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
1. 4 <number of commands>
2. 1 2 <1 = enqueue number>
3. 2 <2 = deuque from head>
4. 1 5
5. 3 <3 = print head>

Output:
𝘛𝘩𝘦 𝘴𝘶𝘥𝘥𝘦𝘯 𝘳𝘦𝘢𝘭𝘪𝘻𝘢𝘵𝘪𝘰𝘯 𝘵𝘩𝘢𝘵 𝘵𝘩𝘦 𝘦𝘯𝘲𝘶𝘦𝘶𝘦 𝘪𝘴 𝘢𝘭𝘭 𝘸𝘳𝘰𝘯𝘨 𝘢𝘯𝘥 𝘵𝘩𝘢𝘵 𝘵𝘩𝘪𝘴 𝘱𝘢𝘴𝘴𝘦𝘥 𝘵𝘩𝘦 𝘵𝘦𝘴𝘵𝘴 𝘣𝘺 𝘤𝘩𝘦𝘦𝘳 𝘮𝘪𝘳𝘢𝘤𝘭𝘦. Ɛ( · — ·)3
5 <only print shows smt in terminal>

*/