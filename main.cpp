// C++ program for Kruskal Algorithm with 2 criteria optimization
#include <bits/stdc++.h>
#include <numeric>
using namespace std;

// DSU data structure
// path compression + rank by union
class DSU
{
    int* parent;
    int* rank;

public:
    DSU(int n)
    {
        parent = new int[n];
        rank = new int[n];

        for (int i = 0; i < n; i++) {
            parent[i] = -1;
            rank[i] = 1;
        }
    }

    // Find function
    int find(int i)
    {
        if (parent[i] == -1)
            return i;

        return parent[i] = find(parent[i]);
    }

    // Union function
    void unite(int x, int y)
    {
        int s1 = find(x);
        int s2 = find(y);

        if (s1 != s2) {
            if (rank[s1] < rank[s2]) {
                parent[s1] = s2;
            }
            else if (rank[s1] > rank[s2]) {
                parent[s2] = s1;
            }
            else {
                parent[s2] = s1;
                rank[s1] += 1;
            }
        }
    }
};

class Graph {
    //private class variables
    vector<vector<int> > edgelist;
    int V;


public:

    //graph class builder function
    Graph(int V)
    { this->V = V;
     }

    // Function to add edge in a graph
    void addEdge(int x, int y,int p, int w,int t)
    {   //Ta kanoume insert me seira : (weight,profit, vertex1, vertex2)
        edgelist.push_back({ t, w, p, x, y });
    }




    void kruskals_mst()
    {

        float left_binary_margin = 0.0, right_binary_margin = 200.0,C=(left_binary_margin+right_binary_margin)/2;
        int best_mst_profit_sum,best_mst_weight_sum;
        while(left_binary_margin<=right_binary_margin-0.1)
        {
          for(int i=0;i<edgelist.size();i++){
          int w=edgelist[i][1];
          int p=edgelist[i][2];
          int t=int(p-C*w);
          edgelist[i][0]=t;
          //cout<<"(w, p, t) = ("<<w<<", "<<p<<", "<<t<<")"<<endl;
          //edgelist[i].insert(edgelist[i].begin(),t);
        }

        //taksinomw me vasi to t descending gia na kanw Kruskal vasei autou
        sort(edgelist.begin(), edgelist.end(),greater<vector<int>>());
        int edges_selected=0;
        //arxizoume apo to prwto stoixeio opws exoun taksinomithei
        //vector<vector<int>>::iterator it=edgelist.begin();

        // Initialize of the DSU data structure to help us build the MST
        DSU s(V);
        //Sto katw while loop ginetai i eklogi twn V-1 edges pou tha apotelesoun to
        //veltistopoihmeno mas elaxisto sunektiko dentro
        //H veltistopoihsh 2 kritiriwn ginetai ws eksis :
        int sum_w=0,sum_p=0;
        for(int j=0;j<edgelist.size();j++) { //evgala to  apo ti sunthiki
            int w = edgelist[j][1];
            int p = edgelist[j][2];
            int x = edgelist[j][3];
            int y = edgelist[j][4];

            // Take this edge in MST if it does
            // not form a cycle
            if (s.find(x) != s.find(y)) {
                s.unite(x, y);
                sum_w+= w;
                sum_p+=p;
                //pame stin epomeni akmi gia eksetasi an kleinei kuklo
                edges_selected++;
            }
        }
        if((sum_p -C*sum_w)>0)
     //uparxei perithorio auksisis tou C
        {
         best_mst_profit_sum=sum_p;
         best_mst_weight_sum=sum_w;
         left_binary_margin=C+0.1;
         C=(left_binary_margin+right_binary_margin)/2;
        }
       else
        //psaxnoume se mikrotera C
       {
        right_binary_margin=C-0.1;
        C=(left_binary_margin+right_binary_margin)/2;
       }
    }

    int gcd=__gcd(best_mst_profit_sum,best_mst_weight_sum);
    cout<<best_mst_profit_sum/gcd<<" "<<best_mst_weight_sum/gcd<<endl;

    }
};

// Driver code
int main()
{
    int N,M,new_vertex_x,new_vertex_y,new_p,new_w,t=1;
    cin>>N;
    Graph g(N);
    cin>>M;

    for(int i=0;i<M;i++)
    {
        cin>>new_vertex_x;
        cin>>new_vertex_y;
        cin>>new_p;
        cin>>new_w;
        g.addEdge(new_vertex_x-1,new_vertex_y-1,new_p,new_w,t);
    }
    g.kruskals_mst();
    return 0;
}
