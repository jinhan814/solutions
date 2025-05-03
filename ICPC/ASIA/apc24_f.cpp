#include <bits/stdc++.h>
using namespace std;

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int N; cin >> N;
	while (N--) {
		int n; cin >> n;
		vector v(n, 0);
		for (int i = 0; i < n; i++) cin >> v[i];

		auto factor = [](int n) {
			vector res(0, 0);
			for (int i = 2; i * i <= n; i++) {
				if (n % i) continue;
				while (n % i == 0) n /= i;
				res.push_back(i);
			}
			if (n > 1) res.push_back(n);
			return res;
		};

		auto cmp = [](const auto& a, const auto& b) {
			return 1LL * a.first * b.second > 1LL * b.first * a.second;
		};

		auto calc = [&](int k) {
			vector acc(k, 0);
			for (int i = 0; i < n; i++) acc[i % k] += v[i];
			multiset s(acc.begin(), acc.end());
			pair opt(*prev(s.end()), *s.begin());
			for (int i = 1; i < n; i++) {
				int& a = acc[(i + k - 1) % k];
				int& b = acc[i % k];
				s.erase(s.find(a)), s.erase(s.find(b));
				a -= v[i - 1], b -= v[i];
				swap(v[i - 1], v[i]);
				a += v[i - 1], b += v[i];
				s.insert(a), s.insert(b);
				pair res(*prev(s.end()), *s.begin());
				if (cmp(opt, res)) opt = res;
			}
			swap(v[0], v[n - 1]);
			return opt;
		};

		pair opt(1 << 30, 1);
		for (int k : factor(n)) {
			auto res = calc(k);
			if (cmp(opt, res)) opt = res;
		}
		int g = gcd(opt.first, opt.second);
		cout << opt.first / g << ' ' << opt.second / g << '\n';
	}
}