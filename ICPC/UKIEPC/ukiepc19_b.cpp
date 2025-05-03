#include <bits/stdc++.h>
using namespace std;

auto f = [](string a, string b) {
	return abs(stoll(a) - stoll(b));
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	string s; cin >> s;
	string a = s[0] + string(s.size() - 1, 48);
	string b = s[0] + string(s.size() - 1, 48);
	if (++b[0] == 58) b = "10" + b.substr(1);
	cout << (f(a, s) < f(b, s) ? a : b) << '\n';
}