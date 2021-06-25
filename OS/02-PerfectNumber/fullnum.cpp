#include <iostream>
#include <pthread.h>
#include <mutex>
using namespace std;

#define MAX_THREADS 10

int input_buffer[MAX_THREADS][3] = {0};
int output_buffer[2560] = {0};
int pointer = 0;
int fine_cnt = 0;
int n, p;
mutex m;

bool is_factor(int a, int num)
{
    return !(num % a);
}

void *thread_handler(void *threadId)
{
    int id = *(int *)threadId;
    m.lock();
    cout << "[+] Thread " << id << " start." << endl;
    m.unlock();
    int s = input_buffer[id][0];
    int e = input_buffer[id][1];

    for (int i = s; i <= e; i++)
        if (is_factor(i, n))
        {
            m.lock();
            output_buffer[pointer++] = i;
            m.unlock();
        }

    m.lock();
    cout << "[-] Thread " << id << " finished." << endl;
    m.unlock();
    fine_cnt++;
    return 0;
}

int main()
{
    cout << "Input n and p: ";
    cin >> n >> p;

    if (p > MAX_THREADS)
    {
        cout << "Hyper threads detect! Exit." << endl;
        return 1;
    }

    int num = n / p;
    cout << "[Main] Preparing input... Each thread should process " << num << " nums." << endl;

    for (int i = 0; i < p; i++)
    {
        input_buffer[i][0] = i * num + 1;
        input_buffer[i][1] = (i + 1) * num;
    }
    input_buffer[p - 1][1] = n - 1;

    cout << "[Main] Creating threads..." << endl;
    pthread_t threads[p];
    int rc;

    for (int i = 0; i < p; i++)
    {
        input_buffer[i][2] = i;
        rc = pthread_create(&threads[i], nullptr, thread_handler, (void *)&input_buffer[i][2]);
        if (rc)
        {
            cout << "Thread create error: " << rc << endl;
            return 1;
        }
    }

    cout << "[Main] Done. Waiting for threads finished.." << endl;
    while (fine_cnt != p)
        ;
    cout << "[Main] Seems threads are done. Check for answer..." << endl;

    int res = 0;
    for (int i = 0; i < pointer; i++)
        res += output_buffer[i];

    if (res == n)
        cout << "Yes, the num is a complete number" << endl;
    else
        cout << "No, the number isnot a complete number" << endl;

    return 0;
}