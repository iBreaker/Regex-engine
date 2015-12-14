
#include "stdio.h"
#include <string.h>
#define MAXNODE 100

typedef struct node
{
    int go[26];
    int failre;
    int end;

}Node;

Node ACNode[MAXNODE];
int nodeCnt = 0;

create_goto(char * str)
{
    int current_node_index = 0;
    Node * current = &(ACNode[0]);
    while(*str != 0)
    {
        int index = (int)*str - 'a';
        
        if(current->go[index] == 0)
        {   
            printf("第%d个节点加入%c\n", current_node_index, *str);
            nodeCnt++;
            printf("%d->go[%c] = %d \n", current_node_index, index + 'a', nodeCnt);
            current->go[index] = nodeCnt; 
            current = &ACNode[current->go[index]];
            current_node_index = nodeCnt;
        }
        else
        {
            printf("%d->go[%c] == %d\n", current_node_index, index + 'a', current->go[index]);
            current_node_index = current->go[index];
            current = &ACNode[current->go[index]];
            printf("current_node_index = %d \n", current_node_index);
        }
        str++; 
    }

    printf("\n");
}

create_failure()
{

}

create_out()
{

}

ACsearch()
{

}

copy_char(char * start, char * str)
{
        int i = 0;
        for(i = 0; ;i++)
        {
            * start = * str;
            //printf("%c", *start);
            if(* str == 0)
            {
                break;
            }
            start++;
            str++;
        }
}

void print(Node * p)
{
    int i = 0;
    for(i=0; i < 26; i++)
    {
        if(p->go[i] != 0)
        {
            printf("%c", i + 'a');
            print(&ACNode[p->go[i]]);
        }
    }


}
void main(void)
{
    char pattern[4][10];
    copy_char(pattern[0], "he");
    copy_char(pattern[1], "she");
    copy_char(pattern[2], "his");
    copy_char(pattern[3], "hers");

    memset(ACNode, 0, (sizeof(Node) * MAXNODE));
    // 添加goto表
    int i = 0;
    for (i = 0; i < 4; i++)
    {
        create_goto(pattern[i]);       
    }

    print(&(ACNode[0]));
}
