#include <iostream>
#include <algorithm>
#include <vector>
#include <list>
using namespace std;

struct Conflict {
    int rune1 = 0;
    int rune2 = 0;
    int value = 0;
};

int main() {
    vector<Conflict> conf;
    vector<list<char>> connection;
    vector<int> one_conn_num;
    int n, m;
    cin >> n >> m;
    one_conn_num.push_back(0);
    connection.push_back(list<char>());
    for (int i = 0; i != n; ++i) {
        one_conn_num.push_back(0);
        connection.push_back(list<char>());
        for (int j = 0; j != n; ++j) {
            if (j != i) connection.back().push_back(j + 1);
        }
    }
    for (int i = 0; i != m; ++i) {
        Conflict curr;
        cin >> curr.rune1 >> curr.rune2 >> curr.value;
        conf.push_back(curr);
    }

    sort(
        conf.begin(), conf.end(),
        [](Conflict a, Conflict b){ return a.value > b.value; }
    );
    if (n == 1) { cout << 0 << endl; return 0; }
    else if (n == 2 || n == 3) { cout << conf.back().value << endl; return 0; }
    bool even = (n % 2 == 0);
    bool flag = even;
    int i = 0;
    for ( ; i != conf.size(); ++i) {
        auto item = conf[i];
        list<char> &conn1 = connection[item.rune1];
        list<char> &conn2 = connection[item.rune2];

        conn1.remove(item.rune2);
        conn2.remove(item.rune1);

        if (conn1.size() == 1) {
            ++one_conn_num[conn1.front()];
            if (one_conn_num[conn1.front()] > 1) {
                if (flag) break;
                flag = true;
            }
        }
        else if (conn1.size() == 0) {
            --one_conn_num[conn1.front()];
            if (flag) break;
            flag = true;
        }
        if (conn2.size() == 1) {
            ++one_conn_num[conn2.front()];
            if (one_conn_num[conn2.front()] > 1) {
                if (flag) break;
                flag = true;
            }
        }
        else if (conn2.size() == 0) {
            --one_conn_num[conn2.front()];
            if (flag) break;
            flag = true;
        }
        if (conn1.empty() && conn2.empty()) break;
    }
    if (i == conf.size()) {
        cout << 0 << endl;
    }
    else {
        cout << conf[i].value << endl;
    }
}