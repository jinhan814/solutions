#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

int main() {
	fastio;
	int a, b, c; cin >> a >> b >> c;
	int res = 0, x = 0, y = 1;
	while (y < c) {
		x += b * y;
		while (x >= a) x -= a, y++;
		res++;
	}
	cout << res << '\n';
}