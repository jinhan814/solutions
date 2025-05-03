#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

int main() {
	cin.tie(0)->sync_with_stdio(0);
	i64 n, res = 0; cin >> n;
	vector v(n << 1, 0);
	for (int i = 0; i < n << 1; i++) {
		int a, b; cin >> a >> b;
		if (a > b) swap(a, b);
		res += b;
		v[i] = a + b;
	}
	nth_element(v.begin(), v.begin() + n, v.end());
	res -= reduce(v.begin(), v.end() - n, 0LL);
	cout << res << '\n';
}