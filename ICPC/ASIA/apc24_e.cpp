#include <bits/stdc++.h>
using namespace std;

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int N; cin >> N;
	while (N--) {
		int n; cin >> n;
		vector v(n, vector(n, 0));
		for (int i = 0; i < n; i++) for (int j = 0; j < n; j++) cin >> v[i][j];

		vector a(0, 0), b(0, 0), c(n + 1, 0);
		for (int i = 0; i < n; i++) {
			bool flag = 1;
			for (int j = 0; j < n; j++) if (c[v[i][j]]++) flag = 0;
			for (int j = 0; j < n; j++) c[v[i][j]]--;
			if (flag) a.push_back(i);
		}
		for (int j = 0; j < n; j++) {
			bool flag = 1;
			for (int i = 0; i < n; i++) if (c[v[i][j]]++) flag = 0;
			for (int i = 0; i < n; i++) c[v[i][j]]--;
			if (flag) b.push_back(j);
		}

		bool is_trans = a.size() < b.size();
		if (is_trans) {
			for (int i = 0; i < n; i++) for (int j = i + 1; j < n; j++) swap(v[i][j], v[j][i]);
			swap(a, b);
		}

		vector res(0, tuple(0, 0, 0));
		for (int i = 0; i < b.size(); i++) {
			int x = a[i];
			int y = b[i];
			int c = v[x][y] ^ 1 ? 1 : 2;
			res.push_back({ x, y, v[x][y] = c });
		}
		for (int i = b.size(); i < a.size(); i++) {
			int x = a[i];
			int y = 0;
			int c = -1;
			for (int i = 0; i < n; i++) if (i != x && v[x][y] != v[i][y]) c = v[i][y];
			if (c == -1) c = v[x][y] ^ 1 ? 1 : 2;
			res.push_back({ x, y, v[x][y] = c });
		}
		if (is_trans) for (auto& [a, b, c] : res) swap(a, b);

		cout << res.size() << '\n';
		for (auto [a, b, c] : res) cout << a + 1 << ' ' << b + 1 << ' ' << c << '\n';
	}
}