#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<ll>;
using p2 = pair<ll, ll>;
using vp2 = vector<p2>;

#define repe(i, arr) for (auto& i : arr)
#define rep(i, b) for (int i = 0; i < (b); ++i)
#define all(x) begin(x), end(x)
#define first(a) (*begin(a))

// Idk, it's fast though
inline float sqrt1(const float& n)
{
    static union { int i; float f; } u;
    u.i = 0x5F375A86 - (*(int*)&n >> 1);
    return (int(3) - n * u.f * u.f) * n * u.f * 0.5f;
}

// Square roots are costly and there aren't that many possible differences between colors
vector<double> sqrtlookup(256 * 256 * 3, -1);

inline float coldist(tuple<int, int, int> a, tuple<int, int, int> b)
{
    int d1 = get<0>(a) - get<0>(b);
    int d2 = get<1>(a) - get<1>(b);
    int d3 = get<2>(a) - get<2>(b);
    int index = d1 * d1 + d2 * d2 + d3 * d3;
    return sqrtlookup[index];
}


int main() {
    cin.tie(0)->sync_with_stdio(0);

    int n;
    cin >> n;
    vector<tuple<int, int, int>> cols(n * 3);
    rep(i, n * 3)
    {
        int r;
        cin >> r;
        int g;
        cin >> g;
        int b;
        cin >> b;
        cols[i] = { r,g,b };
    }

    rep(i, 256 * 256 * 3) sqrtlookup[i] = sqrt1(i);

    vector<pair<float, int>> scores;

    // Check the color distance for each row
    for (int guessWidth = 20; guessWidth < 700; guessWidth++)
    {
        float score = 0;
        int j = 0;
        while (guessWidth * j + 1 + guessWidth - 1 < n)
        {
            rep(k, guessWidth)
            {
                score += coldist(cols[guessWidth * j + k], cols[(guessWidth * (j + 1)) + k]);
            }
            j++;
        }
        scores.push_back({ score, guessWidth });
    }

    sort(all(scores));


    // If the correct one is i, i-1,i-2,i-3 and i+1,i+2,i+3 are the most likely to be given falsely low scores

    vp2 centerscore(7);

    rep(i, 7) rep(j, 7) centerscore[i].first += abs(scores[i].second - scores[j].second);
    rep(i, 7) centerscore[i].second = i;
    sort(all(centerscore));

    vi candidates;
    rep(i, 7)
    {
        if (abs(scores[i].second - scores[centerscore[0].second].second) < 8)
        {
            candidates.push_back(scores[i].second);
        }
    }

    vector<pair<float, int>> linescore;
    auto getscore = [&](function<int(int)> getindex, function<int(int)> gettarget)
    {
        float score = 0;
        int j = 0;
        while (true)
        {
            int idx = getindex(j);
            int target = gettarget(idx);
            if (max(idx,target) >= n) break;
            score += coldist(cols[idx], cols[target]);
            j++;
        }
        return score;
    };
    // Look for lines in images
    rep(i, candidates.size())
    {
        int guessWidth = candidates[i];
        float score = 0;

        // -j-1 is right side line, +j is left side
        // distance from true=1
        score += getscore([&](int j) {return guessWidth * (j + 1) + j; }, [&](int idx) {return idx + 1; });
        score += getscore([&](int j) {return guessWidth * (j + 1) - j - 1; }, [&](int idx) {return idx - 1; });
        // distance from true=2
        score += getscore([&](int j) {return guessWidth * ((j + 2) / 2) - j - 1; }, [&](int idx) {return idx - 2 + idx % 2; });
        score += getscore([&](int j) {return guessWidth * ((j + 2) / 2) + j; }, [&](int idx) {return idx + 1 + idx % 2; });
        // distance from true=3
        score += getscore([&](int j) {return guessWidth * ((j + 3) / 3) - j - 1; }, [&](int idx) {return idx - 3 + idx % 3; });
        score += getscore([&](int j) {return guessWidth * ((j + 3) / 3) + j; }, [&](int idx) {return idx + 3 - idx % 3; });

        linescore.emplace_back(score, guessWidth);
    }
    sort(all(linescore));
    map<int, float> finalscores;
    rep(i, linescore.size())
    {
        finalscores[linescore[i].second] += pow(linescore[i].first / linescore[0].first, 1.7);
        rep(j, scores.size())
        {
            if (scores[j].second == linescore[i].second)
            {
                finalscores[linescore[i].second] += scores[j].first / scores[0].first;
                break;
            }
        }
    }
    linescore.resize(0);
    repe(score, finalscores)
    {
        linescore.emplace_back(score.second, score.first);
    }
    sort(all(linescore));
    cout << linescore[0].second << "\n";
    return 0;
}
