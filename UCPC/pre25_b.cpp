#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, m; cin >> n >> m;
	i64 acc = 0, mn = 1 << 30;
	for (int i = 0; i < n * m; i++) {
		int x; cin >> x;
		acc += x;
		if (mn > x) mn = x;
	}
	cout << acc - mn << '\n';
}