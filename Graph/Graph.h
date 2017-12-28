#pragma once
#define INFINITE '*'
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <stack>
#include <queue>
#include <fstream>

using namespace std;

/*图的邻接矩阵存储*/
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
		
		cout << "\t\t - - - 用邻接矩阵创建图 - - -\n";
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
		in.close();
		cin.rdbuf(default_in);
	}
	~AMGraph() {
		for (int i = 0; i < vertexNums; i++) {
			delete[] AdjcencyMatrix[i];
		}
		delete[] AdjcencyMatrix;
		vertexes = nullptr;
		AdjcencyMatrix = nullptr;
	}
	void printAM() {
		for (int i = 0; i < vertexNums; i++) {
			for (int j = 0; j < vertexNums; j++) {
				cout << AdjcencyMatrix[i][j] << "   ";
			}
			cout << endl;
		}
	}
	/*
		AM_DFS Pseudocode:
			START
			prepare a stack to store node: s,
					a boolean array to mark one vertex has been visited: visited,
					a counter to count how many vertexes have been visited: count,
					a curRoot:inited to be root
			while count < vertexNums   --> MainLoop
				do visit curRoot
				   s push curRoot
				   mark it have been visited
				   counter + 1
				   while !s.empty
						search s.top's first unvisited AdjacentVertex(FUAV)
						if search success
							then
								visite curRoot's FUAV
								mark FUAV have been visited
								count + 1
								s push FUAV
							else
								s.pop
				  if count < vertexNums
						curRoot = first unvisited vertex
						goto MainLoop
			END
	*/

	void DFSTraversal() {
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
			//当栈为空时,可能存在某些还未访问过的节点(比如非连通图)
			if (count < vertexNums) {
				for (int i = 0; i < vertexNums; i++) {
					if (visited[i] == false) {
						curRoot = vertexes[i];
						break;
					}
				}
			}
		}
		delete[] visited;
	}
	void BFSTraversal() {
		queue<string> q;
		bool* visited = new bool[vertexNums];
		for (int i = 0; i < vertexNums; i++) {
			visited[i] = false;
		}
		int count = 0;
		string curRoot = root;
		while (count < vertexNums) {
			q.push(curRoot);
			visited[locate(curRoot)] = true;
			count++;
			cout << curRoot << " ";
			while (!q.empty()) {
				int row = locate(q.front());
				q.pop();
				int col = 0;
				for (; col < vertexNums; col++) {
					if (AdjcencyMatrix[row][col] == '1' && !visited[col]) {
						cout << vertexes[col] << " ";
						visited[col] = true;
						count++;
						q.push(vertexes[col]);
					}
				}
			}
			//当队列为空时,可能还存在未被访问的节点(比如非连通图)
			if (count < vertexNums) {
				for (int i = 0; i < vertexNums; i++) {
					if (visited[i] == false) {
						curRoot = vertexes[i];
						break;
					}
				}
			}
		}
		delete[] visited;
	}
	void setRoot(string root) {
		this->root = root;
	}
public:
	size_t vertexNums;
private:
	char **AdjcencyMatrix;
	string* vertexes;
	string root;
private:
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
		for (int ret = 0; ret < vertexNums; ret++) {
			if (vertexes[ret] == vertex)
				return ret;
		}
		return -1;
	}
};

