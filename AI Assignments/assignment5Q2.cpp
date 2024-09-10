#include <bits/stdc++.h>
using namespace std;

int gcd(int a, int b)
{
    if (b==0)
       return a;
    return gcd(b, a%b);
}

vector<pair<int, int>> pour(int fromCap, int toCap, int d)
{
    int from = fromCap;
    int to = 0;

    vector<pair<int, int>> sequen;

    pair<int, int> step;
    step.first = from;
    step.second = to;

    sequen.push_back(step);

    while (from != d && to != d)
    {
        int temp = min(from, toCap - to);

        to   += temp;
        from -= temp;

        step.first = from;
        step.second = to;

        sequen.push_back(step);

        if (from == d || to == d)
            break;

        if (from == 0)
        {
            from = fromCap;
        }

        if (to == toCap)
        {
            to = 0;
        }
    }

    return sequen;
}

vector<pair<int, int>> sequence(int m, int n, int d)
{
    if (m > n)
        swap(m, n);

    // if (d > n)
    //     return -1;

    // if ((d % gcd(n,m)) != 0)
    //     return -1;

    return pour(n,m,d);
}

int main()
{
    int n = 3, m = 5, d = 4;
    vector<pair<int, int>> ans;
    ans = sequence(m, n, d);

    for(int i = 0; i<ans.size(); i++) {
        cout<<" -> ("<<ans[i].first<<","<<ans[i].second<<")";
    }

    return 0;
}
