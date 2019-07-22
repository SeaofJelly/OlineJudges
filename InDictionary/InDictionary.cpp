#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <stdlib.h>

#define WRONG_WORD_CAPACITY 25000
#define MAX_LENGTH 50
int stringqueue = 1;

typedef struct Trie_Node
{
	int isWord;
	struct Trie_Node* next[26];
} Trie_Node;

//Constructr
Trie_Node* createTrieNode()
{
	Trie_Node *node = (Trie_Node*)malloc(sizeof(Trie_Node));
	node->isWord=0;
	int c5 = 0;
	for(;c5<26;c5++)
	node->next[c5]=NULL;
	return node;
}

void Trie_Insert(Trie_Node* T,char *str)
{
	Trie_Node* node = T;
	char *p=str;
	int id=0;
	while(*p)
	{
		id=int(*p-'a');
		if(id<0 || id > 26)
		{
			p++;
			continue;
		}
		if(node->next[id]==NULL)
		node->next[id]=createTrieNode();
		node=node->next[id];
		++p;
	}
	node->isWord=1;
}

int Trie_Search(Trie_Node* T,char str[],int s,int e)
{
	Trie_Node* node = T;
	int id;
	int c4 = s;
	for(;c4<=e;c4++)
	{
		id=int (str[c4]-'a');
		if(node->next[id]==NULL)
		return 0;
		node=node->next[id];
	}
	if(node->isWord)
	return 1;
	else
	return 0;
}
 
void del(Trie_Node *root)
{
	int c6=0;
	for(;c6<10;c6++)
	if(root->next[c6]) 
	del(root->next[c6]);
	free(root);
}

//储存单词位置用
typedef struct Mispell_Position
{
	int data;
	Mispell_Position *next;
} Mispell_Position;

//构造函数 
Mispell_Position *createPosition()
{
	Mispell_Position *node = (Mispell_Position*)malloc(sizeof(Mispell_Position));
	node->data = 0;
	node->next = NULL;
	return node;
}

//查找是否已有单词用,若有，返回在单词队列中的位置 
typedef struct Mispell_Node
{
	int isWord;
	int positioninqueue;
	struct Mispell_Node* next[26];
} Mispell_Node;

//构造函数 
Mispell_Node* createWordNode()
{
	Mispell_Node* node = (Mispell_Node*)malloc(sizeof(Mispell_Node));
	node->isWord=0;
	node->positioninqueue = 0;
	int c7=0;
	for(c7=0;c7<26;c7++)
	node->next[c7] = NULL;
	return node;
}

//8存在就创建，存在就返回位置 
int Mispell_Insert(Mispell_Node* T,char str[],int s,int e)
{
	int unexisting = 0;
	Mispell_Node* node = T;
	int id=0;
	int u=s;
	for(;u<=e;u++ )
	{
		id=int(str[u]-'a');
		if(id<0||id>26)
		continue;
		if(node->next[id]==NULL)
		{
			node->next[id] = createWordNode();
			unexisting = 1;
		}
		node = node->next[id];
	}
	
	if(!unexisting && node->isWord)
	{
		return node->positioninqueue;
	}
	else
	{
		node->positioninqueue = stringqueue;  
		node->isWord=1;
		return 0;
	}
	return 0;
}

//用于输出的队列 
typedef struct String_Queue
{
	char str[MAX_LENGTH];
	int count;
	Mispell_Position *pos;
	Mispell_Position *head_pos;
} String_Queue;

//构造函数 
String_Queue* createString()
{
	String_Queue *queue = (String_Queue*)malloc(sizeof(String_Queue));
	queue->count = 1;
	int c3 = 0;
	for(;c3 < MAX_LENGTH;c3 ++)
	queue->str[c3] = '\0';
	queue->pos = NULL;
	queue->head_pos = NULL;
	return queue;
}

//8存在错误单词时的入队 
void Enque(String_Queue *que[],char *enstr,int s,int e,int word_position)	
{
	int u = 0;
	que[stringqueue]=createString();	
	int c2;
	for(c2 = s;c2 <= e;c2 ++)
	{
		que[stringqueue]->str[u++] = enstr[c2];
	}
	que[stringqueue]->pos = createPosition();
	que[stringqueue]->pos->data = word_position;
	que[stringqueue]->head_pos = que[stringqueue]->pos;
	que[stringqueue]->head_pos->data = word_position;
	stringqueue ++;
}

