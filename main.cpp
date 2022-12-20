//ALUNOS: FULVIO STEFANINE E JOAO PEDRO
//TEORIA DOS GRAFOS - TRABALHO 2
//OUT-NOV/2022

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include<time.h>
#include <conio.h>

FILE *graph;

//FUNCAO INICIALIZA MATRIZ ZERADA
int **functionArrayNull(int **m, int v)
{
	for (int i = 0; i < v; i++)
	{
		for (int j = 0; j < v; j++)
			m[i][j] = 0;
	}
	return m;
}
//FUNCAO CRIA GRAFO
int **functionCreateGraph(int **m, int v, float d, int tagDir)
{
	int e, aux, i, j;
	if(tagDir==1){
		e = (((v * v) - v) / 2) * d*2;
	}else{
		e = (((v * v) - v) / 2) * d;
	}

	i = 0;
	j = 0;
	aux = 0;
	if (tagDir == 1)
	{
		do
		{
			if (j >= v)
			{
				j = 0;
				i++;
			}
			if (i != j)
			{
				m[i][j] = rand() % 1000 + 1;
				aux++;
			}
			j++;
		} while (aux < e);
	}
	else
	{
		do
		{
			if (j == v)
			{
				j = 0;
				i++;
			}
			if (i != j && m[j][i] == 0)
			{
				m[i][j] = rand() % 1000 + 1;
				m[j][i] = m[i][j];
				aux++;
			}
			j++;
		} while (aux < e);
	}
	return m;
}
//FUNCAO IMPRIME MATRIZ
void functionShowGraph(int **m, int v)
{
	int i, j;
	printf("\nMat");
	for (i = 0; i < v; i++)
	{
		printf("\t%d", i);
	}
	for (i = 0; i < v; i++)
	{
		printf("\n%d", i);
		for (j = 0; j < v; j++)
		{
			printf("\t%d", m[i][j]);
		}
	}
}
//FUNCAO BFS E FILA
typedef struct TypeCellR *PointerR; 
typedef struct TypeItemR { 
	int num;
} ItemR;
typedef struct TypeCellR {
	ItemR id;
	PointerR next;
}CellR; 
typedef struct TypeRow {
	PointerR front, back;
}Row;
void FFVazia(Row *row){
	row->front = (PointerR) malloc(sizeof(CellR));
	row->back = row->front;
	row->front->next = NULL;
}
int VaziaR(Row row){
	return(row.back == row.front);
}
void Enfileira(ItemR x, Row *row){
	row->back->next = (PointerR)malloc(sizeof(CellR));
	row->back = row->back->next;
	row->back->id = x;
	row->back->next = NULL;
}
void Desenfileira(Row *row, ItemR *x){
	PointerR q;
	if(VaziaR(*row)){
		printf("\nErro: fila esta vazia");
		return;
	}
	q = row->front;
	row->front = row->front->next;
	*x = row->front->id;
	free(q);
}
void functionBFS(int **m, int n){
    printf("Ordem crescente(0) ou decrescente(1)?");
    int ordem, i;
    scanf("%d",&ordem);
    if(ordem==1) i=n-1;
    else i=0;
	Row fila;
	ItemR item;
	int visitado[n], j;
	for(j=0; j<n; j++)
	{
		visitado[j]=0;
	}
	FFVazia(&fila);
	item.num = i;
	Enfileira(item, &fila);
	visitado[item.num] = 1;
    printf("\nOrdem de visitacao: %d", item.num);
	while(!(VaziaR(fila))){
        if(ordem==1){
            i = fila.back->id.num;
            item.num = i;
            Desenfileira(&fila, &item);
            for(j=(n-1);j>=0;j--){
                if(visitado[j]==0 && m[i][j]!=0){
                    visitado[j]=1;
                    item.num = j;
                    Enfileira(item, &fila);
                    printf(" %d",item.num);
                }
            }
        }else{
            i = fila.back->id.num;
            item.num = i;
            Desenfileira(&fila, &item);
            for(j=0;j<n;j++){
                if(visitado[j]==0 && m[i][j]!=0){
                    visitado[j]=1;
                    item.num = j;
                    Enfileira(item, &fila);
                    printf(" %d",item.num);
                }
            }
        }
	}
    getchar();
}
//FUNCAO DFS E PILHA
typedef struct TypeCellS *PointerS; 
typedef struct TypeItemS{ 
    int num; 
}ItemS; 
typedef struct TypeCellS{ 
	ItemS item; 
	PointerS prox; 
}CellS; 
typedef struct TypeStack{ 
	PointerS  fundo, topo; 
	int tam; 
}Stack;
void FPVazia(Stack *stack) { 
	stack ->topo=(PointerS) malloc(sizeof(CellS)); 
	stack ->fundo = stack ->topo; 
	stack ->topo->prox = NULL; 
}
int VaziaS(Stack stack) {
	return ( stack .topo == stack .fundo) ; 
}
void Empilha(ItemS x, Stack *stack) { 
	PointerS aux; 
	aux = (PointerS) malloc(sizeof(CellS)); 
	stack->topo->item = x; 
	aux->prox = stack->topo; 
	stack->topo = aux; 	
}
void Desempilha(Stack *stack , ItemS *item) {
	PointerS q; 
	if (VaziaS( *stack ) ) { 
		printf ( "Erro : lista vazia\n" ) ; 	return; 
	} 
	q = stack->topo; 
	stack->topo = q->prox; 
	*item = q->prox->item; 
	free(q);
}
void functionDFS(int **m, int n){
	printf("Ordem crescente(0) ou decrescente(1)?");
    int ordem, i;
    scanf("%d",&ordem);
    if(ordem==1) i=n-1;
    else i=0;
	int visitado[n], j, aux;
	for(j=0; j<n; j++)
	{
		visitado[j]=0;
	}
	Stack stack;
	ItemS item;
	FPVazia(&stack);
	item.num = i;
	Empilha(item, &stack);
	visitado[item.num]=1;
	printf("\nOrdem de visitacao: %d", item.num);
	while(!(VaziaS(stack))){
		if(ordem==1){
			i = stack.topo->item.num; 
			item.num = i;
			aux = -1;
			j=n-1;;
			printf("\nteste 1 n: %d", i);
			while(aux<0 && j>=0){
				if(visitado[j]==0 && m[i][j]!=0){
                    aux=j;
					printf("\nteste 2 aux: %d - m: %d", aux, m[i][j]);
                }else{
					printf("\nteste 2 j: %d - m: %d", j, m[i][j]);
					j--;
				}
				printf("\nteste 3 aux: %d - m: %d", aux, m[i][j]);
				printf("\nteste 3 j: %d - m: %d", j, m[i][j]);
			}
			if(aux!=-1){
				visitado[j] = 1;
				item.num = j;
				Empilha(item, &stack);
				printf(" %d",item.num);
			}else{
				Desempilha(&stack, &item);
			}
		}else{
			i = stack.topo->item.num; 
			item.num = i;
			aux = -1;
			j=0;
			printf("\nteste 1 n: %d", i);
			while(aux<0 || j<n){
				if(visitado[j]==0 && m[i][j]!=0){
                    aux=j;
					printf("\nteste 2 aux: %d - m: %d", aux, m[i][j]);
                }else{
					printf("\nteste 2 j: %d - m: %d", j, m[i][j]);
					j++;
				}
				printf("\nteste 3 aux: %d - m: %d", aux, m[i][j]);
				printf("\nteste 3 j: %d - m: %d", j, m[i][j]);
			}
			if(aux!=-1){
				visitado[j] = 1;
				item.num = j;
				Empilha(item, &stack);
				printf(" %d",item.num);
			}else{
				Desempilha(&stack, &item);
			}
		}
	}
}
//FUNCAO FLOYD-WARSHALL
void floydwarshall(int **m, int n){
	int d[n][n];
	for(i=0;i<n;i++){
		for(j=0;j<n;j++){
			if(m[i][j]==0){
				d[i][j] = MAX_INT;
			}else{
				d[i][j] = m[i][j];	
			}
		}
	}
	for(k=0;k<n;k++){
		for(i=0;i<n;i++){
			for(j=0;j<n;j++){
				d[i][j] = min(d[i][j], d[i][k]+d[k][j]);
			}
		}
	}
}
//FUNCAO DIJKSTRA
void dijkstra(int **m, int i, int n){
	int *c, aux=0, j, k;
	for(j=0;j<n;j++){
		if(i!=x){
			c[aux]=i;
			aux++;
		}
	}
	int *d;
	for(j=0;j<n;j++){
		if(m[x][j]==0){
			d[j]=MAX_INT;
		}else{
			d[j]=m[x][j];
		}
	}
	int v, menor;
	for(j=1;j<n;j++){
		menor = MAX_INT;
		for(k=0;k<n;k++){
			if(menor > d[k]){
				v = k;
			}
		}
		for(k=0;k<n-1;k++){
			if(c[k]==v){
				c[k] == -1;
			}
		}
		for(w=0;w<n;k++){
			if(w!=-1){
				d[w] = min(d[w], d[v]+m[v][w]);	
			}
		}
	}
}
//FUNCAO BELLMAN-FORD	
void bellmanford(int **m, int i, int n){
	int j,v,w,d[n];
	for(j=0;j<n;j++){
		if(d==i){
			d[j]=0;
		}else{
			d[j] = MAX_INT;
		}
	}
	for(j=0;j<n-1;j++){
		for(v=0;v<n;v++){
			for(w=0;w<n;w++){
				d[w] = min(d[w], d[v]+m[v][w]);
			}
		}
	}
}

