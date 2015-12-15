
#include "stdio.h"
#include <string.h>
#define MAXNODE 100

typedef struct node
{
    int go[26];
    int failure;
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

char cur_list[10];
int now_position = 0;

push(char str)
{
    if(now_position == 9)
        return;
    cur_list[now_position] = str;
    now_position ++;
}

char pop()
{
    if(now_position == 0)
        return '!';
    now_position --;
    return cur_list[now_position];
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

void traversal(Node * p)
{
    int i = 0;
    for(i=0; i < 26; i++)
    {
        if(p->go[i] != 0)
        {
            push((char)(i + 'a'));
            printf("push %c\n", i + 'a');
            
            // 循环后缀子串
            int j = 0;
            for(j = 1; j < now_position; j++)
            {
                int current_index = 0;
                int k = j;

                // 对于每一个后缀字串遍历字符
                while( k < now_position )
                {
                    char tmp = cur_list[k];
                    int index = tmp - 'a';
                    if(ACNode[current_index].go[index] != 0)
                    {
                        current_index = ACNode[current_index].go[index];
                    }
                    else
                    {
                        break;
                    }
                    k++;
                }

                if( k == now_position) // 匹配到最长后缀字串
                {
                    p->failure = current_index;
                    printf("failure to %d\n", current_index);
                    break;
                }
            }



            traversal(&ACNode[p->go[i]]);
        }
    }    
    printf(" pop %c\n", pop());
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

    traversal(&(ACNode[0]));
}
