#include<cstdio>
#include<cmath>
#include<algorithm>
using namespace std;
#define MY_MAX(a,b) (a)>(b)?(a):(b)
const int maxN = 20;

/**
 * @brief The NOTE struct
 * pruning algorithm -- test only
 *
 */
struct NOTE
{
    long long weight;
    long long value;
    int num;
}box[maxN];
int n;// 个数小于20
long long m,ans;// m 总重量,ans最优解
long long sum[maxN];      //保存一个后缀和
bool cmp(const struct NOTE &a, const struct NOTE &b)
{//按性价比排序,从大到小排列（注意若有取地址符号，则需有const）
    return a.value*1.0/a.weight > b.value*1.0/b.weight;
}
inline bool cut (int pos,long long now_value,long long last_weight)
{
    if(pos == n+1) return true;//边界返回条件
    if(now_value+sum[pos] < ans) return true;////如果后面所有的钻石加起来都<=ans，剪掉
    double best = (box[pos].value*1.0/box[pos].weight);//当前最大的性价比
    if(now_value+(long long)ceil(best*last_weight) < ans) return true;//以这个性价比取剩下的所有重量，如果<=ans,剪掉
    return false;
}
void dfs(int pos,long long now_value,long long last_weight) //pos 当前数组的下标位置，now_value 目前的重量和，last_weight当前背包剩余容量
{
    ans = MY_MAX(ans,now_value);
    if(cut(pos,now_value,last_weight))  return;//剪枝函数
    for(int i=box[pos].num;i>=0;--i)//(暴力搜索)枚举顺序从满到空枚举，这样才能最快找到ans，然后利用ans剪枝
    {
        if(last_weight<box[pos].weight*i)   continue;
        dfs(pos+1,now_value+box[pos].value*i,last_weight-box[pos].weight*i);
    }
}
// didn't use
int main()
{
    int cas;
    long long sumv,sumw;// 价值和重量的和；仅仅用到了一次（特殊情况才用到，能够一次全带走）
    scanf("%d",&cas);
    while(cas--)
    {
        ans=0;
        sumv=sumw=0;
        scanf("%d%lld",&n,&m);
        for(int i=1;i<=n;i++)
        {
            scanf("%lld",&box[i].weight);
            sumw+=box[i].weight*i;
        }
        for(int i=1;i<=n;i++)
        {
            scanf("%lld",&box[i].value);
            box[i].num=i;
            sumv+=box[i].value*i;
        }
        // 以上是数据的输入，下面才是刚刚开始的
        // 如果sumv开始就比m总重量还小，直接输出
        if(sumw<=m)
        {
            printf("%lld\n",sumv);
            continue;
        }
        sort(box+1,box+1+n,cmp);// 从1开始计数的
        sum[n+1]=0; // 倒着开始的
        for(int i=n;i>=1;i--)
        {
         //计算后缀和
            sum[i]=sum[i+1]+box[i].value*box[i].num;
        }
        dfs(1,0,m);
        printf("%lld\n",ans);
    }
    return 0;
}
