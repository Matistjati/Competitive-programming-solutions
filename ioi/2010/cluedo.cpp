#include "grader.h"
#include "cluedo.h"

#include <vector>
using namespace std;

#define repp(i,a,b) for (int i = (a); i < (b); i++)
#define sz(x) ((int)(x).size())

struct Candidate {
    int a,b,c;
};

void Solve(){
    vector<Candidate> candidates;
    repp(a,1,7) repp(b,1,11) repp(c,1,7) candidates.push_back({a,b,c});

    while (1) {
        auto [a,b,c] = candidates[0];

        int res = Theory(a,b,c);
        if (res==0) return;
        vector<Candidate> new_candidates;
        vector<int> forbidden = {
            res==1?a:-1,
            res==2?b:-1,
            res==3?c:-1
        };
        for (auto [a1, b1, c1] : candidates) {
            if (a1 != forbidden[0] && b1 != forbidden[1] && c1 != forbidden[2]) new_candidates.push_back({a1,b1,c1});
        }
        candidates = new_candidates;
    }
}
