#include <stdio.h>
#include <stdlib.h>

struct Node
{
    int data;
    struct Node* next;
    struct Node* down;
};

struct Node * createrow(int m){

    struct Node *head = NULL, *new = NULL;
    struct Node *prev = NULL;
    int val;

    head = (struct Node *)malloc(sizeof(struct Node));
    scanf("%d",&val);
    head->data = val;
    head->next = NULL;
    head->down = NULL;
    
    prev = head;
    for(int i = 2; i<=m; i++){
        new = (struct Node *)malloc(sizeof(struct Node));
        scanf("%d",&val);
        new->data = val;
        prev->next = new;
        new->next = NULL;
        new->down = NULL;
        prev = new;
        
    }
    
    return head;
};

struct Node * createcol(int n){

    struct Node *head = NULL;
    struct Node *new = NULL;
    struct Node *prev = NULL;
    int val;

    head = (struct Node *)malloc(sizeof(struct Node));
    scanf("%d", &val);
    head->data = val;
    head->next = NULL;
    head->down = NULL;
    
    prev = head;
    for(int i = 2; i<=n; i++){
        new = (struct Node *)malloc(sizeof(struct Node));
        scanf("%d",&val);
        new->data = val;
        prev->down = new;
        new->next = NULL;
        new->down = NULL;
        prev = new;
        
    }
    
    return head;
};

void connect_rows(struct Node *head1, struct Node *head2, int m){
    if(head1==NULL)return;
    if(head2==NULL)return;
    struct Node *node1;
    struct Node *node2;
    node1 = head1;
    node2 = head2;
    for(int i=1; i<=m; i++){
        node1-> down = node2;
        node1 = node1->next;
        node2 = node2->next;
    }
}

void connect_cols(struct Node *head1, struct Node *head2, int n){
    if(head1==NULL)return;
    if(head2==NULL)return;
    struct Node *node1;
    struct Node *node2;
    node1 = head1;
    node2 = head2;
    for(int i=1; i<=n; i++){
        node1-> next = node2;
        node1 = node1->down;
        node2 = node2->down;
    }
}

struct Node* make_matrix(int n, int m){
    
    struct Node *prev;
    struct Node *current;
    struct Node *row1;
    struct Node *rowm;
    
    // read 1 row separately
    row1 = createrow(m);
    prev = row1;
    
    for(int i=2; i<=n; i++){
        current = createrow(m);
        connect_rows(prev, current, m);
        prev = current;
    }
    // rowm = current;
    // for(int j=2; j<=m; j++){
    //     rowm->down = NULL;
    //     rowm = rowm -> next;
    // }
    
    return row1;
}

void print_row_major(struct Node* head, int n, int m){
    if(head==NULL)return;
    struct Node* row_head;
    struct Node* prev;
    struct Node* node;
    
    row_head = head;
    node = head;
    
    for(int j=1; j<=n; j++){
        for(int i=1; i<=m; i++){
            if(i<m){
                printf("%d ",node->data);
                node = node -> next;
            }
            if(i==m){
                printf("%d\n", node->data);
            }
            
        }
        if(j<n){
        node = row_head-> down;
        row_head = row_head ->down;
        }
    }
}


void print_col_major(struct Node* head, int n, int m){
    if(head==NULL)return;
    struct Node* col_head;
    struct Node* prev;
    struct Node* node;
    
    col_head = head;
    node = head;
    if(head==NULL){
        return;
    }
    else{
        
    for(int j=1; j<=m; j++){
        for(int i=1; i<=n; i++){
            if(i<n){
                printf("%d ",node->data);
            }
            if(i==n){
                printf("%d\n", node->data);
            }
            node = node -> down;
            }
            //printf("node down %d\n", node->data);
        node = col_head-> next;
        col_head = col_head ->next;
    }
    }
}

struct Node* insert_row(struct Node* head, int pos, int m, int n){
    if(head==NULL)return head;
    struct Node* new = NULL;
    struct Node* temp = NULL;
    //struct Node* next = NULL;
    struct Node* node = head;
    if(pos==1){
        new = createrow(m);
        connect_rows(new, head, m);
        head = new;
    }
    else if(pos==n+1){
        //printf("Inserting at last index\n");
        for(int i=2; i<=n; i++){
            node = node -> down;
        }
        new = createrow(m);
        connect_rows(node, new, m);
    }
    else{
        for(int i=2; i<pos; i++){
        node = node -> down;
        }
    // pos-1th node
    new = createrow(m);
    temp = node -> down;
    connect_rows(node, new, m);
    connect_rows(new, temp, m);
    }
    return head;
    
}

struct Node* go_to_index(struct Node* row_head, int pos){
    struct Node* node = row_head;
    for(int i=2; i<=pos; i++){
        node = node -> next;
    }
    return node;
}

