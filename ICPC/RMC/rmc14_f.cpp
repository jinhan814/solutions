#include <bits/stdc++.h>
using namespace std;

struct union_find {
	union_find(int n) : p(n, -1) {}
	int find(int x) { return p[x] < 0 ? x : p[x] = find(p[x]); }
	bool merge(int a, int b) {
		a = find(a), b = find(b);
		if (a == b) return 0;
		p[b] = a;
		return 1;
	}
private:
	vector<int> p;
};

auto sol = [](int n, auto v, auto e) {
	int res = 0;
	union_find uf(n + 1);
	sort(e.begin(), e.end());
	for (auto [c, a, b] : e) {
		if (v[a] || v[b]) continue;
		if (uf.merge(a, b)) res += c;
	}
	int a = 0, b = 0;
	for (int i = 1; i <= n; i++) {
		if (uf.find(i) != i) continue;
		v[i] ? a++ : b++;
	}
	if (b == 0 && a <= 2) {
		if (a == 1) return 0;
		for (auto [c, a, b] : e) {
			if (uf.merge(a, b)) return res + c;
		}
	}
	if (b == 1) {
		int cnt = 0;
		for (auto [c, a, b] : e) {
			if (v[a] && v[b]) continue;
			if (uf.merge(a, b)) res += c, cnt++;
		}
		if (cnt == a) return res;
	}
	return -1;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, m, k; cin >> n >> m >> k;
	vector v(n + 1, 0);
	vector e(m, array{ 0, 0, 0 });
	for (int i = 0; i < k; i++) { int x; cin >> x; v[x] = 1; }
	for (auto& [c, a, b] : e) cin >> a >> b >> c;
	int res = sol(n, v, e);
	if (res >= 0) cout << res << '\n';
	else cout << "impossible" << '\n';
}