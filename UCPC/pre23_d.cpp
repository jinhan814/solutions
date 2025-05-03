#include <bits/stdc++.h>
using namespace std;

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, m, k; cin >> n >> m >> k;
	vector v(n, string{});
	for (int i = 0; i < n; i++) cin >> v[i];
	int res = 0;
	for (int x = 0; x < k; x++) {
		for (int y = 0; y < k; y++) {
			vector c(26, 0);
			int p = 0;
			for (int i = x; i < n; i += k) {
				for (int j = y; j < m; j += k) {
					c[v[i][j] - 65]++;
					if (c[p] < c[v[i][j] - 65]) p = v[i][j] - 65;
				}
			}
			for (int i = x; i < n; i += k) {
				for (int j = y; j < m; j += k) {
					if (v[i][j] == p + 65) continue;
					v[i][j] = p + 65;
					res++;
				}
			}
		}
	}
	cout << res << '\n';
	for (int i = 0; i < n; i++) cout << v[i] << '\n';
}