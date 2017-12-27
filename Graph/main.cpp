// Graph.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Graph.h"
#include <string>

using std::string;

int main()
{
	//邻接矩阵 顶点数组
	//string vertexes[] = {"V1","V2","V3","V4","V5","V6","V7","V8"};
	//int nums = sizeof(vertexes) / sizeof(*vertexes);
	//AMGraph g(vertexes, nums);
	//cout << "\nBFSTraversal:";
	//g.BFSTraversal();
	//cout << "\nDFSTraversal:";
	//g.DFSTraversal();
	//cout << endl << endl;
	//system("pause");

	//邻接表 顶点数组
	Vertex v1("v1");
	Vertex v2("v2");
	Vertex v3("v3");
	Vertex v4("v4");
	Vertex v5("v5");
	Vertex v6("v6");
	Vertex v7("v7");
	Vertex v8("v8");
	Vertex vertexes[] = {v1,v2,v3,v4,v5,v6,v7,v8};

	ALGraph g(vertexes, 8);
	cout << endl;
	g.printAL();
	cout << endl;
	//g.BFSTraversal();
	g.DFSTraversal();

	system("pause");
    return 0;
}

