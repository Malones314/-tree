#include<stdio.h>
#include<stdlib.h>
typedef struct Node{
    struct Node* leftChild, *rightChild;
    int visited_or_not;
    int data;
}Node;

typedef struct Bitree{
    Node* firstChild;
}Bitree;

typedef struct Stack{
    Node* myStack[20];
    int top;
    int size_S;
}Stack;


void pushStack( Stack* myS, Node* node){
    if( myS->top==19){
        printf("没有足够的空间放入新节点 ! ");
        return;
    }else{
        myS->size_S++;
        myS->top++;
        myS->myStack[myS->top] = node;
    }
}
Node* popStack( Stack* myS){
    myS->size_S--;
    return myS->myStack[myS->top--];
}

Node* creatABitree( Node* p){
    int i;
    scanf("%d", &i);
    if( i == -1)
        p = NULL;
    else{
        p = (Node*)malloc (sizeof(Node));
        p->data = i;
        p->leftChild = creatABitree(p->leftChild);
        p->rightChild = creatABitree(p->rightChild);
    }
    return p;
}
void DLR1( Node* node){
    if( node != NULL){
        printf( "%d ", node->data);
        DLR1( node->leftChild);
        DLR1( node->rightChild);
    }
}
void DLR2(Stack* myS,  Node* node){
    Node*p;
    p = node;
    while(p != NULL || myS->size_S!=0){
        while(p){
            printf("%d ", p->data);
            pushStack(myS, p);
            p = p->leftChild;
        }
        p = popStack(myS);
        p = p->rightChild;
    }
}

void LDR1( Node* node){
    if(node){
        LDR1( node->leftChild);
        printf("%d ", node->data);
        LDR1( node->rightChild);
    }
}
void LDR2(Stack* myS, Node* node){
    Node*p = node;
    while( myS->size_S > 0 || p){
        while( p){
            pushStack(myS, p);
            p = p->leftChild;
        }
        p = popStack(myS);
        printf("%d ", p->data);
        p = p->rightChild;
    }
}
void LRD1(Node* node){
    if(node!=NULL){
        LRD1( node->leftChild);
        LRD1( node->rightChild);
        printf("%d ", node->data);
    }
}
void LRD2( Stack*myS, Node* node){
    Node*p = node;
    while( p || myS->size_S > 0){
        while(p){
            p->visited_or_not = 0;
            pushStack(myS, p);
            p = p->leftChild;
        }
        p = popStack(myS);
        if(p->visited_or_not == 0){
            pushStack(myS, p);
            p->visited_or_not = 1;
            p = p->rightChild;
        }else{
            printf("%d ", p->data);
            p = NULL;
        }
    }
}
void show(){
    printf("\t\t二叉树的建立和遍历\n\n");
    printf("=============================================\n");
    printf("\t1.创建二叉树\n");
    printf("\t2.先序遍历(递归)   3.先序遍历(非递归)\n");
    printf("\t4.中序遍历(递归)   5.中序遍历(非递归)\n");
    printf("\t6.后序遍历(递归)   7.后序遍历(非递归)\n");
    printf("\t0.退出\n");
    printf("=============================================\n");
    printf("你选择的操作是：");
}
int main(){
    int d = 0;
    Bitree* myTree;
    myTree = (Bitree*)malloc( sizeof(Bitree));
    myTree->firstChild = (Node*)malloc (sizeof(Node));
    myTree->firstChild->leftChild = (Node*)malloc (sizeof(Node));
    myTree->firstChild->rightChild =  (Node*)malloc (sizeof(Node));
    Stack* myS;
    myS = (Stack*)malloc( sizeof(Stack));
    myS->size_S = 0;
    myS->top = 0;
    do{
        show();
        scanf("%d", &d);
        printf("\n");
        if(d == 1){
            printf("请输入二叉树(-1为空节点):\n");
            myTree->firstChild = creatABitree( myTree->firstChild);
        }else if( d == 2){
            DLR1(myTree->firstChild);
            printf("\n");
        }else if( d == 3){
            DLR2( myS, myTree->firstChild);
            printf("\n");
        }else if( d == 4){
            LDR1( myTree->firstChild);
            printf("\n");
        }else if( d == 5){
            LDR2( myS, myTree->firstChild);
            printf("\n");
        }else if( d == 6){
            LRD1( myTree->firstChild);
            printf("\n");
        }else if( d == 7){
            LRD2( myS, myTree->firstChild);
            printf("\n");
        }
    }while(d!=0);
//   1 2 4 -1 -1 5 -1 -1 3 6 -1 -1 7 -1 -1
    return 0;
}
