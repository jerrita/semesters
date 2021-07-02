#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

int n, W;
int dp[101][101];
int w[101], v[101];

int main()
{
  int t; // t 组数据
  cin >> t;
  while (t--)
  {
    cin >> n >> W;
    memset(dp, 0, sizeof(dp));

    for (int i = 0; i < n; i++)
      cin >> w[i];
    for (int i = 0; i < n; i++)
      cin >> v[i];

    // 算到 n, W
    for (int i = 1; i <= n; i++)
      for (int j = 1; j <= W; j++)
      {
        if (w[i - 1] > j)
          dp[i][j] = dp[i - 1][j];
        else
          dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - w[i - 1]] + v[i - 1]);
      }

    for (int i = 1; i <= n; i++)
    {
      for (int j = 1; j <= W; j++)
        cout << dp[i][j] << " | ";
      cout << endl;
    }
    cout << dp[n][W] << endl;
  }
  return 0;
}
