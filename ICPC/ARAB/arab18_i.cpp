#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int N; cin >> N;
	while (N--) {
		int n, m; cin >> n >> m;
		vector v(n, array{ 0, 0 });
		for (int i = 0; i < n; i++) cin >> v[i][0];
		for (int i = 0; i < n; i++) cin >> v[i][1];
		sort(v.begin(), v.end());
		i64 r1 = v[m - 1][0];
		vector buc(0, 0LL);
		for (auto [a, b] : v) if (a <= r1) buc.push_back(b);
		sort(buc.begin(), buc.end());
		i64 r2 = reduce(buc.end() - m, buc.end());
		cout << r1 << ' ' << r2 << '\n';
	}
}