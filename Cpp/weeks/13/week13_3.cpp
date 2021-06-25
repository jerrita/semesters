#include <iomanip>
#include <iostream>
#define X 10
using namespace std;

int n;
const int dir[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
bool used[X + 1][X + 1] = {0};
int arr[X + 1][X + 1];

bool check(int x, int y) {
  if (x <= n && x >= 1 && y <= n && y >= 1 && !used[x][y])
    return true;
  else
    return false;
}
int main() {
  cin >> n;
  int i = 1, x = 1, y = 1;
  arr[x][y] = i++;
  used[x][y] = true;
  while (i <= n * n) {
    for (int j = 0; j < 4; j++) {
      while (check(x + dir[j][0], y + dir[j][1])) {
        x += dir[j][0];
        y += dir[j][1];
        arr[x][y] = i++;
        used[x][y] = true;
      }
    }
  }

  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      cout << setfill('*') << setw(4) << arr[i][j];
    }
    cout << endl;
  }
  return 0;
}
