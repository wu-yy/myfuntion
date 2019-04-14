#include <deque>
#include <iostream>
#include <cmath>
#include <fstream>
#include <algorithm>
#include<iostream>
#include<cstring>
#include<map>
#include <vector>
#include <set>
#include <algorithm>
#include<limits.h>
#include<stack>
#include <queue>
#include <string>
#include <cstring>
#include <cstdio>
#include <cstdlib>
using namespace std;

class Solution {
private:
    /**
    *	distance 为该结构体的二维矩阵
    *	用于保存每个子问题的最短路径以及依赖的前一个子问题在distance 矩阵中的坐标
    */
    struct distanceEle {
        int minVal;
        int prei;
        int prej;

        distanceEle() :minVal(0), prei(0), prej(0) {}
    };


    /**
    *	seq 当前的序列
    *	visited 标识当前访问过的元素
    *	depth 当前的深度 从0开始
    *	n 最大的深度
    */
    void getSubsets(deque<int> &seq,bool *visited,int depth,int n) {
        if (depth == 0) {
            subsets.push_back(deque<int>());	//加入空集合
            getSubsets(seq, visited, depth + 1, n);
        }
        else if (depth >= n) {
            //已经达到了最大的深度
            return;
        }
        else {
            for (int i = 1; i < n; ++i) {
                //判断是否访问过，比较大小，防止出现顺序不同但集合元素相同的情况
                if (!visited[i]) {
                    if (!seq.empty() && i < seq.back())
                        continue;
                    visited[i] = true;
                    seq.push_back(i);
                    subsets.push_back(*new deque<int>(seq));	//保存当前的序列
                    getSubsets(seq, visited, depth + 1, n);
                    visited[i] = false;
                    seq.pop_back();
                }
            }
        }
    }

    static bool cmp(const deque<int> &obj1, const deque<int> &obj2) {
        if (obj1.size() < obj2.size())
            return true;
        else
            return false;
    }

    /**
    *	用于求出某个集合关于总的集合的补集
    */
    deque<int> getsupplementSet(deque<int> &fullSet, deque<int> &subset) {
        //首先对集合排序
        sort(fullSet.begin(), fullSet.end());
        sort(subset.begin(), subset.end());

        deque<int>::iterator iterFull = fullSet.begin(), iterSub = subset.begin();
        deque<int> result;

        while (iterSub != subset.end()) {
            if (*iterFull < *iterSub) {
                result.push_back(*iterFull);
                ++iterFull;
            }
            else {
                ++iterFull, ++iterSub;
            }
        }

        while (iterFull != fullSet.end()) {
            result.push_back(*iterFull);
            ++iterFull;
        }

        return result;
    }


    /**
    *	在subsets 中定位subset 的坐标
    */
    int locateSubsetIndex(deque<int> subset) {
        bool flag = true;
        for (int i = 0; i < subsets.size(); ++i) {
            if (subset.size() != subsets[i].size())
                continue;
            flag = true;
            for (int j = 0; j < subsets[i].size(); ++j) {
                if (subsets[i][j] != subset[j])
                    flag = false;
            }
            if (flag == true)
                return i;
        }
        return -1;
    }

    /**
    *	依次解决子问题
    */
    void dynamicProgram(int n,deque<int> fullset) {
        deque<int> supplementSet;
        for (int i = 1; i < subsets.size(); ++i) {
            supplementSet = getsupplementSet(fullset, subsets[i]);	//获取当前子集的补集

            for (auto ele : supplementSet) {		//对补集中的每一个元素进行操作
                int tmp;
                deque<int> tmpSet;
                distance[ele][locateSubsetIndex(subsets[i])].minVal = INT_MAX;	//先初始化一个大的值

                for (int j = 0; j < subsets[i].size(); ++j) {
                    tmpSet = deque<int>(subsets[i]);
                    tmp = tmpSet[j];
                    tmpSet.erase(tmpSet.begin() + j);
                    //记录基于前面的子问题的最短路径
                    if (arc[ele][tmp] + distance[tmp][locateSubsetIndex(tmpSet)].minVal < distance[ele][locateSubsetIndex(subsets[i])].minVal) {
                        distance[ele][locateSubsetIndex(subsets[i])].minVal = arc[ele][tmp] + distance[tmp][locateSubsetIndex(tmpSet)].minVal;
                        distance[ele][locateSubsetIndex(subsets[i])].prei = tmp;
                        distance[ele][locateSubsetIndex(subsets[i])].prej = locateSubsetIndex(tmpSet);
                    }
                }
            }
        }
    }

