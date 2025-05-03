#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int N; cin >> N;
	while (N--) {
		int n, m, k; cin >> n >> m >> k;
		map buc{ pair(0, vector(0, 0)) };
		for (int i = 0; i < k; i++) {
			int a, b; cin >> a >> b;
			buc[a].push_back(b);
		}
		buc[n + 1].push_back(0);
		vector p(1, m + 1);
		i64 a = 0, b = 0, px = 1;
		for (auto [x, v] : buc) {
			i64 py = 1;
			for (int i = 0; i < p.size(); i++) {
				i64 val = (x - px) * (p[i] - py);
				if (i & 1) a += val;
				else b += val;
				py = p[i];
			}
			px = x;
			for (int y : v) p.push_back(y);
			sort(p.begin(), p.end());
		}
		cout << a << ' ' << b << '\n';
	}
}