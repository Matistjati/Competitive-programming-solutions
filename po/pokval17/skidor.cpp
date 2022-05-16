#include <iostream>
#include <vector>
#include <map>
#include <sstream>
#include <algorithm>
#include <cmath>
#include <set>
#include <unordered_set>
#include <string>
#include <iterator>
#include <queue>
#include <tuple>
#include <numeric>
#include <random>
#include <time.h>
#include <stack>
#include <chrono>
#include <unordered_map>
#include <iomanip>

using namespace std;

#define ll long long
#define vi vector<ll>
#define vvi vector<vi>
#define p2 pair<ll, ll>
#define p3 vi
#define p4 vi
#define inf 2e9
#define linf 1e17

#define read(a) cin >> a
#define write(a) cout << (a) << endl
#define deb __debugbreak();

#define readpush(type,a) type temp; read(temp); a.push_back(temp)
#define readinsert(type,a) type temp; read(temp); a.insert(temp)
#define setcontains(set, x) (set.find(x) != set.end())
#define all(a) begin(a),end(a)

#define rep(i, high) for (ll i = 0; i < high; i++)
#define repe(i, container) for (auto& i : container)
#define per(i, high) for (ll i = high; i >= 0; i--)

#define ceildiv(x,y) ((x + y - 1) / y)


inline void fast()
{
    ios::sync_with_stdio(false);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
}


// Node for storing minimum nd maximum value of given range
struct Node
{
    ll minimum;
    ll maximum;
    ll sum;
    Node* left;
    Node* right;
    ll leftedge;
    ll rightedge;
};

class SegmentTree
{
public:
    Node root;
    vi lookupMin;
    vi lookupMax;

    Node* construct(vector<ll>& arr, ll start, ll end)
    {
        //if (end - start <= 0 || arr.size() == 0)
        //{
        //    return nullptr;
        //}


        if (end - start == 1)
        {
            Node* n = new Node();
            n->maximum = arr[start];
            n->minimum = arr[start];
            n->sum = arr[start];
            n->leftedge = start;
            n->rightedge = end;
            return n;
        }
        else
        {
            Node* n = new Node();
            ll mid = start + (end - start) / 2;
            n->left = construct(arr, start, mid);
            n->right = construct(arr, mid, end);
            n->maximum = max(n->left->maximum, n->right->maximum);
            n->minimum = min(n->left->minimum, n->right->minimum);
            n->sum = n->left->sum + n->right->sum;
            n->leftedge = start;
            n->rightedge = end;
            return n;
        }


    }

    SegmentTree(vector<ll> v, ll l)
    {
        lookupMin = vi(v.size(),-1);
        lookupMax = vi(v.size(),-1);

        root = *construct(v, 0, v.size());
        for (ll i = 0; i < v.size()-l+1; i++)
        {
            lookupMax[i] = qmax(i, i + l, root, true);
            lookupMin[i] = qmin(i, i + l, root, true);
        }

    }

    ll qmin(ll qs, ll qe, Node n, bool first)
    {
        if (first)
        {
            if (lookupMin[qs] != -1)
            {
                return lookupMin[qs];
            }
        }
        if (qs <= n.leftedge && qe >= n.rightedge)
        {
            return n.minimum;
        }
        else if (qs > n.rightedge || qe < n.leftedge)
        {
            return inf;
        }
        else
        {
            ll a = inf;
            if (n.left != nullptr)
            {
                a = qmin(qs, qe, *n.left, false);
            }
            ll b = inf;
            if (n.right != nullptr)
            {
                b = qmin(qs, qe, *n.right, false);
            }

            if (first)
            {

                lookupMin[qs] = min(a, b);
            }
            return min(a,b);
        }
    }

    ll qmax(ll qs, ll qe, Node n, bool first)
    {
        if (first)
        {
            if (lookupMax[qs] != -1)
            {
                return lookupMax[qs];
            }
        }
        if (qs <= n.leftedge && qe >= n.rightedge)
        {
            return n.maximum;
        }
        else if (qs > n.rightedge || qe < n.leftedge)
        {
            return -inf;
        }
        else
        {
            ll a = -inf;
            if (n.left != nullptr)
            {
                a = qmax(qs, qe, *n.left, false);
            }
            ll b = -inf;
            if (n.right != nullptr)
            {
                b = qmax(qs, qe, *n.right, false);
            }

            if (first)
            {

                lookupMax[qs] = max(a, b);
            }
            return max(a, b);
        }
    }
};

struct TreeNode
{
    SegmentTree* minTree;
    SegmentTree* maxTree;
    ll minimum;
    ll maximum;
    ll sum;
    TreeNode* left;
    TreeNode* right;
    ll leftedge;
    ll rightedge;
};


class SegmentTreeTree
{
public:
    TreeNode root;


    TreeNode* construct(vector<SegmentTree>& arr, ll start, ll end)
    {
        //if (end - start <= 0 || arr.size() == 0)
        //{
        //    return nullptr;
        //}


        if (end - start == 1)
        {
            TreeNode* n = new TreeNode();
            n->maximum = arr[start].root.maximum;
            n->minimum = arr[start].root.minimum;
            n->sum = arr[start].root.sum;
            n->minTree = &arr[start];
            n->maxTree = &arr[start];
            n->leftedge = start;
            n->rightedge = end;
            return n;
        }
        else
        {
            TreeNode* n = new TreeNode();
            ll mid = start + (end - start) / 2;
            n->left = construct(arr, start, mid);
            n->right = construct(arr, mid, end);
            if (n->left->maximum > n->right->maximum)
            {
                n->maxTree = n->left->maxTree;
                n->maximum = n->left->maximum;
            }
            else
            {
                n->maxTree = n->right->maxTree;
                n->maximum = n->right->maximum;
            }

            if (n->left->minimum < n->right->minimum)
            {
                n->minTree = n->left->minTree;
                n->minimum = n->left->minimum;
            }
            else
            {
                n->minTree = n->right->minTree;
                n->minimum = n->right->minimum;
            }
            n->sum = n->left->sum + n->right->sum;
            n->leftedge = start;
            n->rightedge = end;
            return n;
        }


    }