int main()
{
	clock_t inicio, fim;
	unsigned long int tempo;
	// ABERTURA DO ARQUIVO PARA ESCRITA
	graph = fopen("graph.dat", "w");
	if (graph == NULL)
	{
		printf("\n Houve um erro ao abrir o arquivo.");
	}
	else
	{
		int v, tagDir, i, j, **m;
		float d;
		do
		{
			printf("\nQuantidade de vertices (entre 3 e 10 milhoes): ");
			scanf("%d", &v);
			if (v < 3 || v > 10000)
				printf("\nValor invalido!");
		} while (v < 3 || v > 10000);
		do
		{
			printf("\nDensidade (entre 0.2 ate 1.0): ");
			scanf("%f", &d);
			if (d < 0.2 || d > 1.0)
				printf("\nValor invalido!");
		} while (d < 0.2 || d > 1.0);
		do
		{
			printf("\nDirecional(1) ou nao direcional(0): ");
			scanf("%d", &tagDir);
			if (tagDir != 0 && tagDir != 1)
				printf("\nValor invalido!");
		} while (tagDir != 0 && tagDir != 1);
		//ALOCA ESPAÇO PARA A MATRIZ
		m = (int**) malloc(v * sizeof(int *));
		for (int i = 0; i < v; i++)
		{
			m[i] = (int*) malloc(v * sizeof(int *));
		}
		m = functionArrayNull(m, v);
		m = functionCreateGraph(m, v, d, tagDir);

		int e;
		e = (((v * v) - v) / 2) * d;

		//GRAVA OS VALORES NO ARQUIVO
		fprintf(graph, "%d %d\n", v, e);
		printf("\n\n%d %d\n", v, e);
		for (i = 0; i < v; i++)
		{
			if (tagDir == 1)
			{
				for (j = 0; j < v; j++)
				{
					if (m[i][j] != 0)
					{
						fprintf(graph, "%d %d %d\n", i, j, m[i][j]);
						printf("%d %d %d\n", i, j, m[i][j]);
					}
				}
			}
			else
			{
				for (j = 0; j < v; j++)
				{
					if (m[i][j] != 0)
					{
						fprintf(graph, "%d %d %d\n", i, j, m[i][j]);
						printf("%d %d %d\n", i, j, m[i][j]);
					}
				}
			}
		}
		fclose(graph);
		//ABRE O ARQUIVO GERADO PARA LEITURA
		graph = fopen("graph.dat", "r");
		int op=-1;
        getchar();getchar();
        while(op!=0){
            system("clear || cls");
            printf("\n\n    <-> MENU <->\n");
            printf("\n 1 - Busca BFS.");
            printf("\n 2 - Busca DFS.");
            printf("\n 3 - Caminho Floyd-Warshall.");
            printf("\n 4 - Caminho Dijkstra.");
            printf("\n 5 - Caminho Bellman-Ford.");
            printf("\n 0 - Fechar programa.");
            printf("\n\n-> Digite a opcao desejada: ");
            scanf("%d", &op);
            switch (op)
            {
            case 1:
                system("clear || cls");
                fflush(stdin);
                printf("<-> Busca BFS <->");
				inicio = clock();
                functionBFS(m, v);
				fim = clock();
				tempo = (fim - inicio)*1000/CLOCKS_PER_SEC;
				printf("\nTempo: %lu milissegundos\n",tempo);
                printf("\n\n Precisone alguma tecla para continuar...");
                getchar();
                break;
            case 2:
				system("clear || cls");
                fflush(stdin);
                printf("<-> Busca DFS <->");
				inicio = clock();
                functionDFS(m, v);
				fim = clock();
				tempo = (fim - inicio)*1000/CLOCKS_PER_SEC;
				printf("\nTempo: %lu milissegundos\n",tempo);
                printf("\n\n Precisone alguma tecla para continuar...");
                getchar();
                break;
            case 3:
				system("clear || cls");
                fflush(stdin);
                printf("<-> Caminho Floyd-Warshall <->");
				inicio = clock();
                floydwarshall(m, v)
				fim = clock();
				tempo = (fim - inicio)*1000/CLOCKS_PER_SEC;
				printf("\nTempo: %lu milissegundos\n",tempo);
                printf("\n\n Precisone alguma tecla para continuar...");
                getchar();
                break;
            case 4:
				system("clear || cls");
                fflush(stdin);
                printf("<-> Caminho Dijkstra <->");
				inicio = clock();
                dijkstra(m, 1, v);
				fim = clock();
				tempo = (fim - inicio)*1000/CLOCKS_PER_SEC;
				printf("\nTempo: %lu milissegundos\n",tempo);
                printf("\n\n Precisone alguma tecla para continuar...");
                getchar();
                break;
            case 5:
				system("clear || cls");
                fflush(stdin);
                printf("<-> Caminho Bellman-Ford <->");
				inicio = clock();
                bellmanford(m, 0, v);
				fim = clock();
				tempo = (fim - inicio)*1000/CLOCKS_PER_SEC;
				printf("\nTempo: %lu milissegundos\n",tempo);
                printf("\n\n Precisone alguma tecla para continuar...");
                getchar();
                break;
            case 0:
				system("clear || cls");
				fflush(stdin);
				printf("	-> Fechar programa <-\n\n");
				printf("\n O programa sera fechado :( \n");
				printf("\n Precisone alguma tecla para continuar...\n");
				getchar();
			break;
			default:
				system("clear || cls");
				printf("Opcao invalida!\n");
				printf("\n\n Precisone alguma tecla para continuar...");
				getchar();
				system("clear || cls");
			break;
            }
        }
		getch();
		return 0;
	}
}
