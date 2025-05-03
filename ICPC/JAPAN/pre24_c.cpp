#include <bits/stdc++.h>
using namespace std;

auto sol = [](int x, int y) {
	if (x * y > 0) return abs(x + y);
	return max(abs(x), abs(y));
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n; cin >> n;
	for (int i = 0; i < n; i++) {
		int x, y; cin >> x >> y;
		cout << sol(x, y) << '\n';
	}
}