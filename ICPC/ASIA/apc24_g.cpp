#include <bits/stdc++.h>
using namespace std;

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, m, k; cin >> n >> m >> k;
	vector v(n, string{});
	for (int i = 0; i < n; i++) cin >> v[i];

	vector buc(m, vector(26, vector(0, 0)));
	for (int i = 0, opt = -1; i < n; i++) {
		vector c(i, 0);
		for (int j = 0; j < m; j++) {
			if (v[i][j] == '.') continue;
			for (auto p : buc[j][v[i][j] - 'A']) if (++c[p] == k) opt = max(opt, p);
			buc[j][v[i][j] - 'A'].push_back(i);
		}
		if (opt == -1) continue;
		cout << opt + 1 << ' ' << i + 1 << '\n';
		return 0;
	}
	cout << -1 << '\n';
}