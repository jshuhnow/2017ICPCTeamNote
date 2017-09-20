#define MX 1234567

vector<int> arr[MX];
int depth[MX],parent[MX][18]; // 2^18 should be larger than MX
void dfs(int n)
{
	for(int e=0;e<arr[n].size();e++)
	{
		int next=arr[n][e];
		if(depth[next]==-1)
		{
			depth[next]=depth[n]+1;
			parent[next][0]=n;
			dfs(next);
		}
	}
}
int main(void)
{
	memset(parent,-1,sizeof(parent));
	memset(depth,-1,sizeof(depth));
	int n;
	scanf("%d",&n);
	for(int e=0;e<n-1;e++)
	{
		int a,b;
		scanf("%d%d",&a,&b);
		arr[a].push_back(b);
		arr[b].push_back(a);
	}
	depth[1]=0;
	dfs(1);
	for(int e=0;e<17;e++)
	{
		for(int p=2;p<=n;p++)
		{
			if(parent[p][e]!=-1)
			{
				parent[p][e+1]=parent[parent[p][e]][e];
			}
		}
	}
	int m;
	scanf("%d",&m);
	for(int e=0;e<m;e++)
	{
		int a,b;
		scanf("%d%d",&a,&b);
		if(depth[a]<depth[b])
		{
			int tmp=a;
			a=b;
			b=tmp;
		}
		int diff=depth[a]-depth[b];
		for(int p=0;diff;p++)
		{
			if(diff%2) a=parent[a][p];
			diff/=2;
		}
		if(a!=b)
		{
			for(int p=17;p>=0;p--)
			{
				if(parent[a][p]!=-1&&parent[a][p]!=parent[b][p])
				{
					a=parent[a][p];
					b=parent[b][p];
				}
			}
			a=parent[a][0];
		}
		printf("%d\n",a);
	}
}
