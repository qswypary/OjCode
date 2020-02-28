#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

// 用于处理确定了首位数字时，剩下的数字能产生的最小差值
// remained 中值小于 0 的将被忽略，其他数已经升序排序
// rmdlen 为剩余有效数字的个数，保证为非 0 偶数
int figureout_mindiff(int smaller, int bigger, const vector<int> &remained, int rmdlen) {
    if (smaller != bigger) {
        int cnt = 0;
        for (auto beg = remained.begin(); beg != remained.end() && cnt != rmdlen / 2; ++beg) {
            if (*beg < 0) continue;
            ++cnt;
            bigger *= 10; bigger += *beg;
        }
        cnt = 0;
        for (auto beg = remained.rbegin(); beg != remained.rend() && cnt != rmdlen / 2; ++beg) {
            if (*beg < 0) continue;
            ++cnt;
            smaller *= 10; smaller += *beg;
        }
        // cout << bigger << " - " << smaller << " = " << bigger - smaller << endl;
        return bigger - smaller;
    }
    else if (rmdlen == 0) {
        return 0;
    }

    int minneighbour = 10;
    int n = remained.size();
    vector<int> nums;
    for (int i = 0; i != n; ++i) {
        if (remained[i] >= 0) nums.push_back(remained[i]);
    }
    int fix = 0;
    if (n == rmdlen) fix = 1;
    for (int i = 1; i != rmdlen; ++i) {
        if (nums[i - fix] <= 0) continue;
        int diff = nums[i] - nums[i - 1];
        if (diff < minneighbour) {
            minneighbour = diff;
        }
    }
    int mindiff = 100000;
    for (int i = 1; i != rmdlen; ++i) {
        if (nums[i - fix] <= 0) continue;
        int diff = nums[i] - nums[i - 1];
        // cout << nums[i] << " - " << nums[i - 1] << " = " << diff << endl;
        if (diff == minneighbour) {
            smaller *= 10; smaller += nums[i - 1]; nums[i - 1] = -1;
            bigger *= 10; bigger += nums[i]; nums[i] = -1;
            int diff = figureout_mindiff(smaller, bigger, nums, rmdlen - 2);
            if (diff < mindiff) {
                mindiff = diff;
            }
            nums[i - 1] = smaller % 10; smaller /= 10;
            nums[i] = bigger % 10; bigger /= 10;
        }
    }
    return mindiff;
}

int main() {
    int t;
    cin >> t;
    for (int groupi = 0; groupi != t; ++groupi) {
        int n;
        vector<int> nums;
        cin >> n;
        for (int i = 0; i != n; ++i) {
            int tmp; cin >> tmp;
            nums.push_back(tmp);
        }

        sort(nums.begin(), nums.end());

        if (n == 2) {
            cout << abs(nums[0] - nums[1]) << endl;
            continue;
        }

        int i = 0;
        for ( ; i != n && nums[i] == 0; ++i) ;
        if (i == n - 1) {
            cout << nums[i] * pow(10, i - 1) << endl;
            continue;
        }

        int bigger = 0;
        int rmd = n;
        if (n % 2 != 0) {
            bigger = nums[i]; nums[i] = -1;
            --rmd;
        }
        cout << figureout_mindiff(0, bigger, nums, rmd) << endl;
    }
}