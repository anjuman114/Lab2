#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

void add_edge(Graph* self, int from, int to, int w) {
	EdgeNodePtr new_node = malloc(sizeof(struct edgeNode));

	new_node->edge.to_vertex = to;
	new_node->edge.weight = w;

	new_node->next = self->edges[from].head;
	self->edges[from].head = new_node;
}

int main() {
	Graph G;
	int from, to, weight;

	FILE* file = fopen("C:\\Users\\miman\\source\\repos\\Lab2\\x64\\Debug\\musae_git_edges.csv", "r");
	if (file == NULL) {
		printf("Error opening file!\n");
		return 0;
	}

	fscanf(file, "%d", &G.V);

	G.edges = malloc(sizeof(EdgeList) * G.V);

	for (int v = 0; v < G.V; v++) {
		G.edges[v].head = NULL;
	}

	while (fscanf(file, "%d,%d", &from, &to) == 2) {
		add_edge(&G, from, to, 0);
	}


	fclose(file);
	int* in_degrees = malloc(sizeof(int) * G.V);

	for (int v = 0; v < G.V; v++) {
		in_degrees[v] = 0;
	}

	for (int v = 0; v < G.V; v++) {
		EdgeNodePtr current = G.edges[v].head;

		while (current != NULL) {
			int to = current->edge.to_vertex;
			in_degrees[to]++;
			current = current->next;
		}
	}

	for (int v = 0; v < G.V; v++) {
		printf("Vertex %d: %d\n", v, in_degrees[v]);
	}

	return 0;
}