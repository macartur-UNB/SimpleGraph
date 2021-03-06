#include "graph.h"
#include <queue>
#include <stack>
#include <iostream>

const int Graph::VERTEX_ALREADY_IN_GRAPH = -1;
const int Graph::VERTEX_INSERTED_ON_GRAPH = 0;
const int Graph::EDGE_INSERTED_ON_GRAPH = 0;
const int Graph::VERTEX_NOT_FOUND = -1;
const int Graph::VERTEX_FOUND = 0;

std::ostream& operator<<(std::ostream& os, Graph* graph)
{
	if(!graph)
		return os;

	os<<std::endl;
	os<<"Printing graph structure..."<<std::endl;

	std::map<int, Vertex*>::iterator it;
	std::map<int, int>::iterator itEdge;

	for(it = graph->vertexMap.begin(); it != graph->vertexMap.end(); it++)
	{
		int vertexNumber = it->first;

		os<<"Vertex: "<<vertexNumber<<std::endl;
		Vertex *vertex = it->second;
		
		os<<"Total Edges: "<<vertex->getNumEdge()<<std::endl;

		for(itEdge = vertex->edge.begin(); itEdge != vertex->edge.end(); itEdge++)
			os<<vertexNumber<<" --> "<<itEdge->first<<", Cost = "<<itEdge->second<<std::endl;

		os<<std::endl;
	}

	return os;
}	

Graph::Graph()
{
	numVertex = 0;
}

Graph::~Graph()
{
	std::map<int, Vertex*>::iterator it;

	for(it = vertexMap.begin(); it != vertexMap.end(); it++)
		delete it->second;
}

int
Graph::getNumVertex() const
{
	return numVertex;
}

int
Graph::addVertex(int vertexNumber)
{
	std::map<int, Vertex*>::iterator it;
	it = vertexMap.find(vertexNumber);

	if(it != vertexMap.end())
		return VERTEX_ALREADY_IN_GRAPH;
	
	Vertex*  vertex = new Vertex(vertexNumber);

	vertexMap[vertexNumber] = vertex;
	numVertex++;

	return VERTEX_INSERTED_ON_GRAPH;
}

Vertex*
Graph::getVertex(int vertexNumber)
{
	std::map<int, Vertex*>::iterator it;
	it = vertexMap.find(vertexNumber);

	if(it == vertexMap.end())
		return 0;
	else
		return it->second;
}

int
Graph::addEdge(int from, int to, int cost)
{

	if(!isVertexInGraph(from))
		return VERTEX_NOT_FOUND;
	
	if(!isVertexInGraph(to))
		return VERTEX_NOT_FOUND;

	std::map<int, Vertex*>::iterator it;
	it = vertexMap.find(from);

	Vertex *vertex = it->second;

	vertex->edge[to] = cost;
	vertex->incEdgeNum();

	return EDGE_INSERTED_ON_GRAPH;
}

bool
Graph::isVertexInGraph(int vertex)
{
	std::map<int, Vertex*>::iterator it;

	it = vertexMap.find(vertex);

	return (it == vertexMap.end())?false:true;
}

int
Graph::breadthFirstSearch(int vertexNumber, int vertexToFind)
{
	if(!isVertexInGraph(vertexNumber))
		return VERTEX_NOT_FOUND;
	
	if(!isVertexInGraph(vertexToFind))
		return VERTEX_NOT_FOUND;

	int* allVertex = new int[numVertex+1];
	std::queue<int> vertexQueue;
	std::map<int, int>::iterator it;

	for(int i =0; i<=numVertex; i++)
		allVertex[i] = 0;

	allVertex[vertexNumber] = 1;

	vertexQueue.push(vertexNumber);
	std::cout<<"Breadth First Search starting from vertex: ";

	while(!vertexQueue.empty())
	{
		Vertex *vertex = vertexMap[vertexQueue.front()];
		vertexQueue.pop();
		int vertexValue = vertex->getNumber();
		std::cout<<vertexValue<<" ";

		if(vertexValue == vertexToFind)
		{
			delete [] allVertex;
			return VERTEX_FOUND;
		}	
		
		allVertex[vertexValue] = 1;
	
		for(it = vertex->edge.begin(); it != vertex->edge.end(); it++)
		{
			if(allVertex[it->first] == 0)
				vertexQueue.push(it->first);
		}
	}

	delete [] allVertex;
	return VERTEX_NOT_FOUND;
}

int
Graph::depthFirstSearch(int vertexRoot, int vertexToFind)
{
	if(!isVertexInGraph(vertexRoot))
		return VERTEX_NOT_FOUND;

	if(!isVertexInGraph(vertexToFind))
		return VERTEX_NOT_FOUND;

	std::stack<int> vertexStack;
	std::map<int, int>::reverse_iterator it;
	int* allVertex = new int[numVertex+1];

	for(int i =0; i<=numVertex; i++)
		allVertex[i] = 0;

	vertexStack.push(vertexRoot);
	allVertex[vertexRoot] = 1;

	std::cout << "Depth first Search starting from vertex: ";

	while(!vertexStack.empty())
	{
		Vertex *vertex = vertexMap[vertexStack.top()];
		vertexStack.pop();

		int vertexNumber = vertex->getNumber();
		std::cout<<vertexNumber<<" ";

		if(vertexNumber == vertexToFind)
		{
			delete [] allVertex;
			return VERTEX_FOUND;
		}	

		for(it = vertex->edge.rbegin(); it != vertex->edge.rend(); it++)
		{

			if(!allVertex[it->first])
			{
				allVertex[it->first] = 1;
				vertexStack.push(it->first);
			}
		}	

	}
	
	delete [] allVertex;
	return VERTEX_NOT_FOUND;

}
