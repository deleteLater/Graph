// Graph.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Graph.h"
#include <string>

using std::string;

int main()
{
	/*邻接矩阵 顶点数组
	string vertexes[] = {"V1","V2","V3","V4","V5","V6","V7","V8"};
	int nums = sizeof(vertexes) / sizeof(*vertexes);
	AMGraph g(vertexes, nums);
	cout << "\nBFSTraversal:";
	g.BFSTraversal();
	cout << "\nDFSTraversal:";
	g.DFSTraversal();
	cout << endl << endl;
	system("pause");*/

	//邻接表 顶点数组
	Vertex v1("V1");
	Vertex v2("V2");
	Vertex v3("V3");
	Vertex v4("V4");
	Vertex v5("V5");
	Vertex v6("V6");
	Vertex v7("V7");
	Vertex v8("V8");
	Vertex vertexes[] = {v1,v2,v3,v4,v5,v6,v7,v8};

	ALGraph g(vertexes, 8);
	cout << "\n邻接表为:\n";
	g.printAL();
	cout << "\nBFSTraversal:";
	g.BFSTraversal();
	cout << "\nDFSTraversal:";
	g.DFSTraversal();
	cout << endl << endl;
	system("pause");
    return 0;
}

