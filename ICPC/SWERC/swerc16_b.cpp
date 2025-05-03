#include <bits/stdc++.h>
using namespace std;

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, x, y; cin >> n >> x >> y;
	int cnt = 0;
	vector v(0, pair(0, 0));
	for (int i = 1; i < n; i++) {
		int a, b; cin >> a >> b; a -= x, b -= y;
		if (a | b) v.push_back({ a, b });
		else cnt++;
	}

	auto ccw = [&](const auto& a, const auto& b, const auto& c) {
		int x1 = b.first - a.first;
		int y1 = b.second - a.second;
		int x2 = c.first - b.first;
		int y2 = c.second - b.second;
		return x1 * y2 - x2 * y1;
	};

	sort(v.begin(), v.end(), [&](const auto& a, const auto& b) {
		if (a > pair(0, 0) ^ b > pair(0, 0)) return a > b;
		return ccw(pair(0, 0), a, b) > 0;
	});

	int mn = 1 << 30;
	for (int l = 0, r = 0; l < v.size(); l++) {
		if (r < l) r++;
		while (r + 1 < l + v.size()) {
			int res = ccw(pair(0, 0), v[l], v[(r + 1) % v.size()]);
			if (res < 0) break;
			if (res == 0 && (v[l] > pair(0, 0) ^ v[(r + 1) % v.size()] > pair(0, 0))) break;
			r++;
		}
		if (v[l].first >= 0 && v[l].second <= 0) mn = min(mn, r - l + 1);
	}

	int mx = 0;
	for (int l = 0, r = 0; l < v.size(); l++) {
		if (r < l) r++;
		while (r + 1 < l + v.size()) {
			int res = ccw(pair(0, 0), v[l], v[(r + 1) % v.size()]);
			if (res < 0) break;
			r++;
		}
		if (v[l].first >= 0 && v[l].second <= 0) mx = max(mx, r - l + 1 + cnt + 1);
	}

	{
		vector c(3, 0);
		for (auto [x, y] : v) c[x ? x < 0 ? 0 : 1 : 2]++;
		mn = min(mn, c[1] + 1);
		mx = max(mx, c[1] + c[2] + cnt + 1);
	}

	{
		vector c(3, 0);
		for (auto [x, y] : v) c[y ? y < 0 ? 0 : 1 : 2]++;
		mn = min(mn, c[1] + 1);
		mx = max(mx, c[1] + c[2] + cnt + 1);
	}

	cout << mn << ' ' << mx << '\n';
}