#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n; cin >> n;
	i64 m; cin >> m;
	vector v(n, 0LL);
	for (int i = 0; i < n; i++) cin >> v[i];
	vector idx(n, 0);
	iota(idx.begin(), idx.end(), 0);
	sort(idx.begin(), idx.end(), [&](int i, int j) {
		i64 x1 = i * m - v[i], x2 = j * m - v[j];
		i64 y1 = i * m + v[i], y2 = j * m + v[j];
		if (x1 != x2) return x1 < x2;
		return y1 < y2;
	});
	vector lis(0, 0LL); lis.reserve(n);
	for (int i : idx) {
		i64 y = i * m + v[i];
		if (lis.empty() || lis.back() <= y) lis.push_back(y);
		else *upper_bound(lis.begin(), lis.end(), y) = y;
	}
	cout << n - lis.size() << '\n';
}