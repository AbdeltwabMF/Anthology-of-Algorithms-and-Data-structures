/** https://www.hackerearth.com/practice/data-structures/advanced-data-structures/fenwick-binary-indexed-trees/practice-problems/algorithm/help-ashu-1/description/
 **/

#pragma GCC optimize ("Ofast")

#include <bits/stdc++.h>

#define endl      '\n'

using namespace std;

typedef int64_t    ll;
typedef __int128 i128;

void Fast() {
    cin.sync_with_stdio(0);
    cin.tie(0);cout.tie(0);
}

class SegmentTree
{
    vector <pair <int, int> > sTree;
    vector <int> localArr;
    int NP2, oo = 0x3f3f3f3f;

  public :
    template <class T>
    SegmentTree(T _begin, T _end)
    {
        NP2 = 1;
        int n = _end - _begin;
        while(NP2 < n) NP2 <<= 1;

        sTree.assign(NP2 << 1, {0, 0});
        localArr.assign(NP2 + 1, 0);

        __typeof(_begin) i = _begin;
        for(int j = 1; i != _end; i++, ++j)
            localArr[j] = *i;

        build(1, 1, NP2);
    }

    void build(int p, int l, int r)
    {
        if(l == r) {
            if(localArr[l] & 1)
                sTree[p] = {1, 0};
            else
                sTree[p] = {0, 1};
            return;
        }

        build(left(p),      l, mid(l, r));
        build(right(p), mid(l, r) + 1, r);

        sTree[p] = {sTree[left(p)].first  + sTree[right(p)].first,
                    sTree[left(p)].second + sTree[right(p)].second};
    }

    void update_point(int inx, int val)
    {
        inx += NP2 - 1;
        if(val & 1) {
            if(sTree[inx].second)
                sTree[inx] = {1, 0};
        } else {
            if(sTree[inx].first)
                sTree[inx] = {0, 1};
        }

        while(inx > 1)
        {
            inx >>= 1;
            sTree[inx] = {sTree[left(inx)].first  + sTree[right(inx)].first,
                          sTree[left(inx)].second + sTree[right(inx)].second};
        }
    }

    int query(int ql, int qr, int type) {
        return query(ql, qr, 1, 1, NP2, type);
    }

  private :
    int query(int ql, int qr, int p, int l, int r, int type)
    {
        if(isOutside(ql, qr, l, r)) return 0;

        if(isInside(ql, qr, l, r)) {
            if(type == 1)
                return sTree[p].second;
            else
                return sTree[p].first;
        }

        return query(ql, qr, left(p),      l, mid(l, r), type) +
               query(ql, qr, right(p), mid(l, r) + 1, r, type);
    }

    inline bool isInside(int ql, int qr, int sl, int sr) {
        return (ql <= sl && sr <= qr);
    }

    inline bool isOutside(int ql, int qr, int sl, int sr) {
        return (sr < ql || qr < sl);
    }

    inline int mid (int l, int r) {
        return ((l + r) >> 1);
    }

    inline int left(int p) {
        return (p << 1);
    }

    inline int right(int p) {
        return ((p << 1) | 1);
    }
};

const int N = 1e2 + 9, M = 1e4 + 9, oo = 0x3f3f3f3f;
ll INF = 0x3f3f3f3f3f3f3f3f;
int n, q, l, r, type, x, y;
vector <int> a;

void Solve()
{
    cin >> n;

    a.resize(n);
    for(int i = 0; i < n; ++i)
        cin >> a[i];

    SegmentTree st(a.begin(), a.end());

    cin >> q;
    while(q--)
    {
        cin >> type >> x >> y;

        if(type == 0)
            st.update_point(x, y);
        else if(type == 1)
            cout << st.query(x, y, 1) << endl;
        else
            cout << st.query(x, y, 2) << endl;
    }
}

int main()
{
    Fast();

    int tc = 1;
    for(int i = 1; i <= tc; ++i)
        Solve();
}

