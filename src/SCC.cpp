int dfs(int n)
{
	vis[n]=++curr;
	s.push(n);
	int result=vis[n];
	for(int e=0;e<arr[n].size();e++)
	{
		int next=arr[n][e];
		if(vis[next]==0) result=min(result,dfs(next));
		else if(finished[next]==0) result=min(result,vis[next]); 
	}
	if(result==vis[n])
	{
		vector<int> kk;
		while(1)
		{
			int now=s.top();s.pop();
			finished[now]=1;
			sn[now]=SN;
			kk.push_back(now);
			if(now==n) break;
		}
		SN++;
		sort(kk.begin(),kk.end());
		scc.push_back(kk);
	}
	return result;
}
메인에서
for(int e=1;e<=n;e++) if(vis[e]==0) dfs(e);


