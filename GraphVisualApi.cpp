#include <iostream>
#include <vector>
#include <queue>
#include <graphics.h>
using namespace std;

int WINHEIGHT = 600;
int WINWIDTH = 800;
void StartGraphics(int winx = WINWIDTH,int winy = WINHEIGHT){
    // int gd = DETECT,gm;
    // initgraph(&gd,&gm,NULL);
    initwindow(winx,winy);
}

void EndGraphics(){
   closegraph();
}

class Node{
    public:
        int xpos;
        int ypos;
        int nodeId;
        Node(){
            xpos =0;
            ypos =0;
            nodeId =0;
        }
        Node(int x,int y , int nid){
            xpos = x;
            ypos = y;
            nodeId = nid;
        }
        Node* GetNewNode(int x,int y,int nid){
            return new Node(x,y,nid);
        }

};

class Graph {
    private:
        int Nofcomponents;
        int Nofnodes;
        int Nofedges;
        unsigned int STDDELAY;
        unsigned int STDRADIUS;
        vector<pair<Node*,vector<Node*>>>graph;
        vector<pair<int,int>>edge;
        
        vector<int> ShortestPathUtil(int src,int end,vector<pair<Node*,vector<Node*>>>g){
            vector<int>par(Nofnodes,-1);
            par[src] = src;
            queue<Node*>process;
            process.push(GetNode(src));
            vector<bool>vis(Nofnodes,0);
            vis[src]=1;
            while(not process.empty()){
                Node *currnode = process.front();
                process.pop();
                for(auto nbs : g[currnode->nodeId].second){
                    if(not vis[nbs->nodeId]){
                        par[nbs->nodeId] = currnode->nodeId;
                        vis[nbs->nodeId] = 1;
                        if(nbs->nodeId==end){
                            return par;
                        }
                        process.push(nbs);
                    }
                }
            }
            return par;
        }

        void DepthFirstSearchUtil(vector<pair<Node*,vector<Node*>>>g,vector<bool>&vis,int cnode){
            if( not vis[cnode]){
                vis[cnode]=1;
                Node *node = GetNode(cnode);
                FillCircle(node->xpos,node->ypos,15);
                for(auto nb : g[cnode].second){
                    if( not vis[nb->nodeId]){
                        DrawEdge(g[cnode].first,nb);
                        DepthFirstSearchUtil(g,vis,nb->nodeId);
                    }
                }
            }
        }

        void BredthFirstSearchUtil(queue<Node*>&process,vector<bool>&vis,int source){
            Node *node = GetNode(source);
            process.push(node);
            FillCircle(node->xpos,node->ypos,15);
            while(not process.empty()){
                Node* currnode = process.front();
                process.pop();
                vis[currnode->nodeId]=1;
                for(auto nbs : graph[currnode->nodeId].second){
                    if( not vis[nbs->nodeId]){
                        process.push(nbs);
                        DrawEdge(currnode,nbs);
                    }
                }
            }
        }

        void FillCircle(int x,int y,int radius= 15){
            circle(x,y,radius);
            fillellipse(x,y,radius,radius); 
        }

        Node* GetNode(int nodeId){
            return graph[nodeId].first;
        }

        void WriteToScreen(string text,int posx = 200,int posy = 200){
            settextstyle(4,HORIZ_DIR,2);
            outtextxy(posx,posy,&text[0]);   
        }


        void DrawEdge(Node* u,Node* v){
            int radius = STDRADIUS;
            FillCircle(u->xpos,u->ypos,radius);
            setlinestyle(0, 0, 5); 
            line(u->xpos,u->ypos,v->xpos,v->ypos);
            FillCircle(v->xpos,v->ypos,radius);
            delay(STDDELAY);
        }

        void CreateGraph(){  
            for(int c =0;c<Nofnodes;c++){
                int x,y;
                cin>>x>>y;
                x+=100;
                y+=100;
                Node node;
                graph[c].first = node.GetNewNode(x,y,c);
            }

            for(int e =0;e<Nofedges;e++){
                cin>>edge[e].first>>edge[e].second; 
                graph[edge[e].first].second.push_back(graph[edge[e].second].first);
                graph[edge[e].second].second.push_back(graph[edge[e].first].first);
            }

        }

    public:
    
        Graph(int n =0,int e=0){
            Nofnodes = n;
            STDDELAY = 1500;
            STDRADIUS = 15;
            Nofedges = e;
            Nofcomponents =0;
            graph.resize(n);
            edge.resize(e);
            CreateGraph();
        }

        

        pair<int,int> GetCordinates(int node_id){
            return {graph[node_id].first->xpos,graph[node_id].first->ypos};
        }
        
        void ShowGraph(){
            for(auto edg : edge){
                DrawEdge(GetNode(edg.first),GetNode(edg.second));
            }
            for(auto node : graph){
                if(node.second.empty()){
                    FillCircle(node.first->xpos,node.first->ypos,15);
                }
            }
        }

        int DepthFirstSearch(){
            vector<bool>vis(Nofnodes,0);
            for(int n =0;n<Nofnodes;n++){
                if(not vis[n]){
                   DepthFirstSearchUtil(graph,vis,n);
                   Nofcomponents++;
                }
            }
            delay(STDDELAY);
            return Nofcomponents;
        }

        int BredthFirstSearch(){
            queue<Node*>process;
            vector<bool>vis(Nofnodes,0);
            for(int nd = 0;nd<Nofnodes;nd++){
                if(not vis[nd]){
                    BredthFirstSearchUtil(process,vis,nd);
                    Nofcomponents++;
                }
            }
            delay(STDDELAY);
            return Nofcomponents;
        }

        
        void ShortestPath(int source, int end){
            if(source!=end){
                vector<int>path = ShortestPathUtil(source,end,graph);
                int last = end;
                if(path[end]!=-1){
                    while(last!=path[last]){
                        int parlast = path[last];
                        DrawEdge(GetNode(last),GetNode(parlast));
                        last = parlast;
                    }
                }else{
                    WriteToScreen("Destination not reachable");
                }
                delay(STDDELAY);
                clearviewport();
            }else{
                Node* node = GetNode(source);
                FillCircle(node->xpos,node->ypos,STDRADIUS);
                delay(STDDELAY);
            }
        }

};




int main(){
    int n,m;
    cin>>n>>m;
    Graph g(n,m);
    StartGraphics();

    g.ShowGraph();

    EndGraphics();
    return 0;
}