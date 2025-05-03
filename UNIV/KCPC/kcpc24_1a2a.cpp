#include <bits/stdc++.h>
using namespace std;

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n; cin >> n;
	if (n & 1) {
		cout << -1 << ' ' << -2 << ' ' << 3 << ' ';
		n -= 3;
	}
	for (int i = 1; i <= n / 2; i++) {
		int x = i + 3;
		cout << x << ' ' << -x << ' ';
	}
	cout << 0 << '\n';
}