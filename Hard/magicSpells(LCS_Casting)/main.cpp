#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Spell { 
    private:
        string scrollName;
    public:
        Spell(): scrollName("") { }
        Spell(string name): scrollName(name) { }
        virtual ~Spell() { }
        string revealScrollName() {
            return scrollName;
        }
};

class Fireball : public Spell { 
    private: int power;
    public:
        Fireball(int power): power(power) { }
        void revealFirepower(){
            cout << "Fireball: " << power << endl;
        }
};

class Frostbite : public Spell {
    private: int power;
    public:
        Frostbite(int power): power(power) { }
        void revealFrostpower(){
            cout << "Frostbite: " << power << endl;
        }
};

class Thunderstorm : public Spell { 
    private: int power;
    public:
        Thunderstorm(int power): power(power) { }
        void revealThunderpower(){
            cout << "Thunderstorm: " << power << endl;
        }
};

class Waterbolt : public Spell { 
    private: int power;
    public:
        Waterbolt(int power): power(power) { }
        void revealWaterpower(){
            cout << "Waterbolt: " << power << endl;
        }
};

class SpellJournal {
    public:
        static string journal;
        static string read() {
            return journal;
        }
}; 
string SpellJournal::journal = "";

void counterspell(Spell *spell) {

/* Enter your code here. Read input from STDIN. Print output to STDOUT */
    if(Fireball* fire = dynamic_cast<Fireball*>(spell)){ 
        fire->revealFirepower();
        return;
    }
    if(Waterbolt* water = dynamic_cast<Waterbolt*>(spell)){ 
        water->revealWaterpower();
        return;
    }
    
    if(Thunderstorm* thunder = dynamic_cast<Thunderstorm*>(spell)){ 
        thunder->revealThunderpower();
        return;
    }
    
    if(Frostbite* frost = dynamic_cast<Frostbite*>(spell)){ 
        frost->revealFrostpower();
        return;
    }
    
    string spella = spell->revealScrollName();
    string spellb = SpellJournal::journal;
    
    vector<vector<int>> detect(spella.length() + 1, vector<int>(spellb.length() + 1, 0));
    
    for(int a = 1; a<=spella.length(); a++){
        for(int b = 1; b<=spellb.length(); b++){
            if(spella[a-1]==spellb[b-1]){
                detect[a][b] = 1 + detect[a-1][b-1];
            }else{
                detect[a][b] = max(detect[a-1][b], detect[a][b-1]);
            }
        }
    }
    
    cout<< detect[spella.length()][spellb.length()]<< endl;
    return;
}

class Wizard {
    public:
        Spell *cast() {
            Spell *spell;
            string s; cin >> s;
            int power; cin >> power;
            if(s == "fire") {
                spell = new Fireball(power);
            }
            else if(s == "frost") {
                spell = new Frostbite(power);
            }
            else if(s == "water") {
                spell = new Waterbolt(power);
            }
            else if(s == "thunder") {
                spell = new Thunderstorm(power);
            } 
            else {
                spell = new Spell(s);
                cin >> SpellJournal::journal;
            }
            return spell;
        }
};

int main() {
    int T;
    cin >> T;
    Wizard Arawn;
    while(T--) {
        Spell *spell = Arawn.cast();
        counterspell(spell);
    }
    return 0;
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