#include <vector>
#include <queue>
#include <stack>
#include <fstream>
#include <string>
#include <set>
#include <algorithm>
using namespace std;

vector<vector<int>> convertMatrixToList(const string& filename){
    ifstream inputFile(filename);
    if(!inputFile){
        return vector<vector<int>>();
    }
    int n;
    inputFile>>n;
    vector<vector<int>> adjList(n);
    for(int i = 0; i < n;i++){
        vector<int> list;
        for(int j = 0; j < n; j++){
            int c;
            inputFile>>c;
            if(c != 0) list.push_back(j);
        }
        adjList[i] = list;
    }
    return adjList;
}

vector<vector<int>> convertListToMatrix(const string& filename){
    ifstream inputFile(filename);
    if(!inputFile) return vector<vector<int>>();
    int n;
    inputFile>>n;
    vector<vector<int>> adjMatrix(n,vector<int>(n,0));
    for(int i =0;i<n;i++){
        int m;
        inputFile>>m;
        for(int j = 0;j < m;j++){
            int v;
            inputFile>>v;
            adjMatrix[i][v] = 1;
        }
    }
    return adjMatrix;
}

bool isDirected(const vector<vector<int>>& adjMatrix){
    int n = adjMatrix.size();
    for(int i = 0;i<n;i++){
        for(int j= 0; j < n;j++){
            if(adjMatrix[i][j] == 0 && adjMatrix[j][i] != 0) return true;
            if(adjMatrix[i][j] != 0 && adjMatrix[j][i] == 0) return true;
        }
    }
    return false;
}

int countVertices(const vector<vector<int>>& adjMatrix){
    int n = adjMatrix.size();
    vector<bool> visit(n,false);
    int count = 0;
    for(int i = 0; i < n;i++){
        for(int j = 0; j < n; j++){
            if(visit[i] && visit[j]) continue;
            if(adjMatrix[i][j]){
                count += !visit[i] + !visit[j];
                visit[i] = visit[j] = true;
            }
        }
    }
    return count;
}

int countEdges(const vector<vector<int>>& adjMatrix){
    int n = adjMatrix.size();
    int count = 0;
    bool directed = false;
    if(isDirected(adjMatrix)) directed = true;
    vector<vector<bool>> visit(n, vector<bool>(n,false));
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            if(visit[i][j] || !adjMatrix[i][j]) continue;
            visit[i][j] = true;
            if(!directed) visit[j][i] = true;
            count++;
        }
        
    }
    return count;
}

vector<int> getIsolatedVertices(const vector<vector<int>>& adjMatrix){
    int n = adjMatrix.size();
    vector<int> res;
    for(int i = 0; i< n;i++){
        bool isIsolated = true;
        for(int j = 0; j< n;j++){
            if(adjMatrix[i][j] || adjMatrix[j][i]) {
                isIsolated = false;
                break;
            }
        }
        if(isIsolated) res.push_back(i);
    }
    return res;
}

bool isCompleteGraph(const vector<vector<int>>& adjMatrix){
    int n = adjMatrix.size();
    for(int i = 0;i< n;i++){
        for(int j = 0; j< n;j++){
            if(i == j) continue;
            if(adjMatrix[i][j] == 0) return false;
        }
    }
    return true;
}

bool isBipartite(const vector<vector<int>>& adjMatrix){
    int n = adjMatrix.size();
    vector<bool> set1(n,false);
    vector<int> set2(n,false);
    queue<int> q;
    for(int i = 0; i< n;i++){
        if(set1[i] || set2[i]) continue;
        bool vertexDetect = false;
        for(int j = 0; j <n;j++){
            if(adjMatrix[i][j] || adjMatrix[j][i]){
                vertexDetect = true;
                break;
            }
        }
        if(!vertexDetect) continue;
        set1[i] = true;
        q.push(i);
        while (!q.empty())
        {
            int k = q.front();
            q.pop();
            for(int j = 0; j< n; j++){
                if(adjMatrix[k][j] || adjMatrix[j][k]){
                    if(set1[k] && set1[j]) return false;
                    if(set2[k] && set2[j]) return false;

                    if(set1[k]) set2[j] = true;
                    else set1[j] = true;

                    q.push(j);
                }
                
            }

        }
    }
    return true;
}

