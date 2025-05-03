#include <bits/stdc++.h>
using namespace std;

int main() {
	cin.tie(0)->sync_with_stdio(0);
	int n; cin >> n;
	int s = 0, x; char c;
	while (n--) cin >> x >> c >> x, s += c == 'R' ? x : -x;
	int p; cin >> p;
	cout << p + s << '\n';
}