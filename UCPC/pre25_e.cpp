#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n; cin >> n;
	vector v(n + 1, 0LL);
	for (int i = 1; i <= n; i++) cin >> v[i];
	int q; cin >> q;
	while (q--) {
		int op; cin >> op;
		if (op == 1) {
			int i, x; cin >> i >> x;
			for (int j = i, val = x; j >= 1; j--) {
				i64 d = min(v[j], (i64)val);
				v[j] += d;
				val -= d;
				if (val == 0) break;
			}
			for (int j = i + 1, val = x; j <= n; j++) {
				i64 d = min(v[j], (i64)val);
				v[j] += d;
				val -= d;
				if (val == 0) break;
			}
		}
		else {
			int i; cin >> i;
			cout << v[i] << '\n';
		}
	}
}