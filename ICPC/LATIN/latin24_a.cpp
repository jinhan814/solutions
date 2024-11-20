#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

auto sol = [](string s) {
	string t = s;
	sort(t.begin(), t.end());
	t.erase(unique(t.begin(), t.end()), t.end());
	return s.size() - t.size();
};

int main() {
	fastio;
	string s; cin >> s;
	cout << sol(s) << '\n';
}