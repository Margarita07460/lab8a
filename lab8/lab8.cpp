#define _CRT_SECURE_NO_WARNINGS

#include <cstdio>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <locale.h>
#include <queue>



using namespace std;
queue<int>Q;
vector<bool> vis;

struct Node {
	int inf; // Информационное поле (название объекта)
	Node* next; // Указатель на следующий элемент в очереди
};


void queue_BFS(int s,vector<vector<int>> G) {
	clock_t start = clock();
	vector<bool> vis(G.size(), 0);
	// Инициализация указателей на головы и хвосты как NULL

	Node* heads = NULL;
	Node* lasts = NULL;

	Node* newItem = new Node;
	newItem->inf = s;
	newItem->next = 0;
	heads = lasts = newItem;

	while (heads != 0) {
		s = heads->inf;
		if (!vis[s]) {
			printf("->%d  ", s);
			vis[s] = 1;
			for (int i = 0; i < G.size(); i++) {
				if (G[s][i] == 1 and !vis[i]) {
					Node* newItem = new Node;
					newItem->inf = i;
					newItem->next = 0;

					if (lasts == 0) {
						heads = lasts = newItem;
					}
					else {
						lasts->next = newItem;
						lasts = newItem;
					}

				}

			}

		}
		Node* temp = heads;
		heads = heads->next;
		delete temp;
		
		
	}
	clock_t end = clock();
	printf("\n\n");
	printf("Время работы алгоритма:\n");
	printf("%f\n", (double)(end - start) / CLOCKS_PER_SEC);
}


void BFS(int s,vector<vector<int>> G) {
	clock_t start = clock();
	vector<bool> vis(G.size(), 0);
	vis[s] = 1;
	Q.push(s);
	while (!Q.empty()) {
		s = Q.front();
		Q.pop();
		printf("->%d  ", s);
		for (int i = 1; i < G.size(); i++) {

			if (G[s][i] == 1 and vis[i] != 1) {
				Q.push(i);
				vis[i] = 1;



			}


		}

	}
	clock_t end = clock();
	printf("\n\n");
	printf("Время работы алгоритма:\n");
	printf("%f\n", (double)(end - start) / CLOCKS_PER_SEC);
	printf("\n");
}



void list_BFS(int s, vector < vector < int>>adjacency_list) {
	vector<bool> vis(adjacency_list.size(), 0);
	vis[s] = 1;
	Q.push(s);
	while (!Q.empty()) {
		s = Q.front();
		Q.pop();
		printf("->%d  ", s);
		s + 1;
		for (int neighbor : adjacency_list[s]) {    //добавляем всех непосещённых соседей.
			if (vis[neighbor]!=1) {
				Q.push(neighbor);
				vis[neighbor] = 1;
			}

		}
	}printf("\n\n");


}





vector<vector<int>> list_cmej(vector<vector<int>> G) {
	int num_vertices = G.size()-1;
	vector<vector<int>> adjacency_list(num_vertices+1);
	for (int i = 1; i <= num_vertices; ++i) {
		for (int j = 1; j <= num_vertices; ++j) {
			if (G[i][j] == 1) {
				adjacency_list[i].push_back(j);
			}
		}
	}
	return adjacency_list;
}

void printList(vector<vector<int>>list) {
	//printf("Список смежности:\n");
	for (int i = 1; i < list.size(); ++i) {
		printf("%d: ", i);
		for (int j : list[i]) {
			printf("%d ", j);
		}
		printf("\n");
	}
}


int swt = 0;
vector<vector<int>> cmej_mat(int num_vertices, double veroj) {
	vector<vector<int>> cmej_mat(num_vertices + 1, vector<int>(num_vertices + 1, 0));
	int cont = 0;
	for (int i = 1; i <= num_vertices; ++i) {
		for (int j = i + 1; j <= num_vertices; ++j) {
			if (static_cast<double>(rand()) / RAND_MAX < veroj) {
				cmej_mat[i][j] = 1;
				cmej_mat[j][i] = 1;
				cont++;
			}
		}
	}

	if (cont == 0) {
		swt = 1;
	}
	printf("Матрица смежности:\n");
	for (int i = 1; i <= num_vertices; ++i) {
		for (int j = 1; j <= num_vertices; ++j) {
			printf("%d ", cmej_mat[i][j]);
		}
		printf("\n");
	}
	printf("\n");
	return cmej_mat;
}




int main() {
	setlocale(LC_ALL, "RUS");
	int num_vertices;
	double veroj = 0.5;
	int s;
	printf("Введите количество вершин: ");
	scanf("%d", &num_vertices);
	printf("Введите номер вершины, с которой хотите начать обход ");
	scanf("%d", &s);
	srand(static_cast<unsigned int>(time(0)));
	auto G = cmej_mat(num_vertices, veroj);
	auto list = list_cmej(G);
	if (swt == 1) {
		printf("\nОбход произвести нельзя! Первая вершина изолированна\n");
	}
	else {
		printf("------------------------\n");
		printf("обход матрицы в ширину:\n");
		printf("------------------------\n");
		BFS(s, G);
		printf("-----------------\n");
		printf("список смежности\n");
		printf("-----------------\n");
		printList(list);
		printf("----------------------------------\n");
		printf("Обход в ширину (список смежности):\n");
		printf("----------------------------------\n");
		list_BFS(s, list);
		printf("---------------------------------------------\n");
		printf("Обход в ширину с помощью собственной очереди:\n");
		printf("---------------------------------------------\n");
		queue_BFS(s, G);
		
	}

	return 0;


}
