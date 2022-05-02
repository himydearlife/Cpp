/*
  删除树节点
  https://leetcode-cn.com/problems/delete-tree-nodes/
  input:
      nodes 节点的总数
      value[i] 第i个节点的值
      parent[i] 第i个节点的父节点
  删除节点之和为0的每一棵子树
*/
// 1
class Solution {
public:
    int deleteTreeNodes(int nodes, vector<int>& parent, vector<int>& value) {
        vector<vector<int>> edgs(nodes);
        for (int i = 0; i < nodes; ++i) {
            if (parent[i] != -1) {
                edgs[parent[i]].push_back(i);
            }
        }
        vector<int> cnt_nodes(nodes, 1);
        dfs(0, edgs, cnt_nodes, value);
        return cnt_nodes[0];
    }
    void dfs(int u, vector<vector<int>>& edgs, vector<int>& cnt_nodes, vector<int>& value) {
        for (auto& v : edgs[u]) {
            dfs(v, edgs, cnt_nodes, value);
            value[u] += value[v];
            cnt_nodes[u] += cnt_nodes[v];
        }
        if (value[u] == 0) {
            cnt_nodes[u] = 0;
        }
    }
};
// 2 重点学习拓扑排序
class Solution {
public:
    int deleteTreeNodes(int nodes, vector<int>& parent, vector<int>& value) {
        vector<int> in_cnt(nodes, 0);
        vector<int> nodes_cnt(nodes, 1);
        for (int i = 0; i < nodes; ++i) {
            if (parent[i] != -1) {
                ++in_cnt[parent[i]];
            }
        }
        queue<int> que;
        for (int i = 0; i < nodes; ++i) {
            if (in_cnt[i] == 0) que.push(i);
        }
        while (!que.empty()) {
            int u = que.front();
            que.pop();
            if (value[u] == 0) nodes_cnt[u] = 0;
            int v = parent[u];
            if (v != -1) {
                value[v] += value[u];
                nodes_cnt[v] += nodes_cnt[u];
                if (--in_cnt[v] == 0) que.push(v);
            }
        }
        return nodes_cnt[0];
    }
};
