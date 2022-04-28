class Solution {
public:
    // 主要是学习拓扑排序
    // 拓扑排序只适用于DAG即有向无环图
    vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
        vector<int> in_cnt(numCourses, 0);
        vector<vector<int>> edgs(numCourses);
        for (auto& p : prerequisites) {
            ++in_cnt[p[0]];
            edgs[p[1]].push_back(p[0]);
        }
        queue<int> que;
        for (int i = 0; i < numCourses; ++i) {
            if (in_cnt[i] == 0) que.push(i);
        }
        vector<int> res;
        while (!que.empty()) {
            int curr = que.front();
            que.pop();
            res.push_back(curr);
            for (auto& e : edgs[curr]) {
                in_cnt[e]--;
                if (in_cnt[e] == 0) {
                    que.push(e);
                }
            }
        }
        return res.size() == numCourses ? res : vector<int> {};
    }
};
// 2 拓扑排序不需要再次记录边
class Solution {
public:
    vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
        vector<int> in_cnt(numCourses, 0);
        for (auto& p : prerequisites) {
            ++in_cnt[p[0]];
        }
        queue<int> que;
        for (int i = 0; i < numCourses; ++i) {
            if (in_cnt[i] == 0) que.push(i);
        }
        vector<int> res;
        while (!que.empty()) {
            int curr = que.front();
            que.pop();
            res.push_back(curr);
            for (auto& p : prerequisites) {
                if (p[1] == curr) {
                    --in_cnt[p[0]];
                    if (in_cnt[p[0]] == 0) que.push(p[0]); 
                }
            }
        }
        return res.size() == numCourses ? res : vector<int> {};
    }
};
