#include <cstdio>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

class UnionFind {
private:
    unordered_map<int, int> parent;
    unordered_map<int, int> rank;
    
public:
    // Find with path compression
    int find(int x) {
        if (parent.find(x) == parent.end()) {
            parent[x] = x;
            rank[x] = 0;
            return x;
        }
        
        // Path compression
        if (parent[x] != x) {
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }
    
    // Union by rank
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
    
    // Clear the data structure for reuse
    void clear() {
        parent.clear();
        rank.clear();
    }
};

int main() {
    int t;
    scanf("%d", &t);
    
    UnionFind uf;
    
    while (t--) {
        int n;
        scanf("%d", &n);
        
        // We'll use two vectors to separate equality and inequality constraints
        vector<pair<int, int>> equals;
        vector<pair<int, int>> not_equals;
        
        // Read all constraints
        for (int i = 0; i < n; i++) {
            int x, y, e;
            scanf("%d %d %d", &x, &y, &e);
            
            if (e == 1) {
                equals.push_back({x, y});
            } else {
                not_equals.push_back({x, y});
            }
        }
        
        bool possible = true;
        
        // Process all equality constraints first
        for (const auto& p : equals) {
            uf.unite(p.first, p.second);
        }
        
        // Check all inequality constraints
        for (const auto& p : not_equals) {
            if (uf.connected(p.first, p.second)) {
                possible = false;
                break;
            }
        }
        
        printf("%s\n", possible ? "YES" : "NO");
        
        // Clear the UnionFind for the next test case
        uf.clear();
    }
    
    return 0;
}