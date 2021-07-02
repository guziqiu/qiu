#include <iostream>
#include <map>
#include <set>
#include <algorithm>
using namespace std;
#define MAX_N 10000

int arr[MAX_N + 5];
int main() {
    int n, x;
    cin >> n >> x;
    int ans = 0;
    map<int, int> ma;
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
        ma[arr[i]] = 1;
    }
    int num = ma.begin()->first;
    for (int i = 0; i < n; i++) {
       num+= x;
       if (ma.count(num) == 0) ans++;
    }
    cout << ans << endl;
    



    return 0;
}