// struct Node* insert_col(struct Node* head, int pos, int n, int m){
//     struct Node* new = NULL;
//     struct Node* temp_side = NULL;
//     struct Node* node = NULL;
//     struct Node* temp_down = NULL;
//     //struct Node* next = NULL;
//     struct Node* row_head = head;
//     for(int i=1; i<=n; i++){
//         node = go_to_index(row_head, pos)
//         temp_side = node -> next
//         temp_down = node -
        
        
//     }
// }

struct Node* insert_col(struct Node* head, int pos, int n, int m){
    if(head==NULL)return head;
    struct Node* new = NULL;
    struct Node* temp = NULL;
    //struct Node* next = NULL;
    struct Node* node = head;
    if(pos==1){
        new = createcol(n);
        connect_cols(new, head, n);
        head = new;
    }
    else if(pos==m+1){
        //printf("Inserting at last index\n");
        for(int i=2; i<=m; i++){
            node = node -> next;
        }
        new = createcol(n);
        connect_cols(node, new, n);
    }
    else{
        for(int i=2; i<pos; i++){
        node = node -> next;
        }
    // pos-1th node
    new = createcol(n);
    temp = node -> next;
    connect_cols(node, new, n);
    connect_cols(new, temp, n);
    }
    return head;
    
}


void free_row(struct Node* head, int m){
    if(head==NULL)return;
    struct Node* node = head;
    struct Node* next = NULL;
    for(int i=2; i<=m; i++){
        next = node -> next;
        free(node);
        node = next;
    }
}

void free_col(struct Node* head, int m){
    struct Node* node = head;
    struct Node* next = NULL;
    for(int i=2; i<=m; i++){
        next = node -> down;
        free(node);
        node = next;
    }
}

struct Node* delete_row(struct Node*head, int pos, int n, int m){
    if(head==NULL)return head;
    struct Node* next = NULL;
    struct Node* del = NULL;
    struct Node* prev = NULL;
    struct Node* node = head;
    
    if(pos==1){
        next = head ->down;
        free_row(head, m);
        head = next;
    }
    else if(pos==n){
        //printf("Inserting at last index\n");
        for(int i=2; i<n; i++){
            node = node -> down;
        }
        
        del = node -> down;
        for(int i=1; i<m; i++){
            node -> down = NULL;
            node = node -> next;
        }

        free_row(del, m);
    }
    else{
    //printf("Inserting at other index\n");
        for(int i=2; i<=pos; i++){
        prev = node;
        node = node -> down;
        }
    // pos-1th node
    //printf("loop done\n");
    next = node -> down;
    connect_rows(prev, next, m);
    //printf("rows connected\n");
    free_row(node, m);
    //printf("row freed\n");
    }
    // m = m-1;
    return head;
}

struct Node* delete_col(struct Node*head, int pos, int n, int m){
    if(head==NULL)return head;
    struct Node* next = NULL;
    struct Node* del = NULL;
    struct Node* prev = NULL;
    struct Node* node = head;
    
    if(pos==1){
        //printf("entered pos 1");
        next = head ->next;
        free_col(head, n);
        head = next;
        return head;
    }
    else if(pos==m){
        //printf("Inserting at last index\n");
        for(int i=2; i<m; i++){
            node = node -> next;
        }
        
        del = node -> next;
        for(int i=1; i<n; i++){
            node -> next = NULL;
            node = node -> down;
        }

        free_col(del, n);
    }
    else{
    //printf("Inserting at other index\n");
        for(int i=2; i<=pos; i++){
        prev = node;
        node = node -> next;
        }
    // pos-1th node
    //printf("loop done\n");
    next = node -> next;
    connect_cols(prev, next, n);
    //printf("rows connected\n");
    free_col(node, n);
    //printf("row freed\n");
    }
    // m = m-1;
    return head;
    

}

// struct Node* delete_col(struct Node*head, int pos, int n, int m){
//     struct Node* next = NULL;
//     struct Node* del = NULL;
//     struct Node* prev = NULL;
//     struct Node* node = head;
    
//     if(pos==1){
//         next = head ->next;
//         free_col(head, n);
//         head = next;
//     }
//     else if(pos==m){
        
//         printf("Inserting at last index\n");
//         for(int i=1; i<pos; i++){
//             printf("Traversing nodes\n");
            
//             if(node->next)
//             node = node -> next;
//             printf("this node done%p\n", node);
            
//         }
        
//     // Return if list is empty 
// //     if(head == NULL)
// //     {
// //         printf("List is empty.");
// //         return head;
// //     }
    
// //         node = head;
// //         printf("%d", head -> data);
// //         while(node->next != NULL)
// //         {
// //             // printf("Data = %d\n", temp->data); // Print data of current node
// //             node = node->next;                 // Move to next node
// //         }
// // // }

//         printf("Loop done");
//         del = node;
//         printf("set del");
//         for(struct Node* ptr = node; ptr; ptr = ptr ->down){
//             ptr -> next = NULL;
//         }
//         printf("loop done");
//         free_col(del, m);
//         printf("freed");
//     }
//     else{
//     //printf("Inserting at other index\n");
//         for(int i=2; i<=pos; i++){
//         prev = node;
//         node = node -> next;
//         }
//     // pos-1th node
//     //printf("loop done\n");
//     next = node -> next;
//     connect_cols(prev, next, n);
//     //printf("rows connected\n");
//     free_col(node, n);
//     //printf("row freed\n");
//     }
//     // m = m-1;
//     return head;
    

