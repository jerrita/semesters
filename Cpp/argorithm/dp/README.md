## 第一题

解决背包问题

```cpp
#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> Item; // weight, value
typedef vector<Item> ItemStack;

Item items[5] = {Item(3, 25), Item(2, 20), Item(1, 15), Item(4, 40), Item(5, 50)};
bool visited[5];
int res = 0;

void dfs(int weight, ItemStack q)
{
  if (weight > 6)
    return;

  for (int i = 0; i < 5; i++)
  {
    if (!visited[i])
    {
      visited[i] = true;
      q.push_back(items[i]);
      dfs(weight + items[i].first, q);
      q.pop_back();
      visited[i] = false;
    }
  }

  int sum = 0;
  for (auto i : q)
    sum += i.second;
  if (sum > res)
  {
    res = sum;
    cout << "Found new:";
    for (auto i : q)
      cout << " (" << i.first << ',' << i.second << ')';
    cout << " <=> " << res << endl;
  }
}

int main()
{
  ItemStack tmp;
  dfs(0, tmp);
  return 0;
}
```

简单写了个程序，遍历完所有选项，得到答案是选择3号和5号，总价值为65

```bash
Found new: (3,25) (2,20) (1,15) <=> 60
Found new: (1,15) (5,50) <=> 65
```



## 第二题

利用Floyd算法求解以下图的完全最短路径

