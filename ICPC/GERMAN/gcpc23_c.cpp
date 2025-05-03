#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

struct frac {
	frac(i64 x) : frac(x, 1) {}
	frac(i64 a, i64 b) : a(a), b(b) { norm(); }
	frac operator+ (const frac& x) const { return frac(a * x.b + x.a * b, b * x.b); }
	frac operator- (const frac& x) const { return frac(a * x.b - x.a * b, b * x.b); }
	frac operator* (const frac& x) const { return frac(a * x.a, b * x.b); }
	auto operator<=> (const frac& x) const { return a * x.b <=> x.a * b; }
	friend ostream& operator<< (ostream& out, const frac& x) { return out << x.a << '/' << x.b; }
private:
	i64 a, b;
	void norm() {
		if (a < 0) a = -a, b = -b;
		i64 g = gcd(a, b);
		a /= g, b /= g;
	}
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, m, k; cin >> n >> m >> k;
	vector v(k, 0);
	vector adj(n + 1, vector(0, 0));
	for (int i = 0; i < k; i++) cin >> v[i];
	for (int i = 0; i < m; i++) {
		int a, b; cin >> a >> b;
		adj[a].push_back(b);
		adj[b].push_back(a);
	}

	auto get_dist = [&](int st) {
		vector d(n + 1, -1);
		deque q{ st }; d[st] = 0;
		while (q.size()) {
			int cur = q.front(); q.pop_front();
			for (int nxt : adj[cur]) {
				if (~d[nxt]) continue;
				q.push_back(nxt); d[nxt] = d[cur] + 1;
			}
		}
		return d;
	};
	auto d1 = get_dist(1), dn = get_dist(n);

	frac res(d1[n]), acc(0);
	for (int x : v) acc = acc + frac(dn[x]);
	for (int x : v) res = min(res, frac(d1[x]) + frac(1, k - 1) * (acc - frac(dn[x])));
	cout << res << '\n';
}