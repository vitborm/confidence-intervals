#include <iostream>
#include <stdio.h>

#define MAGIC 0.95

using namespace std;

double sum(double l, double r, double *arr)
{
    double res = 0;
    for(int i = l; i <= r; ++i)
        res += arr[i];

    return res;
}

int main()
{
    freopen("in.txt", "r", stdin);
    freopen("result.txt", "w", stdout);
    int cnt; double p, sum_p = 0; cin >> cnt;
    double *chanceOf = new double[cnt + 1];
    for(int i = 1; i <= cnt; ++i) chanceOf[i] = 0;
    chanceOf[0] = 1;
    for(int i = 0; i < cnt; ++i) {
        cin >> p;
        sum_p += p;
        for(int j = cnt; j > 0; --j) {
            chanceOf[j] = (1 - p)*chanceOf[j] + p*chanceOf[j - 1];
        }
        chanceOf[0] *= (1 - p);
    }

    for(int i = 0; i <= cnt; ++i) {
        cout << i << "\t" << chanceOf[i] << endl;
    }
    cout << "Expecting value: " << sum_p << endl;

    int r = 0, l = cnt;
    while(sum(0, r,   chanceOf) < MAGIC) r++;
    while(sum(l, cnt, chanceOf) < MAGIC) l--;
    while(2*chanceOf[r] + MAGIC < 1) r--;
    while(2*chanceOf[l] + MAGIC < 1) l++;
    cout << "Confidence interval is from " << l << " to " << r << " with " << sum(l, r, chanceOf) << endl;

    return 0;
}
