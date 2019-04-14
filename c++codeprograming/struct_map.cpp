//
// Created by wuyongyu on 2019/4/14.
//

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

struct Node{
    int x;
    int y;
    Node(int a,int b):x(a),y(b){}

    friend bool operator < (const struct Node &ls, const struct Node &rs);

    friend bool operator > (const struct Node &ls, const struct Node &rs);
    friend bool operator == (const struct Node &ls, const struct Node &rs);
};
inline bool operator < (const struct Node &ls, const struct Node &rs)
{
    return (ls.x < rs.x || (ls.x == rs.x && ls.y < rs.y));
}

inline bool operator > (const struct Node &ls, const struct Node &rs)
{
    return (ls.x > rs.x || (ls.x == rs.x && ls.y > rs.y));
}

inline bool operator == (const struct Node &ls, const struct Node &rs)
{
    return (ls.x == rs.x  && ls.y == rs.y);
}

int get_max(vector<int>  nums){
    int max=1;

    for(int i=0;i<nums.size();i++){
        int begin=nums[i];
        int len=1;
        for(int j=i+1;j<nums.size();j++){
            if(++begin==nums[j]){
                len++;
                if(len>max){
                    max=len;
                }

            }else{
                i=j-len;
                break;
            }
        }
    }

    return max;
}
int main(){

    map<Node,vector<int>> key_index;
    return 0;
}
