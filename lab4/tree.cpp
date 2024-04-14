#include "tree.h"
#include <random>
#include <chrono>

void average_filling(size_t size) {
	double result_set = 0.0;
	double result_vec = 0.0;
	for (size_t i = 0; i < 100; i++)
	{
		mt19937 gen(i);
		uniform_int_distribution<> distrib(-2000000, 2000000);
		MySet set;
		vector<int> vec;
		auto start_set = chrono::high_resolution_clock::now();
		for (size_t i = 0; i < size; i++)
		{
			set.insert(distrib(gen));
		}
		auto end_set = chrono::high_resolution_clock::now();
		auto start_vec = chrono::high_resolution_clock::now();
		for (size_t i = 0; i < size; i++)
		{
			vec.push_back(distrib(gen));
		}
		auto end_vec = chrono::high_resolution_clock::now();
		double seconds_set = chrono::duration<double>(end_set - start_set).count();
		double seconds_vec = chrono::duration<double>(end_vec - start_vec).count();
		result_set += seconds_set / 100;
		result_vec += seconds_vec / 100;
	}
	cout << "SET Average(100) filling time with " << size << " items: " << result_set << endl;
	cout << "VEC Average(100) filling time with " << size << " items: " << result_vec << endl;
}

void average_finding(size_t size) {
	double result_set = 0.0;
	double result_vec = 0.0;
	MySet set;
	vector<int> vec;
	mt19937 gen(30);
	uniform_int_distribution<> distrib(-2000000, 2000000);
	for (size_t i = 0; i < size; i++)
	{
		auto t = distrib(gen);
		set.insert(t);
		vec.push_back(t);
	}
	for (size_t i = 0; i < 1000; i++)
	{
		auto t = distrib(gen);
		auto start_set = chrono::high_resolution_clock::now();
		set.contains(t);
		auto end_set = chrono::high_resolution_clock::now();
		auto start_vec = chrono::high_resolution_clock::now();
		find(vec.begin(), vec.end(), t);
		auto end_vec = chrono::high_resolution_clock::now();
		double seconds_set = chrono::duration<double>(end_set - start_set).count();
		double seconds_vec = chrono::duration<double>(end_vec - start_vec).count();
		result_set += seconds_set / 1000;
		result_vec += seconds_vec / 1000;
	}
	cout << "SET Average(1000) finding time in " << size << " items: " << result_set << endl;
	cout << "VEC Average(1000) finding time in " << size << " items: " << result_vec << endl;
}

void average_erasing(size_t size) {
	double result_set = 0.0;
	double result_vec = 0.0;
	MySet set;
	vector<int> vec;
	mt19937 gen(30);
	uniform_int_distribution<> distrib(-2000000, 2000000);
	for (size_t i = 0; i < size; i++)
	{
		auto t = distrib(gen);
		set.insert(t);
		vec.push_back(t);
	}
	for (size_t i = 0; i < 1000; i++)
	{
		bool del_set = false;
		bool del_vec = false;
		int deleted = distrib(gen);
		auto start_set = chrono::high_resolution_clock::now();
		if (set.erase(deleted)) {
			del_set = true;
		}
		auto end_set = chrono::high_resolution_clock::now();
		auto start_vec = chrono::high_resolution_clock::now();
		for (size_t i = 0; i < size; i++)
		{
			if (vec[i] == deleted) {
				vec.erase(vec.begin() + i);
				del_vec = true;
				break;
			}
		}
		auto end_vec = chrono::high_resolution_clock::now();
		if (del_set) {
			set.insert(deleted);
		}
		if (del_vec) {
			vec.push_back(deleted);
		}
		double seconds_set = chrono::duration<double>(end_set - start_set).count();
		double seconds_vec = chrono::duration<double>(end_vec - start_vec).count();
		result_set += seconds_set / 1000;
		result_vec += seconds_vec / 1000;
	}
	cout << "SET Average(1000) erasing time in " << size << " items: " << result_set << endl;
	cout << "VEC Average(1000) erasing time in " << size << " items: " << result_vec << endl;
}

void average_insertion(size_t size) {
	double result_set = 0.0;
	double result_vec = 0.0;
	MySet set;
	vector<int> vec;
	mt19937 gen(30);
	uniform_int_distribution<> distrib(-2000000, 2000000);
	for (size_t i = 0; i < size; i++)
	{
		auto t = distrib(gen);
		set.insert(t);
		vec.push_back(t);
	}
	for (size_t i = 0; i < 1000; i++)
	{
		bool ins_set = false;
		bool ins_vec = false;
		int inserted = distrib(gen);
		auto start_set = chrono::high_resolution_clock::now();
		if (set.insert(inserted)) {
			ins_set = true;
		}
		auto end_set = chrono::high_resolution_clock::now();
		auto start_vec = chrono::high_resolution_clock::now();
		vec.push_back(inserted);
		auto end_vec = chrono::high_resolution_clock::now();
		if (ins_set) {
			set.erase(inserted);
		}
		vec.pop_back();
		double seconds_set = chrono::duration<double>(end_set - start_set).count();
		double seconds_vec = chrono::duration<double>(end_vec - start_vec).count();
		result_set += seconds_set / 1000;
		result_vec += seconds_vec / 1000;
	}
	cout << "SET Average(1000) insertion time in " << size << " items: " << result_set << endl;
	cout << "VEC Average(1000) insertion time in " << size << " items: " << result_vec << endl;
}

int main() {
	average_filling(1000);
	average_filling(10000);
	average_filling(100000);

	average_finding(1000);
	average_finding(10000);
	average_finding(100000);

	average_erasing(1000);
	average_erasing(10000);
	average_erasing(100000);

	average_insertion(1000);
	average_insertion(10000);
	average_insertion(100000);
}
