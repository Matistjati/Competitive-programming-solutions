struct rollinghash
{
    vi suf, b;
    int mod;
    rollinghash(string& s, int base=131, int mod = 1e9 + 7) : mod(mod), suf(s.size() + 1), b(s.size() + 1)
    {
        b[0] = 1;
        b[1] = base;

        per(i, s.size())
        {
            suf[i] = ((ll)suf[i + 1] * base + (s[i] - 'a' + 1)) % mod;
        }

        repp(i, 2, s.size() + 1)
        {
            b[i] = (ll)b[i - 1] * b[1] % mod;
        }
    }

    unsigned ll gethash(int l, int r) // [l, r]
    {
        ll v = suf[l] - (ll)suf[r + 1] * b[r - l + 1];
        // Make sure that v is within [0, mod)
        v %= mod;
        v += mod;
        v %= mod;

        return v;
    }
};
