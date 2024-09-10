#include <bits/stdc++.h>
using namespace std;

vector<pair<int, int>> pour(int fromCap, int toCap, int d)
{
    int from = fromCap;
    int to = 0;

    vector<pair<int, int>> sequence;

    pair<int, int> step;
    step.first = from;
    step.second = to;

    sequence.push_back(step);

    while (from != d && to != d)
    {
        int temp = min(from, toCap - to);

        to   += temp;
        from -= temp;

        step.first = from;
        step.second = to;

        sequence.push_back(step);

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

    return sequence;
}

int main()
{
    int n = 3, m = 5, d = 4;
    vector<pair<int, int>> ans;
    ans = pour(m, n, d);

    for(int i = 0; i<ans.size(); i++) {
        cout<<" -> ("<<ans[i].first<<","<<ans[i].second<<")";
    }

    return 0;
}
