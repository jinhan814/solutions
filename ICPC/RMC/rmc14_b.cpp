#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

int main() {
	fastio;
	int tc; cin >> tc;
	while (tc--) {
		string a, b, c; cin >> a >> b >> c;
		int n; cin >> n;
		int x = stoi(b.substr(0, 4));
		int y = stoi(c.substr(0, 4));
		int f = x < 2010 && y < 1991 ? n < 41 ? 1 : 2 : 0;
		cout << a << ' ';
		cout << (f ? f & 1 ? "coach petitions" : "ineligible" : "eligible") << '\n';
	}
}