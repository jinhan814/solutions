#include <bits/stdc++.h>
using namespace std;

using i64 = long long;
using pii = pair<int, int>;

auto calc = [](const pii& line, i64 x) {
	return line.first * x + line.second;
};

auto get_upper_hull = [](auto& v) {
	vector res(0, pair(0, 0));
	sort(v.begin(), v.end());
	auto check = [](const pii& a, const pii& b, const pii& c) -> bool {
		i64 x = a.second - c.second;
		i64 y = c.first - a.first;
		return b.first * x + b.second * y <= c.first * x + c.second * y;
	};
	for (int l = 0, r = 0; l < v.size(); l = r) {
		while (r < v.size() && v[l].first == v[r].first) r++;
		while (res.size() > 1 && check(res.end()[-2], res.back(), v[r - 1])) res.pop_back();
		res.push_back(v[r - 1]);
	}
	return res;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n; cin >> n;
	vector v(n, pair(0, 0));
	for (auto& [a, b] : v) cin >> a >> b;
	int q; cin >> q;
	vector queries(q, pair(0, 0));
	for (auto& [a, b] : queries) cin >> a >> b;

	auto dnc = [&](const auto& self, int l, int r, auto buc) -> void {
		if (l == r) {
			if (l == q) return;
			cout << buc.size();
			for (int x : buc) cout << ' ' << x + 1;
			cout << '\n';
		}
		else {
			int mid = l + r >> 1;
			vector lines(0, pair(0, 0));
			for (int i = l; i <= mid; i++) lines.push_back(queries[i]);
			auto hull = get_upper_hull(lines);
			auto is_in = [&](int x, int y) -> bool {
				int lo = 0, hi = hull.size() - 1;
				while (lo + 2 < hi) {
					int a = (lo + lo + hi) / 3;
					int b = (lo + hi + hi) / 3;
					if (calc(hull[a], x) < calc(hull[b], x)) lo = a;
					else hi = b;
				}
				for (int i = lo; i <= hi; i++) if (calc(hull[i], x) > y) return 1;
				return 0;
			};
			vector l_buc(0, 0);
			vector r_buc(0, 0);
			for (int x : buc) {
				if (is_in(v[x].first, v[x].second)) l_buc.push_back(x);
				else r_buc.push_back(x);
			}
			self(self, l, mid, l_buc);
			self(self, mid + 1, r, r_buc);
		}
	};

	vector idx(n, 0);
	iota(idx.begin(), idx.end(), 0);
	dnc(dnc, 0, q, idx);
}