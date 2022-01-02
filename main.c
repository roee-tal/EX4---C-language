// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// #include "algo.h"

// int main()
// {
//     char ch;
//     node *head = NULL;
//     // edge *e_h = NULL;
//     int num;
//     // printf("insert: ");
//     while (scanf("%c", &ch) == 1)
//     {
//         switch (ch)
//         {
//         case 'A':
//             printf("enter num:");
//             scanf("%d", &num);
//             createNodes(num, &head);
//             // printGraph_cmd();
//             break;
//         case '2':
//             printf("n");
//             createGraph(&head);
//             printGraph_cmd(head);
//         case '3':
//             printf("n2");
//             createGraph(&head);
//             printGraph_cmd(head);
//             break;

//         case '4':
//             printf("n3");
//             remove_node(&head);
//             printGraph_cmd(head);
//             break;

//         case '5':
//             printf("n4");
//             // int src;
//             // int dest;
//             int num;
//             // scanf("%d", &src);s
//             // scanf("%d", &dest);            
//             // shortsPath_cmd(&head, src, dest);
//             scanf("%d", &num);
//             TSP(num, &head);
//             break;

//         case 'T':
//             break;

//         default:
//             break;
//         }
//     }

//     return 0;
// }

#include <stdio.h>
#include <string.h>
#include "algo.h"
#include "graph.h"

int main()
{
    char ch;
    int num;
    int num2;
    int ans = 0;
    node *head = NULL;
    while (1)
    {
        scanf("%c", &ch);
        if (ch == 'A') {
            scanf("%d", &num);
            createNodes(num, &head);
        }
        if(ch == 'n') {
            createGraph(&head);
        }
        if(ch == 'B') {
            createGraph(&head);
        }
        if(ch == 'D') {
            scanf("%d", &num);
            remove_node(&head, num);
        }
        if(ch == 'S') {
            scanf("%d", &num);
            scanf("%d", &num2);
            ans =  shortsPath_cmd(&head, num, num2);
            printf("Dijsktra shortest path: %d \n", ans);
        }
        if(ch == 'T') {
            scanf("%d", &num);
            TSP(num, &head);
        }
        if(ch == '\n') {
            delete_g(&head);
            break;
        }

    }

    return 0;
}