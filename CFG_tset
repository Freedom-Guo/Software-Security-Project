//
//  main.cpp
//  A_3
//
//  Created by 郭倜维 on 2018/10/20.
//  Copyright © 2018 郭倜维. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <ctype.h>

#define MAX 200

typedef struct Func //函数信息链表
{
    char back_value[10];
    char func_name[30];
    int para_num;
    char para_type_1[10];
    char para_type_2[10];
    char para_type_3[10];
    char para_remain[30];
    struct Func *next;
}Func;

typedef struct Functree //函数体中子函数链表
{
    char func_name[30];
    struct Functree *next;
}Functree;

typedef struct Tree //函数体链表
{
    char main_func_name[30]; //函数体名称
    struct Functree *head;
    struct Tree *next;
}Tree;

void Pre_deal(FILE* F_In,FILE* F_Out,char In_name[30],char Out_name[20]);
struct Func* Func_Chain_Create(FILE* pf);
struct Tree* Tree_create(FILE* pf);
bool Judge_Func(char str[MAX]);
bool Judge_body(char str[MAX]);
void Func_Analyze(char str[MAX],struct Func* func);
int Count_Char(char str_1[200],char str_2[]);
void Show(struct Tree* tree) ;

int main(int argc, const char * argv[])
{
    int i=0, j=0, c1=0, c2=0;
    int flag_1=0 ,flag_2=0;
    double rate_line=0.0,rate=0.0;
    double rate_chain[20]={0};
    FILE *pf1,*pf2,*pf3,*pf4;
    struct Tree* tree_1;
    struct Tree* tree_1_head;
    struct Functree* functree_1;
    struct Tree* tree_2;
    struct Tree* tree_2_head;
    struct Functree* functree_2;
    struct Functree* functree_2_head;
    //文件名
    char file_name_in_1[30]={0};
    char file_name_out_1[30]={0};
    //char file_name_in_2[30]={0};
    //char file_name_out_2[30]={0};
    
    char tree_name_1[30]={0};
    char tree_name_2[30]={0};
    char func_name_1[30]={0};
    char func_name_2[30]={0};
    
    //预处理文件1
    printf("请输入文件1名：\n");
    scanf("%s",file_name_in_1);
    pf1=fopen(file_name_in_1,"r");
    printf("请输入文件1名：\n");
    scanf("%s",file_name_out_1);
    pf2=fopen(file_name_out_1,"w");
    Pre_deal(pf1,pf2,file_name_in_1,file_name_out_1);
    fclose(pf1);
    fclose(pf2);
    pf2=fopen(file_name_out_1,"r");
    tree_1_head=Tree_create(pf2);
    tree_1 = tree_1_head;
    Show(tree_1);
    
    
    char in_name_2[50][30]={"1.txt","12.txt","13.txt","14.txt","15.txt","26.txt","37.txt","48.txt","29.txt","10.txt"};
    char out_name_2[50][30]={"b.txt","c,txt","d.txt","e,txt","f.txt","g.txt","h.txt","i.txt","j.txt","k.txt"};
    int k;
    for(k=0; k<10; k++)
    {
        i=0;
        j=0;
        c1=0;
        c2=0;
        rate_line=0.0;
        rate=0.0;
        flag_1=0;
        flag_2=0;
        //预处理文件2
        //printf("请输入文件2名：\n");
        //scanf("%s",file_name_in_2);
        pf3=fopen(in_name_2[k],"r");
        //printf("请输入文件2名：\n");
        //scanf("%s",out_name_2[);
        pf4=fopen(out_name_2[k],"w");
        Pre_deal(pf3,pf4,in_name_2[k],out_name_2[k]);
        fclose(pf3);
        fclose(pf4);
        pf4=fopen(out_name_2[k],"r");
        //生成文件的函数体链表
        tree_2=Tree_create(pf4);
        Show(tree_2);
        
        //找到主函数相同的两条链,比较这两条链中函数名
        tree_2_head = tree_2->next;
        while(tree_1->next != NULL)
        {
            flag_1 = 0; //
            tree_1 = tree_1->next;
            functree_1 = tree_1->head; //functree_1指向tree_1指向的函数链表
            functree_1 = functree_1->next;
            c2++;
            strcpy(tree_name_1, functree_1->func_name); //获得函数体链表1的函数体名字
            while(tree_2->next != NULL)
            {
                tree_2 = tree_2->next;
                functree_2 = tree_2->head;
                functree_2 = functree_2->next; //指向函数体函数链表函数体名字
                strcpy(tree_name_2, functree_2->func_name);
                if(!strcmp(tree_name_1, tree_name_2)) //比较函数体名字是否相同
                {
                    flag_1 = 1;
                    functree_2_head = functree_2;
                    while(functree_1->next != NULL)
                    {
                        flag_2 = 1;
                        functree_2 = functree_2_head; //指向函数体2的函数链表首节点
                        functree_1 = functree_1->next; //函数体1的函数链表中的函数
                        strcpy(func_name_1, functree_1->func_name);
                        i++; //函数体1中的函数个数
                        while(functree_2->next != NULL)
                        {
                            functree_2 = functree_2->next;
                            strcpy(func_name_2, functree_2->func_name);
                            if(!strcmp(func_name_1,func_name_2))
                                c1++; //函数体1和2中函数名相同的个数
                        }
                    }
                    if(flag_2)
                    {
                        rate_line = c1*100/i;
                        rate_chain[j] = rate_line;
                    }
                    else
                    {
                        rate_chain[j] = 50;
                    }
                    j++;
                    i = 0;
                    c1 = 0;
                    flag_2 = 0;
                }
            }
            tree_2 = tree_2_head;
            if(!flag_1) //不存与在函数体1相同的函数体2
            {
                rate_chain[j] = 0.0;
                j++;
            }
        }
        for(i=0;i<20;i++)
        {
            rate=rate_chain[i]+rate;
        }
        rate=rate/c2; //函数体链表中函数体个数c2
        printf("函数调用关系的相似度至少为：%.3f(百分制)",rate);
        //fclose(pf2);
        fclose(pf4);
        //free(tree_2);
        //free(tree_1);
        tree_1 = tree_1_head;
    }
    
    
    return 0;
}