// }

// int main()
// {
//     int option, val;
//     int n,m;
//     struct Node *b;
//     int flag = 0;
//     while(1)
//     {
//         scanf("%d",&option);
        
//         if(option==-1){
//             break;
//         }

//         switch(option)
//         {
//         case 0:
//             printf("hello 0\n");
//             scanf("%d %d",&n, &m);
//             b = make_matrix(n,m);
//             printf(" \n");
//             //print_row_major(b, n, m);
//             //printf(" \n");
//             //printf("hello all done");
//             // flag = 1;
//             // int pos;
//             // printf("enter position\n");
//             // scanf("%d", &pos);
//             // if(pos<1){
//             //     pos = 1;
//             // }
//             // // if(pos>n){
//             // //     pos = n + 1;
//             // // }
//             // // b = delete_col(b, pos, n, m);
//             // // m = m-1;
//             // //n = n-1;
//             printf("Printing matrix\n");
//             print_row_major(b, n, m);
//             break;
//         case 1:
//             printf("helllo2\n");
//             if (flag!=1){
//                 break;
//             }
//             printf("val is %d\n", val);
//             break;
//         }
//         }

//     return 0;
// };
int main() {
    int option, val;
    int n, m;
    struct Node * b;
    int flag = 0;
    int pos;
    while (1) {
        scanf("%d", & option);

        if (option == -1) {
            break;
        }

        switch (option) {
        case 0:
            // printf("hello 0\n");
            scanf("%d %d", & n, & m);
            b = make_matrix(n, m);
            // printf(" \n");
            //print_row_major(b, n, m);
            //printf(" \n");
            //printf("hello all done");
            // flag = 1;

            // //int pos;
            // // printf("enter position\n");
            // scanf("%d", & pos);
            // if (pos < 1) {
            //     pos = 1;
            // }
            // // if(pos>n){
            // //     pos = n + 1;
            // // }
            // b = delete_col(b, pos, n, m);
            // m = m - 1;
            // //n = n-1;
            // // printf("Printing matrix\n");
            // print_row_major(b, n, m);
            break;
        case 1:
            // // printf("helllo2\n");
            // if (flag != 1) {
            //     break;
            // }
            print_row_major(b, n, m);
            // printf("val is %d\n", val);
            break;
        case 2:
            // // printf("helllo2\n");
            // if (flag != 1) {
            //     break;
            // }
            print_col_major(b, n, m);
            // printf("val is %d\n", val);
            break;
        case 3:
            // // printf("helllo2\n");
            // if (flag != 1) {
            //     break;
            // }
            //int pos;
            // printf("enter position\n");
            scanf("%d", &pos);
            if (pos < 1) {
                pos = 1;
            }
            if(pos>n+1){
                break;
            }
            b = insert_row(b, pos, m, n);
            n = n + 1;
            // printf("val is %d\n", val);
            break;
        case 4:
            // // printf("helllo2\n");
            // if (flag != 1) {
            //     break;
            // }
            //int pos;
            // printf("enter position\n");
            scanf("%d", &pos);
            if (pos < 1) {
                pos = 1;
            }
            if(pos>m+1){
                break;
            }
            b = insert_col(b, pos, n, m);
            m = m + 1;
            // printf("val is %d\n", val);
            break;
        case 5:
            // // printf("helllo2\n");
            // if (flag != 1) {
            //     break;
            // }
            //int pos;
            // printf("enter position\n");
            scanf("%d", &pos);
            if (pos < 1) {
                pos = 1;
            }
            if(pos>n){
                break;
            }
            b = delete_row(b, pos, n, m);
            n = n - 1;
            // printf("val is %d\n", val);
            break;
        case 6:
            // printf("in case 6 m %d\n", m);
            // // printf("helllo2\n");
            // if (flag != 1) {
            //     break;
            // }
            //int pos;
            // printf("enter position\n");
            // printf("probelm in scanf\n");
            // int pos;
            // scanf("%d", & pos);
            // printf("no problem in case scanf\n");
            // // printf("pos %d m %d",pos, m);
            // if (pos < 1) {
            //     pos = 1;
            // }
            // else if(pos>m){
            //     printf("end case\n");
            //     pos = m;
            //     printf("pos %d\n",pos);
            // }
            // b = delete_col(b, pos, n, m);
            // m = m - 1;
            // // printf("val is %d\n", val);
            // break;
            scanf("%d", &pos);
            if (pos < 1) {
                pos = 1;
            }
            if(pos>m){
                break;
            }
            b = delete_col(b, pos, n, m);
            m = m - 1;
            // printf("val is %d\n", val);
            break;
        
        }
    }

    return 0;
};
