#include <stdio.h>
#include <stdlib.h>

#include "graph.h"

#define INF 1000000
static int minPath = INF;
pNode GetNode(int data, node **H);
void deleteGraph_cmd(node **H);
void remove_node(node**, int);



node *createOneNode(int src, node **H){
    node *lst = (node*)malloc(sizeof(node));
    if(!lst){
        return NULL;
    }
    lst->nodeId = src;
    lst->next = NULL;
    lst->edges = NULL;
    lst->n_weight = INF;
    lst->visit = 0;
    node *tmp = *H;
    while(tmp->next){
        tmp = tmp->next;
    }
    tmp->next = lst;
    return lst;
}

    void free_edges_of_node(node *n){
        edge *e_head = n->edges;
        if(!e_head){
            return;
        }
        edge *tmp = e_head->next;
        if(tmp == NULL){
            free(e_head);
            n->edges = NULL;
            // return;
        }
        else{
            while(e_head->next){
                edge *tmp2 = tmp;
                e_head->next = tmp->next;
                free(tmp2);
            }
        free(e_head);
        }

    }

   void insertNode(int i, node **H){
        int dst;
        int w;
        node *new = createOneNode(i, H);
        edge *ed = (edge*)malloc(sizeof(edge));
        if(!ed){
            return;
        }
        // printf("srcId: %d\n", new->nodeId);
        if (scanf("%d", &dst) == 1)
        {
            if (scanf("%d", &w) == 1){
                ed->dest = GetNode(dst, H);
                ed->weight = w;
                ed->next = NULL;
                new->edges = ed;
            }
        }
        edge *temp = ed;   
        while (scanf("%d", &dst) == 1)
        {
            if (scanf("%d", &w) == 1){
                edge *curr = (edge*)malloc(sizeof(edge));
                curr->dest = GetNode(dst, H);
                curr->weight = w;
                curr->next = NULL;
                temp->next = curr;
                temp = curr;
            }
        }
    }

    void delete_g(node **H){
        node *tmp =*H;
        int node_id;
        while(tmp){
            node_id = tmp->nodeId;
            tmp = tmp->next;
            remove_node(H, node_id);
            
        }
        *H = NULL;
    }

void createNodes(int size, node **H){
    if(*H){
        delete_g(H);
    }
    node *first = (node*)malloc(sizeof(node));
    if(!first){
        return;
    }
    first->nodeId = 0;
    first->next = NULL;
    first->edges = NULL;
    first->n_weight = INF;
    first->visit = 0;
    *H = first;
    node *tmp = *H;
    for(int i=1;i<size;i++){
        node *newnode = (node*)malloc(sizeof(node));
        if(!newnode){
            return;
        }
        newnode->nodeId = i;
        newnode->edges = NULL;
        newnode->next = NULL;
        tmp->next = newnode;
        tmp = newnode;
    }
}

// void free_edges(int src, node **H){

// }

void createGraph(node **H){
    int src;
    int dst;
    int w;
    scanf("%d", &src);
    node *source = GetNode(src, H);
    if(source != 0){
        if(source->edges != NULL){
            free_edges_of_node(source);
        }
        edge *ed = (edge*)malloc(sizeof(edge));
        if(!ed){
            return;
        }
        if (scanf("%d", &dst) == 1)
        {
            if (scanf("%d", &w) == 1){
                ed->dest = GetNode(dst, H);
                ed->weight = w;
                ed->next = NULL;
                source->edges = ed;
            }
        }
        else{free(ed);}
        edge *temp = ed;   
        while (scanf("%d", &dst) == 1)
        {
            if (scanf("%d", &w) == 1){
                edge *curr = (edge*)malloc(sizeof(edge));
                curr->dest = GetNode(dst, H);
                curr->weight = w;
                curr->next = NULL;
                temp->next = curr;
                temp = curr;
            }
        }
    }
    else{
        insertNode(src, H);
    }
}   



    void remove_node(node **H, int del){
        // int del;
        // printf("node to delete:");s
        // scanf("%d", &del);
        node *n = GetNode(del, H);
        node *head = *H;
        while(head){
            edge *curr = head->edges;
            edge *e_head = curr;
            // printf("dest: %d, w: %d", curr->dest->nodeId, curr->weight);
            while(e_head){
                if(e_head->dest == n){
                    // printf("!");
                    head->edges = curr->next;
                    edge *new = e_head;
                    free(new);
                    e_head = NULL;
                }
                else{
                    edge *temp3 = e_head->next;
                    if(temp3 != NULL && temp3->dest == n){
                        e_head->next = temp3->next;
                        free(temp3);
                    }
                    else{
                        e_head = temp3;
                    }
                }  
        }
        head = head->next;
        }
        if(!*H)
            return;
        if((*H)->nodeId == del){
            node *tmp = *H;
            *H = (*H)->next;
            free_edges_of_node(n);
            free(tmp);
            return;
        }
        node *tmp = *H;
        while(tmp->next && tmp->next->nodeId != del){
            tmp = tmp->next;
        }
        if(!tmp->next){
            return;
        }
        node *tmp2 = tmp->next;
        tmp->next = tmp->next->next;
        free_edges_of_node(n);
        free(tmp2);
    }
    
  
    pNode GetNode(int data, node **H){
        node *n = *H;
        while(n->nodeId != data){
            n = n->next;
            if(!n){
                return NULL;
            }  
        }
        return n;
    }
    
