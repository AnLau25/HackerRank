#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <set>
using namespace std;

pair<long long, long long> floydCycle(long long x0, long long P, long long Q, long long N) {
    const long long MASK = (1LL << 31) - 1;
    auto f = [&](long long x) { return (x * P + Q) & MASK; };

    long long tortoise = f(x0);
    long long hare = f(f(x0));

    long long steps = 1;
    while (tortoise != hare && steps <= N) {
        tortoise = f(tortoise);
        hare = f(f(hare));
        steps++;
    }
    if (steps > N) {
        return {N, 0}; // no cycle within N steps
    }

    // Find cycle length (lam)
    long long lam = 1;
    hare = f(tortoise);
    while (tortoise != hare) {
        hare = f(hare);
        lam++;
    }

    // Find pre-cycle length (mu)
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

long long uniqueCount(long long S, long long P, long long Q, long long N) {
    auto [mu, lam] = floydCycle(S, P, Q, N);
    if (lam == 0) {
        return N; // no cycle within N
    }
    long long total = mu + lam; // unique elements before repetition
    return min(N, total);
}

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    unsigned int n, s, p, q;
    cin>>n>>s>>p>>q;   
  
    cout << uniqueCount(s, p, q, n) << endl; 
    
    return 0;
}
