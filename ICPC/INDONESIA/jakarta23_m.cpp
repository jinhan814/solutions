#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

int main() {
	cin.tie(0)->sync_with_stdio(0);
	i64 n, x, s = 0, m = 0; cin >> n;
	while (n--) cin >> x, s += x, m = max(m, x);
	cout << min(s - m, s / 3) << '\n';
}