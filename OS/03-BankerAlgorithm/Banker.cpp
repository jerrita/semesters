#include <bits/stdc++.h>

#define FPT for (int i = 0; i < pattern; i++)
#define WD 20 // 制表宽度
using namespace std;

const int max_n = 64; // 可支持最大资源种类
int available[max_n]; // 系统当前拥有资源
int used[max_n];      // 已用
int pattern;          // 显示几种资源的占用数量
int pid = 0;          // 起点

// 得到可用的资源
inline int getCanUse(int n) { return available[n] - used[n]; }

struct Customer {
  int pid;
  int pat;
  int max[max_n];
  int allocated[max_n];
  int need[max_n];

  void calcNeed() {
    for (int i = 0; i < pat; i++)
      need[i] = max[i] - allocated[i];
  }
};

vector<Customer> workers;

string resPrinter(int *arr) {
  string out;
  FPT out += " " + to_string(arr[i]);
  return out;
}

void sys_init() {
  memset(available, 0, sizeof(available));
  memset(used, 0, sizeof(used));
  cout << "-------------------------------------------\n"
       << "     Banker algorithm v1 for OS Course     \n"
       << "                                 by jerrita\n"
       << "-------------------------------------------" << endl;
  cout << "Please input initial resources: ";

  pattern = 0;
  while (cin.peek() != '\n')
    cin >> available[pattern++];
  cout << "System inited. Default pattern is: " << pattern << endl;
}

void sys_info() {
  cout << "\n-------------------------------------------\n"
       << "                 System info\n"
       << "Available resources: ";
  FPT cout << available[i] << ' ';
  cout << endl;
  cout << "               Used: ";
  FPT cout << used[i] << ' ';
  cout << "\n-------------------------------------------" << endl;

  cout << "Info of " << workers.size() << " processors:\n" << endl;
  cout.width(WD);
  cout << "PID" << setw(WD) << "Max" << setw(WD) << "Allocated" << setw(WD)
       << "Need" << endl;
  for (auto p : workers) {
    cout.width(WD);
    cout << p.pid << setw(WD) << resPrinter(p.max) << setw(WD)
         << resPrinter(p.allocated) << setw(WD) << resPrinter(p.need) << endl;
  }
  cout << endl;
}

void menu() {
  cout << "-------------------------------------------\n"
       << "                    Menu\n"
       << "1: New process.\n"
       << "2: Allocate resources for process.\n"
       << "3: Process finish.\n"
       << "4: Show system info.\n"
       << "5: Exit system.\n"
       << "-------------------------------------------" << endl;
}

void newProcess() {
  Customer customer{};
  customer.pid = pid;
  memset(customer.max, 0, sizeof(customer.max));
  memset(customer.allocated, 0, sizeof(customer.allocated));
  memset(customer.need, 0, sizeof(customer.need));

  cout << "Input need resources: ";
  customer.pat = 0;
  if (cin.peek() == '\n')
    cin.get();
  while (cin.peek() != '\n')
    cin >> customer.max[customer.pat++];

  for (int i = 0; i < customer.pat; i++)
    if (customer.max[i] > available[i]) {
      cout << "Resources not enough! Failed." << endl;
      return;
    }

  customer.calcNeed();
  workers.push_back(customer);
  pid++;
  sys_info();
}

