#include<iostream>
using namespace std;
#define ll int 
#define MAX 100010
ll lazy[4 * MAX];
void propagate(int ss, int se, int idx)
{
    if (ss != se)
    {
        lazy[2 * idx + 1] ^= lazy[idx];
        lazy[2 * idx + 2] ^= lazy[idx];
        lazy[idx] = 0;
    }
}
void update(int ss, int se, int qs, int qe, int idx, ll value)
{
    if (qs > se || qe < ss)
        return;
    if (qs <= ss && qe >= se)
    {
        lazy[idx] ^= value;
        return;
    }
    int mid = (ss + se) / 2;
    update(ss, mid, qs, qe, 2 * idx + 1, value);
    update(mid + 1, se, qs, qe, 2 * idx + 2, value);
}
ll get(int ss, int se, int q, int idx)
{
    if (lazy[idx] != 0)
        propagate(ss, se, idx);
    if (q > se || q < ss)
        return 0;
    if (ss == se)
        return lazy[idx];

    int mid = (ss + se) / 2;
    if (q > mid)
        return get(mid + 1, se, q, 2 * idx + 2);
    return get(ss, mid, q, 2 * idx + 1);
}
int main()
{

    int n, q, type, l, r;
    cin >> n >> q;
    ll x;
    while (q--)
    {
        cin >> type;
        if (type == 1) {
            cin >> l >> r >> x;
            update(0, n - 1, l - 1, r - 1, 0, x);
        }
        else {
            cin >> l;
            cout << get(0, n - 1, l - 1, 0) << endl;
        }

    }

    return 0;
}