    SegmentTreeTree(vector<SegmentTree>& v)
    {
        root = *construct(v, 0, v.size());

    }

    TreeNode* qmin(ll qs, ll qe, ll ql, ll qr, TreeNode* n)
    {
        if (qs <= n->leftedge && qe >= n->rightedge)
        {
            TreeNode* ret = nullptr;
            if (n->left != nullptr)
            {
                TreeNode* t = qmin(qs, qe, ql, qr, n->left);
                if (t != nullptr)
                {
                    ret = t;
                }
            }

            if (n->right != nullptr)
            {
                TreeNode* t = qmin(qs, qe, ql, qr, n->right);
                if (t != nullptr)
                {
                    if (ret)
                    {
                        ll tM = t->minTree->qmin(ql, qr, t->minTree->root, true);
                        ll tR = ret->minTree->qmin(ql, qr, ret->minTree->root, true);
                        if (tM < tR)
                        {
                            ret = t;
                        }
                    }
                    else
                    {
                        ret = t;
                    }

                }
            }

            if (!ret)
            {
                ret = n;
            }

            return ret;
        }
        else if (qs > n->rightedge || qe < n->leftedge)
        {
            return nullptr;
        }
        else
        {
            TreeNode* ret = nullptr;
            if (n->left != nullptr)
            {
                TreeNode* t = qmin(qs, qe, ql, qr, n->left);
                if (t != nullptr)
                {
                    ret = t;
                }
            }

            if (n->right != nullptr)
            {
                TreeNode* t = qmin(qs, qe, ql, qr, n->right);
                if (t != nullptr)
                {
                    if (ret)
                    {
                        ll tM = t->minTree->qmin(ql, qr, t->minTree->root, true);
                        ll tR = ret->minTree->qmin(ql, qr, ret->minTree->root, true);
                        if (tM < tR)
                        {
                            ret = t;
                        }
                    }
                    else
                    {
                        ret = t;
                    }

                }
            }

            return ret;
        }
    }

    TreeNode* qmax(ll qs, ll qe, ll ql, ll qr, TreeNode* n)
    {
        if (qs <= n->leftedge && qe >= n->rightedge)
        {
            TreeNode* ret = nullptr;
            if (n->left != nullptr)
            {
                TreeNode* t = qmax(qs, qe, ql, qr, n->left);
                if (t != nullptr)
                {
                    ret = t;
                }
            }

            if (n->right != nullptr)
            {
                TreeNode* t = qmax(qs, qe, ql, qr, n->right);
                if (t != nullptr)
                {
                    if (ret)
                    {
                        ll tM = t->maxTree->qmax(ql, qr, t->maxTree->root, true);
                        ll tR = ret->maxTree->qmax(ql, qr, ret->maxTree->root, true);
                        if (tM > tR)
                        {
                            ret = t;
                        }
                    }
                    else
                    {
                        ret = t;
                    }

                }
            }

            if (!ret)
            {
                ret = n;
            }

            return ret;
        }
        else if (qs > n->rightedge || qe < n->leftedge)
        {
            return nullptr;
        }
        else
        {
            TreeNode* ret = nullptr;
            if (n->left != nullptr)
            {
                TreeNode* t = qmax(qs, qe, ql, qr, n->left);
                if (t != nullptr)
                {
                    ret = t;
                }
            }

            if (n->right != nullptr)
            {
                TreeNode* t = qmax(qs, qe, ql, qr, n->right);
                if (t != nullptr)
                {
                    if (ret)
                    {
                        ll tM = t->maxTree->qmax(ql, qr, t->maxTree->root, true);
                        ll tR = ret->maxTree->qmax(ql, qr, ret->maxTree->root, true);
                        if (tM > tR)
                        {
                            ret = t;
                        }
                    }
                    else
                    {
                        ret = t;
                    }

                }
            }

            return ret;
        }
    }
};

int main()
{
    fast();


    ll r;
    ll c;
    ll l;
    read(r);
    read(c);
    read(l);

    vvi rows;
    rep(i, r)
    {
        vi row;
        rep(j, c)
        {
            readpush(ll, row);
            if (temp == -1)
            {
                row[row.size()-1] = -linf;
            }
        }
        rows.push_back(row);
    }

    vector<SegmentTree> trees;
    repe(row, rows)
    {
        SegmentTree s(row, l);
        trees.push_back(s);
    }

    SegmentTreeTree treetree(trees);

    ll best = linf;
    ll besti = -1;
    ll bestj = -1;

    for (ll i = 0; i < r-l+1; i++)
    {
        for (ll j = 0; j < c-l+1; j++)
        {
            ll largest = -linf;
            ll smallest = linf;
            auto t = treetree.qmin(i, i + l, j, j + l, &treetree.root)->minTree;
            smallest = t->qmin(j, j + l, t->root, true);

            auto t2 = treetree.qmax(i, i + l, j, j + l, &treetree.root)->maxTree;
            largest = t2->qmax(j, j + l, t2->root, true);

            if (abs(largest-smallest) < best)
            {
                best = abs(largest - smallest);
                besti = i;
                bestj = j;
            }
        }
    }

    cout << besti << " " << bestj;

    return 0;
}