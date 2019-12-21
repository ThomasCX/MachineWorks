#include <iostream>
#include <cstdio>
#include <string>
#include <algorithm>
using namespace std;
//����һ��long long ����
typedef long long LL;
//����ƽ�������<x,y>����
typedef pair<int,LL> PR;
//����һ������MAXN
const int MAXN = 100005;
#define INF 0x3f3f3f3f

//����һ��������
typedef struct node
{
	LL D;	//��������������
	LL P;	//���������ļ۸�
	LL R;	//�����������ۿۼ�
	LL G;	//����ÿ�յ�����
	//��<�����ع�
	bool operator < (const node& oth)
	{
		return D < oth.D;
	}
}node;

node M[MAXN];
//����ƽ������<x,y>�㼯
PR sets[MAXN];
//ÿ���ؼ���ʱ����������
LL F[MAXN];
//����һ�����д����͹�ǵ㼯
LL q[MAXN],head,tail;
//��������Ļ���������̨������˾�˻���ʼ��ת��������
LL n,c,d;

//��б��ʽ�е�y��ֵ�� 
LL cal_y(int j)
{
	return F[j]-(M[j].D+1)*M[j].G-M[j].P+M[j].R;
}

//��j,i���в���k�㣬����kj>ki��������͹�ǵ㼯��
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
	//l+r��ֵ����1λ���൱l+r��ֵ����2ȡ��;
	int mid = (l+r)>>1;
	Cdq(l,mid);
	int m=0;
	head=tail=0;
	//�������
	for(int i=l;i<=mid;i++) 
	{
		//��ǰ���ڣ����㹻��Ǯ�������
		if(F[i]>=M[i].P) 
			sets[m++]=PR(M[i].G,cal_y(i));
	}
	//������������
	sort(sets, sets+m);  
	for(int i=0;i<m;i++)   
	{
		//����������Թ���ĵ��������У�������͹��
		while(head+1<tail&&!insert(q[tail-2],q[tail-1],i))tail--;
		q[tail++]=i;
	}

	for(int i=mid+1;i<=r;i++)  
	{
		//���������ѯ������
		while(head+1<tail&&sets[q[head+1]].second-sets[q[head]].second>M[i].D*(sets[q[head]].first-sets[q[head+1]].first))
			head++;
		F[i]=max(sets[q[head]].second+M[i].D * sets[q[head]].first,F[i]);
	}
	Cdq(mid+1,r);
}

int main()
{
	int count=0;
	//����N��C��D��Ϣ
	while(scanf("%lld%lld%lld",&n,&c,&d),n+c+d)
	{
		count++;
		//����ÿ̨��������ϢD��P��R��G
		for(int i=1;i<=n;i++)
		{
			scanf("%lld%lld%lld%lld",&M[i].D,&M[i].P,&M[i].R,&M[i].G);
		}
		//���һ�����
		n++;
		M[n].D=d+1;
		M[n].P=M[n].G=M[n].R=0;
		//�����������л�������ʱ������
		sort(M+1,M+1+n);
		for(int i=0;i<=n;i++) F[i]=c;
		Cdq(0,n);
		printf("Case %d: %lld\n",count,F[n]);
	}
	return 0;
}
