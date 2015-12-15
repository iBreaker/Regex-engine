
#include "stdio.h"
#include <string.h>
#define MAXNODE 100

typedef struct node
{
    int go[26];         // goto表，仅支持26个小写字母
    int failure;        // failure表
    int end;            // 这个节点是不是某个模式串的结尾
}Node;

Node ACNode[MAXNODE];   // 节点结构体数组

int nodeCnt = 0;        // 节点个数

create_goto(char * str)
{
    int current_node_index = 0;         // 当前节点index
    Node * current = &(ACNode[0]);      // 当前节点指针，最开始指向root
    while(*str != 0)                    // 循环遍历所有字符
    {
        int index = (int)*str - 'a';    // 计算go数组的下标
        if(current->go[index] == 0)     // 没有这个节点，新建
        {   
            printf("第%d个节点加入%c\n", current_node_index, *str);
            nodeCnt++;                  // 申请一个新的借点下标
            printf("%d->go[%c] = %d \n", current_node_index, index + 'a', nodeCnt);
            current->go[index] = nodeCnt;           // 增加goto表
            current = &ACNode[current->go[index]];  // 指向下一个节点
            current_node_index = nodeCnt;           // 
        }
        else                            // 这个节点已经存在
        {
            printf("%d->go[%c] == %d\n", current_node_index, index + 'a', current->go[index]);
            current_node_index = current->go[index];    // 指向下一个节点
            current = &ACNode[current->go[index]];
            printf("current_node_index = %d \n", current_node_index);
        }
        str++; 
    }
    printf("\n");
}

void create_failure(Node * p)    // 递归构建failure表
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

            create_failure(&ACNode[p->go[i]]);
        }
    }    
    printf(" pop %c\n", pop());
}


create_out()
{

}

ACsearch()
{

}


char cur_list[10];      // 栈空间
int now_position = 0;   // 指向栈顶的指针

push(char str)          // push操作
{
    if(now_position == 9)
        return;
    cur_list[now_position] = str;
    now_position ++;
}

char pop()              // pop操作
{
    if(now_position == 0)
        return '!';
    now_position --;
    return cur_list[now_position];
}


copy_char(char * start, char * str) // 拷贝字符串
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

    create_failure(&(ACNode[0]));
}
