#include <bits/stdc++.h>
using namespace std;

auto ask = [](int x) {
	cout << "? " << x << endl;
	cin >> x;
	return x;
};

int main() {
	int n; cin >> n;
	int a = ask(1), b = ask(n);
	auto f = [&](int x) { return 2 * ask(x) - a - b; };
	int lo = 2, hi = n;
	while (lo + 1 < hi) {
		int mid = lo + hi >> 1;
		if (f(mid) <= 0) lo = mid;
		else hi = mid;
	}
	int x = lo;
	if (x + 1 < n && abs(f(x)) > abs(f(x + 1))) x++;
	cout << "! " << 1 << ' ' << x << ' ' << n << endl;
}