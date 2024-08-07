#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

using i64 = long long;

int main() {
	fastio;
	int n, k; cin >> n >> k;
	string s; cin >> s;
	vector _c(n + 1 << 1, 0);
	auto c = _c.begin() + n + 1;
	for (int i = 0, x = 0; i < 2 * n; i++) c[x += s[i] & 1 ? 1 : -1]++;
	i64 res = 0, l = -n, r = n;
	while (r - l > k) {
		if (r == 0 || l && c[l] < c[r]) c[l + 2] += c[l], res += c[l++];
		else c[r - 2] += c[r], res += c[r--];
	}
	cout << res << '\n';
}