/*边表节点*/
class edge_node {
public:
	edge_node(size_t index,edge_node* next = nullptr) {
		this->adjvex_pos = index;
		this->next = next;
	}
	size_t adjvex_pos;
	edge_node* next;
};
/*顶点*/
class Vertex {
public:
	string data;
	edge_node * next;
	Vertex(string data, edge_node* next = nullptr) {
		this->data = data;
		this->next = next;
	}
};
/*图的邻接表存储*/
class ALGraph {
public:
	ALGraph(Vertex vertexes[], int nums) {
		//init
		this->vertexes = vertexes;
		this->vertexNums = nums;
		//create
		streambuf* default_in = cin.rdbuf();
		ifstream in("data.txt");
		cin.rdbuf(in.rdbuf());

		cout << "\t\t - - - 用邻接表创建图 - - -\n";
		cout << "结点:";
		for (int i = 0; i < nums; i++) {
			cout << vertexes[i].data << "  ";
		}
		cout << endl;
		for (int i = 0; i < nums; i++) {
			string line;
			cout << "输入节点 " << vertexes[i].data << " 的邻接节点(节点间请用空格隔开):";
			getline(cin, line);
			cout << line << endl;
			if (line == "null" || line.empty()) {
				continue;
			}
			//build List for vertexes[i]
			vector<string> vs = splitString(line, ' ');
			vertexes[i].next = new edge_node(locate(vs[0]));
			edge_node* rear = vertexes[i].next;
			for (int i = 1; i < vs.size(); i++) {
				rear->next = new edge_node(locate(vs[i]));
				rear = rear->next;
			}
		}
		in.close();
		cin.rdbuf(default_in);
	}
	~ALGraph() {
		edge_node* n;
		edge_node* tmp;
		for (int i = 0; i < vertexNums; i++) {
			n = vertexes[i].next;
			while (n) {
				tmp = n;
				n = n->next;
				delete tmp;
			}
		}
		vertexes = nullptr;
		vertexNums = 0;
	}
	void BFSTraversal() {
		bool* visited = new bool[vertexNums];
		edge_node* n(nullptr);
		for (int i = 0; i < vertexNums; i++) {
			visited[i] = false;
		}
		for (int i = 0; i < vertexNums; i++) {
			if (!visited[i]) {
				cout << vertexes[i].data << " ";
				visited[i] = true;
			}
			n = vertexes[i].next;
			while (n) {
				if (!visited[n->adjvex_pos]) {
					cout << vertexes[n->adjvex_pos].data << " ";
					visited[n->adjvex_pos] = true;
				}
				n = n->next;
			}
		}
	}

	/*
		AL_DFS Pseudocode:
		   START
			prepare a boolean array make one vertex has been visited: visited
					a edge_node pointer : n
					a loopIndex : i
			for i < vertexNums   --> MainLoop
				if Vetex[i] hasn't been visited
					then visit Vertex[i]
						 mark it visited
					else
						 n = Vertex[i]'s first edge_node
						 while n exsits
							while n exists && !visited[n->adjvex_pos]
								visit Vertex[n->adjcex_pos]
								mark visited
								n = Vertex[n->adjvex_pos]
							if n exists
								then n = n->next
								goto MainLoop
		  END					
	*/

	void DFSTraversal() {
		bool* visited = new bool[vertexNums];
		edge_node* n(nullptr);
		for (int i = 0; i < vertexNums; i++) {
			visited[i] = false;
		}
		for (int i = 0; i < vertexNums; i++) {
			if (!visited[i]) {
				cout << vertexes[i].data << " ";
				visited[i] = true;
			}
			n = vertexes[i].next;
			while (n) {
				while (n && !visited[n->adjvex_pos]) {
					cout << vertexes[n->adjvex_pos].data << " ";
					visited[n->adjvex_pos] = true;
					n = vertexes[n->adjvex_pos].next;
				}
				if(n) n = n->next;
			}
		}
	}
	void printAL() {
		cout << "邻接表如下:\n";
		edge_node* next;
		for (int i = 0; i < vertexNums; i++) {
			cout << vertexes[i].data << ": ";
			next = vertexes[i].next;
			while (next) {
				cout << next->adjvex_pos << "  ";
				next = next->next;
			}
			cout << endl;
		}
	}
	size_t vertexNums;
private:
	Vertex * vertexes;
private:
	vector<string> splitString(string str, char delimiter) {
		string tmp{};
		vector<string> ret;
		size_t start = 0;
		size_t end = str.find(delimiter, 0);
		while (end != string::npos) {
			ret.push_back(str.substr(start, end - start));
			start = end + 1;
			end = str.find(delimiter, start);
		}
		if (start != str.length())
			ret.push_back(str.substr(start));
		return ret;
	}
	int locate(string vex) {
		for (int ret = 0; ret < vertexNums;ret++) {
			if (vertexes[ret].data == vex)
				return ret;
		}
		return -1;
	}
};