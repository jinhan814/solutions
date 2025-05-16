#include <bits/stdc++.h>
using namespace std;

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int tc; cin >> tc;
	while (tc--) {
		int n, m; cin >> n >> m;
		vector pv(m + 1, 0);
		for (int i = 1; i <= n; i++) {
			vector v(m + 1, 0);
			for (int j = 1; j <= m; j++) cin >> v[j];
			for (int j = 1; j <= m; j++) {
				int a = v[j - 1], b = pv[j], c = pv[j - 1], p = 0;
				array val{ 0, a, b, (a + b) / 2, a + b - c };
				for (int k = 0; k < 5; k++) {
					int vp = abs(v[j] - val[p]);
					int vk = abs(v[j] - val[k]);
					if (vp > vk) p = k;
				}
				cout << p << ' ' << v[j] - val[p] << ' ';
			}
			cout << '\n';
			pv.swap(v);
		}
	}
}