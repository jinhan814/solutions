#include <bits/stdc++.h>
#define fastio cin.tie(0)->sync_with_stdio(0)
using namespace std;

int main() {
    fastio;
    string s; cin >> s;
    int sum = 0, cnt = 0;
    for (int i = s.size() - 1; i >= 0; i--) if (s[i] == '1') sum += (s.size() - ++cnt - i) % 3;
    cout << (sum % 3 ? "Alice" : "Bob") << '\n';
}