// void deleteGraph_cmd(){
//     pNode* tmp = &graphNodes;sj
//     int nodeId;
//     while (*tmp)
//     {
//         nodeId = (*tmp)->nodeId;
//         deleteNode(nodeId);
        
//     }
    
// }


void printGraph_cmd(node *H)
{
    node *head = H;
    printf("{");
    while(head){
        printf("[id: %d, ", head->nodeId);
        edge *curr = head->edges;
        printf("Edges: ");
        while(curr){
            printf("dest: %d, w: %d", curr->dest->nodeId, curr->weight);
            curr = curr->next;
        }
        printf("], ");
        head = head->next;
    }
    printf("}");
}

    int restartGraph(node **H){
        node *tmp = *H;
        int cou = 0;
        while (tmp){
            tmp->n_weight = INF;
            // tmp->parent = NULL;1
            tmp->visit = 0;
            tmp = tmp->next;
            cou++;
        }
        return cou;
}   

    node *get_low_node(node **H){
         node *tmp = *H;
         node *res = NULL;
         int max = 1000001;
         while (tmp)
         {
             if(tmp->n_weight < max){
                 if(tmp->visit == 0){
                    max = tmp->n_weight;
                    res = tmp;
                 }
             }
             tmp=tmp->next;
         }
         return res;
    }

    void relax(node *source, node *dst, edge *e){
        int wEdge = e->weight;
        int wSrc = source->n_weight;
        int wDest = dst->n_weight;
        if(wDest > wSrc + wEdge){
            dst->n_weight = wEdge + wSrc;
        }
    }
    
    int shortsPath_cmd(node **H, int src, int dest){
        node *cur = GetNode(src, H);
        int g_size = restartGraph(H);
        cur->n_weight = 0;
        while(g_size>0){
            cur = get_low_node(H);
            // if(cur->visit == 0){
                if(cur->nodeId == dest){
                    // int res = cur->n_weight;s
                    // printf("the res is: %d", res);
                    return cur->n_weight;
                }
                cur->visit = 1;
                pEdge e = cur->edges;
                while (e){
                    relax(cur, e->dest, e);
                    e = e->next;
                }            
            // }
            g_size--;
        }
        // node *d = GetNode(dest, H);
        // int res = d->n_weight;
        // printf("the res is: %d", res);s
        return 0;
    }

    void swap(int *x, int *y)
{
    int temp;
    temp = *x;
    *x = *y;
    *y = temp;
}


void permutation(node** H, int a[], int size, int n) {
    if (size == 1) {
        int sum = 0;
        for (int j = 0; j < n-1; ++j) {
            sum += shortsPath_cmd(H, a[j], a[j + 1]);
        }
        if (sum < minPath) {
            minPath = sum;
            return;
        }
    }

    for (int i = 0; i < size; i++) {
        permutation(H, a, size - 1, n);

        // if size is odd, swap 0th i.e (first) and
        // (size-1)th i.e (last) element
        if (size % 2 == 1)
            swap(&a[0], &a[size - 1]);

            // If size is even, swap ith and
            // (size-1)th i.e (last) element
        else
            swap(&a[i], &a[size - 1]);
    }

}

void TSP(int num, node **H) {
    minPath = INF;
    int cities[num];
    int n;
    for (int i = 0; i < num; i++) {
        scanf("%d", &n);
        cities[i] = n;
    }
    permutation(H, cities, num, num);
    if(minPath == INF){
        minPath = -1;
    }
    printf("TSP shortest path: %d \n", minPath);
}





    // pNode head = H;
    // printf("{");
    // while (head)
    // {
    //     printf("[id: %d, ", head->nodeId);
    //     pEdge ep = head->edges;
    //     printf("edges: ");
    //     while (ep)
    //     {
    //         printf("w: %d, dest: %d, ", ep->weight, ep->dest->nodeId);
    //         ep = ep->next;
    //     }
    //     printf("], ");
    //     head = head->next;
    // }
    // printf("}");

