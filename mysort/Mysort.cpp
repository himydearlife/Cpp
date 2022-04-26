#include <iostream>
#include <vector>
#include <ctime>
#include <time.h> 
#include <stdio.h> 
#include <string>
#include <unordered_map> //Used to provide hash tables
#include <iomanip>  // Used to support setf() 
#include <algorithm>
#include <cmath>
#include <unistd.h>


using namespace std;


template<typename T> class MysortCell;
class Mysort;


class Fault {
private:
	int flag;
public:
	Fault(int flag) : flag(flag) {}
	void what();
};
void Fault::what() {
	switch (flag)
	{
	case 0:
		cout << "First Parameter n must be positive integer" << endl;
		break;
	case 1:
		cout << "Please choose the right sort mode" << endl;
		break;
	case 2:
		cout << "Second Parameter must be chosen from random|up|down|constant" << endl;
		break;
	case 3:
		cout << "-i and -m cannot appear at the same time" << endl;
		break;
	case 4:
		cout << "Wrong Switch, use only one of -o|-c|-t|-m|-i" << endl;
		break;
	case 5:
		cout << "mysort n Direction [ -o ] [ -c ] [ -t ] [ -m | -i ]" << endl;
		break;
	case 6:
		cout << "no input Direction parameter" << endl;
	default:
		cout << "Unknow error" << endl;
		break;
	}
}


template<typename T>
class MysortCell {
private:
	char mode; 	
public:
	MysortCell() {}

	void fun(vector<T>& nums) {
		if (mode == 'i') InsertionSort(nums);
		else MergeSort(nums);
	}
	void set_mode(char mode) {
		this->mode = mode;
	}
	bool IsSortedAndNothingIsLost(vector <T> & Before, vector <T> & After); 	
	void InsertionSort(vector<T> & a);
	void MergeSort(vector<T> & a);
	void MergeSortCell(int left, int right, vector<T> & a, vector<T> & tmp); 	
};
template <typename T>
bool MysortCell<T>::IsSortedAndNothingIsLost(vector <T>& Before, vector <T>& After) {
	int b_n = Before.size(), a_n = After.size();
	if (b_n != a_n) return false;
	unordered_map<double, int> cnt;
	for (int i = 0; i < b_n; ++i) {
		++cnt[Before[i]];
		--cnt[After[i]];
	}
	for (auto it = cnt.begin(); it != cnt.end(); ++it) {
		if (it->second != 0) return false;
	}
	return true;
}
template <typename T>
void MysortCell<T>::InsertionSort(vector<T> & a) {
	int n = a.size();
	if (n < 2) return;
	for (int i = 1; i < n; ++i) {
		if (a[i] < a[i - 1]) {
			T key = a[i];
			int j = i - 1;
			while (j >= 0 && a[j] > key) {
				a[j + 1] = a[j];
				--j;
			}
			a[j + 1] = key;
		}
	}
}
template <typename T>
void MysortCell<T>::MergeSort(vector<T> & a) {
	int n = a.size();
	if (n < 2) return;
	vector<T> tmp(n, 0);
	MergeSortCell(0, n - 1, a, tmp);
}
template <typename T>
void MysortCell<T>::MergeSortCell(int left, int right, vector<T> & nums, vector<T> & tmp) {
	if (left >= right) return;
	int mid = left + (right - left) / 2;
	int s1 = left, e1 = mid, s2 = mid + 1, e2 = right;
	MergeSortCell(s1, e1, nums, tmp);
	MergeSortCell(s2, e2, nums, tmp);
	int index = left;
	while (s1 <= e1 && s2 <= e2) {
		tmp[index++] = nums[s1] < nums[s2] ? nums[s1++] : nums[s2++];
	}
	while (s1 <= e1) {
		tmp[index++] = nums[s1++];
	}
	while (s2 <= e2) {
		tmp[index++] = nums[s2++];
	}
	for (index = left; index <= right; ++index) {
		nums[index] = tmp[index];
	}
}


