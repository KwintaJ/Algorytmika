//#########################//
//                         //
//      Jan Kwinta 2E      //
//                         //
//   Problem G08: Kabelki  //
//                         //
//    Satori status: OK    //
//                         //
//#########################//

#include <bits/stdc++.h>
using namespace std;

struct vertex
{
    int number;
    int parent;
    int rank;
};

struct edge
{
    int number;
    vertex end1;
    vertex end2;
    int weight;
};

bool operator>(const edge &X, const edge &Y)
{
    return X.weight > Y.weight;
}

/* find-union implementation */
vertex _find(vertex &a, vertex allVertexes[])
{
    if(a.parent == -1)
        return a;

    vertex foundParent = _find(allVertexes[a.parent], allVertexes);
    allVertexes[a.number].parent = foundParent.number;
    return foundParent;
}

void _union(vertex &a, vertex &b, vertex allVertexes[])
{
    // cerr << "unioning " << a.number << " and " << b.number << endl;

    int aRoot = _find(allVertexes[a.number], allVertexes).number;
    int bRoot = _find(allVertexes[b.number], allVertexes).number;

    if(allVertexes[aRoot].rank > allVertexes[bRoot].rank)
        allVertexes[bRoot].parent = aRoot;

    else if(allVertexes[aRoot].rank < allVertexes[bRoot].rank)
        allVertexes[aRoot].parent = bRoot;

    else if(aRoot != bRoot)
    {
        allVertexes[bRoot].parent = aRoot;
        allVertexes[aRoot].rank++;
    }
}

void takeEdges(vector<edge> &toBeTaken, vertex allVertexes[])
{
    for(auto x : toBeTaken)
    {
        _union(allVertexes[x.end1.number], allVertexes[x.end2.number], allVertexes);
    }
}

void optimum(int n, int m, edge allEdges[], vertex allVertexes[], bool optimalEdges[])
{
    priority_queue<edge, vector<edge>, greater<edge>> Que;
    for(int i=0; i<m; i++)
    {
        Que.push(allEdges[i]);
        // cerr << "pushed edge from " << allEdges[i].end1.number << " to " << allEdges[i].end2.number << endl;
    }
    
    int lightest = 0;
    vector<edge> sameWeight;
    while(!Que.empty())
    {
        while(!Que.empty() && Que.top().weight == lightest)
        {
            edge current = Que.top();
            // cerr << "current edge is from " << current.end1.number << " to " << current.end2.number;
            // cerr << " while lightest is " << lightest << endl;
            Que.pop();

            vertex oneEndRoot = _find(allVertexes[current.end1.number], allVertexes);
            // cerr << "oneEndRoot is " << oneEndRoot.number << endl;
            vertex otherEndRoot = _find(allVertexes[current.end2.number], allVertexes);
            // cerr << "otherEndRoot is " << otherEndRoot.number << endl;

            if(oneEndRoot.number != otherEndRoot.number)
            {
                optimalEdges[current.number] = true;
                sameWeight.push_back(current);
            }
        }

        if(!sameWeight.empty())
        {
            takeEdges(sameWeight, allVertexes);
            sameWeight.clear();
        }

        lightest++;
    }
}   

//#####################################
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);

    int z; cin>>z;
    while(z--)
    {
        /* ===variables=== */
        int n, m;
        cin >> n >> m;
        edge allEdges[m];
        vertex allVertexes[n+1];
        bool optimalEdges[m]={false};

        /* =====input===== */
        for(int i=0; i<m; i++)
        {
            int a, b, l;
            cin >> a >> b >> l;

            edge input_e;
            input_e.number = i;

            vertex inp_A, inp_B;
            inp_A.number = a;
            inp_B.number = b;
            inp_A.parent = inp_B.parent = -1;
            inp_A.rank = inp_B.rank = 0;
            allVertexes[a] = inp_A;
            allVertexes[b] = inp_B;

            input_e.end1 = inp_A;
            input_e.end2 = inp_B;
            input_e.weight = l;

            allEdges[i] = input_e;
        }

        /* ===algorithm=== */
        optimum(n, m, allEdges, allVertexes, optimalEdges);
        
        /* =====output==== */
        for(int i=0; i<m; i++)
        {
            if(optimalEdges[i])
                cout << "TAK" << endl;
            else
                cout << "NIE" << endl;
        }
    }
}
