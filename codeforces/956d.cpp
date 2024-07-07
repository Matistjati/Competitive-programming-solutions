#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
#define int ll
const int inf = int(1e18);

typedef vector<int> vi;
typedef vector<vi> vvi;
typedef pair<int, int> p2;

#define rep(i, high) for (int i = 0; i < high; i++)
#define repp(i, low, high) for (int i = low; i < high; i++)
#define repe(i, container) for (auto& i : container)
#define sz(container) ((int)container.size())
#define all(x) begin(x),end(x)
#define ceildiv(x,y) (((x) + (y) - 1) / (y))

inline void fast() { ios::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL); }

#if _LOCAL
#define assert(x) if (!(x)) __debugbreak()
#endif

// Merge function that also counts inversions
int mergeAndCount(std::vector<int>& arr, std::vector<int>& temp, int left, int mid, int right) {
    int i = left; // Starting index for left subarray
    int j = mid + 1; // Starting index for right subarray
    int k = left; // Starting index to be sorted
    int inv_count = 0;

    // Conditions are checked to ensure that i doesn't exceed mid and j doesn't exceed right
    while ((i <= mid) && (j <= right)) {
        if (arr[i] <= arr[j]) {
            temp[k++] = arr[i++];
        }
        else {
            // There are mid - i inversions, because all elements left to i in the left subarray
            // are greater than arr[j]
            temp[k++] = arr[j++];
            inv_count += (mid - i + 1);
        }
    }

    // Copy the remaining elements of left subarray, if any
    while (i <= mid)
        temp[k++] = arr[i++];

    // Copy the remaining elements of right subarray, if any
    while (j <= right)
        temp[k++] = arr[j++];

    // Copy the sorted subarray into Original array
    for (i = left; i <= right; i++)
        arr[i] = temp[i];

    return inv_count;
}

// Function to count inversions using merge sort
int mergeSortAndCount(std::vector<int>& arr, std::vector<int>& temp, int left, int right) {
    int mid, inv_count = 0;
    if (left < right) {
        mid = (left + right) / 2;

        // Inversions will be counted in the left subarray, right subarray and during merge
        inv_count += mergeSortAndCount(arr, temp, left, mid);
        inv_count += mergeSortAndCount(arr, temp, mid + 1, right);

        // Merge the two subarrays and add the inversion count
        inv_count += mergeAndCount(arr, temp, left, mid, right);
    }
    return inv_count;
}

// Function to count inversions in the array
int countInversions(std::vector<int>& arr) {
    std::vector<int> temp(arr.size());
    return mergeSortAndCount(arr, temp, 0, arr.size() - 1);
}

vi remove_largest(vi nums)
{
    vector<p2> occs;
    int n = sz(nums);
    rep(i, sz(nums)) occs.emplace_back(nums[i], i);
    sort(all(occs));

    if (occs.back().second != n - 1)
    {
        if (occs.back().second==0)
        {
            swap(nums[1], nums[2]);
            swap(nums[0], nums[1]);
            swap(nums[1], nums[n - 1]);
            swap(nums[0], nums[n - 2]);
        }
        else
        {
            swap(nums[n - 1], nums[occs.back().second]);
            swap(nums[n - 2], nums[occs.back().second - 1]);
        }
        
    }
    return nums;
}

vi lexo_small(vi nums)
{
    int n = sz(nums);
    if (sz(nums)<=4)
    {
        set<vi> vis;
        queue<vi> q;
        q.emplace(nums);
        while (sz(q))
        {
            vi p = q.front();
            q.pop();

            if (vis.find(p) != vis.end()) continue;
            vis.insert(p);

            repp(l, 1, n)
            {
                rep(i, n - 1)
                {
                    if (i + l > n - 1) break;
                    rep(j, n - 1)
                    {
                        if (j + l > n - 1) break;
                        vi c(p);
                        swap(c[i], c[i + l]);
                        swap(c[j], c[j + l]);
                        q.emplace(c);
                    }
                }
            }
        }

        return *begin(vis);
    }
    // size 3 and 4 are bad
    nums = remove_largest(nums);
    int b1 = nums.back();
    nums.pop_back();
    nums = remove_largest(nums);
    int b2 = nums.back();
    nums.pop_back();
    int invcnt = countInversions(nums);
    sort(all(nums));
    if (invcnt % 2 == 1) swap(b1, b2);
    nums.push_back(b2);
    nums.push_back(b1);
    return nums;
}

void solve()
{
    int n;
    cin >> n;
    vi numsa(n);
    vi numsb(n);
    rep(i, n) cin >> numsa[i];
    rep(i, n) cin >> numsb[i];

    if (multiset<int>(all(numsa))!=multiset<int>(all(numsb)))
    {
        cout << "NO\n";
        return;
    }

    vi la = lexo_small(numsa);
    vi lb = lexo_small(numsb);
    if (la!=lb)
    {
        cout << "NO\n";
        return;
    }
    cout << "YES\n";
    return;
}

signed main()
{
    fast();

    int t;
    cin >> t;
    while (t--)
    {
        solve();
    }


    return 0;
}
