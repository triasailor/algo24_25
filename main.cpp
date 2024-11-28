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
    //global class variables
    vector<vector<int> > edgelist;
    int V,sum_p=0,sum_w=0,ccompute_called=0;
    float C,binary_margin;

public:
    //graph class builder function
    Graph(int V,float binary_margin)
    { this->V = V;
      this->binary_margin = binary_margin;
     }

    // Function to add edge in a graph
    void addEdge(int x, int y,int p, int w)
    {   //Ta kanoume insert me seira : (weight,profit, vertex1, vertex2)
        edgelist.push_back({ w,p, x, y });
    }
    //Function to recompute C factor  with binary search
    float recompute_C(int p_current_sum,int w_current_sum){
      this->ccompute_called++;
      int bias=0;
      if(this->ccompute_called==1)
       bias=19;
      float left=0.0,right=this->binary_margin,C;
      while (left-right<=0.00000000001) {
		float mid = (left + right) / 2;
		//For each mid-value check if it is posleast K
		if (p_current_sum+bias-mid*w_current_sum>0) {
			C = mid;
			left = mid + 0.0001;
		}
		else
			right = mid - 0.0001;
	}
	return C;
    }


    void kruskals_mst()
    {

        //Tis katw duo grammes giati ?? arxika einai 0 ta sums ...
        int curr_p_sum=this->sum_p,curr_w_sum=this->sum_w;
        float C=recompute_C(curr_p_sum,curr_w_sum);
        //Parakatw prosthetw stin kathe akmi epipleon to tin toupla?? w,t ?
        for(int i=0;i<edgelist.size();i++){
          int w=edgelist[i][0];
          int p=edgelist[i][1];
          int t=int(p-C*w);
          //cout<<"(w, p, t) = ("<<w<<", "<<p<<", "<<t<<")"<<endl;
          edgelist[i].insert(edgelist[i].begin(),t);
          //cout<<"edgelist["<<i<<"] = "<<edgelist[i]<<endl;
        }

        // Initialize the DSU alli thesi ????
        DSU s(V);
        //taksinomw me vasi ti?
        sort(edgelist.begin(), edgelist.end(),greater<vector<int>>());

        int edges_selected=0;
        //???an den kanei kuklo logv tou kritiriou taksinomisis tha einai i prvti pou tha epilegei???
        int index_of_edge_element_selected=0;
        vector<vector<int>>::iterator it=edgelist.begin();

        //Sto katw while loop ginetai i eklogi twn V-1 edges pou tha apotelesoun to
        //veltistopoihmeno mas elaxisto sunektiko dentro
        //H veltistopoihsh 2 kritiriwn ginetai ws eksis :
        //
        while (!edgelist.empty()&&edges_selected<V-1) {
            int w = edgelist[index_of_edge_element_selected][1];
            int p = edgelist[index_of_edge_element_selected][2];
            int x = edgelist[index_of_edge_element_selected][3];
            int y = edgelist[index_of_edge_element_selected][4];

            // Take this edge in MST if it does
            // not form a cycle
            if (s.find(x) != s.find(y)) {
                s.unite(x, y);
                this->sum_w+= w;
                this->sum_p+=p;
                edgelist.erase(it);
                edges_selected++;
                if(edgelist.size()>1){
                 //xreiazetai nea var?
                int curr_p_sumi=this->sum_p,curr_w_sumi=this->sum_w;
                float Ci=recompute_C(curr_p_sumi,curr_w_sumi);

                 for(int i=0;i<edgelist.size();i++){
                   int wi=edgelist[i][1];
                   int pi=edgelist[i][2];
                   int t=floor(pi-Ci*wi);
                   edgelist[i][0]=t;
                  }
                }
                  if(edgelist.size()>1){
                    sort(edgelist.begin(), edgelist.end(),greater<vector<int>>());
                  }
            }
            //An i akmi kleinei kuklo ???na min tin vgalw ektos ?
            else {
                if(edgelist.size()>1){
                   index_of_edge_element_selected++;
              ++it; //nomizw lathos -> edgelist.erase(it);
                }
            }
        }
        int final_p=this->sum_p,final_w=this->sum_w,gcd=__gcd(final_p,final_w);
        int f1=final_p/gcd,f2=final_w/gcd;
        cout<<f1<<" "<<f2<<endl;
    }
};

// Driver code
int main()
{
    int N,M,new_vertex_x,new_vertex_y,new_p,new_w;
    //int sum_p_max=0,sum_w_max=0;
    cin>>N;
    Graph g(N,200.0);
    cin>>M;

    for(int i=0;i<M;i++)
    {
        cin>>new_vertex_x;
        cin>>new_vertex_y;
        cin>>new_p;
        cin>>new_w;
        g.addEdge(new_vertex_x-1,new_vertex_y-1,new_p,new_w);
        //sum_p_max+=new_p;
        //sum_w_max+=new_w;
    }
    // Function call
    g.kruskals_mst();
    return 0;
}