void allocateResources() {
  int op;

  cout << "Enter process pid: ";
  cin >> op;

  vector<Customer>::iterator process;
  for (process = workers.begin();
       process->pid != op && process != workers.end(); process++)
    ;

  if (process == workers.end()) {
    cout << "Cannot find the process. Failed." << endl;
    return;
  }
  int tempNeed[max_n] = {0};

  cout << "Info of process:" << endl;
  cout.width(WD);
  cout << "PID" << setw(WD) << "Max" << setw(WD) << "Allocated" << setw(WD)
       << "Need" << endl;

  cout.width(WD);
  cout << process->pid << setw(WD) << resPrinter(process->max) << setw(WD)
       << resPrinter(process->allocated) << setw(WD)
       << resPrinter(process->need);

  cout << endl;

  cout << "Enter allocate resources: ";
  int p = 0;
  if (cin.peek() == '\n')
    cin.get();
  while (cin.peek() != '\n')
    cin >> tempNeed[p++];

  cout << "Checking for conflict..." << endl;

  for (int i = 0; i < process->pat; i++) {
    // 检查此次申请是否超过了之前声明的最大需求
    if (process->allocated[i] + tempNeed[i] > process->max[i]) {
      cout << "Illegal allocate! Failed." << endl;
      return;
    }

    // 检查剩余资源是否可满足此次请求
    if (tempNeed[i] > getCanUse(i)) {
      cout << "Not have enough resources. Failed." << endl;
      return;
    }
  }

  // 试探性分配与安全性检查
  // 状态备份
  int vAvailable[max_n] = {0}, vUsed[max_n] = {0};
  int vAllocatedAvailable[max_n] = {0}, vAllocatedUsed[max_n] = {0};
  vector<Customer> vTempWorkers(workers);
  FPT {
    vAvailable[i] = available[i];
    available[i] = available[i] - tempNeed[i];
    vAllocatedAvailable[i] = available[i];
    vUsed[i] = used[i];
    used[i] = used[i] + tempNeed[i];
    vAllocatedUsed[i] = used[i];

    process->allocated[i] += tempNeed[i];
  }
  process->calcNeed();

  // 分配后状态保存
  vector<Customer> vAllocated(workers);

  // 安全性检查
  bool pass = true;

  vector<int> safe;
  while (!workers.empty()) {
    bool ck1 = false; // 判断是否有进程可以被满足

    for (auto it = workers.begin(); it != workers.end(); it++) {
      bool ck2 = true; // 判断能不能满足进程剩余需求
      for (int i = 0; i < it->pat; i++)
        if (it->need[i] > available[i]) {
          ck2 = false;
          break;
        }

      if (ck2) {
        ck1 = true;
        safe.push_back(it->pid);

        // 释放空间
        for (int i = 0; i < it->pat; i++) {
          available[i] += it->allocated[i];
          used[i] -= it->allocated[i];
        }
        workers.erase(it);
        break;
      }
    }

    if (!ck1) // 不安全
    {
      pass = false;
      break;
    }
  }

  // 安全性检查结束
  if (pass) {
    // 还原到第一次分配后状态
    workers = vAllocated;
    FPT {
      available[i] = vAllocatedAvailable[i];
      used[i] = vAllocatedUsed[i];
    }

    cout << "Success. Find seq: ";
    for (int i : safe)
      cout << i << ' ';
    cout << endl;
  } else {
    // 还原到原始状态
    workers = vTempWorkers;
    FPT {
      available[i] = vAvailable[i];
      used[i] = vUsed[i];
    }

    cout << "Failed. Cannot pass security check!" << endl;
  }
}

void killProcess() {
  int p;
  cout << "Enter pid: ";
  cin >> p;

  for (auto it = workers.begin(); it != workers.end(); it++) {
    if (it->pid == p) {
      cout << "Info of process:" << endl;
      cout.width(WD);
      cout << "PID" << setw(WD) << "Max" << setw(WD) << "Allocated" << setw(WD)
           << "Need" << endl;

      cout.width(WD);
      cout << it->pid << setw(WD) << resPrinter(it->max) << setw(WD)
           << resPrinter(it->allocated) << setw(WD) << resPrinter(it->need);

      for (int i = 0; i < it->pat; i++) {
        available[i] += it->allocated[i];
        used[i] -= it->allocated[i];
      }

      workers.erase(it);

      cout << "\nErased." << endl;
    }
  }
}

int main() {
  int choose;

  sys_init();

  while (true) {
    menu();
    cout << "Enter num to choose: ";
    cin >> choose;

    switch (choose) {
    case 1:
      newProcess();
      break;
    case 2:
      allocateResources();
      break;
    case 3:
      killProcess();
      break;
    case 4:
      sys_info();
      break;
    case 5:
      return 0;
    default:
      continue;
    }
  }
}
