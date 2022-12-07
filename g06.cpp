//#########################//
//                         //
//      Jan Kwinta 2E      //
//                         //
//    Problem G06: Mapa    //
//       galaktyczna       //
//                         //
//    Satori status: ___   //
//                         //
//#########################//    
   
#include <bits/stdc++.h>
using namespace std;

/* egde */
struct portal
{
    int wDestination;
    int wLength;
};

bool operator>(const portal &a, const portal &b)
{
    return a.wLength > b.wLength;
}

/* vertex */
struct solarSystem
{
    int number;
    string name;
    vector<portal> nearbySystems;
    int delta = 99999999; //99 999 999
    int wTime = 2000000031; //2 000 000 031 - travel time from supervertex to this
    bool checked=false;
};

/* bellman-ford to find all delta values */
void findDelta(solarSystem galaxyMap[], int systemsQty)
{
    for(int i=0; i<systemsQty; i++)
    {
        for(int j=1; j<systemsQty+1; j++)
        {   
            for(auto &u : galaxyMap[j].nearbySystems)
            {
                if(galaxyMap[j].delta + u.wLength < galaxyMap[u.wDestination].delta)
                {
                    galaxyMap[u.wDestination].delta = galaxyMap[j].delta + u.wLength;
                }
            }
        }
    }
}

/* dijkstra - find all distances between systemI and systemJ */
void calculateDistances(solarSystem galaxyMap[], int systemsQty, vector<vector<int>> &distArray)
{
    for(int x=1; x<systemsQty+1; x++)
    {
        cerr<< "    dj for " << x << endl;
        priority_queue<portal, vector<portal>, greater<portal>> dijkstraNext;
        dijkstraNext.push(galaxyMap[x].nearbySystems[0]);
        distArray[x][0] = galaxyMap[x].nearbySystems[0].wLength;     
        while(!dijkstraNext.empty())
        {
            portal currentPortal = dijkstraNext.top();
            dijkstraNext.pop();
            if(galaxyMap[currentPortal.wDestination].checked)
            {
                continue;
            }    
            galaxyMap[currentPortal.wDestination].checked = true;

            for(auto nextPortal : galaxyMap[currentPortal.wDestination].nearbySystems)
            {
                int travelTime = distArray[x][currentPortal.wDestination] + nextPortal.wLength + galaxyMap[currentPortal.wDestination].delta - galaxyMap[nextPortal.wDestination].delta;
                if(!galaxyMap[nextPortal.wDestination].checked && travelTime < distArray[x][nextPortal.wDestination])
                {
                    galaxyMap[nextPortal.wDestination].wTime = travelTime;
                    portal toPush;
                    toPush.wDestination = nextPortal.wDestination; 
                    toPush.wLength = distArray[x][nextPortal.wDestination];
                    dijkstraNext.push(toPush);
                }
            }
        }
        cerr<< "        finished" << endl;
        for(int i=0; i<systemsQty+1; i++)
        {
            galaxyMap[i].checked = false;
        }
    }
}

/* void function for output */
void printDistances(int systemsQty, string systemNames[], vector<vector<int>> &distArray)
{
    cout << "            "; //12 spaces

    /* first line */
    for(int i=1; i<systemsQty+1; i++)
    {
        cout << setw(12) << systemNames[i];
    }
    cout << endl;

    /* following lines */
    for(int i=1; i<systemsQty+1; i++)
    {
        cout << setw(12) << systemNames[i];
        for(int j=1; j<systemsQty; j++)
        {
            cout << setw(12) << distArray[i][j];
        }
        cout << endl;
    }
}

//#########################################################
int main()
{
    ios_base::sync_with_stdio(false);   
    int z; cin >> z;
    while(z--)
    {
    /* =====variables===== */
    int systemsQty, wormholesQty;
    cin >> systemsQty;
    string systemNames[systemsQty+1];

    /* map<systemName, systemNumber> */
    map<string, int> nameToNumber;

    /* graph for Johnson's algorithm
    struct solarSystem = vertex
    struct portal = edge */
    solarSystem galaxyMap[systemsQty+1];
    galaxyMap[0].number = 0;
    galaxyMap[0].delta = 0;

    /* array[i][j] = distance between systemI and systemJ */
    vector<vector<int>> distanceArray;
    vector<int> justAVector;
    for(int i=0; i<systemsQty+1; i++)
    {
        justAVector.push_back(99999999);
    }
    for(int i=0; i<systemsQty+1; i++) 
    //building distArr with inf_values on every [i][j] and 0 on [i][i]
    {
        distanceArray.push_back(justAVector);
        distanceArray[i][i] = 0;
    }


    /* =======input======= */
    for(int i=1; i<systemsQty+1; i++)
    {
        cin >> systemNames[systemsQty];
        nameToNumber[systemNames[i]] = i;
        galaxyMap[i].number = i;
        galaxyMap[i].name = systemNames[i];
    }
    
    cin >> wormholesQty;
    for(int i=0; i<wormholesQty; i++)
    {
        string systemA, systemB;
        int between;
        cin >> systemA >> systemB >> between;
        
        int systemANumber = nameToNumber[systemA];
        int systemBNumber = nameToNumber[systemB];
        portal portalFromAToB;
        portalFromAToB.wDestination = systemBNumber;
        portalFromAToB.wLength = between;
        galaxyMap[systemANumber].nearbySystems.push_back(portalFromAToB);
    }
    cerr << "input done" << endl;    

    /* ===bellman-ford==== */
    findDelta(galaxyMap, systemsQty);
    cerr << "bellman-ford done" << endl;


    /* =====dijsktra====== */
    calculateDistances(galaxyMap, systemsQty, distanceArray);
    cerr << "dijkstra done" << endl;

    /* ======output======= */
    printDistances(systemsQty, systemNames, distanceArray);
    cerr << "printing done" << endl;
    }
    return 0;
}
