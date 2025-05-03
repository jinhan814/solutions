#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

const auto p = [] {
	vector p(19, 1LL);
	for (int i = 1; i <= 18; i++) p[i] = p[i - 1] * 10;
	return p;
}();

i64 g(int k) {
	if (k == 1) return 10;
	return 9 * p[k - 1 >> 1];
}

i64 sol(i64 n) {
	if (n < 10) return n + 1;
	string s = to_string(n);
	i64 ret = 0, k = s.size();
	for (int i = 1; i < k; i++) ret += g(i);
	for (int i = k; i > k >> 1; i--) {
		int j = 2 * i - k - 1 >> 1;
		i64 a = s[k - i] - 48 - (i == k);
		i64 b = p[j < 0 ? 0 : j];
		ret += a * b;
	}
	string t = s;
	for (int i = k; i >= k + 1 >> 1; i--) t[i - 1] = t[k - i];
	if (t <= s) ret++;
	return ret;
}

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int N; cin >> N;
	while (N--) {
		i64 l, r; cin >> l >> r;
		cout << sol(r) - sol(l - 1) << '\n';
	}
}