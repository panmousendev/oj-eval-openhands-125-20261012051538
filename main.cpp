#include <cstdio>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

// Coordinate compression based Union-Find
class UnionFind {
private:
    vector<int> parent;
    vector<int> rank;
    int n;
    
public:
    UnionFind(int size) {
        n = size;
        parent.resize(n);
        rank.resize(n, 0);
        for (int i = 0; i < n; i++) {
            parent[i] = i;
        }
    }
    
    int find(int x) {
        if (parent[x] != x) {
            parent[x] = find(parent[x]); // Path compression
        }
        return parent[x];
    }
    
    void unite(int x, int y) {
        int rootX = find(x);
        int rootY = find(y);
        
        if (rootX == rootY) return;
        
        // Union by rank
        if (rank[rootX] < rank[rootY]) {
            parent[rootX] = rootY;
        } else if (rank[rootX] > rank[rootY]) {
            parent[rootY] = rootX;
        } else {
            parent[rootY] = rootX;
            rank[rootX]++;
        }
    }
    
    bool connected(int x, int y) {
        return find(x) == find(y);
    }
};

int main() {
    int t;
    scanf("%d", &t);
    
    while (t--) {
        int n;
        scanf("%d", &n);
        
        vector<tuple<int, int, int>> constraints;
        vector<int> variables;
        
        // Read all constraints and collect variables
        for (int i = 0; i < n; i++) {
            int x, y, e;
            scanf("%d %d %d", &x, &y, &e);
            constraints.push_back(make_tuple(x, y, e));
            variables.push_back(x);
            variables.push_back(y);
        }
        
        // Coordinate compression
        sort(variables.begin(), variables.end());
        auto last = unique(variables.begin(), variables.end());
        variables.erase(last, variables.end());
        
        // Create mapping from original variable to compressed index
        unordered_map<int, int> comp_map;
        for (int i = 0; i < variables.size(); i++) {
            comp_map[variables[i]] = i;
        }
        
        // Create UnionFind with compressed coordinates
        UnionFind uf(variables.size());
        bool possible = true;
        
        // Process all equality constraints
        for (const auto& constraint : constraints) {
            int x = get<0>(constraint);
            int y = get<1>(constraint);
            int e = get<2>(constraint);
            
            if (e == 1) { // Equality
                uf.unite(comp_map[x], comp_map[y]);
            }
        }
        
        // Check all inequality constraints
        for (const auto& constraint : constraints) {
            int x = get<0>(constraint);
            int y = get<1>(constraint);
            int e = get<2>(constraint);
            
            if (e == 0) { // Inequality
                if (uf.connected(comp_map[x], comp_map[y])) {
                    possible = false;
                    break;
                }
            }
        }
        
        printf("%s\n", possible ? "YES" : "NO");
    }
    
    return 0;
}