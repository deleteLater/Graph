// Graph.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Graph.h"
#include <string>

using std::string;

int main()
{
	//顶点数组
	string vertexes[] = {"V1","V2","V3","V4","V5","V6","V7","V8"};
	int nums = sizeof(vertexes) / sizeof(*vertexes);
	AMGraph g(vertexes, nums);
	cout << "\nBFSTraversal:";
	g.BFSTraversal();
	cout << "\nDFSTraversal:";
	g.DFSTraversal();
	cout << endl << endl;
	system("pause");
    return 0;
}

