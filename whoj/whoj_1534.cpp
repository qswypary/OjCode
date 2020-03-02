#include <iostream>
#include <string>
#include <deque>
using namespace std;

int main() {
    string rawa, rawb;
    while (cin >> rawa >> rawb) {
        if (rawa == "0" || rawb == "0") {
            cout << 0 << endl;
            continue;
        }
        if (rawa.size() > rawb.size()) swap(rawa, rawb);
        deque<int> a, b, result(1000, 0);
        for (auto item : rawa) a.push_front(item - '0');
        for (auto item : rawb) b.push_front(item - '0');
        int pcarry = 0, first = 0, len = a.size();
        for ( ; first != len; ++first) {
            if (a[first] == 0) continue;
            int mcarry = 0, slen = b.size();
            for (int second = 0; second != slen; ++second) {
                int mres = a[first]*b[second] + mcarry;
                result[first + second] += mres % 10;
                mcarry = mres / 10;
            }
            result[first + slen] += mcarry;
        }
        for (auto beg = result.begin(); beg + 1 != result.end(); ++beg) {
            *(beg + 1) += *beg / 10;
            *beg %= 10;
        }
        auto rbeg = result.rbegin();
        for ( ; rbeg != result.rend() && *rbeg == 0; ++rbeg) ;
        for ( ; rbeg != result.rend(); ++rbeg) {
            cout << *rbeg;
        }
        cout << endl;
    }
}