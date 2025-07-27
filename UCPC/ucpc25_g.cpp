#include <bits/stdc++.h>
using namespace std;

auto sol = [](int n, int a, int b, auto l, auto r) {
	vector par(n + 1, 0), dep(n + 1, 0);
	vector buc(n + 1, 0), s(1, 1);
	for (int i = 1; i <= n; i++) {
		int x = buc[i] = s.back(); s.pop_back();
		for (int nx : { r[x], l[x] }) {
			if (nx == 0) continue;
			par[nx] = x;
			dep[nx] = dep[x] + 1;
			s.push_back(nx);
		}
	}
	vector in(n + 1, 0), out(n + 1, 0);
	for (int i = n; i >= 1; i--) {
		in[buc[i]] = out[buc[i]] = i;
		if (l[buc[i]]) out[buc[i]] = out[l[buc[i]]];
		if (r[buc[i]]) out[buc[i]] = out[r[buc[i]]];
	}
	int len = 1 << 30;
	for (int i = 1; i <= n; i++) {
		if (2 * dep[i] != dep[a] + dep[b]) continue;
		int f = 1, x = i, y = b, k = 0;
		while (1) {
			if (in[x] <= in[a] && in[a] <= out[x] &&
				in[y] <= in[i] && in[i] <= out[y]) break;
			if ((l[par[x]] == x) != (l[par[y]] == y)) { f = 0; break; }
			x = par[x], y = par[y], k++;
		}
		if (f) len = min(len, k);
	}
	if (len == 1 << 30) return string("ERROR");
	string res((dep[a] - dep[b]) / 2 + 2 * len, 'B');
	for (int i = 0; i < len; i++) {
		res[res.size() - 1 - i] = "RL"[l[par[b]] == b];
		b = par[b];
	}
	return res;
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int tc; cin >> tc;
	while (tc--) {
		int n, a, b; cin >> n >> a >> b;
		vector l(n + 1, 0), r(n + 1, 0);
		for (int i = 1; i <= n; i++) cin >> l[i] >> r[i];
		cout << sol(n, a, b, l, r) << '\n';
	}
}