#include <iostream>
using namespace std;

int main() {
    int n;
    const int put = 7;
    while (cin >> n) {
        if (n == 0) break;
        int sum = 0, incre = 0, dim = 1, rem = 0;
        while (n != 0) {
            int tail = n % 10;
            sum += incre*tail;
            if (tail > put) sum += dim;
            else if (tail == put) sum += rem + 1;
            rem += tail*dim;
            incre *= 10; incre += dim;
            dim *= 10;
            n /= 10;
        }
        cout << sum << endl;
    }
}