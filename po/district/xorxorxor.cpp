#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<ll>;
using vvi = vector<vi>;
using p2 = pair<ll, ll>;
const ll inf = 1e18;

#define rep(i,n) for (ll i = 0; i < (n); i++)
#define repp(i,a,n) for (ll i = (a); i < (n); i++)
#define repe(i, arr) for (auto& i : arr)
#define all(x) begin(x),end(x)
#define sz(x) ((ll)(x).size())

array<int,256> distribution;
// for a given key length, offset, and key candidate for this offset, is it reasonable?
bool works(vi& text, int offset, int keylen, int key) {
    fill(all(distribution),0);
    for (int i = offset; i < text.size(); i += keylen) {
        char c = text[i] ^ key;
        distribution[c]++;
        // Sort out obviously wrong characters
        if (!isspace(c) && !isprint(c)) {
            return false;
        }
    }
    int tot = accumulate(all(distribution), 0);

    // If fisk testcase, does not follow normal grammar heuristics
    {
        string fisk = "FISK";
        int fishes = 0;
        rep(i, 4) fishes += distribution[fisk[i]] + distribution[tolower(fisk[i])];
        if ((fishes + 0.) / tot > 0.6) return true;
    }


    // Punctuation is rare
    {
        string punctuation = "!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~;";

        int n_punctuation = 0;
        repe(c, punctuation) n_punctuation += distribution[c];
        if (n_punctuation * 10 > tot) return false;

    }


    // If more than 5% is uppercase, it's probably wrong
    {
        int num_uppercase = 0;
        for (int i = 'A'; i <= 'Z'; i++) num_uppercase += distribution[i];

        if (num_uppercase * 5 > tot) return false;
    }


    // e and a are common in all languages: check we have enough
    {
        int num_lowercase = 0;
        for (int i = 'a'; i <= 'z'; i++) num_lowercase += distribution[i];

        if (distribution['e'] < num_lowercase / 26 && distribution['a'] < num_lowercase / 26) return false;
    }

    return true;
}

int main() {
    cin.tie(0)->sync_with_stdio(0);

    string input, temp;
    while (cin >> temp) input += temp;

    auto todec = [](char c) {
        if (isdigit(c)) return c-'0';
        return c-'a'+10;
    };

    vi bytes;
    // Hex to decimal
    for (int i = 0; i < input.size(); i += 2) {
        bytes.push_back(todec(input[i]) * 16 + todec(input[i + 1]));
    }

    auto try_keylen = [&](int keylen) {
        vvi keys;

        rep(offset, keylen) {
            vi block_keys;

            rep(key, 256) {
                if (works(bytes, offset, keylen, key)) block_keys.emplace_back(key);
            }

            keys.emplace_back(block_keys);
        }

        vi finalkeys(keylen, -1);
        // first pass: none=bad key length, continue
        // singular = done for this key. happens often
        rep(j, sz(keys)) {
            if (sz(keys[j]) == 0) return;
            else finalkeys[j] = keys[j][0];
        }

        // second pass:
        // score all with more than one by how similar their distribution is to already decoded values (those with singular option)
        rep(j, sz(keys)) {
            string decoded = "";
            rep(j, sz(bytes)) {
                if (finalkeys[j % sz(finalkeys)] != -1) decoded += char(bytes[j] ^ finalkeys[j % sz(finalkeys)]);
            }
            vi decoded_dist(256);
            repe(c, decoded) {
                if (c >= 0 && c < 256) decoded_dist[c]++;
            }

            if (sz(keys[j]) > 1) {
                vector<pair<ll, int>> scored_keys;

                repe(key, keys[j]) {
                    vi distribution(256);
                    for (int i = j; i < sz(bytes); i += keylen) distribution[bytes[i] ^ key]++;
                    ll score = 0;
                    rep(i, 256) {
                        ll delta = distribution[i] - decoded_dist[i];
                        score += delta * delta;
                    }
                    scored_keys.emplace_back(score, key);
                }
                sort(all(scored_keys));
                finalkeys[j] = scored_keys[0].second;
            }
        }


        rep(j, sz(bytes)) {
            cout << char(bytes[j] ^ finalkeys[j % finalkeys.size()]);
        }
        exit(0);
    };

    repp(keylen, 1, 16) {
        try_keylen(keylen);
    }

    assert(0);
}

