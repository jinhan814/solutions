#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

int main() {
	cin.tie(0)->sync_with_stdio(0);
	i64 n, x, a, b, k; cin >> n >> x >> a >> b >> k;
	string s; cin >> s;
	vector v(n, 0LL);
	i64 res = 0, acc = 0;
	for (int i = 0; i < n; i++) {
		v[i] = (n - i) * b;
		if (s[i] & 1) v[i] += (n - i) * a, acc++;
		res += x - acc * a;
	}
	nth_element(v.begin(), v.end() - k, v.end());
	for (int i = 0; i < k; i++) res += v[n - 1 - i];
	cout << res << '\n';
}