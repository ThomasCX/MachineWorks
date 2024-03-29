#include <iostream>
#include <cstdio>
#include <string>
#include <algorithm>
using namespace std;
//定义一个long long 类型
typedef long long LL;
//定义平面坐标点<x,y>类型
typedef pair<int,LL> PR;
//定义一个常量MAXN
const int MAXN = 100005;
#define INF 0x3f3f3f3f

//定义一个新类型
typedef struct node
{
	LL D;	//卖出机器的日期
	LL P;	//卖出机器的价格
	LL R;	//卖出机器的折扣价
	LL G;	//机器每日的利润
	//对<进行重构
	bool operator < (const node& oth)
	{
		return D < oth.D;
	}
}node;

node M[MAXN];
//定义平面坐标<x,y>点集
PR sets[MAXN];
//每个关键点时间的最大收益
LL F[MAXN];
//定义一个队列存放上凸壳点集
LL q[MAXN],head,tail;
//定义输入的机器卖出总台数、公司账户开始余额、转型总天数
LL n,c,d;

//求斜截式中的y的值； 
LL cal_y(int j)
{
	return F[j]-(M[j].D+1)*M[j].G-M[j].P+M[j].R;
}

//在j,i点中插入k点，满足kj>ki，构成上凸壳点集；
int insert(int k,int j,int i)   
{
	LL x1=sets[j].first-sets[k].first;
	LL x2=sets[i].first-sets[k].first;
	LL y1=sets[j].second-sets[k].second;
	LL y2=sets[i].second-sets[k].second;
	double Temp=(double)x1*y2-(double)x2*y1;
	return Temp<0;
}

void Cdq(int l,int r)
{
	if(l>=r) return;
	//l+r的值右移1位，相当l+r的值除以2取整;
	int mid = (l+r)>>1;
	Cdq(l,mid);
	int m=0;
	head=tail=0;
	//左半区间
	for(int i=l;i<=mid;i++) 
	{
		//当前日期，有足够金钱购买机器
		if(F[i]>=M[i].P) 
			sets[m++]=PR(M[i].G,cal_y(i));
	}
	//按横坐标排序
	sort(sets, sets+m);  
	for(int i=0;i<m;i++)   
	{
		//将左区间可以购买的点插入队列中，满足上凸型
		while(head+1<tail&&!insert(q[tail-2],q[tail-1],i))tail--;
		q[tail++]=i;
	}

	for(int i=mid+1;i<=r;i++)  
	{
		//对右区间查询并更新
		while(head+1<tail&&sets[q[head+1]].second-sets[q[head]].second>M[i].D*(sets[q[head]].first-sets[q[head+1]].first))
			head++;
		F[i]=max(sets[q[head]].second+M[i].D * sets[q[head]].first,F[i]);
	}
	Cdq(mid+1,r);
}

int main()
{
	int count=0;
	//输入N、C、D信息
	while(scanf("%lld%lld%lld",&n,&c,&d),n+c+d)
	{
		count++;
		//输入每台机器的信息D、P、R、G
		for(int i=1;i<=n;i++)
		{
			scanf("%lld%lld%lld%lld",&M[i].D,&M[i].P,&M[i].R,&M[i].G);
		}
		//最后一天情况
		n++;
		M[n].D=d+1;
		M[n].P=M[n].G=M[n].R=0;
		//对卖出的所有机器按照时间排序
		sort(M+1,M+1+n);
		for(int i=0;i<=n;i++) F[i]=c;
		Cdq(0,n);
		printf("Case %d: %lld\n",count,F[n]);
	}
	return 0;
}
