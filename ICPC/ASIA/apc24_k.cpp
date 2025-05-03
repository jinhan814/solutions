#include<bits/stdc++.h>
using namespace std;

using i64 = long long;

struct fenwick {
	fenwick(int n) : sz(n), tree(n + 1) {}
	void update(int i, i64 x) {
		for (; i <= sz; i += i & -i) tree[i] += x;
	}
	i64 query(int i) const {
		i64 ret = 0;
		for (; i; i -= i & -i) ret += tree[i];
		return ret;
	}
private:
	int sz;
	vector<i64> tree;
};

struct bit_array { // 0-indexed
   using u64 = unsigned long long;
   explicit bit_array(int sz) : n(sz + 64 >> 6), data(n), psum(n) {}
   void set(int i) { data[i >> 6] |= u64(1) << (i & 63); }
   int rank(int i, bool x) const {
      auto res = rank(i);
      return x ? res : i - res;
   }
   int rank(int l, int r, bool x) const {
      auto res = rank(r) - rank(l);
      return x ? res : r - l - res;
   }
   bool operator[](int i) const {
      return data[i >> 6] >> (i & 63) & 1;
   }
   void init() {
      for (int i = 1; i < n; i++)
         psum[i] = psum[i - 1] + __builtin_popcountll(data[i - 1]);
   }
private:
   int n;
   vector<u64> data;
   vector<int> psum;
   int rank(int i) const {
      return psum[i >> 6] + __builtin_popcountll(data[i >> 6] & (u64(1) << (i & 63)) - 1);
   }
};

template<typename T, enable_if_t<is_integral_v<T>, int> = 0>
struct wavelet_matrix { // 0-indexed
	explicit wavelet_matrix(vector<T> v) :
		n(v.size()),
		lg(__lg(*max_element(v.begin(), v.end())) + 1),
		data(lg, bit_array(n)),
		zero(lg, 0) {
		for (int i = lg - 1; i >= 0; i--) {
			for (int j = 0; j < n; j++) if (v[j] >> i & 1) data[i].set(j);
			data[i].init();
			auto it = stable_partition(v.begin(), v.end(), [&](T x) { return ~x >> i & 1; });
			zero[i] = it - v.begin();
		}
	}
	int count(int l, int r, T x) const { // count i s.t. (l <= i < r) && (v[i] < x)
		if (x >> lg) return r - l + 1;
		int res = 0;
		for (int i = lg - 1; i >= 0; i--) {
			bool f = x >> i & 1;
			if (f) res += data[i].rank(l, r, 0);
			adjust(i, l, r, f);
		}
		return res;
	}
private:
	int n, lg;
	vector<bit_array> data;
	vector<int> zero;
	void adjust(int i, int& l, int& r, bool f) const {
		if (!f) {
			l = data[i].rank(l, 0);
			r = data[i].rank(r, 0);
		}
		else {
			l = zero[i] + data[i].rank(l, 1);
			r = zero[i] + data[i].rank(r, 1);
		}
	}
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n, q, root; cin >> n >> q;
	vector adj(n + 1, vector(0, 0));
	for (int i = 1; i <= n; i++) {
		int x; cin >> x;
		if (x) adj[x].push_back(i);
		else root = i;
	}

	vector in(n + 1, 0), out(n + 1, 0), v(n + 1, 0), sz(n + 1, 1);
	{
		int ord = 0;
		auto dfs = [&](const auto& self, int cur) -> void {
			in[cur] = ++ord;
			v[in[cur]] = cur;
			for (int nxt : adj[cur]) {
				self(self, nxt);
				sz[cur] += sz[nxt];
			}
			out[cur] = ord;
		};
		dfs(dfs, root);
	}

	vector queries(n + 1, vector(0, pair(0, 0)));
	for (int i = 1; i <= q; i++) {
		i64 x; cin >> x;
		queries[(x - 1) / n + 1].push_back({ i, (x - 1) % n + 1 });
	}

	vector res(q + 1, 0LL);
	{
		fenwick ft(n);
		auto ft_kth = [&](int k) {
			int lo = 0, hi = n;
			while (lo + 1 < hi) {
				int mid = lo + hi >> 1;
				if (ft.query(mid) < k) lo = mid;
				else hi = mid;
			}
			return hi;
		};

		wavelet_matrix wm(v);
		auto wm_kth = [&](int u, int c, int k) {
			int lo = 0, hi = n;
			while (lo + 1 < hi) {
				int mid = lo + hi >> 1;
				int a = wm.count(in[u], out[u] + 1, mid + 1);
				int b = c ? wm.count(in[c], out[c] + 1, mid + 1) : 0;
				if (a - b < k) lo = mid;
				else hi = mid;
			}
			return hi;
		};

		vector c(n + 1, 0);
		auto dfs = [&](const auto& self, int cur) -> void {
			ft.update(cur, sz[cur]);
			for (auto [i, k] : queries[cur]) {
				int x = cur;
				int l = ft_kth(k);
				int y = wm_kth(l, c[l], k - ft.query(l - 1));
				res[i] = (x - 1LL) * n * n + (l - 1LL) * n + (y - 1LL);
			}
			for (int nxt : adj[cur]) {
				ft.update(cur, -sz[nxt]);
				c[cur] = nxt;
				self(self, nxt);
				ft.update(cur, +sz[nxt]);
				c[cur] = 0;
			}
			ft.update(cur, -sz[cur]);
		};
		dfs(dfs, root);
	}
	for (int i = 1; i <= q; i++) cout << res[i] << '\n';
}