bool isCompleteBipartite(const vector<vector<int>>& adjMatrix){
    int n = adjMatrix.size();
    vector<bool> set1(n,false);
    vector<bool> set2(n,false);
    for(int i = 0;i< n;i++){
        int found = -1;
        for(int j = 0;j < n;j++){
            if(adjMatrix[i][j] || adjMatrix[j][i]){
                found = j;
                break;
            }
        }
        if(found == -1) continue;
        set1[i] = true;
        for(int j = 0; j < n;j++){
            if(adjMatrix[i][j]) set2[j] = true;
            if(adjMatrix[found][j]) set1[j] = true;
        }
    }
    for(int i = 0; i < n;i++){
        if(!set1[i]) continue;
        for(int j = 0; j < n;j++){
            if( adjMatrix[i][j] && !set2[j]) return false;
            if(!adjMatrix[i][j] &&  set2[j]) return false;
        }
    }
    for(int i = 0; i< n;i++){
        if(!set2[i]) continue;
        for(int j = 0; j< n;j++){
            if( adjMatrix[i][j] && !set1[j]) return false;
            if(!adjMatrix[i][j] &&  set1[j]) return false;
        }
    }
    return true;
}

vector<vector<int>> convertToUndirectedGraph(const vector<vector<int>>& adjMatrix){
    int n  = adjMatrix.size();
    vector<vector<int>> res(n,vector<int>(n,0));
    for(int i = 0;i<n;i++){
        for(int j = 0;j<n;j++){
            if(adjMatrix[i][j]){
                res[i][j] = res[j][i] = adjMatrix[i][j];
            }
        }
    }
    return res;
}

vector<vector<int>> getComplementGraph(const vector<vector<int>>& adjMatrix){
    int n = adjMatrix.size();

    vector<vector<int>> res(n,vector<int>(n,0));
    for(int i =0;i< n;i++){
        for(int j = 0;j<n;j++){
            res[i][j] = !adjMatrix[i][j];
        }
    }
    return res;
}

bool hasEulerCycle(const vector<vector<int>> &adjMatrix, bool &directed){
    int n = adjMatrix.size();
    if(isDirected(adjMatrix)){
        for(int i = 0; i < n;i++){
            int inDegree = 0, outDegree = 0;
            for(int j = 0; j < n;j++){
                if(adjMatrix[i][j]) outDegree++;
                if(adjMatrix[j][i]) inDegree++;
            }
            if(inDegree != outDegree) return false;
        }
        directed = true;
    }
    else{
        for (int i = 0; i < n; i++)
        {
            int degree = 0;
            for (int j = 0; j < n; j++)
            {
                if(adjMatrix[i][j]) degree++;
            }
            if(degree % 2 != 0) return false;
        }
    }
    return true;
}

vector<int> findEulerCycle(const vector<vector<int>>& adjMatrix){
    int n = adjMatrix.size();
    vector<stack<int>> adjList(n);
    set<pair<int,int>> edges;
    for(int i =0; i < n;i++){
        for (int j = 0; j < n; j++){
            if(adjMatrix[i][j]) adjList[i].push(j), edges.insert({i,j});
        }
    }
    vector<int> res;
    bool directed = false;
    if(hasEulerCycle(adjMatrix,directed)){
        stack<int> s;
        int start;
        for(int i = 0; i < n; i++){
            if(!adjList[i].empty()) {
                start = i;
                break;
            }
        }
        s.push(start);
        while(!s.empty()){
            int currV = s.top();

            while(!adjList[currV].empty() && !edges.count({currV,adjList[currV].top()}))
                adjList[currV].pop();
            if(!adjList[currV].empty()){
                int neig = adjList[currV].top();
                
                s.push(neig);
                edges.erase({currV,neig});
                if(!directed) edges.erase({neig,currV});
                adjList[currV].pop();
            }
            else{
                res.push_back(currV);
                s.pop();
            }
        }
        reverse(res.begin(),res.end());
    }
    return res;
}

