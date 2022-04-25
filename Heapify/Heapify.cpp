#include <iostream>
#include <vector>

using namespace std;
/*
  第一行表示输入的数据
  第二行表示当前堆顶的元素
  第三行表示输出的顺序
*/
template<typename T>
class Priority_que {
private:
	vector<T> que;
	string mode;
public:
	Priority_que(string mode = "up"):mode(mode) {}
	bool size() { return que.size(); }
	bool empty() { return que.empty(); }
	T front() { 
		if (que.size() == 0) {
			cout << "no element in que" << endl;
			return T(0);
		}
		return que.front(); 
	}
	bool push(T ele);
	bool pop();
	bool compare(T& a, T& b);
	void heapify(int n, int i);
	void heapify_down_to_up(int n);
};
template<typename T>
bool Priority_que<T>::push(T ele) {
	que.push_back(ele);
	if (que.size() > 1) heapify_down_to_up(que.size());
	return true;
}
template<typename T>
bool Priority_que<T>::pop() {
	if (que.empty()) {
		cout << "no element in que" << endl;
		return false;
	}
	swap(que.front(), que.back());
	que.pop_back();
	if (que.size() > 1) heapify(que.size(), 0);
	return true;
}
template<typename T>
bool Priority_que<T>::compare(T& a, T& b) {
	if (mode == "up") return a > b;
	else return a < b;
}
template<typename T>
void Priority_que<T>::heapify(int n, int i) {
	int max = i, left = 2 * i + 1, right = 2 * i + 2;
	if (left < n && compare(que[left], que[max])) max = left;
	if (right < n && compare(que[right], que[max])) max = right;
	if (max != i) {
		swap(que[i], que[max]);
		heapify(n, max);
	}
}
template<typename T>
void Priority_que<T>::heapify_down_to_up(int n) {
	int s = n - 1, f = (s - 1) / 2;
	while (f >= 0 && compare(que[s], que[f]))
	{
		swap(que[f], que[s]);
		s = f;
		f = (s - 1) / 2;
	}
}
int testmain() {
	Priority_que<int> que;
	srand(time(0));
	vector<int> cur;
	for (int i = 0; i < 10; ++i) {
		const int tmp = rand() % 20;
		que.push(tmp);
		cout << tmp << " ";
		cur.push_back(que.front());
	}
	cout << endl;
	for (auto& c : cur) {
		cout << c << " ";
	}
	cout << endl;
	while (!que.empty())
	{
		cout << que.front() << " ";
		que.pop();
	}
	return 0;
}
int main() {
	int n = 10;
	while (n--)
	{
		testmain();
		cout << endl;
		cout << "=========" << endl;
	}
}
