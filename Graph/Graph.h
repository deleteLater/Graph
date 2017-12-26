#pragma once
#define INFINITE '*'
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <stack>
#include <fstream>

using namespace std;

class AMGraph {
public:
	AMGraph(string vertexes[],int nums) {
		//init
		this->vertexNums = nums;
		this->vertexes = vertexes;
		root = vertexes[0];
		AdjcencyMatrix = new char*[vertexNums];
		for (size_t i = 0; i < vertexNums; i++) {
			AdjcencyMatrix[i] = new char[vertexNums];
		}
		for (int i = 0; i < vertexNums; i++) {
			for (int j = 0; j < vertexNums; j++) {
				AdjcencyMatrix[i][j] = INFINITE;
			}
		}
		//create
		streambuf* default_in = cin.rdbuf();
		ifstream in("data.txt");
		cin.rdbuf(in.rdbuf());
		
		cout << "\t\t - - - 创建图 - - -\n";
		cout << "结点:";
		for (int i = 0; i < nums; i++) {
			cout << vertexes[i] << "  ";
		}
		cout << endl;
		for (int i = 0; i < nums; i++) {
			string line;
			int row = locate(vertexes[i]);
			cout << "输入节点 " << vertexes[i] <<" 的邻接节点(节点间请用空格隔开):";
			getline(cin,line);
			cout << line <<endl;
			if (line == "null" || line.empty()) {
				continue;
			}
			vector<string> strs = splitString(line,' ');
			for (string vertex : strs) {
				int col = locate(vertex);
				AdjcencyMatrix[row][col] = '1';
			}
		}
		cout << "邻接矩阵如下:\n";
		printAM();
		cin.rdbuf(default_in);
	}
	~AMGraph() {
		for (int i = 0; i < vertexNums; i++) {
			delete[] AdjcencyMatrix[i];
		}
		delete[] AdjcencyMatrix;
	}
	void printAM() {
		for (int i = 0; i < vertexNums; i++) {
			for (int j = 0; j < vertexNums; j++) {
				cout << AdjcencyMatrix[i][j] << "   ";
			}
			cout << endl;
		}
	}
	void BFSTraversal() {
		stack<string> s;
		bool* visited = new bool[vertexNums];
		for (int i = 0; i < vertexNums; i++) {
			visited[i] = false;
		}
		int count = 0;	//访问的节点个数
		string curRoot = root;
		while (count < vertexNums) {
			cout << curRoot << " ";
			s.push(curRoot);
			visited[locate(curRoot)] = true;
			count++;
			while (!s.empty()) {
				int row = locate(s.top());
				int col = 0;
				for (; col < vertexNums; col++) {
					if (AdjcencyMatrix[row][col] == '1' && !visited[col]) {
						cout << vertexes[col] << " ";
						visited[col] = true;
						count++;
						s.push(vertexes[col]);
						break;
					}
				}
				if (col == vertexNums) {
					s.pop();
				}
			}
			//当栈为空时,可能存在某些还未访问过的节点
			if (count < vertexNums) {
				for (int i = 0; i < vertexNums; i++) {
					if (visited[i] == false) {
						curRoot = vertexes[i];
					}
				}
			}
		}
		delete[] visited;
	}
	void DFSTraversal() {

	}
	void setRoot(string root) {
		this->root = root;
	}
public:
	size_t vertexNums;
	size_t edgeNums;
private:
	char **AdjcencyMatrix;
	string* vertexes;
	string root;
	vector<string> splitString(string str, char delimiter) {
		string tmp{};
		vector<string> ret;
		size_t start = 0;
		size_t end = str.find(delimiter,0);
		while (end != string::npos) {
			ret.push_back(str.substr(start, end-start));
			start = end + 1;
			end = str.find(delimiter, start);
		}
		
		if (start != str.length())
			ret.push_back(str.substr(start));
		return ret;
	}
	int locate(string vertex) {
		int ret = -1;
		for (int i = 0; i < vertexNums; i++) {
			if (vertexes[++ret] == vertex)
				return ret;
		}
		return ret;
	}
};