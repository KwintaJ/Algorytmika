//#########################//
//                         //
//      Jan Kwinta 2E      //
//                         //
//  Problem E12: Zmierzch  //
//   transportu kolowego   //
//                         //
//    Satori status: OK    //
//                         //
//#########################//

#include <bits/stdc++.h>

using namespace std;


struct roads{
    vector<long long> crossings; //neighbours
};

long long p_get(long long n, long long cost[], roads list[], long long v, bool p, long long parent, long long whereToPutThem[][2]) //v - aktualnie odwiedzany wierzcholek; p - czy policjant
{
    if(whereToPutThem[v][p] != -1)
    {
        return whereToPutThem[v][p];
    }

    // cerr<<v<<" "<<p;
    if(list[v].crossings.size()==1 && list[v].crossings[0]==parent)
    {
        // cerr<<" leaf"<<endl;
        if(!p)
        {
            whereToPutThem[v][0]=0;
        	return 0;
        }
        else
        {
            whereToPutThem[v][1]=cost[v];
            return cost[v];
        }
    }
    // cerr<<endl;
    long long min_cost_v=0;
    for(long long i=0; i<list[v].crossings.size(); i++)
    {
        long long u=list[v].crossings[i];
        if(u!=parent)
        {
            if(!p)
            {
                min_cost_v+=p_get(n, cost, list, u, true, v, whereToPutThem);
            }
            else
            {
                min_cost_v+=min(p_get(n, cost, list, u, true, v, whereToPutThem), p_get(n, cost, list, u, false, v, whereToPutThem));
            }
        }
    }

    if(p)
    {
        min_cost_v+=cost[v];
        whereToPutThem[v][1]=min_cost_v;
    }
    else
    {
        whereToPutThem[v][0]=min_cost_v;
    }

    return min_cost_v;
}

void binary_get(long long n, roads list[], long long v, bool p, long long parent, long long whereToPutThem[][2], long long binary_out[])
{
    if(p)
    {
        for(long long i=0; i<list[v].crossings.size(); i++)
        {
            long long u=list[v].crossings[i];
            // cerr << u << " " << whereToPutThem[u][0] << " " << whereToPutThem[u][1] << endl;
            if(u!=parent)
            {
                if(whereToPutThem[u][0] < whereToPutThem[u][1])
                {
                    binary_out[u] = false;
                    binary_get(n, list, u, false, v, whereToPutThem, binary_out);
                }
                else
                {
                    binary_out[u] = true;
                    binary_get(n, list, u, true, v, whereToPutThem, binary_out);
                }
            }
        }
        return;
    }
    else
    {
        for(long long i=0; i<list[v].crossings.size(); i++)
        {
            long long u=list[v].crossings[i];
            if(u!=parent)
            {
                binary_out[u] = true;
                binary_get(n, list, u, true, v, whereToPutThem, binary_out);
            }
        }
        return;
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    long long z; cin>>z;
    while(z--)
    {
        long long n; cin>>n;
        long long cost[n+1];
        roads list[n+1];
        long long whereToPutThem[n+1][2];
        whereToPutThem[0][0] = -1; 
        whereToPutThem[0][1] = -1;
        
        for(long long i=1; i<n+1; i++)
        {
            // cerr<<"a";
            cin>>cost[i];
            whereToPutThem[i][0] = -1; 
            whereToPutThem[i][1] = -1;
        }

        for(long long i=0; i<n-1; i++)
        {
            long long u, v;
            cin>>u>>v;
            list[u].crossings.push_back(v);
            list[v].crossings.push_back(u);
            // cerr<<"b";
        }

        long long root_false = p_get(n, cost, list, 1, false, 0, whereToPutThem);        
        long long root_true = p_get(n, cost, list, 1, true, 0, whereToPutThem);
        long long o = min(root_false, root_true);
        cout << o << endl;

        long long binary_out[n+1];
        for(long long i=0; i<n+1; i++)
        {
            binary_out[i] = -1;
        }

        if(whereToPutThem[1][0] < whereToPutThem[1][1])
        {
            binary_out[1] = false;
            binary_get(n, list, 1, false, 0, whereToPutThem, binary_out);
        }
        else
        {
            binary_out[1] = true;
            binary_get(n, list, 1, true, 0, whereToPutThem, binary_out);
        }

        for(long long i=1; i<n+1; i++)
        {
            cout << binary_out[i];
        } cout << endl;
    }
}