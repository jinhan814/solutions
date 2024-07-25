#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

using i64 = long long;

int main() {
	fastio;
	i64 n, s = 0, m = 0; cin >> n;
	while (n--) { i64 x; cin >> x; s += x; m = max(m, x); }
	cout << min(s - m, s / 3) << '\n';
}