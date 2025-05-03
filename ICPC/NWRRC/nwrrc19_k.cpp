#include <bits/stdc++.h>
using namespace std;

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, m; cin >> n >> m;
	vector v(n, string{});
	for (int i = 0; i < n; i++) cin >> v[i];

	vector pos(0, pair(0, 0));
	for (int i = 0; i < n; i++) for (int j = 0; j < m; j++) {
		if (v[i][j] == '.') continue;
		if (v[i][j] == 'A') pos.insert(pos.begin(), { i, j });
		else pos.push_back({ i, j });
	}
	pos.push_back({ pos[0].first, -1 });
	pos.push_back({ pos[0].first, m });
	pos.push_back({ -1, pos[0].second });
	pos.push_back({ n, pos[0].second });

	auto cmp = [](const auto& a, const auto& b) -> bool {
		if (a[0] == -1) return 1;
		int sa = (a[1] - a[0] + 1) * (a[3] - a[2] + 1);
		int sb = (b[1] - b[0] + 1) * (b[3] - b[2] + 1);
		return sa < sb;
	};

	auto get_bound = [&] {
		array opt{ -1, -1, -1, -1 };
		for (int a = 1; a < pos.size(); a++) {
			for (int b = a + 1; b < pos.size(); b++) {
				for (int c = b + 1; c < pos.size(); c++) {
					for (int d = c + 1; d < pos.size(); d++) {
						auto [x1, y1] = pos[a];
						auto [x2, y2] = pos[b];
						auto [x3, y3] = pos[c];
						auto [x4, y4] = pos[d];
						int x_mn = min({ x1, x2, x3, x4 }) + 1;
						int x_mx = max({ x1, x2, x3, x4 }) - 1;
						int y_mn = min({ y1, y2, y3, y4 }) + 1;
						int y_mx = max({ y1, y2, y3, y4 }) - 1;
						if (x_mn > pos[0].first) continue;
						if (x_mx < pos[0].first) continue;
						if (y_mn > pos[0].second) continue;
						if (y_mx < pos[0].second) continue;
						int cnt = 0;
						for (auto [x, y] : pos) {
							if (x < x_mn || x_mx < x) continue;
							if (y < y_mn || y_mx < y) continue;
							cnt++;
						}
						if (cnt != 1) continue;
						array val{ x_mn, x_mx, y_mn, y_mx };
						if (cmp(opt, val)) opt = val;
					}
				}
			}
		}
		return opt;
	};

	auto fill_bound = [&](int x1, int x2, int y1, int y2) {
		auto dnc = [&](const auto& self, int x1, int x2, int y1, int y2) -> void {
			int cx = 1 << 30, mx = -1;
			for (auto [x, y] : pos) {
				if (x < x1 || x2 < x) continue;
				if (y < y1 || y2 < y) continue;
				cx = min(cx, x);
				mx = max(mx, x);
			}
			vector buc(0, 0);
			for (auto [x, y] : pos) {
				if (y < y1 || y2 < y) continue;
				if (x == cx) buc.push_back(y);
			}
			int px = x1;
			int nx = cx != mx ? cx : x2;
			for (int i = 0; i < buc.size(); i++) {
				int py = i ? buc[i - 1] + 1 : y1;
				int ny = i + 1 < buc.size() ? buc[i] : y2;
				for (int x = px; x <= nx; x++) for (int y = py; y <= ny; y++) {
					if (v[x][y] != '.') continue;
					v[x][y] = v[cx][buc[i]] ^ 32;
				}
			}
			if (cx != mx) self(self, nx + 1, x2, y1, y2);
		};
		if (x1 <= x2 && y1 <= y2) dnc(dnc, x1, x2, y1, y2);
	};

	auto [x1, x2, y1, y2] = get_bound();
	fill_bound(x1, x2, y1, y2);
	fill_bound(0, x1 - 1, 0, m - 1);
	fill_bound(x2 + 1, n - 1, 0, m - 1);
	fill_bound(x1, x2, 0, y1 - 1);
	fill_bound(x1, x2, y2 + 1, m - 1);
	for (int i = 0; i < n; i++) cout << v[i] << '\n';
}