#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

int main() {
	fastio;
	string s; cin >> s;
	for (char& c : s) c ^= 32;
	cout << s << '\n';
	for (int i = 1; i < s.size(); i++) {
		if (s[i - 1] != 's' || s[i] != 's') continue;
		cout << s.substr(0, i - 1) << 'B' << s.substr(i + 1) << '\n';
	}
}