bool Judge_Func(char str[MAX])
{
    bool flag;
    if(strstr(str,"(")!=NULL)
    {
        if(strstr(str,"char ")!=NULL || strstr(str,"int ")!=NULL || strstr(str,"long ")!=NULL || strstr(str,"float ")!=NULL || strstr(str,"double ")!=NULL || strstr(str,"void ")!=NULL)
            flag=true;
        else
            flag=false;
    }
    else
        flag=false;
    return flag;
}

int Count_Char(char str_1[200],char str_2[])
{
    int n = 0;
    unsigned long len = strlen(str_2);
    do
    {
        str_1=strstr(str_1,str_2);
        if(str_1!=NULL)
        {
            n++;
            str_1=str_1+len;
        }
        else
            break;
    }
    while(*str_1!='\0');
    return n;
}

void Func_Analyze(char str[MAX],struct Func* func)
{
    int c1=0;
    sscanf(str,"%[^ ]",func->back_value);
    str=strstr(str," ");
    str++;
    sscanf(str,"%[^(]",func->func_name);
    str=strstr(str,"(");
    str++;
    c1=Count_Char(str,",");
    func->para_num=c1+1;
    switch(c1)
    {
        case 0:
            sscanf(str,"%[^ ]",func->para_type_1);
            break;
        case 1:
            sscanf(str,"%[^ ]",func->para_type_1);
            str=strstr(str,",");
            str++;
            sscanf(str,"%[^ ]",func->para_type_2);
            break;
        case 2:
            sscanf(str,"%[^ ]",func->para_type_1);
            str=strstr(str,",");
            str++;
            sscanf(str,"%[^ ]",func->para_type_2);
            str=strstr(str,",");
            str++;
            sscanf(str,"%[^ ]",func->para_type_3);
            break;
        default:
            sscanf(str,"%[^ ]",func->para_type_1);
            str=strstr(str,",");
            str++;
            sscanf(str,"%[^ ]",func->para_type_2);
            str=strstr(str,",");
            str++;
            sscanf(str,"%[^ ]",func->para_type_3);
            str=strstr(str,",");
            str++;
            sscanf(str,"%[^)]",func->para_remain);
            break;
    }
}

struct Func* Func_chain_Create(FILE* pf) //产生函数链表
{
    char buf[MAX]={0};
    struct Func *head,*tail,*_new;
    head=(struct Func*)malloc(sizeof(struct Func));
    tail=head;
    tail->next=NULL;
    while(!feof(pf))
    {
        fgets(buf,MAX,pf);
        if(Judge_Func(buf))
        {
            _new=(struct Func*)malloc(sizeof(struct Func));
            Func_Analyze(buf,_new);
            tail->next=_new;
            tail=_new;
            tail->next=NULL;
        }
    }
    rewind(pf); //将pf指向文件开头
    return head;
}

bool Judge_body(char str[MAX])
{
    int flag;
    if(strstr(str,"(")!=NULL)
    {
        if(strstr(str,"int")!=NULL || strstr(str,"char")!=NULL || strstr(str,"long")!=NULL || strstr(str,"double")!=NULL || strstr(str,"float")!=NULL || strstr(str,"void")!=NULL)
        {
            if(strstr(str,";")==NULL)
            {
                flag=true;
            }
            else
                flag=false;
        }
        else
            flag=false;
    }
    else
        flag=false;
    return flag;
}

