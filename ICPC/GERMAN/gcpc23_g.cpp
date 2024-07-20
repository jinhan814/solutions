#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

int main() {
	fastio;
	string s; cin >> s;
	int res = s.size() > 1 ? s.size() - 1 : 1;
	for (int x = 1; x <= 9; x++) {
		string t = string(s.size(), x | 48);
		res += t.size() - (s < t);
	}
	cout << res << '\n';
}