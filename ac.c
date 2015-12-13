/*
    AC自动机算法
    自动机算法可以参考《柔性字符串匹配》里的相应章节，讲的很清楚
*/

#include <stdio.h>
#include <string.h>

const  int MAXQ = 500000+10;
const  int MAXN = 1000000+10;
const  int MAXK = 26;  //自动机里字符集的大小 

struct  TrieNode
{
	TrieNode* fail;         // 
	TrieNode* next[MAXK];
	bool danger;            // 该节点是否为某模式串的终结点 
	int  cnt;               // 以该节点为终结点的模式串个数
	
	TrieNode()
	{
		fail = NULL;
		memset(next, NULL, sizeof(next));
		danger = false;
		cnt = 0;
	}
	
}*que[MAXQ], *root;

//文本字符串
char  msg[MAXN];
int   N;

void  TrieInsert(char *s)   //插入新的模式串
{
	int  i = 0;
	TrieNode *ptr = root;
	while(s)
	{
		int idx = s - 'a';
		if(ptr->next[idx] == NULL)
			ptr->next[idx] = new TrieNode();
		ptr = ptr->next[idx];
		i++;
	}
	ptr->danger = true;
	ptr->cnt++;
}

void  Init()    // 
{
	int  i;
	char  s[100];
	root = new TrieNode();      // 创建root
	printf("输入模式串数量：");
	scanf("%d", &N);
	for(i = 0; i < N; i++)
	{
		printf("输入第%d个模式串（共%d个）：",i,N);
		scanf("%s", s);
		TrieInsert(s);         // 插入新的模式串
	}
}

void  Build_AC_Automation()     // 创建ac状态机
{
	int  rear = 1, front = 0, i;
	que[0] = root;
	root->fail = NULL;
	while(rear != front)
	{
		TrieNode *cur = que[front++];
		for(i = 0; i < 26; i++)
			if(cur->next != NULL)
			{
				if(cur == root)
					cur->next->fail = root;
				else
				{
					TrieNode *ptr = cur->fail;
					while(ptr != NULL)
					{
						if(ptr->next != NULL)
						{
							cur->next->fail = ptr->next;
							if(ptr->next->danger == true)
								cur->next->danger = true;
							break;
						}
						ptr = ptr->fail;
					}
					if(ptr == NULL) cur->next->fail = root;
				}
				que[rear++] = cur->next;
			}
	}
}

int  AC_Search()    // ac查找
{
	int  i = 0, ans = 0;
	TrieNode *ptr = root;
	while(msg)
	{
		int  idx = msg-'a';
		while(ptr->next[idx] == NULL && ptr != root) ptr = ptr->fail;
		ptr = ptr->next[idx];
		if(ptr == NULL) ptr = root;
		TrieNode *tmp = ptr;
		while(tmp != NULL )&& tmp->cnt != -1)
		{
			ans += tmp->cnt;	//统计文本中出现过的不同模式串数量
			tmp->cnt = -1;//对于每个模式串的出现只计算一次，如统计所有出现则应注释该行
			tmp = tmp->fail;
		}
		i++;
	}
	return  ans;
}

int  main()     // 主函数
{
	int  T;
	printf("输入测试次数：");
	scanf("%d", &T);
	while(T--)
	{
		Init();  // 初始化
		Build_AC_Automation();
		//文本 
		printf("输入匹配文本：");
		scanf("%s", msg);
		printf("%dn", AC_Search());
	}
	getchar();
    return 0;
}