    /**
    *	处理动态规划的最后一个阶段
    *	distanceColNum 表示distance 的列的个数
    */
    void endProgram(deque<int> fullSet,int distanceColNum) {
        int tmp;
        deque<int> tmpSet;

        distance[0][distanceColNum - 1].minVal = INT_MAX;
        for (int i = 0; i < fullSet.size(); ++i) {
            tmpSet = deque<int>(fullSet);
            tmp = tmpSet[i];
            tmpSet.erase(tmpSet.begin() + i);
            if (arc[0][tmp] + distance[tmp][locateSubsetIndex(tmpSet)].minVal < distance[0][distanceColNum - 1].minVal) {
                distance[0][distanceColNum - 1].minVal = arc[0][tmp] + distance[tmp][locateSubsetIndex(tmpSet)].minVal;
                distance[0][distanceColNum - 1].prei = tmp;
                distance[0][distanceColNum - 1].prej = locateSubsetIndex(tmpSet);
            }
        }
    }


public:
    deque<deque<int>> subsets;	//所有的子集的集合
    int **arc;	//带权的矩阵
    distanceEle **distance;	//动态规划中的填表
    vector<vector<int>> myacc;

    void findShortest() {
        int n;
        cin>>n;
//        ifstream infile("input.txt");
//        int n = 0;
//        infile >> n;
        bool *visited = new bool[n];
        for (int i = 0; i < n; ++i)
            visited[i] = false;
        deque<int> seq;
        getSubsets(seq, visited, 0, n);
        sort(subsets.begin(), subsets.end(), &Solution::cmp);	//对子集进行排序

        //读取带权图的矩阵
        int tmp = 0;
        arc = new int*[n];
        for (int i = 0; i < n; ++i) {
            arc[i] = new int[n];
            vector<int>tt1;
            for (int j = 0; j < n; ++j) {
                cin>> tmp;
                tt1.push_back(tmp);
                if (tmp == -1)
                    tmp = INT_MAX;
                arc[i][j] = tmp;
            }

            myacc.push_back(tt1);
        }
//        infile.close();

        //测试

//        cout << "遍历arc :" << endl;
//        for (int i = 0; i < n; ++i) {
//            for (int j = 0; j < n; ++j) {
//                cout << arc[i][j] << "  ";
//            }
//            cout << endl;
//        }

//        cout << "遍历子集：" << endl;
//        for (int i = 0; i < subsets.size(); ++i) {
//            for (auto ele : subsets[i])
//                cout << ele << "  ";
//            cout << endl;
//        }
        deque<int> fullSet;
        for (int i = 1; i < n; ++i)
            fullSet.push_back(i);
        //求取各个子集的补集
//        cout << "对应的补集为：" << endl;
//        for (int j = 0; j < subsets.size(); ++j) {
//            for (auto ele : getsupplementSet(fullSet, subsets.at(j))) {
//                cout << ele << "  ";
//            }
//            cout << endl;
//        }
        ///
        //初始化distance
        distance = new distanceEle*[n];
        for (int i = 0; i < n; ++i) {
            distance[i] = new distanceEle[subsets.size()];
        }
        //初始化distance 第0列，1~n-1行
        for (int i = 1; i < n; ++i)
            distance[i][0].minVal = arc[i][0];
        //对求出来的各个子集，按照大小，从空集合开始动态规划
        dynamicProgram(n, fullSet);
        endProgram(fullSet, subsets.size());
        //测试输出distance
///        cout << "遍历distance :" << endl;
//        int hua=0;
//        for (int i = 0; i < n; ++i) {
//            for (int j = 0; j < subsets.size(); ++j) {
//                cout << "(" << distance[i][j].minVal << ", " << distance[i][j].prei << ", " << distance[i][j].prej
//                                                                            << ")   ";
//
//            }
//           cout << hua<<endl;
//        }

    }


    /**
    *	输出最短路径
    */
    void outputShortestPath(int distanceColNum) {
        int indexi = 0, indexj = distanceColNum - 1;
        int i, j;

        int hua=0;
        vector<int> begin_ec;
        while (indexj > 0) {
            begin_ec.push_back(indexi);
            i = distance[indexi][indexj].prei;
            j = distance[indexi][indexj].prej;
            indexi = i;
            indexj = j;
        }
        begin_ec.push_back(indexi);
        begin_ec.push_back(0);
        for(int k=0;k<begin_ec.size();k++){
            hua+=myacc[begin_ec[k]][begin_ec[k+1]];
        }
        cout<<hua;

    }


};

int main()
{
    Solution solution;
    solution.findShortest();
    solution.outputShortestPath(solution.subsets.size());
    return 0;
}
