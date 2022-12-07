//#########################//
//                         //
//      Jan Kwinta 2E      //
//                         //
//   Problem H05: Rycerze  //
//     Okrągłego stołu     //
//                         //
//    Satori status: ___   //
//                         //
//#########################//

#include <bits/stdc++.h>
using namespace std;

/* every node contains information:
maximal and minimal sums on 
whole interval, prefix and suffix 
and also just sum of whole interval*/
struct node
{
	/* max */
	int interval_max = 0;
	int prefix_max = 0;
	int suffix_max = 0;

	/* min */
	int interval_min = 0;
	int prefix_min = 0;
	int suffix_min = 0;

	/* just sum */
	int sum = 0;
};


node glue(const node &X, const node &Y)
{
	node Z; // nodes X and Y glued together


}


/* update the tree */
node update(node tree[], int v, int left, int right, int k, const node &x)
{
	if(right - left == 1) // v is leaf
    {
        // cerr << "a" << endl;
        if(left == k) 
            tree[v] = x;

        return tree[v];
    }

    if(left <= k && k < right) // v is not leaf but k is in range (left, right)
    {
        // cerr << "b" << endl;
        int middle = (left + right) / 2;
        node child1 = update(tree, 2*v, left, middle, k, x);
        node child2 = update(tree, 2*v+1, middle, right, k, x);
        tree[v] = glue(child1, child2);
    }

    // cerr << "c" << endl;
    return tree[v]; // k is not in range (left, right)
}

//#############################################
int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);

	int z; cin>>z;
	while(z--)
	{
		int leafNum; cin >> leafNum; 
		node tree[4*leafNum+1];

		for(int i=0; i<leafNum; i++)
		{
			int ipt; // input
			cin >> ipt;

			node ipt_node; //new node
			ipt_node.interval_max = ipt;
			ipt_node.prefix_max = ipt;
			ipt_node.suffix_max = ipt;
			ipt_node.interval_min = ipt;
			ipt_node.prefix_min = ipt;
			ipt_node.suffix_min = ipt;
			ipt_node.sum = ipt;

			update(tree, 1, 0, leafNum, i, ipt);
		}

		cout << tree[1] << endl;

		int updatesNum; cin >> updatesNum;
		for(int i=0; i<updatesNum; i++)
		{
			int k, ipt;
			cin >> k >> ipt;

			node ipt_node; //new node
			ipt_node.interval_max = ipt;
			ipt_node.prefix_max = ipt;
			ipt_node.suffix_max = ipt;
			ipt_node.interval_min = ipt;
			ipt_node.prefix_min = ipt;
			ipt_node.suffix_min = ipt;
			ipt_node.sum = ipt;

			update(tree, 1, 0, leafNum, k, ipt);

			cout << tree[1] << endl;
		}
	}
}