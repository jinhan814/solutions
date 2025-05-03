#include <bits/stdc++.h>
using namespace std;

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int a, b, c; cin >> a >> b >> c;
	int res = 0, x = 0, y = 1;
	while (y < c) {
		x += b * y;
		while (x >= a) x -= a, y++;
		res++;
	}
	cout << res << '\n';
}