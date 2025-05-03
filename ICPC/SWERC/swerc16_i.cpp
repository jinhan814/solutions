#include <bits/stdc++.h>
using namespace std;

template<int mod>
struct modint {
	using i64 = long long;
	constexpr modint() : r(0) {}
	constexpr modint(int x) : r(x % mod) { if (r < 0) r += mod; }
	constexpr modint(i64 x) : r(x % mod) { if (r < 0) r += mod; }
	static modint pow(modint x, size_t n) { modint ret = 1;
		for (; n; n >>= 1, x *= x) if (n & 1) ret *= x; return ret; }
	modint inv() const { return pow(*this, mod - 2); }
	modint operator- () const { return r ? mod - r : 0; }
	modint operator+ (const modint& x) const { return modint(*this) += x; }
	modint operator- (const modint& x) const { return modint(*this) -= x; }
	modint operator* (const modint& x) const { return modint(*this) *= x; }
	modint operator/ (const modint& x) const { return modint(*this) /= x; }
	modint& operator+= (const modint& x) { r = r - mod < -x.r ? r + x.r : r - mod + x.r; return *this; }
	modint& operator-= (const modint& x) { r = r < x.r ? r - x.r + mod : r - x.r; return *this; }
	modint& operator*= (const modint& x) { r = (i64)r * x.r % mod; return *this; }
	modint& operator/= (const modint& x) { return *this *= x.inv(); }
	bool operator== (const modint& x) const { return r == x.r; }
	bool operator!= (const modint& x) const { return r != x.r; }
	operator int() const { return r; }
	friend istream& operator>> (istream& in, modint& x) { i64 t; in >> t; x = modint(t); return in; }
	friend ostream& operator<< (ostream& out, const modint& x) { return out << x.r; }
private:
	int r;
};

using mint = modint<13>;

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, s, t, m; cin >> n >> s >> t >> m;
	vector data(0, pair(0, vector(0, 0)));
	for (int i = 0; i < m; i++) {
		int cost, k; cin >> cost >> k;
		vector v(k, 0);
		for (int i = 0; i < k; i++) cin >> v[i];
		data.push_back({ cost, v });
	}

	map idx{ pair(pair(0, 0), 0) }; idx.clear();
	for (const auto& [cost, v] : data) {
		for (int i = 1; i < v.size(); i++) {
			int a = v[i - 1], b = v[i];
			if (a > b) swap(a, b);
			if (!idx.count({ a, b })) idx[{ a, b }] = idx.size();
		}
	}

	vector mat(m, vector(idx.size() + 1, mint(0)));
	for (int i = 0; i < m; i++) {
		const auto& [cost, v] = data[i];
		for (int j = 1; j < v.size(); j++) {
			int a = v[j - 1], b = v[j];
			if (a > b) swap(a, b);
			mat[i][idx[{ a, b }]] += mint(1);
		}
		mat[i][idx.size()] = mint(cost);
	}

	auto sub = [](auto& a, const auto& b, mint x) {
		for (int i = 0; i < a.size(); i++) a[i] -= b[i] * x;
	};

	int rank = 0;
	for (int j = 0; j <= idx.size() && rank < m; j++) {
		for (int i = rank + 1; i < m; i++) if (mat[i][j]) swap(mat[rank], mat[i]);
		if (mat[rank][j] == mint(0)) continue;
		mint inv = mat[rank][j].inv();
		for (mint& x : mat[rank]) x *= inv;
		for (int i = 0; i < m; i++) if (i != rank && mat[i][j]) sub(mat[i], mat[rank], mat[i][j]);
		rank++;
	}

	vector adj(n + 1, vector(0, pair(0, 0)));
	for (auto [e, i] : idx) {
		auto [a, b] = e;
		int cost = int(mat[i].back());
		adj[a].push_back({ b, cost });
		adj[b].push_back({ a, cost });
	}

	vector d(n + 1, 1 << 30);
	set pq{ pair(d[s] = 0, s) };
	while (pq.size()) {
		auto [cdist, cur] = *pq.begin(); pq.erase(pq.begin());
		for (auto [nxt, cost] : adj[cur]) {
			int ndist = cdist + cost;
			if (d[nxt] <= ndist) continue;
			pq.erase({ d[nxt], nxt });
			pq.insert({ d[nxt] = ndist, nxt });
		}
	}
	cout << d[t] << '\n';
}