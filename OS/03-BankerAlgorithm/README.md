# 银行家算法

编写一个模拟程序，循环检查每一个提出请求的银行客户，并能判断此请求是否安全。
把有关请求和相应决定的列表输出到一个文件中。



## 算法流程
- 检查此次申请是否超过了之前声明的最大需求
- 检查剩余资源是否可满足此次请求
- 试探分配
- 安全性检查



## 算法介绍
　　银行家算法（Banker’s Algorithm）是一个避免死锁（Deadlock）的著名算法，是由艾兹格·迪杰斯特拉在1965年为T.H.E系统设计的一种避免死锁产生的算法。它以银行借贷系统的分配策略为基础，判断并保证系统的安全运行。
　　在银行中，客户申请贷款的数量是有限的，每个客户在第一次申请贷款时要声明完成该项目所需的最大资金量，在满足所有贷款要求时，客户应及时归还。银行家在客户申请的贷款数量不超过自己拥有的最大值时，都应尽量满足客户的需要。在这样的描述中，银行家就好比操作系统，资金就是资源，客户就相当于要申请资源的进程。
　　银行家算法是一种最有代表性的避免死锁的算法。在避免死锁方法中允许进程动态地申请资源，但系统在进行资源分配之前，应先计算此次分配资源的安全性，若分配不会导致系统进入不安全状态，则分配，否则等待。为实现银行家算法，系统必须设置若干数据结构。
　　
银行家算法中的数据结构
　　为了实现银行家算法，在系统中必须设置这样四个数据结构，分别用来描述系统中可利用的资源、所有进程对资源的最大需求、系统中的资源分配，以及所有进程还需要多少资源的情况。
　　(1) 可利用资源向量 Available。这是一个含有 m 个元素的数组，其中的每一个元素代表一类可利用的资源数目，其初始值是系统中所配置的该类全部可用资源的数目，其数值随该类资源的分配和回收而动态地改变。如果 Available[j] = K，则表示系统中现Rj类资源K个。
　　(2) 最大需求矩阵Max。这是一个n x m的矩阵，它定义了系统中n个进程中的每个进程对m类资源的最大需求。如果Max[i,j] = K，则表示进程i需要Rj 类资源的最大数目为K。
　　(3) 分配矩阵 Allocation。这也是一个n x m的矩阵，它定义了系统中每一类资源当前已分配给每一进程的资源数。如果 Allocation[i,jl = K，则表示进程i当前己分得Rj类资源的数目为K。
　　(4) 需求矩阵Need.这也是一个n×m的矩阵，用以表示每一个进程尚需的各类资源数。如果Need[i,j] = K，则表示进程i还需要Rj类资源K个方能完成其任务。
上述三个矩阵间存在下述关系:
　　　　　　　　　　　　　　Need[i,j] = Max[i,j] - allocation[i, j]
　　　　　　　　　　　　　　
银行家算法详述：
　　设 Request；是进程Pi的请求向量，如果 Requesti[j] = K，表示进程Pi需要K个Rj类型的资源。当Pi发出资源请求后，系统按下述步骤进行检査:
　　(1) 如果 Requesti[j] ≤ Need[i,j]便转向步骤(2)；否则认为出错，因为它所需要的资源数已超过它所宣布的最大值。
　　(2) 如果 Requesti[j] ≤ Available[j]，便转向步骤(3)；否则，表示尚无足够资源，Pi须等待。
　　(3) 系统试探着把资源分配给进程Pi，并修改下面数据结构中的数值
　　　　Available[j] = Available[j] - Requesti[j];
　　　　Allocation[i,j] = Allocation[i,j] + Requesti[j];
　　　　Need[i,j] = Need[i,j] - Requesti[j];
　　(4) 系统执行安全性算法，检查此次资源分配后系统是否处于安全状态。若安全，才正式将资源分配给进程Pi，以完成本次分配；否则，将本次的试探分配作废，恢复原来的资源分配状态，让进程Pi等待。
　　
安全性算法:
系统所执行的安全性算法可描述如下:
　　(1) 设置两个向量:①工作向量Work，它表示系统可提供给进程继续运行所需的各类资源数目，它含有m个元素，在执行安全算法开始时，Work = Available；② Finish:它表示系统是否有足够的资源分配给进程，使之运行完成。开始时先做 Finish[i] = false；当有足够资源分配给进程时，再令Finish[i] = true。
　　(2) 从进程集合中找到一个能满足下述条件的进程
　　　　① Finish[i] = false;
　　　　② Need[i,j] ≤ Work[j];
若找到，执行步骤(3)，否则，执行步骤(4)。
　　(3)当进程Pi获得资源后，可顺利执行，直至完成，并释放出分配给它的资源，故应执行:
　　　　Work[j] = Work[j] + Allocation[i,j];
　　　　Finish[i] = true;
　　　　go to step 2;(goto语句不推荐使用 _ )
　　(4)如果所有进程的 Finish[i] =true都满足，则表示系统处于安全状态；否则，系统处于不安全状态。
　　
难点透析：
　　本程序的难点在于安全性算法，对于一个安全的系统来说，此步骤较为容易，难在于判断不安全的系统。为什么这么说呢？由于本程序再设计寻找安全序列的部分使用while循环，就需要找到分别处理安全系统与不安全系统的终止循环条件，对于安全的系统，满足条件 Finish[i] = false 和 Need[i,j] ≤ Work[j] 的，必定也会按照预期的将 Finish[i] 向量全部置为true，那是不是就可以设置一个变量来累加计数，当该变量与进程数量相等的时候，就说明已经全部置为true了，终止循环，也就是说系统安全。
　　对于不安全的系统，上述方法肯定是不行的，因为不可能将向量 Finish[i] 都置为 true ，必定存在 false。就得寻求一个跳出循环的条件，但是由于需要不断循环查找并尝试分配，寻求一个安全序列，到底该怎么算是已经找不到安全路径了呢？下面说本程序的解决办法，首先需要想到的是，当我们寻找一轮都没有找到一个可以安全执行的进程，是不是就说明往后也找不到了呢？没错，就是这样的！所以我们每次在记录 Finish[i] = true 的次数的时候，不妨把这个次数再使用另一个变量存放起来，然后在判断语句当中判断当寻找一轮下来，该值未发生改变，说明已经找不到安全的进程了，即可跳出循环，该系统不安全



## 参考资料
- [操作系统-Bilibili](https://www.bilibili.com/video/BV1YE411D7nH?p=31)
- [银行家算法-CSDN](https://blog.csdn.net/qq_36260974/article/details/84404369)