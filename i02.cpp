//#########################//
//                         //
//      Jan Kwinta 3E      //
//                         //
//    Problem I02: Pole    //
//    wypuklej otoczki     //
//                         //
//    Satori status: ___   //
//                         //
//#########################//
 
#include <bits/stdc++.h>
using namespace std;
 
struct poinT
{
    long long x;
    long long y;
};
 
bool operator<(const poinT &A, const poinT &B)
{
    if(A.y == B.y)
        return A.x < B.x;
    return A.y < B.y;
}
 
bool operator==(const poinT &A, const poinT &B)
{
    if(A.x == B.x && A.y == B.y)
        return true;
    return false;
}
 
struct vectoR
{
    poinT destination;
    long long X;
    long long Y;
    long long length;
};
 
/* angle sort */
bool operator<(const vectoR &A, const vectoR &B)
{
    if((A.X * B.Y) > (B.X * A.Y))
        return true;
    if((A.X * B.Y) < (B.X * A.Y))
        return false;
    if(A.length > B.length)
        return true;
    return false;
}
 
vectoR newVectoR(const poinT &A, const poinT &B)
{
    vectoR alpha; // a vector from A to B
    alpha.destination = B;
    alpha.X = B.x - A.x;
    alpha.Y = B.y - A.y;
    alpha.length = pow((alpha.X), 2) + pow((alpha.Y), 2);
    return alpha;
}
 
void angleSortPoints(vector<poinT> &setOfPoints, int numberOfPoints, const poinT &c)
{
    vector<vectoR> vectorsFromC; // all vectors from c to other points
    for(int i=0; i<numberOfPoints; i++)
    {
        if(setOfPoints[i] == c)
            continue;
 
        poinT z = setOfPoints[i];
 
        /* making a vector from point c to point z */
        vectoR fromCtoI = newVectoR(c, z);
        vectorsFromC.push_back(fromCtoI);
    }
 
    sort(vectorsFromC.begin(), vectorsFromC.end());
    setOfPoints.clear();
    setOfPoints.push_back(c);
    for(vectoR m : vectorsFromC)
        setOfPoints.push_back(m.destination);
}
 
long long doubledSurfaceArea(const vector<poinT> &polygon)
{
    long long area = 0; // doubled area of the polygon
    for(int i=0; i<(polygon.size() - 1); i++)
    {
        area += (polygon[i].x * polygon[i+1].y) - (polygon[i+1].x * polygon[i].y);
    }
    area += (polygon[polygon.size()-1].x * polygon[0].y) - (polygon[0].x * polygon[polygon.size()-1].y);
    return abs(area);
}
 
poinT secondToTop(stack<poinT> &Q)
{
    poinT temporary = Q.top();
    Q.pop();
    poinT output = Q.top();
    Q.push(temporary);
    return output;
}
 
//#####################################
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
 
    int z; cin >> z;
    while(z--)
    {
        /* ===variables=== */
        int numberOfPoints; // n
        cin >> numberOfPoints;
        vector<poinT> setOfPoints; // all points on given plane
 
        /* =====input===== */
        for(int i=0; i<numberOfPoints; i++)
        {
            poinT A;
            cin >> A.x >> A.y;
            setOfPoints.push_back(A);
        }
 
        /* ===algorithm=== */
        /* sorting to find a point with min x */
        sort(setOfPoints.begin(), setOfPoints.end());
        angleSortPoints(setOfPoints, numberOfPoints, setOfPoints[0]);
 
        vector<poinT> convexHull;
        convexHull.push_back(setOfPoints[0]);
        poinT previous, actual, next;
        stack<poinT> sIfConvHull;
 
        sIfConvHull.push(setOfPoints[0]);
        sIfConvHull.push(actual = setOfPoints[1]);
        sIfConvHull.push(next = setOfPoints[2]);
 
        for(int i=3; i<numberOfPoints; i++)
        {
            vectoR A = newVectoR(secondToTop(sIfConvHull), sIfConvHull.top());
            vectoR B = newVectoR(secondToTop(sIfConvHull), setOfPoints[i]);
 
            while((A.X * B.Y) < (B.X * A.Y))
            {
                sIfConvHull.pop();
                A = newVectoR(secondToTop(sIfConvHull), sIfConvHull.top());
                B = newVectoR(secondToTop(sIfConvHull), setOfPoints[i]);
            }
 
            sIfConvHull.push(setOfPoints[i]);
        }
 
        while(!sIfConvHull.empty())
        {
            convexHull.push_back(sIfConvHull.top());
            sIfConvHull.pop();
        }
 
        for(poinT m : convexHull)
            cerr << "(" << m.x << ", " << m.y << ")" << endl;
 
 
        /* =====output==== */
        cout << doubledSurfaceArea(convexHull) << endl;
    }
}