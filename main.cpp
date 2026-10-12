#include <cstdio>
#include <vector>
#include <unordered_map>

using namespace std;

class UnionFind {
private:
    unordered_map<int, int> parent;
    unordered_map<int, int> rank;
    
    int findRoot(int x) {
        if (parent.find(x) == parent.end()) {
            parent[x] = x;
            rank[x] = 0;
            return x;
        }
        
        if (parent[x] != x) {
            parent[x] = findRoot(parent[x]);
        }
        return parent[x];
    }

public:
    void merge(int x, int y) {
        int rootX = findRoot(x);
        int rootY = findRoot(y);
        
        if (rootX == rootY) return;
        
        if (rank[rootX] < rank[rootY]) {
            parent[rootX] = rootY;
        } else if (rank[rootX] > rank[rootY]) {
            parent[rootY] = rootX;
        } else {
            parent[rootY] = rootX;
            rank[rootX]++;
        }
    }
    
    bool areConnected(int x, int y) {
        return findRoot(x) == findRoot(y);
    }
    
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
        
        // Vectors to store constraints
        vector<pair<int, int>> equals;
        vector<pair<int, int>> notEquals;
        
        // Read all constraints
        for (int i = 0; i < n; i++) {
            int x, y, e;
            scanf("%d %d %d", &x, &y, &e);
            
            if (e == 1) {
                equals.push_back({x, y});
            } else {
                notEquals.push_back({x, y});
            }
        }
        
        bool valid = true;
        
        // Process all equality constraints
        for (const auto& p : equals) {
            uf.merge(p.first, p.second);
        }
        
        // Check all inequality constraints
        for (const auto& p : notEquals) {
            if (uf.areConnected(p.first, p.second)) {
                valid = false;
                break;
            }
        }
        
        printf("%s\n", valid ? "YES" : "NO");
        
        // Clear UnionFind for next test case
        uf.clear();
    }
    
    return 0;
}