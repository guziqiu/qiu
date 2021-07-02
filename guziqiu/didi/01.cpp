#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;
#define MAX_N 5000
int v[MAX_N + 5][2];
int main() {
    int n;
    int ans[2] = {0};
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> v[i][0] >> v[i][1];
        ans[0] += v[i][0];
        ans[1] += v[i][1];
    }
    int t = ans[0] > ans[1] ? ans[0] : ans[1];
    if (ans[0] < ans[1])t += fabs(ans[1] - ans[0]);
    cout << t << endl;


    return 0;
}

