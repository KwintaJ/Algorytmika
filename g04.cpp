//#########################//
//                         //
//      Jan Kwinta 2E      //
//                         //
// Problem G04:Skojarzenia //
//                         //
//    Satori status: OK    //
//                         //
//#########################//
 
#include <bits/stdc++.h>

using namespace std;
 
struct gameword
{
    string w; //said word
    int len; //length of word w
    string k; //key of the next vertex
};
 
struct association
{
    int name; //number of vertex
    vector<gameword> edges; //all possible word starting on the key (in map)
};
 
/* check if there is a negative cycle */
bool bellman_ford(map<string, int> &_char, vector<association> &graph, int n, int m, double p)
{
    double path_l[m];
    path_l[0]=0;
    for(int i=1; i<m; i++)
    {
        path_l[i]=numeric_limits<double>::max();
    }
 
    for(int i=0; i<m-1; i++)
    {
        for(auto g : graph)
        {
            for(auto u : g.edges)
            {
                int v=_char[u.k];
                if(path_l[g.name] + (p-u.len) < path_l[v])
                {
                    path_l[v]=path_l[g.name]+(p-u.len);
                  // cerr<<path_l[v]<<endl;
                }
            }
        }
    }
 
    for(auto g : graph)
    {
        for(auto u : g.edges)
        {
            int v=_char[u.k];
            if(path_l[g.name] + (p-u.len) < path_l[v])
            {
                // cerr<<" b";
                return true;
            }
        }
    }
 
    return false;
}
 
/* binsearching for accurate avg */
double binsearch(map<string, int> &_char, vector<association> &graph, int n, int m, double left, double right)
{
    if(right-left<0.00001)
    {
        return right;
    }
 
    double mid=(left+right)/2;
    // cerr<<mid<<" ";
 
    if(bellman_ford(_char, graph, n, m, mid))
    {
        return binsearch(_char, graph, n, m, mid, right);
    }
    else
    {
        return binsearch(_char, graph, n, m, left, mid);
    }
}
 
//###################################################################
int main()
{
    int z; cin>>z;
    while(z--)
    {
        /* =====variables===== */
        int n; cin>>n;
 
        /* map<key, number> _characters;
        key - two starting/ending characters
        number - number of vertex in graph */
        map<string, int> _char;
 
        /*vector<vertex> graph;
        vertex's number is corresponding with map _char value */
        vector<association> graph;
 
        /* ============input============ */
        association ubervertex;
        ubervertex.name=0;
        graph.push_back(ubervertex); //0-vertex with null-cost-edges to all vertexes
        int count=1;
        int longest_word=0;
        for(int i=0; i<n; i++)
        {
            string _in;
            cin>>_in;
            int l=_in.length();
            if(l>longest_word)
                longest_word=l;
 
            string first_two;
            first_two+=(_in[0]+_in[1]);
            string last_two;
            last_two+=(_in[l-2]+_in[l-1]);
 
            if(_char.find(first_two)==_char.end())
            {
                _char[first_two]=count;
                association x;
                    x.name=count;
                    gameword Y;
                        Y.w=_in;
                        Y.len=l;
                        Y.k=last_two;
                    x.edges.push_back(Y);
                        Y.len=0;
                    graph[0].edges.push_back(Y); //edge from ubervertex to new one
                graph.push_back(x);
 
                count++;
            }
            else
            {
                int num=_char.find(first_two)->second;
                gameword Y;
                    Y.w=_in;
                    Y.len=l;
                    Y.k=last_two;
                graph[num].edges.push_back(Y);
            }
        }
 
        /* ====computing and output===== */
        double o=binsearch(_char, graph, n, count, 0, longest_word);
 
        if(o<2)
        {
            cout<<"NIE"<<endl;
        }
        else
        {
            cout.setf(ios::fixed, ios::floatfield);
            cout.precision(4);
            cout<<o<<endl;
        }
    }
    return 0;
}