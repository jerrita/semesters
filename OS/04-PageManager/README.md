# OS 第四次作业



## 虚拟内存

虚拟内存的目的是为了让物理内存扩充成更大的逻辑内存，从而让程序获得更多的可用内存。

为了更好的管理内存，操作系统将内存抽象成地址空间。每个程序拥有自己的地址空间，这个地址空间被分割成多个块，每一块称为一页。这些页被映射到物理内存，但不需要映射到连续的物理内存，也不需要所有页都必须在物理内存中。当程序引用到不在物理内存中的页时，由硬件执行必要的映射，将缺失的部分装入物理内存并重新执行失败的指令。

从上面的描述中可以看出，虚拟内存允许程序不用将地址空间中的每一页都映射到物理内存，也就是说一个程序不需要全部调入内存就可以运行，这使得有限的内存运行大程序成为可能。例如有一台计算机可以产生 16 位地址，那么一个程序的地址空间范围是 0~64K。该计算机只有 32KB 的物理内存，虚拟内存技术允许该计算机运行一个 64K 大小的程序。

![](https://img.jerrita.cn/blog/68747470733a2f2f63732d6e6f7465732d313235363130393739362e636f732e61702d6775616e677a686f752e6d7971636c6f75642e636f6d2f37623238316231652d303539352d343032622d616533352d3863393130383463333363312e706e67.png)



## 算法说明

在地址映射过程中，若在页面中发现所要访问的页面不在内存中，则产生缺页中断。当发生缺页中断时，如果操作系统内存中没有空闲页面，则操作系统必须在内存选择一个页面将其移出内存，以便为即将调入的页面让出空间。而用来选择淘汰哪一页的规则叫做页面置换算法



## 分页系统地址映射

内存管理单元（MMU）管理着地址空间和物理内存的转换，其中的页表（Page table）存储着页（程序地址空间）和页框（物理内存空间）的映射表。

一个虚拟地址分成两个部分，一部分存储页面号，一部分存储偏移量。

下图的页表存放着 16 个页，这 16 个页需要用 4 个比特位来进行索引定位。例如对于虚拟地址（0010 000000000100），前 4 位是存储页面号 2，读取表项内容为（110 1），页表项最后一位表示是否存在于内存中，1 表示存在。后 12 位存储偏移量。这个页对应的页框的地址为 （110 000000000100）。

<div align="center"> <img src="https://cs-notes-1256109796.cos.ap-guangzhou.myqcloud.com/cf4386a1-58c9-4eca-a17f-e12b1e9770eb.png" width="500"/> </div><br>



## 页面置换算法

在程序运行过程中，如果要访问的页面不在内存中，就发生缺页中断从而将该页调入内存中。此时如果内存已无空闲空间，系统必须从内存中调出一个页面到磁盘对换区中来腾出空间。

页面置换算法和缓存淘汰策略类似，可以将内存看成磁盘的缓存。在缓存系统中，缓存的大小有限，当有新的缓存到达时，需要淘汰一部分已经存在的缓存，这样才有空间存放新的缓存数据。

页面置换算法的主要目标是使页面置换频率最低（也可以说缺页率最低）。

### 1. 最佳

> OPT, Optimal replacement algorithm

所选择的被换出的页面将是最长时间内不再被访问，通常可以保证获得最低的缺页率。

是一种理论上的算法，因为无法知道一个页面多长时间不再被访问。

举例：一个系统为某进程分配了三个物理块，并有如下页面引用序列：

```html
7，0，1，2，0，3，0，4，2，3，0，3，2，1，2，0，1，7，0，1
```

开始运行时，先将 7, 0, 1 三个页面装入内存。当进程要访问页面 2 时，产生缺页中断，会将页面 7 换出，因为页面 7 再次被访问的时间最长。

### 2. 最近最久未使用

> LRU, Least Recently Used

虽然无法知道将来要使用的页面情况，但是可以知道过去使用页面的情况。LRU 将最近最久未使用的页面换出。

为了实现 LRU，需要在内存中维护一个所有页面的链表。当一个页面被访问时，将这个页面移到链表表头。这样就能保证链表表尾的页面是最近最久未访问的。

因为每次访问都需要更新链表，因此这种方式实现的 LRU 代价很高。

```html
4，7，0，7，1，0，1，2，1，2，6
```

<div align="center"> <img src="https://cs-notes-1256109796.cos.ap-guangzhou.myqcloud.com/eb859228-c0f2-4bce-910d-d9f76929352b.png"/> </div><br>
### 3. 最近未使用

> NRU, Not Recently Used

每个页面都有两个状态位：R 与 M，当页面被访问时设置页面的 R=1，当页面被修改时设置 M=1。其中 R 位会定时被清零。可以将页面分成以下四类：

- R=0，M=0
- R=0，M=1
- R=1，M=0
- R=1，M=1

当发生缺页中断时，NRU 算法随机地从类编号最小的非空类中挑选一个页面将它换出。

NRU 优先换出已经被修改的脏页面（R=0，M=1），而不是被频繁使用的干净页面（R=1，M=0）。

### 4. 先进先出

> FIFO, First In First Out

选择换出的页面是最先进入的页面。

该算法会将那些经常被访问的页面换出，导致缺页率升高。

### 5. 第二次机会算法

FIFO 算法可能会把经常使用的页面置换出去，为了避免这一问题，对该算法做一个简单的修改：

当页面被访问 (读或写) 时设置该页面的 R 位为 1。需要替换的时候，检查最老页面的 R 位。如果 R 位是 0，那么这个页面既老又没有被使用，可以立刻置换掉；如果是 1，就将 R 位清 0，并把该页面放到链表的尾端，修改它的装入时间使它就像刚装入的一样，然后继续从链表的头部开始搜索。

<div align="center"> <img src="https://cs-notes-1256109796.cos.ap-guangzhou.myqcloud.com/ecf8ad5d-5403-48b9-b6e7-f2e20ffe8fca.png"/> </div><br>

### 6. 时钟

> Clock

第二次机会算法需要在链表中移动页面，降低了效率。时钟算法使用环形链表将页面连接起来，再使用一个指针指向最老的页面。

<div align="center"> <img src="https://cs-notes-1256109796.cos.ap-guangzhou.myqcloud.com/5f5ef0b6-98ea-497c-a007-f6c55288eab1.png"/> </div><br>



## 本例中实现的算法及对比

在随机生成的页面访问序列为以下序列的情况下

```bash
60, 60, 0, 3, 61, 1, 63, 60, 2, 62, 2, 63, 2, 60, 2, 2, 0, 62, 62, 63, 61, 1, 61, 61, 61, 61, 63, 62, 63, 61, 61, 61, 63, 2, 62, 2, 4, 2, 0, 0, 62, 63, 5, 5, 3, 4, 63, 5, 0, 6, 6, 5, 6, 5, 1, 1, 6, 1, 5, 6, 2, 3, 0, 4
```

### 1. OPT

#### 实现方式

```cpp
void OPT(int n)
{
  int i = 0, j = 0;

  if (!isInMemo(n)) //不在
  {

    if (index == block)
    {
      lost++;
      int max = 0, pos, tag; // max最久不用；换掉第pos

      for (i = 0; i < block; i++) //一块块算
      {
        tag = -1;

        for (j = n + 1; j < V; j++) //算出下一次使用位置tag
        {
          if (access[j] == memo[i])
          {
            tag = j;
            break;
          }
        }

        if (tag == -1) //之后不再使用
        {
          max = V;
          pos = i;
          break;
        }

        if (max < tag)
        {
          max = tag;
          pos = i;
        }
      }

      memo[pos] = access[n];
    }

    else //预存
    {
      memo[index] = access[n];
      index++;
    }
  }
}
```

#### 结果

```bash
最佳置换算法缺页率：0.390625，缺页：25，耗时：214.000000
```



### 2. LRU

#### 实现方式

```cpp
void LRU(int n)
{
  int i, j;

  if (!isInMemo(n))

    if (index == block)
    {
      lost++;
      int max = n, pos = -1, tag; // max最久

      for (i = 0; i < block; i++)
      {
        for (j = n - 1; j >= 0; j--)
        {
          if (access[j] == memo[i])
          {
            tag = j;
            break;
          }
        }

        if (tag < max)
        {
          max = tag;
          pos = i;

          if (max == 0)
          {
            break; //最久
          }
        }
      }

      memo[pos] = access[n];
    }

    else
    {
      memo[index] = access[n];
      index++;
    }
}
```

#### 结果

```bash
最近最久未使用缺页率：0.500000，缺页：32，耗时：136.000000
```



### 3.FIFO

#### 实现方式

```cpp
void fifo(pQueue q, int num)
{
  if (!findInQueue(q, num))
  {
    if (q->n == block) //满了
    {
      pop(q);
      push(q, num);
      lost++;
    }

    else
    {
      push(q, num);
    }
  }
}
```

#### 结果

```bash
先进先出算法缺页率：0.546875 ,缺页：35，耗时：240.000000
```



### 4.CLOCK

#### 实现方式

```cpp
void updated_Clock(int n)
{
  if (!isInNodes(n))
    if (index == block) //满了
    {
      lost++;
      int i = 0, tag = -1; // tag要换掉的

      while (true)
      {
        if ((i / block) % 2 == 0) //第一遍
        {
          if (nodes[i % block].flag == 0 && nodes[i % block].modify == 0)
          {
            tag = i % block; //记录
            break;
          }
        }

        if ((i / block) % 2 == 1) //第二遍
        {
          if (nodes[i % block].flag == 0 && nodes[i % block].modify == 1)
          {
            tag = i % block;
            break;
          }

          else
          {
            nodes[i % block].flag = 0; //将经过的所有页面访问位置0
          }
        }

        i++;
      }

      nodes[tag].data = access[n];
      nodes[tag].flag = 1;

      if (rand() % 10 < 4) //随机修改该页
        nodes[tag].modify = 1;
      else
        nodes[tag].modify = 0;
    }

    else //预装
    {
      nodes[index].data = access[n];
      nodes[index].flag = 1;

      if (rand() % 10 < 4) //随机修改该页
        nodes[index].modify = 1;
      else
        nodes[index].modify = 0;

      index++;
    }
}
```

#### 结果

```bash
改进型Clock置换算法缺页率： 0.500000，缺页： 32，耗时：216.000000
```



### 5. PBA

#### 实现方式

```cpp
void PBA(pQueue q, int num)
{
  Node *p;
  if (!findInQueue(q, num))
  {
    if (q->n == block) //满了
    {
      if ((p = isinLinks(num)) != NULL) //在链表
      {
        pop(q);
        push(q, p->num);
      }
      else //不在
      {
        lost++;
        if (q->front->modify == 1)
          addToLink(num, 1);
        else
          addToLink(num, 0);
        pop(q);
        push(q, num);
      }
    }

    else
    {
      push(q, num);
    }
  }
}
```

#### 结果

```bash
页面缓冲算法缺页率：0.312500 ,缺页：20，耗时：242.000000
```

