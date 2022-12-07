#include <iostream>
#include <vector>
#include <algorithm>
#include <string>


using namespace std;

struct verteX{
	int c1=-1; //child 1
	int c2=-1; //child 2
	bool leaf=false;
};

int draw(int n, string structure, verteX tree[], int u)
{
	if(structure[u]=='0')
	{
		tree[u].leaf=true;
		return u+1;
	}

	if(structure[u]=='1')
	{
		tree[u].c1=u+1;
		return draw(n, structure, tree, u+1);
	}

	if(structure[u]=='2')
	{
		tree[u].c1=u+1;
		tree[u].c2=draw(n, structure, tree, u+1);
		return draw(n, structure, tree, tree[u].c2);
	}

}

int max_c(vector<vector<int>> &X, int n, string structure, verteX tree[], int u, bool color)
{
	int B=0;
	if(color)
	{
		B=1;
	}

	if(X[u][B]!=-1)
	{
		return X[u][B];
	}

	if(tree[u].leaf)
	{	
		if(color)
		{
			// cerr<<"uh ";
			X[u][B]=1;
			return 1;
		}
		else
		{
			// cerr<<"oh ";
			X[u][B]=0;
			return 0;
		}
	}

	if(structure[u]=='1')
	{
		if(color)
		{
			X[u][B]=1+max_c(X, n, structure, tree, tree[u].c1, false);
			return X[u][B];
		}
		else
		{
			X[u][B]=max(max_c(X, n, structure, tree, tree[u].c1, true), max_c(X, n, structure, tree, tree[u].c1, false));
			return X[u][B];
		}
	}

	if(structure[u]=='2')
	{
		if(color)
		{
			X[u][B]=1+max_c(X, n, structure, tree, tree[u].c1, false)+max_c(X, n, structure, tree, tree[u].c2, false);
			return X[u][B];
		}
		else
		{
			X[u][B]=max(max_c(X, n, structure, tree, tree[u].c1, true)+max_c(X, n, structure, tree, tree[u].c2, false), max_c(X, n, structure, tree, tree[u].c1, false)+max_c(X, n, structure, tree, tree[u].c2, true));
			return X[u][B];
		}
	}
}

int min_c(vector<vector<int>> &Y, int n, string structure, verteX tree[], int u, bool color)
{
	int B=0;
	if(color)
	{
		B=1;
	}

	if(Y[u][B]!=-1)
	{
		return Y[u][B];
	}

	if(tree[u].leaf)
	{	
		if(color)
		{
			//cerr<<"uh ";
			Y[u][B]=1;
			return 1;
		}
		else
		{
			//cerr<<"oh ";
			Y[u][B]=0;
			return 0;
		}
	}

	if(structure[u]=='1')
	{
		if(color)
		{
			Y[u][B]=1+min_c(Y, n, structure, tree, tree[u].c1, false);
			return Y[u][B];
		}
		else
		{
			Y[u][B]=min(min_c(Y, n, structure, tree, tree[u].c1, true), min_c(Y, n, structure, tree, tree[u].c1, false));
			return Y[u][B];
		}
	}

	if(structure[u]=='2')
	{
		if(color)
		{
			Y[u][B]=1+min_c(Y, n, structure, tree, tree[u].c1, false)+min_c(Y, n, structure, tree, tree[u].c2, false);
			return Y[u][B];
		}
		else
		{
			Y[u][B]=min(min_c(Y, n, structure, tree, tree[u].c1, true)+min_c(Y, n, structure, tree, tree[u].c2, false), min_c(Y, n, structure, tree, tree[u].c1, false)+min_c(Y, n, structure, tree, tree[u].c2, true));
			return Y[u][B];
		}
	}
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	int z; cin>>z;
	while(z--)
	{
		string structure; cin>>structure;
		int n=structure.length();

		verteX tree[n];
		draw(n, structure, tree, 0);

		vector<vector<int>> X;
		vector<vector<int>> Y;

		for(int i=0; i<n; i++)
		{
			vector<int> p;
			p.push_back(-1); p.push_back(-1);
			X.push_back(p);
			Y.push_back(p);
		}

		cout<<max(max_c(X, n, structure, tree, 0, false), max_c(X, n, structure, tree, 0, true))<<" ";
		cout<<min(min_c(Y, n, structure, tree, 0, false), min_c(Y, n, structure, tree, 0, true))<<endl;
	}
}