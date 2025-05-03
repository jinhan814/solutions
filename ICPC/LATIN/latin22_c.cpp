#include <bits/stdc++.h>
using namespace std;

using i64 = long long;

int main() {
	cin.tie(0)->sync_with_stdio(0);
	i64 n, a, b; cin >> n >> a >> b; a--, b--;
	string res;
	for (int d = 1; d <= n; d++) {
		i64 val = b >> d - 1 & 3;
		if ((val == 1 || val == 2) ^ (a >> n - d)) {
			res.push_back('L');
			if (a >> n - d) a -= 1LL << n - d;
			else a = (1LL << n - d) - 1 - a;
		}
		else {
			res.push_back('R');
			if (a >> n - d) a = (1LL << n - d + 1) - 1 - a;
			else;
		}
	}
	cout << res << '\n';
}