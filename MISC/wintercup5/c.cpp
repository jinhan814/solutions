#include <bits/stdc++.h>
using namespace std;

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int N; cin >> N;
	while (N--) {
		int n, k; cin >> n >> k;
		vector a(n + 1, 0), b(n + 1, 0);
		vector c(n + 1, vector(n + 1, 0));
		for (int i = 0; i < k; i++) {
			int x, y; cin >> x >> y;
			a[x]++;
			b[y]++;
			c[x][y]++;
		}
		int res = 1 << 30;
		for (int i = 1; i <= n; i++) for (int j = 1; j <= n; j++) {
			int val = a[i] + b[j] - c[i][j];
			res = min(res, val);
		}
		cout << res << '\n';
	}
}