// Graph.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Graph.h"
#include <string>

using std::string;

int main()
{
	//顶点数组
	string vertexes[] = {"V0","V1","V2","V3","V4" ,"V5"};
	int nums = sizeof(vertexes) / sizeof(*vertexes);
	AMGraph g(vertexes, nums);

	system("pause");
    return 0;
}

