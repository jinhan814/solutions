#include <bits/stdc++.h>
using namespace std;

auto sol = [](string s) {
	string t = s;
	sort(t.begin(), t.end());
	t.erase(unique(t.begin(), t.end()), t.end());
	return s.size() - t.size();
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	string s; cin >> s;
	cout << sol(s) << '\n';
}