#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <set>
using namespace std;

pair<long long, long long> floydCycle(long long N, long long x0, long long P, long long Q) {
    const long long MASK = (1LL << 31) - 1; //mond = 2^31
    auto f = [&](long long x) { return (x * P + Q) & MASK; }; //Reucrrence funtion, f(x) if you will

    long long tortoise = f(x0); //So, tortoise moves 1 step at a time
    long long hare = f(f(x0)); //Hare moves 2 at a time (caus it's faster uk)

    //Tortoise-hare technique
    //We either find a cycle or we die trying! (it stops if >N -> no cycle)
    long long steps = 1;
    while (tortoise != hare && steps <= N) {
        tortoise = f(tortoise);
        hare = f(f(hare));
        steps++;
    }
    if (steps > N) {
        return {N, 0}; // no cycle within N steps
    }

    //𝗜𝗙 there is a cycle (rejoice) ↓

    //Step 1: Find cycle length (lambda || next point where tortoise and hare meet || number of unique numbers in the sequence)
    long long lam = 1;
    hare = f(tortoise);
    while (tortoise != hare) {
        hare = f(hare);
        lam++;
    }

    //Step 2: Find pre-cycle length (mu || length of path until meeting || number of unique numbers before cycle start)
    long long mu = 0;
    tortoise = x0; hare = x0;
    for (long long i = 0; i < lam; i++) hare = f(hare);
    while (tortoise != hare) {
        tortoise = f(tortoise);
        hare = f(hare);
        mu++;
    }

    return {mu, lam};
}

long long uniqueCount(long long N, long long S, long long P, long long Q) {
    auto [mu, lam] = floydCycle(S, P, Q, N);
    if (lam == 0) {
        return N; // no cycle within N
    }

    long long total = mu + lam; // unique elements before 1rst repetition (counting, 0, 1, 2)
    return min(N, total);
}

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    unsigned int n, s, p, q;
    cin>>n>>s>>p>>q;   
  
    cout << uniqueCount(n, s, p, q) << endl; //Ɛ( · — ·)3
    
    return 0;
}

/*
𝗡𝗼𝘁𝗲𝘀:
 - N can be as large as 10^8, too many to brute-force with a set. (I tried)
 - Mod2^31 is arround 2billion posible states (I asked chatGPT).
 - 𝗧𝗵𝗲 𝘀𝗲𝗾𝘂𝗲𝗻𝗰𝗲 𝗶𝘀 𝗱𝗲𝘁𝗲𝗿𝗺𝗶𝗻𝗶𝘀𝘁𝗶𝗰, so eventualy it'll repeat pegeonhole principle (Calc prof is gonna be thriled I used that).
 - Once a value repeats, the sequence becomes preiodic.
 - 𝗟𝗶𝗲𝗻𝗲𝗮𝗿 𝗰𝗼𝗻𝗴𝘂𝗿𝗲𝗻𝘁𝗶𝗮𝗹 𝗴𝗲𝗻𝗲𝗿𝗮𝘁𝗼𝗿 (𝗟𝗖𝗚), 𝘀𝗼 -> unique elements = pre-cycle length + cycle length (but clipped to 𝑁)
 - We use Floyd algorithm for cycle detection

Input format:
 1. 100000000 1232077670 126810854 1536183938 <N, S, P, Q>

Output:
 2. 26 <unique numbers in sequence>
*/