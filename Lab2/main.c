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
void calculate_pagerank(Graph* G, int iterations) {
	double* PR = malloc(sizeof(double) * G->V);
	double* sums = malloc(sizeof(double) * G->V);
	int* out_degrees = malloc(sizeof(int) * G->V);

	for (int v = 0; v < G->V; v++) {
		PR[v] = 1.0;
		out_degrees[v] = 0;
	}

	for (int v = 0; v < G->V; v++) {
		EdgeNodePtr current = G->edges[v].head;

		while (current != NULL) {
			out_degrees[v]++;
			current = current->next;
		}
	}

	double d = 0.85;

	for (int i = 0; i < iterations; i++) {

		for (int v = 0; v < G->V; v++) {
			sums[v] = 0.0;
		}

		for (int from = 0; from < G->V; from++) {

			EdgeNodePtr current = G->edges[from].head;

			while (current != NULL) {

				int to = current->edge.to_vertex;

				if (out_degrees[from] > 0) {
					sums[to] += PR[from] / out_degrees[from];
				}

				current = current->next;
			}
		}

		for (int v = 0; v < G->V; v++) {
			PR[v] = (1 - d) + d * sums[v];
		}
	}

	for (int v = 0; v < G->V; v++) {
		printf("Vertex %d: %.4f\n", v, PR[v]);
	}

	free(PR);
	free(sums);
	free(out_degrees);
}

int main() {
	Graph G;
	int from, to, weight;

	FILE* file = fopen("pagerank_test.txt", "r");
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
	calculate_pagerank(&G, 20);
	return 0;
}