class Mysort {
private:
	time_t cost_time; 
	char mode;
	vector<double> ori_nums;
	vector<double> cur_nums;
	string Selection;
	size_t my_n;
	MysortCell<double> cell;
public:
	Mysort(char mode, string Selection, size_t n) : mode(mode), Selection(Selection), my_n(n) {
		cell.set_mode(mode);
	}
	void forward(); // 
	vector<double> GenerateNumbers(string Selection, size_t n);
	void Show_nums();
	void Show_time();
	void Show_bool() {
		if (cell.IsSortedAndNothingIsLost(ori_nums, cur_nums)) cout << "Success" << endl;
		else cout << "Sorting error" << endl;
	}
};
void Mysort::forward() {
	ori_nums = GenerateNumbers(Selection, my_n);
}
vector<double> Mysort::GenerateNumbers(string Selection, size_t n) {

	long long N = pow(10, 12) - 1;
	time_t start, end;
	time(&start);
	vector<double> res;
	if (Selection == "constant") {
		double per_val = rand() % (N + 1) / (double)(N + 1);
		res = vector<double>(n, per_val);
		cur_nums = res;
		time(&end);
		this->cost_time = end - start;
		return res;
	}
	res = vector<double>(n, 0);
	for (auto& num : res) {
		num = rand() % (N + 1) / (double)(N + 1);
	}
	auto tmp = res;
	if (Selection == "up" || Selection == "random") {
		cell.fun(tmp);
	}
	else {
		cell.fun(tmp);
		reverse(tmp.begin(), tmp.end());
	}
	cur_nums = tmp;
	time(&end);
	this->cost_time = end - start;
	return res;
}
void Mysort::Show_nums() {
	int n = ori_nums.size();
	for (int i = 0; i < n; ++i) {
		cout << fixed << setprecision(12) << this->ori_nums[i] << " " << this->cur_nums[i] << endl;
	}
}
void Mysort::Show_time() {
	cout.precision(8);
	cout.setf(ios_base::scientific, ios_base::floatfield);
	cout << "--- It took " << (double) this->cost_time << " seconds to compute-- - " << endl;
}

int main(int argc, char* argv[]) {
	srand(time(0));
	try{
		if (argc == 2) throw(Fault(4));
		if (argc == 3) throw(Fault(5));
	string tmp_str; istringstream(argv[2]) >> tmp_str;
	auto str2int = [](string& str)->int {
		int res = 0;
		bool flag = true;
		for (auto& ch : str) {
			res *= 10;
			if (ch == '-') flag = false;
			else res += ch - '0';
		}
		return flag ? res : -res;
	};
	int tmp = str2int(tmp_str);

	if (tmp <= 0) throw(Fault(0));
	size_t n = (size_t) tmp;
	string Selection; istringstream(argv[3]) >> Selection;
	//random|up|down|constant
	if (Selection != "random" && Selection != "up" && Selection != "down" && Selection != "constant") throw(Fault(2));
	bool flag_o = false, flag_c = false, flag_t = false, flag_m = false, flag_i = false;
	for (int i = 4; i < argc; ++i) {
		string operation_str; istringstream(argv[i]) >> operation_str;
		if (operation_str.size() != 2) throw(Fault(4));
		if (operation_str[1] == 'o') flag_o = true;
		else if (operation_str[1] == 'c') flag_c = true;
		else if (operation_str[1] == 't') flag_t = true;
		else if (operation_str[1] == 'm') flag_m = true;
		else if (operation_str[1] == 'i') flag_i = true;
		else throw(Fault(4));
	}
	if (flag_i && flag_m) throw(Fault(3));
	char mode = 'i';
	if (flag_m) mode = 'm';
	Mysort mysort(mode, Selection, n);
	mysort.forward();
	if (flag_c) mysort.Show_bool();
	if (flag_o) mysort.Show_nums();
	if (flag_t) mysort.Show_time();
	}
	catch(Fault& f){
		f.what();
	}
	return 0;
}
