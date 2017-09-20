#define MX 10001
int p[MX], rank[MX];
inline int find(short x){
	return p[x] == x ? x : p[x]=find(p[x]);
}
inline void unite(short x,short y){
	x=find(x), y=find(y);
	if( x == y ) return;

	if( rank[x] > rank[y] ) swap(x,y);
	p[x] = y;

	if(rank[x] == rank[y]) ++rank[y];
}
int main(){
	int V,s,e,i,u,v;
	int E,t,ans=0;

	scanf("%d %d",&V,&E);

	for (i=1;i<=V;++i) p[i] = i;
	vector<pair<int,pair<int, int> > > list;

 	for (i=0;i<E;++i){
 		scanf("%d %d %d",&s,&e,&w); //start, end, w
 		list.push_back(make_pair(w,make_pair(s,e)));
 	}

 	sort(list.begin(),list.end());

 	for (i=0;i<list.size();++i){
		u=list[i].second.first;
 		v=list[i].second.second;
		
		u=find(u);
		v=find(v);
		if (u!=v){
 			unite(u,v);
			ans += list[i].first;
		}
	}

 	printf("%d\n",ans);
 }