//已存在该字符串时的入队 
void DoubleEnque(String_Queue *strqueue[],int positioninque,int word_position)
{
	strqueue[positioninque]->pos->next = createPosition();
	strqueue[positioninque]->pos = strqueue[positioninque]->pos->next;
	strqueue[positioninque]->pos->data = word_position;
	strqueue[positioninque]->count += 1;
}

int cmpfun (const void * a, const void * b)
{
	if(a == NULL)
	return -1;
	if(b==NULL)
	return 1;
	String_Queue **temp1 = (String_Queue **)a;
	String_Queue **temp2 = (String_Queue **)b;
	if ((*temp2)->count-(*temp1)->count)
	{
		return (*temp2)->count-(*temp1)->count;
	}
	else
	{
		return strcmp((*temp1)->str,(*temp2)->str);
	}
}

int WriteFile(String_Queue *sq[],FILE* OUT)
{
	qsort(sq,stringqueue,sizeof(String_Queue*),cmpfun);
	int i=1;
	for(; i < stringqueue; i++)
	{
		int j = 0;
		for(;sq[i]->str[j] != '\0';j++)
		{
			fprintf(OUT,"%c",sq[i]->str[j]);
		}
		fprintf(OUT," %d",sq[i]->count);
		Mispell_Position *temp = sq[i]->head_pos;
		while(temp)
		{
			fprintf(OUT," %d",temp->data);
			temp = temp->next;
		}
		fprintf(OUT,"\n");
	}
}

int main()
{
	//////////////////////////
	//当前词序 /单词起始位置 
	/////////////////////////
	FILE *out = fopen("test_misspelling.txt","w");
	int char_counts = -1;
	int prev_char_counts = 0;
	String_Queue *stringq[WRONG_WORD_CAPACITY];
	if(1)
	{
		int c1;
		for(c1 = 0; c1 < WRONG_WORD_CAPACITY;c1 ++)
		stringq[c1] = NULL; 
		stringq[0] = createString();
		stringq[0]->count = 99999999;
	}
	Trie_Node* root=createTrieNode();
	Mispell_Node* roooot = createWordNode();
	char dictionary_word[MAX_LENGTH];
	FILE *f1 = fopen("test_dictionary.txt", "r");
    if(!f1)
    abort();
    /////////// 
    //读进词典 
    ///////////
    while(!feof(f1))
    {
		memset(dictionary_word, 0, sizeof(dictionary_word));
        fgets(dictionary_word, sizeof(dictionary_word) - 1, f1);
		Trie_Insert(root,dictionary_word);
	}
    fclose(f1);
    /////////////
    //比对单词 
    /////////////
    FILE *f2 = fopen("test_article.txt", "r");
    char article_word[1999];
    while(!feof(f2))
    {
		memset(article_word, 0, sizeof(article_word));
        fgets(article_word, sizeof(article_word) - 1, f2);
        int start = 0,endl = 0;
        int start_flag = 0,end_flag = 0,line_length = strlen(article_word);
        char word[MAX_LENGTH];
        if(line_length == 0)
        continue;
        int i;
        for(i = 0; i < line_length;i++)
        {
        	char_counts++;
        	//回车则读取下一行 
        	if(article_word[i] == 10)
        	{
        		endl = 1;
			}
        	///////////////
			//单词比对 
			///////////////
        	if(( article_word[i] <= 'z' && article_word[i] >= 'a') || ( article_word[i] >= 'A' && article_word[i] <= 'Z' ))
        	{
        		article_word[i]=(article_word[i]>='a'?article_word[i]:article_word[i]+32);
        	    if(start)
            	{
        	        continue;
		    	}
		     	else
		    	{
					start_flag = i;
					start = 1;
					prev_char_counts = char_counts;
				}
        	}
			else
			{
				//8是正确单词的处理 
				if(start)
        		{
 					end_flag = i-1;
					start = 0;
					if(Trie_Search(root,article_word,start_flag,end_flag))
					continue;
					else
					{
						int position = Mispell_Insert(roooot,article_word,start_flag,end_flag);
						if(!position)
						{
							Enque(stringq,article_word,start_flag,end_flag,prev_char_counts);
						}
						else
						{
							DoubleEnque(stringq,position,prev_char_counts);
						}
					}
				}
				else
				{
					continue;
				}
			}
			if(endl)
			break;
		}
    }
    ////////////////
    //写入错误单词
    ////////////////
	WriteFile(stringq,out);
	fclose(f2);
	fclose(out);
	return 0;
}
