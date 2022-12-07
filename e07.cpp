#include <iostream>
#include <vector>

using namespace std;

int n=0;
vector<int> D;

int reduction(int i, int j, vector<vector<int>> &Q)
{
	if(Q[i][j]!=-1)
	{
		return Q[i][j];
	}

	if(j==i+1)
	{
		// cerr<<"i: "<<i<<" j: "<<j<<" min_cost: "<<0<<endl;
		Q[i][j]=0;
		return 0;
	}

	int min_cost=reduction(i, i+1, Q)+reduction(i+1, j, Q)+(D[i]*D[i+1]*D[j]);
	for(int k=i+2; k<j; k++)
	{
		int x=reduction(i, k, Q)+reduction(k, j, Q)+(D[i]*D[k]*D[j]);
		if(x<min_cost)
		{
			min_cost=x;
		}
	}

	// cerr<<"i: "<<i<<" j: "<<j<<" min_cost: "<<min_cost<<endl;
	Q[i][j]=min_cost;
	return min_cost;
}


void solve()
{
	vector<vector<int>> Q;
	for(int i=0; i<=n; i++)
	{
		vector<int> v;
		for(int j=0; j<=n; j++)
		{
			v.push_back(-1);
		}
		Q.push_back(v);
	}

	int out=reduction(0, n, Q);
	cout<<out<<endl;
}

void read()
{
	cin>>n;
	for(int i=0; i<n; i++)
	{
		int h, h2;
		cin>>h>>h2;
		D.push_back(h);
		if(i==n-1)
		{
			D.push_back(h2);
		}
	}
}

int main()
{
	int z; cin>>z;
	while(z--)
	{
		read();
		solve();
		D.clear();
	}
}
