#include <iostream>
#include <vector>
#include <queue>

using namespace std;
void myprint(vector<vector<int>>&);
void heapify(int i, int n, vector<int>& nums) {
	int max = i, left = 2 * i + 1, right = 2 * i + 2;
	if (left < n && nums[left] > nums[max]) max = left;
	if (right < n && nums[right] > nums[max]) max = right;
	if (max != i) {
		swap(nums[max], nums[i]);
		heapify(max, i, nums);
	}
}
void build_heapify(int n, vector<int>& nums) {
	for (int i = (n - 2) / 2; i >= 0; --i) {
		heapify(i, n, nums);
	}
	vector<vector<int>> layer_show;
	layer_show.push_back({nums[0]});
	queue<int> que;
	que.push(0);
	while (!que.empty()) {
		int cur_size = que.size();
		vector<int> tmp;
		for (int i = 0; i < cur_size; ++i) {
			int index = que.front();
			que.pop();
			if (2 * index + 1 < n) {
				tmp.push_back(nums[2 * index + 1]);
				que.push(2 * index + 1);
			}
			if (2 * index + 2 < n) {
				tmp.push_back(nums[2 * index + 2]);
				que.push(2 * index + 2);
			}
		}
		if (!tmp.empty()) layer_show.push_back(tmp);
	}
	myprint(layer_show);
}

void myprint(vector<vector<int>>& layers) {
	const int cnt = layers.size();
	const int space = pow(2, cnt - 1) * 2 - 1;
	for (int i = 0; i < cnt; ++i) {
		const int begin_pos = (space - pow(2, i) * 2 + 1) / 2;
		for (int j = 0; j < begin_pos; ++j) {
			cout << " ";
		}
		for (auto& val : layers[i]) {
			cout << val << " ";
		}
		cout << endl;
	}
}
int main() {
	int n = 15;
	vector<int> nums(n, 0);
	srand(time(0));
	cout << "原始数组: ";
	for (auto& num : nums) {
		num = rand() % (n * 5);
		cout << num << " ";
	}
	cout << endl;
	build_heapify(n, nums);
}
