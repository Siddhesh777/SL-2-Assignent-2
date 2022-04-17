#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#define N 3
#define SIZE 8
struct node
{
    int val;
    int flag;
    int Count;
    struct node *l[N];
};
struct heap
{
    struct node free_space;
    struct heap *next;
};
struct heap *head=NULL;
struct node *mem_ptr[SIZE];
struct node* insert(int size,struct node *l1,struct node *l2,struct node *l3)
{
    struct heap *ptr=malloc(sizeof(struct heap));
    ptr->free_space.val=size;
    ptr->free_space.flag=0;
    ptr->free_space.l[0]=l1;
    ptr->free_space.l[1]=l2;
    ptr->free_space.l[2]=l3;
    ptr->free_space.Count=0;
    ptr->next=head;
    head=ptr;
    struct node *temp=&(ptr->free_space);
    if(l1 != NULL)
        l1->Count +=1;
    if(l2 != NULL)
        l2->Count +=1;
    if(l3 != NULL)
        l3->Count +=1;
    
    return temp;
}
void printList()
{
    struct heap *temp=head;
    while(temp!=NULL)
    {
        printf("(%d ,connected_nodes=%d , check_mark=%d) ->",temp->free_space.val,temp->free_space.Count,temp->free_space.flag);
        temp=temp->next;
    }
    printf("NULL");
}
void allocate(struct node *root)
{
    (root)->Count+=1;
}
void printRefer(struct node *root)
{
    if(root!=NULL)
    {
        printf("%d(connected_nodes=%d) ",root->val,root->Count);
        printRefer(root->l[0]);
        printRefer(root->l[1]);
        printRefer(root->l[2]);
    }
}
void garbageCollect(struct node *ptr[],int n)
{
    int j=n-1;
    struct heap *temp=head;
    struct heap *prev=NULL;
    
    while(temp!=NULL)
    {
        if(temp->free_space.Count==0)
        {
            for(int i=0;i<N;i++)
            {
                if(temp->free_space.l[i] != NULL)
                    temp->free_space.l[i]->Count -=1;
            }
            prev->next=temp->next;
            free(temp);
            temp=prev;
            ptr[j]=NULL;
        }
        prev=temp;
        temp=temp->next;
        j--;
    }
}
void marknodes(struct node *root)
{
    if(root!=NULL)
    {
        marknodes(root->l[0]);
        marknodes(root->l[1]);
        marknodes(root->l[2]);
        root->flag=1;
    }
}
void sweepmethod()
{
    int j=SIZE-1;
    struct heap *temp=head;
    struct heap *prev=NULL;
    
    while(temp!=NULL)
    {
        if(temp->free_space.flag==0)
        {
            for(int i=0;i<N;i++)
            {
                if(temp->free_space.l[i] != NULL)
                {
                    temp->free_space.l[i]->Count -=1;
                }
            }
            prev->next=temp->next;
            free(temp);
            temp=prev;
            mem_ptr[j]=NULL;
        }
        prev=temp;
        temp=temp->next;
        j--;
    }
}
int main()
{
    mem_ptr[0]=insert(10,NULL,NULL,NULL);
    mem_ptr[1]=insert(9,NULL,NULL,NULL);
    mem_ptr[2]=insert(2,NULL,NULL,NULL);
    mem_ptr[3]=insert(8,mem_ptr[1],NULL,NULL);
    mem_ptr[4]=insert(1,mem_ptr[2],mem_ptr[1],mem_ptr[0]);
    mem_ptr[5]=insert(3,mem_ptr[3],mem_ptr[0],NULL);
    mem_ptr[6]=insert(7,mem_ptr[4],mem_ptr[3],NULL);
    mem_ptr[7]=insert(5,mem_ptr[4],NULL,NULL);
    struct node *root1,*root2;
    root1=mem_ptr[7];
    allocate(root1);
    root2=mem_ptr[4];
    allocate(root2);
    for(int i=SIZE-1;i>=0;i--)
    {
        printRefer(mem_ptr[i]);
        printf("\n");
    }
    printf("\n------\n");
    printf("Heap connected to main node is : \n");
    printRefer(root1);
    printf("\n");
    printRefer(root2);
    printf("\nApplying garbage mathod : \n");
    garbageCollect(mem_ptr,SIZE);
    for(int i=SIZE-1;i>=0;i--)
    {
        printRefer(mem_ptr[i]);
        if(mem_ptr[i]!=NULL)
            printf("\n");
    }
    printf("List is : \n");
    printList();
    marknodes(root1);
    marknodes(root2);
    sweepmethod();
    printf("\nList is : \n");
    printList();
    return 0;
}