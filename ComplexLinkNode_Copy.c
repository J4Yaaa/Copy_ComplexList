#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

typedef int ComplexLinkType;

typedef struct ComplexLinkNode
{
    ComplexLinkType data;
    struct ComplexLinkNode* next;
    struct ComplexLinkNode* sibling;
}ComplexLinkNode;

//初始化链表
void ComplexLinkInit(ComplexLinkNode** head)
{
    assert(head);
    *head = NULL;
}

//创建链表节点
ComplexLinkNode* CreateNode(ComplexLinkType value)
{
    ComplexLinkNode* new_node = (ComplexLinkNode*)malloc(sizeof(ComplexLinkNode));
    new_node->next = NULL;
    new_node->sibling = NULL;
    new_node->data = value;
    return new_node;
}

//尾插,返回新插入元素的地址
ComplexLinkNode* LinkPushBack(ComplexLinkNode** head,ComplexLinkType value)
{
    assert(head);
    ComplexLinkNode* new_node = CreateNode(value);
    if(*head == NULL)
    {
        *head = new_node;
    }
    else
    {
        ComplexLinkNode* cur = *head;
        while(cur->next != NULL)
        {
            cur = cur->next;
        }
        cur->next = new_node;
    }
    return new_node;
}

//拷贝当前节点,将新节点插入到当前节点的后面
void Copy_node(ComplexLinkNode* head)
{
    ComplexLinkNode* cur = head;
    ComplexLinkNode* next = cur->next;
    while(cur->next != NULL)
    {
        ComplexLinkNode*new_node = CreateNode(cur->data);
        cur->next = new_node;
        new_node->next = next;

        cur = next;
        next = next->next;
    }
    ComplexLinkNode*new_node = CreateNode(cur->data);
    cur->next = new_node;
    new_node->next = NULL;
}

//将新插入的节点的sibling指针指向其前面节点的sibling的下一个节点
void Update_NewLink_sibling(ComplexLinkNode* head)
{
    ComplexLinkNode* cur = head;
    while(cur != NULL)
    {
        ComplexLinkNode* new_cur = cur->next;
        if(cur->sibling != NULL)
        {
            new_cur->sibling = cur->sibling->next;
        }
        cur = cur->next->next;
    }
}

//分离链表,将新的节点从链表中拆分出来,组成新的链表
ComplexLinkNode* Separate_NewLink(ComplexLinkNode* head)
{
    ComplexLinkNode* cur = head;
    ComplexLinkNode* new_head = head->next;
    ComplexLinkNode* new_head_cur = new_head;
    while(new_head_cur->next != NULL)
    {
        cur->next = new_head_cur->next;
        cur = cur->next;
        new_head_cur->next = cur->next;
        new_head_cur = new_head_cur->next;
    }
    cur->next = NULL;
    new_head_cur->next = NULL;
    return new_head;
}

//复杂链表的复制
ComplexLinkNode* Copy_Link(ComplexLinkNode* head)
{
    if(head == NULL)
    {
        return NULL;
    }
    //1.首先将每个节点都复制一遍,查在当前节点的下一个
    Copy_node(head);
    //2.新节点的spbling指针指向前一个节点spnling的下一个节点
    Update_NewLink_sibling(head);
    //3.分离出新的链表
    return Separate_NewLink(head);
}

//打印复杂链表
void PrintComplexLink(ComplexLinkNode* head)
{
    if(head == NULL)
    {
        return;
    }
    ComplexLinkNode* cur = head;
    while(cur != NULL)
    {
        printf("[%d : %p] -> ",cur->data,cur);
        cur = cur->next;
    }
    printf("NULL\n");
    cur = head;
    while(cur != NULL)
    {
        if(cur->sibling != NULL)
        {
            printf("%d -> spbling = [%d : %p]\n",cur->data,cur->sibling->data,cur->sibling);
        }
        else
        {
            printf("%d -> spbling = [NULL : %p]\n",cur->data,cur->sibling);
        }
        cur = cur->next;
    }
}

void Test()
{
    ComplexLinkNode* head;
    ComplexLinkInit(&head);
    ComplexLinkNode* pos1 = LinkPushBack(&head,1);
    ComplexLinkNode* pos2 = LinkPushBack(&head,2);
    ComplexLinkNode* pos3 = LinkPushBack(&head,3);
    ComplexLinkNode* pos4 = LinkPushBack(&head,4);
    pos1->sibling = pos2;
    pos2->sibling = NULL;
    pos3->sibling = pos2;
    pos4->sibling = pos1;
    printf("old Link\n");
    PrintComplexLink(head);
    ComplexLinkNode* new_head = Copy_Link(head);
    printf("new Link\n");
    PrintComplexLink(new_head);
}

int main()
{
    Test();
    return 0;
}
