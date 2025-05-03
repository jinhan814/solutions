#include <bits/stdc++.h>
using namespace std;

int main() {
	cin.tie(0)->sync_with_stdio(0);
	string s; cin >> s;
	auto acc = 0LL;
	for (int i = 0, d = 0; i < s.size(); i++) {
		if (s[i] == '(') d++;
		else { d--; if (i && s[i - 1] == '(') acc += d; }
	}
	cout << acc << '\n';
}