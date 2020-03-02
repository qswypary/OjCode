#include <iostream>
using namespace std;

int cnt = 0;

void hanoi(int num, char from, char aid1, char aid2, char to) {
    if (num == 0) {
        return;
    }
    else if (num == 1) {
        cout << "Step " << ++cnt << ":" << from << " -> " << to << endl;
    }
    hanoi(num - 2, from, aid2, to, aid1);
    cout << "Step " << ++cnt << ":" << from << " -> " << aid2 << endl;
    cout << "Step " << ++cnt << ":" << from << " -> " << to << endl;
    cout << "Step " << ++cnt << ":" << aid2 << " -> " << to << endl;
    hanoi(num - 2, aid1, from, aid2, to);
}

int main() {
    int n;
    cin >> n;
    hanoi(n, 'A', 'B', 'C', 'D');
}