#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

int main() {
	fastio;
	int n, s = 0; cin >> n;
	while (n--) {
		char c; int x; cin >> x >> c >> x;
		s += c == 'R' ? x : -x;
	}
	int p; cin >> p;
	cout << p + s << '\n';
}