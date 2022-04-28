class Solution {
public:
    //主要是学习并查集
    vector<int> parents;
    int findCircleNum(vector<vector<int>>& isConnected) {
        int n = isConnected.size();
        int res = 0;
        parents = vector<int> (n, 0);
        for (int i = 0; i < n; ++i) parents[i] = i;
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                if (isConnected[i][j]) Union(i, j);
            }
        }
        for (int i = 0; i < n; ++i) {
            res += parents[i] == i ? 1 : 0;
        }
        return res;
    }
    int Find(int x) {
        return x == parents[x] ? x : parents[x] = Find(parents[x]);
    }
    void Union(int x, int y) {
        parents[Find(x)] = Find(y);
    }
};