int countGraph(const vector<vector<int>>& adjList){
    int n = adjList.size();
    int count = 0;
    queue<int> q;
    vector<bool> visit(n,false);
    for(int i =0; i < n; i++){
        if(!visit[i]) q.push(i);
        while(!q.empty()){
            int currV = q.front(); q.pop();
            visit[currV] = true;
            for(auto neig : adjList[currV]){
                if(visit[neig]) continue;
                q.push(neig);
            }
        }
        if(!adjList[i].empty()) count += 1;
    }
    return count;
}

vector<vector<int>> dfsSpanningTree(const vector<vector<int>>& adjMatrix, int start){
    int n = adjMatrix.size();
    vector<vector<int>> adjList(n);
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if(adjMatrix[i][j]) adjList[i].push_back(j);
        }
    }
    if(countGraph(adjList) != 1) return {{}};

    stack<int> s;
    vector<vector<int>> res(n,vector<int>(n,0));
    vector<bool> visit(n,false);
    s.push(start);

    while(!s.empty()){
        int currV = s.top();
        visit[currV] = true;
        if(!adjList[currV].empty() && visit[adjList[currV].back()]){
            int neig = adjList[currV].back();
            s.push(neig);
            res[currV][neig] = adjMatrix[currV][neig];
        }
        else s.pop();
    }
    return res;
}
vector<vector<int>> bfsSpanningTree(const vector<vector<int>>& adjMatrix, int start){
    int n = adjMatrix.size();
    vector<vector<int>> adjList(n);
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if(adjMatrix[i][j]) adjList[i].push_back(j);
        }
    }
    if(countGraph(adjList) != 1) return {{}};
    queue<int> q;
    vector<bool> visit(n,false);
    vector<vector<int>> res(n,vector<int>(n,0));
    q.push(start);
    while(!q.empty()){
        int currV = q.front();
        q.pop();
        visit[currV] = true;
        for(auto neig : adjList[currV]){
            if(visit[neig]) continue;
            q.push(neig);
            res[currV][neig] = adjMatrix[currV][neig];
        }
    }
    return res;
}

bool isConnected(int u, int v, const vector<vector<int>>& adjMatrix){
    if(adjMatrix[u][v] || adjMatrix[v][u]) return true;
    int n = adjMatrix.size();
    for(int i = 0 ; i < n; i++){
        if(adjMatrix[i][u] || adjMatrix[u][i]){
            if(isConnected(i,v,adjMatrix)) return true;
        }
    }
    return false;
}

vector<int> dijkstra(int start, int end, const vector<vector<int>>& adjMatrix){
    if(!isConnected(start,end,adjMatrix)) return {};
    int n = adjMatrix.size();
    vector<vector<int>> adjList(n);
    for(int i = 0; i < n; i++){
        vector<int>& neigs = adjList[i];
        for(int j = 0; j < n;j++){
            if(adjMatrix[i][j]) neigs.push_back(j);
        }
    }

    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;
    vector<int> track(n);
    track[start] = -1;
    vector<int> dist(n,INT_MAX);
    dist[start] = 0;
    pq.push({dist[start],start});
    vector<bool> visit(n,false);
    while(!pq.empty()){
        int currV = pq.top().second; pq.pop();
        if(currV == end) continue;
        visit[currV] = true;
        for(auto neig : adjList[currV]){
            if(visit[neig]) continue;
            dist[neig] = min(dist[neig],dist[currV] + adjMatrix[currV][neig]);
            pq.push({dist[neig],neig});
        }
        track[pq.top().second] = currV;
    }
    vector<int> res;
    res.push_back(end);
    int curr = end;
    while(curr != -1){
        res.push_back(curr);
        curr = track[curr];
    }
    reverse(res.begin(),res.end());
    return res;
}
vector<int> bellmanFord(int start, int end, const vector<vector<int>>& adjMatrix){
    if(!isConnected(start,end,adjMatrix)) return {};
    int n = adjMatrix.size();

    vector<int> dist(n,INT_MAX);
    dist[start] = 0;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            dist[j] = min(dist[j],dist[i] + adjMatrix[i][j]);
        }
    }
    
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            if(dist[j] < dist[i] + adjMatrix[i][j]) return {};
        }
    }
    vector<int> res;
    return res;
}
