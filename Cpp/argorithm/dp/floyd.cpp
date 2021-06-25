#include <iostream>

#include <iomanip> //控制格式
#include <string>

#define INF 0x3f3f3f3f //定义无穷大
using namespace std;

#define vertexNum 5                          //源点数
int G[vertexNum][vertexNum];                 //邻接矩阵
string vertex[] = {"A", "B", "C", "D", "E"}; //源点字符串组
void CreateMGraph()
{
        for (int i = 0; i < vertexNum; i++)
        for (int j = 0; j < vertexNum; j++)
   
    {
                if (i == j) G[i][j] = 0;
                else G[i][j] = INF;
           
    }
        G[0][1] = 13;
    G[0][3] = 4;
        G[1][0] = 13;
    G[1][2] = 15;
    G[1][4] = 5;
        G[2][3] = 12;
        G[3][0] = 4;
    G[3][2] = 12;
        G[4][2] = 6;
    G[4][3] = 3;
}
void Floyd()
{
        int dist[vertexNum][vertexNum], i, k, j; //dist为权值存储数组
        string path[vertexNum][vertexNum];
        //cout<<"初始权值数组和路径字符串数组:"<<endl;
    for (i = 0; i < vertexNum; i++)
        for (j = 0; j < vertexNum; j++)
   
    {
                dist[i][j] = G[i][j];
                path[i][j] = vertex[i] + "-->" + vertex[j];
              /*  cout<<path[i][j]<<" ";
        if(dist[i][j]!=INF) cout<<dist[i][j]<<endl;
        else cout<<"∞"<<endl;*/
   
    }
        for (k = 0; k < vertexNum; k++)
         for (i = 0; i < vertexNum; i++)
          for (j = 0; j < vertexNum; j++)
   
    {
                if ((dist[i][k] + dist[k][j] < dist[i][j]) && (dist[i][k] != INF) && (dist[k][j] != INF) && (i != j))
       
        {
                        dist[i][j] = dist[i][k] + dist[k][j];
                        path[i][j] = path[i][k] + "-->" + vertex[j];
                   
        }
           
    }
       for (i = 0; i < vertexNum; i++)
   
    {
               cout << "顶点" << vertex[i] << "到各顶点的最短路径及权值和" << endl;
                  for (j = 0; j < vertexNum; j++)
         
        {
                          cout << path[i][j] << " ";
                          if (dist[i][j] != INF) cout << dist[i][j] << endl;
                          else cout << "∞" << endl;
                     
        }
           
    }
}

int main()
{
        CreateMGraph(); //创建邻接矩阵
        cout << "打印邻接矩阵：" << endl;
         for (int i = 0; i < vertexNum; i++)
        for (int j = 0; j < vertexNum; j++)
   
    {
                if (G[i][j] == INF) cout << setw(4) << "∞";
                else cout << setw(4) << G[i][j];
                if (j == vertexNum - 1) cout << endl;
           
    }
        Floyd();
        return 0;
}
