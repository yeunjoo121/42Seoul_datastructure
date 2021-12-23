#include "arrayheap.c"
#include "../graph/arraygraph.c"
#define NODE_COUNT 5

ArrayGraph *prim(ArrayGraph *graph, int startnode)
{
	ArrayGraph *MST = createArrayGraph(6);

	ArrayHeap *MinHeap = createHeap(100);
	int node = startnode;

	while (1)
	{
        addVertexAG(MST, node);
		if (MST->currentVertexCount == NODE_COUNT)//노드가 n개이면 edge가 n-1개이면 MST충족///바꿈
		{
			break;
		}
		//startnode에 연결된 edge들을 heap에 넣기, minheap
		for(int i = 0; i < NODE_COUNT; i++)//node와 연결된 edge들을 heap에 넣음
		{
			if (graph->ppAdjEdge[node][i] != 0 && MST->pVertex[i] == NOT_USED)//edge가 있는거니까 heap에 넣기
			{//weigt from to
				HeapNode tmp = {graph->ppAdjEdge[node][i], node, i};
				insertMinHeapNode(MinHeap, tmp);
			}
		}
		HeapNode *minEdge = deleteMinHeapNode(MinHeap);
        
        if (MST->pVertex[minEdge->toVertex] == NOT_USED)
        {
            addEdgewithWeightAG(MST, minEdge->fromVertex, minEdge->toVertex, minEdge->weight);
        }
        node = minEdge->toVertex;
        free(minEdge);
	}
    deleteArrayHeap(MinHeap);
	return (MST);
}

// MST
// node 0: heap: 3 4   -> heap: 4
// node 2: heap: 1 2 4 -> heap: 2 4
// node 3: heap: 1 2 4 5 -> heap: 2 4 5
// node 4: heap: 2 4 5 6 -> heap: 4 5 6
// node 1: heap: 

void test()
{
	//원래 있던 그래프와 MST그래프.
	//원래 그래프 만들기
	ArrayGraph *Graph = createArrayGraph(6);
	//여기서 노드 추가.
	for(int i = 0; i < NODE_COUNT; i++)
	{
		addVertexAG(Graph, i);
	}
	//여기서 엣지 추가.
	addEdgewithWeightAG(Graph, 0, 1, 3);
	addEdgewithWeightAG(Graph, 0, 3, 15);
	addEdgewithWeightAG(Graph, 0, 2, 3);
	addEdgewithWeightAG(Graph, 1, 2, 3);
	addEdgewithWeightAG(Graph, 1, 4, 9);
	addEdgewithWeightAG(Graph, 2, 3, 26);
	addEdgewithWeightAG(Graph, 2, 4, 6);
	addEdgewithWeightAG(Graph, 3, 4, 7);

	ArrayGraph *MST = prim(Graph, 0);//prim함수에서 원래 그래프를 받아 edge를 추가. MST반환

	displayArrayGraph(MST);//for문 돌려서 array 출력하게.
    deleteArrayGraph(Graph);
    deleteArrayGraph(MST);
}

int main(void)
{
    test();
    system("leaks a.out");
}
