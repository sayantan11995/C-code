#include<stdio.h>
#include<stdlib.h>
#define inf 1000000007

typedef struct node{
    struct node * next;
    int vertex;
    int weight;
} list_node;

typedef struct list_of_list_node{
    list_node * head;
}list;
typedef struct graph{
    int number_of_vertices;
    list *adj_list;
}g;

list_node * create_node(int v, int w){
    list_node * new_node = (list_node *)malloc(sizeof(list_node));
    new_node->vertex = v;
    new_node->weight = w;
    new_node->next = NULL;
    return new_node;
}

g* create_graph(int v){
    g* new_graph = (g*)malloc(sizeof(g));
    new_graph->number_of_vertices = v;
    new_graph->adj_list = (list *)malloc(v * sizeof(list));
    for(int i=0;i<v;i++){
        new_graph->adj_list[i].head = NULL;
    }
    return new_graph;
}

void add_edge(g* _graph, int s, int d, int w){
    list_node * dest_node = create_node(d, w);
    if( _graph->adj_list[s].head == NULL){
        _graph->adj_list[s].head = dest_node;
        return;
    }
    list_node * iter = _graph->adj_list[s].head;
    while(iter->next){
        iter = iter->next;
    }
    iter->next = dest_node;
}
void print_graph(g* _graph){
    int v = _graph->number_of_vertices;
    for(int i=0; i<v;i++){
        list_node * iter = _graph->adj_list[i].head;
        printf("%d",i);
        while(iter){
            printf("->(%d, %d)", iter->vertex,iter->weight);
            iter = iter->next;
        }
        printf("\n");
    }
}

typedef struct dijkstra_matrix{
    int* vertex;
    int* shortest_distance;
    int* visited;
    // int* unvisited;
    // int* prev_node;
    
}table;

table * create_table(int v){
    table* new_table = (table* )malloc(sizeof(table));
    new_table->vertex = (int *)malloc(v * sizeof(int));
    new_table->shortest_distance = (int *)malloc(v * sizeof(int)); 
    new_table->visited = (int *)malloc(v * sizeof(int));
    // new_table->unvisited = (int *)malloc(v * sizeof(int));
    // new_table->prev_node = (int *)malloc(v * sizeof(int));
    for(int i=0;i<v;i++){
        new_table->vertex[i] = i;
        new_table->shortest_distance[i] = inf;
        new_table->visited[i] = 0;
        // new_table->unvisited[i] = 1;
        // new_table->prev_node[i] = -1;
    }
    return new_table;
}
void print_mat(table* t, int v){
    printf("Vertex ->  |");
    for(int i=0;i<v;i++){
        printf(" %d |", t->vertex[i]);
    }
    // printf("\n");
    // printf("Previous node -> |");
    // for(int i=0;i<v;i++){
    //     printf(" %d |", t->prev_node[i]);
    // }
    printf("\n");
    printf("Visited -> |");
    for(int i=0;i<v;i++){
        printf(" %d |", t->visited[i]);
    }
    printf("\n");
    printf("Shortest distance from source -> |");
    for(int i=0;i<v;i++){
        printf(" %d |", t->shortest_distance[i]);
    }
    printf("\n");
    
}

void dijkstra(g* _graph, table* t, int s){
    int selected_node = -1;
    int nearest_node_dist = inf;
    t->shortest_distance[s] = 0;
    t->visited[s] = 1;
    list_node * iter = _graph->adj_list[s].head;
    while(iter){
        t->shortest_distance[iter->vertex] = iter->weight;
        if(t->shortest_distance[iter->vertex] < nearest_node_dist){
            nearest_node_dist = t->shortest_distance[iter->vertex];
            selected_node = iter->vertex;
        }
        iter = iter->next;
    }
    int all_visited_flag = 1;
    
    int i=1, k, sn;
    
    
    while(i < _graph->number_of_vertices){
        print_mat(t, _graph->number_of_vertices);
        printf("\n");
        nearest_node_dist = inf;
        t->visited[selected_node] = 1;
        iter = _graph->adj_list[selected_node].head;
        while(iter){
        
            if(!t->visited[iter->vertex] && iter->weight + t->shortest_distance[selected_node] <= t->shortest_distance[iter->vertex] ){
                t->shortest_distance[iter->vertex] = iter->weight + t->shortest_distance[selected_node];
            }
            iter = iter->next;
        }
        k=1;
        for(k;k<_graph->number_of_vertices;k++){
            if(!t->visited[k] && t->shortest_distance[k] <= nearest_node_dist){
                nearest_node_dist = t->shortest_distance[k];
                selected_node = k;
            }
        }
        i++;
    }
    
}


int main() {
    
    g* mygraph = create_graph(6);
    table* my_table = create_table(6);
    add_edge(mygraph, 0, 2, 45);
    add_edge(mygraph, 0, 1, 50);
    add_edge(mygraph, 0, 3, 10);
    add_edge(mygraph, 1, 2, 10);
    add_edge(mygraph, 1, 3, 15);
    add_edge(mygraph, 2, 4, 30);
    add_edge(mygraph, 3, 0, 10);
    add_edge(mygraph, 3, 4, 15);
    add_edge(mygraph, 4, 1, 20);
    add_edge(mygraph, 4, 2, 35);
    add_edge(mygraph, 5, 4, 3);
    
    
    print_graph(mygraph);
    
    print_mat(my_table, 6);
    printf("\n");
    dijkstra(mygraph, my_table, 0);
    // print_mat(my_table, 6);  
    
}