struct Tree* Tree_create(FILE* pf)
{
    char buf[MAX]={0};
    char buf_1[MAX]={0};
    char* buffer;
    int brace_l=0,brace_r=0,brace=0;
    struct Tree *tree,*tree_tail,*tree_new;
    struct Functree *func_head,*func_tail,*func_new;
    struct Func *func_1,*func_2;
    
    func_1=Func_chain_Create(pf);
    
    tree=(struct Tree*)malloc(sizeof(struct Tree));//tree为头指针
    tree_tail=tree;
    tree_tail->next=NULL;
    
    while(!feof(pf))
    {
        fgets(buf_1, MAX, pf);
        if(Judge_body(buf_1))
        {
            
            func_head = (struct Functree*)malloc(sizeof(struct Functree));
            func_tail = func_head; //函数链表头节点
            func_tail->next = NULL;
            
            func_new = (struct Functree*)malloc(sizeof(Functree));
            buffer = strstr(buf_1, " ");
            buffer ++;
            //将函数体名字存储在函数体链表中
            //sscanf(buffer, "%[^(]", tree_tail->main_func_name);
            //将函数体名字存储在函数链表的首节点
            sscanf(buffer, "%[^(]", func_new->func_name);
            func_tail->next = func_new;
            func_tail = func_new;
            func_tail->next = NULL;
            
            brace_l = Count_Char(buf_1, "{");
            brace = brace + brace_l;
            
            do //求一个函数体的子函数链表
            {
                fgets(buf_1, MAX, pf);
                brace_l = Count_Char(buf_1, "{");
                brace = brace + brace_l;
                brace_r = Count_Char(buf_1, "}");
                brace = brace - brace_r;
                
                func_2 = func_1->next;
                
                while(func_2->next != NULL)
                {
                    if(strstr(buf_1, func_2->func_name))
                    {
                        func_new = (struct Functree*)malloc(sizeof(struct Functree));
                        strcpy(func_new->func_name, func_2->func_name);
                        func_tail->next = func_new;
                        func_tail = func_new;
                        func_tail->next = NULL;
                    }
                    func_2 = func_2->next;
                }
                //fgets(buf_1, MAX, pf);
            }while(brace);
            
            tree_new = (struct Tree*)malloc(sizeof(struct Tree));
            tree_new->head = func_head;
            tree_tail->next = tree_new;
            tree_tail = tree_new;
            tree_tail->next = NULL;
        }
    }
    return tree;
}

//预处理函数
void Pre_deal(FILE* F_In,FILE* F_Out,char In_name[30],char Out_name[20])
{
    char line[MAX];
    char line_temp[MAX];
    char *pc;
    char *Left_flag,*Right_flag;  //注释符检测左标志与右标志
    F_In=fopen(In_name,"r"); //打开输入文件
    F_Out=fopen(Out_name,"w");  //打开输出文件
    
    while(!feof(F_In)) //判断文件尾
    {
        while(fgets(line,MAX,F_In)) //逐行读取文件 遇到换行符结束
        {
            Left_flag=strstr(line,"/*"); //是否存在 /*
            if(Left_flag) //找到左标志
            {
                *Left_flag='\n'; //去掉注释内容
                *(Left_flag+1)='\0';
                strcpy(line_temp,line);
                Right_flag=strstr(Left_flag+2,"*/");  //是否存在 */
                while(Right_flag == NULL) //该行不存在右标志，继续读取下一行，直到找到为止
                {
                    fgets(line,MAX,F_In);
                    Right_flag=strstr(line,"*/");
                }
                strcpy(line,line_temp);
            }
            pc=strstr(line,"#"); //预编译语句判断
            if(pc)
            {
                *pc='\n'; //去掉预编译语句
                *(pc+1)='\0';
            }
            pc=strstr(line,"//"); //注释符判断
            if(pc)
            {
                *pc='\n'; //去掉注释内容
                *(pc+1)='\0';
            }
            pc=line;
            while(isspace(*pc)) //去掉字符串开头的空格
                pc++;
            
            fputs(pc,F_Out);  //逐行写入文件
        }
    }
    fclose(F_In);
    fclose(F_Out);
}

void Show(struct Tree* tree) //打印函数体中的函数链表
{
    printf("\n");
    struct Functree* q;
    while(tree->next!=NULL)
    {
        tree=tree->next;
        q=tree->head;
        while(q->next!=NULL)
        {
            q=q->next;
            printf("%s ",q->func_name);
        }
        printf("\n");
    }
    printf("\n\n");
}
