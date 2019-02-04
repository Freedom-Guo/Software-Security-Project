//
//  main.cpp
//  B_5
//
//  Created by 郭倜维 on 2018/10/24.
//  Copyright © 2018 郭倜维. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX 200

//结构体定义
//普通变量链表
typedef struct Variate
{
    char type[10];
    char name[20];
    int size;
    int row;
    struct Variate* v_next;
}Variate;
//敏感函数链表
typedef struct Func_m
{
    int row;
    char name[10];
    char des[20];
    char sou[20];
    int n;
    struct Func_m* m_next;
}Func_m;
//函数体链表
typedef struct Func
{
    int start_row;
    int end_row;
    struct Variate* va_chain;
    struct Func_m* mf_chain;
    struct Func* func_next;
}Func;

//函数list
void Pre_Func_deal(FILE* F_In,FILE* F_Out,char In_name[30],char Out_name[20]); //预处理函数
bool Judge_body(char str[MAX]); //函数体判断函数
int Count_Char(char str_1[200],char str_2[]); //计算字符str2出现次数
void Judge_variate_analyze(char str[MAX],struct Variate* var); //普通变量判断和分析函数
bool Judge_func_m(char str[MAX]);  //敏感函数判断函数
void Func_m_analyze(char str[MAX],struct Func_m* m_func); //敏感函数分析
struct Func* Func_chain(FILE *pf); //函数体链表生成函数
void Show(FILE* pf,int row,char buf[MAX]); //输出溢出函数

//主函数
int main(int argc, const char * argv[])
{
    FILE *pf1,*pf2;
    char stroutput[MAX];
    char In_name[50][30]={"1.txt","12.txt","13.txt","14.txt","15.txt","26.txt","37.txt","48.txt","29.txt","10.txt"};
    char Out_name[50][30]={"b.txt","c,txt","d.txt","e,txt","f.txt","g.txt","h.txt","i.txt","j.txt","k.txt"};
    //文件操作
    //printf("请输入要检查的文件名：\n");
    //scanf("%s",In_name);
    //printf("请输入要存入的文件名：\n");
    //scanf("%s",Out_name);
    int k;
    for(k=0; k<10; k++)
    {
        printf("%s:\n",In_name[k]);
        char str_des[20]={0};
        char str_sou[20]={0};
        int v_size_des=0;
        int v_size_sou=0;
        int n=0,flag=0;
        int over_flow=0;
        struct Func *f;
        struct Variate *v;
        struct Func_m *m;
        pf1=fopen(In_name[k],"r");
        pf2=fopen(Out_name[k],"w");
        Pre_Func_deal(pf1,pf2,In_name[k],Out_name[k]);
        fclose(pf1);
        fclose(pf2);
        //链表生成
        pf2=fopen(Out_name[k] ,"r");
        f=(struct Func*)malloc(sizeof(struct Func));
        v=(struct Variate*)malloc(sizeof(struct Variate));
        m=(struct Func_m*)malloc(sizeof(struct Func_m));
        f=Func_chain(pf2);
        rewind(pf2);
        
        while(f->func_next!=NULL)
        {
            //链表首节点
            f = f->func_next;
            v = f->va_chain;
            m = f->mf_chain;
            
            while (m->m_next != NULL)
            {
                flag = 1;
                m = m->m_next;
                //取出敏感函数的实参
                strcpy(str_des,m->des);
                strcpy(str_sou,m->sou);
                n = m->n;
                while(v->v_next != NULL)
                {
                    v=v->v_next;
                    //获取敏感函数使用时变量的大小
                    if(!strcmp(str_des,v->name))
                        v_size_des=v->size;
                    if(!strcmp(str_sou,v->name))
                        v_size_sou=v->size;
                }
                //对不同敏感函数的溢出进行判断
                if(!strcmp(m->name,"strcpy") || !strcmp(m->name,"sscanf"))
                {
                    if(v_size_des<v_size_sou)
                        over_flow=1;              //明显大于缓冲空间的，一定会溢出
                    else
                        over_flow=3;              //没有明显大于，不会溢出
                }
                else
                {
                    if(!strcmp(m->name,"strncpy") || !strcmp(m->name,"memcpy"))
                    {
                        if(v_size_des<n)
                            over_flow=1;
                        else
                            over_flow=3;
                    }
                    else
                    {
                        if(!strcmp(m->name,"strcat"))
                        {
                            if(v_size_des<(v_size_des+v_size_sou))
                                over_flow=1;
                            else
                                over_flow=3;
                        }
                    }
                }
                if(over_flow==1)
                {
                    //printf("%s:\n",In_name[k]);
                    printf("Overflow in line %d:\n",m->row);
                    Show(pf2,m->row,stroutput);//打印溢出函数
                }
            }
            if(flag==0)
                //printf("%s:\n",In_name[k]);
                printf("No overflow:No such a function can cause overflow!\n");  //无敏感函数
            else
                if(over_flow==3)
                    //printf("%s:\n",In_name[k]);
                    printf("No overflow:Function in line %d cannot cause overflow!\n",m->row);         //有敏感函数但不会产生溢出
            printf("\n");
        }
        fclose(pf2);
        free(f);
        free(m);
        free(v);
    }
    
    return 0;
}

//预处理文件函数
void Pre_Func_deal(FILE* F_In,FILE* F_Out,char In_name[30],char Out_name[20])
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

//函数体链表生成
struct Func* Func_chain(FILE *pf)
{
    int row=0;
    int brace_l=0, brace_r=0, brace=0;
    char buf_1[MAX]={0};
    char buf_2[MAX]={0};
    struct Func *func_head,*func_tail,*func_new;
    struct Variate *v_head,*v_tail,*v_new;
    struct Func_m *m_head,*m_tail,*m_new;
    //建立函数体链表
    func_head=(struct Func*)malloc(sizeof(struct Func));
    func_tail = func_head;
    func_tail->func_next = NULL;
    
    while (!feof(pf))
    {
        fgets(buf_1, MAX, pf);
        row++;
        if (Judge_body(buf_1))
        {
            //函数体开始的行数
            func_new = (struct Func*)malloc(sizeof(struct Func));
            func_new->start_row = row;
            //建立普通变量链表
            v_head = (struct Variate*)malloc(sizeof(struct Variate));
            v_tail = v_head;
            v_tail->v_next = NULL;
            //建立敏感函数链表
            m_head = (struct Func_m*)malloc(sizeof(struct Func_m));
            m_tail = m_head;
            m_tail->m_next = NULL;
            //函数体指向对应的普通变量和敏感函数链表
            func_new->mf_chain = m_head;
            func_new->va_chain = v_head;
            //链接函数体链表
            func_tail->func_next=func_new;
            func_tail=func_new;
            func_tail->func_next=NULL;
            
            brace_l = Count_Char(buf_1,"{");
            brace = brace + brace_l;
            do
            {
                fgets(buf_2,MAX,pf);
                row++;
                brace_l = Count_Char(buf_2,"{");
                brace = brace + brace_l;
                brace_r = Count_Char(buf_2,"}");
                brace = brace - brace_r;
                if(strstr(buf_2,"char ")!=NULL || strstr(buf_2,"int ")!=NULL || strstr(buf_2,"long ")!=NULL || strstr(buf_2,"float ")!=NULL || strstr(buf_2,"double ")!=NULL)
                {
                    v_new = (struct Variate*)malloc(sizeof(struct Variate));
                    //分析变量v_new的信息
                    Judge_variate_analyze(buf_2, v_new);
                    v_new->row = row;
                    //链接普通变量链表
                    v_tail->v_next = v_new;
                    v_tail = v_new;
                    v_tail->v_next = NULL;
                }
                //判断敏感函数
                if(Judge_func_m(buf_2))
                {
                    m_new = (struct Func_m*)malloc(sizeof(struct Func_m));
                    m_new->row =row;
                    //分析敏感函数
                    Func_m_analyze(buf_2, m_new);
                    //链接敏感函数链表
                    m_tail->m_next = m_new;
                    m_tail = m_new;
                    m_tail->m_next = NULL;
                }
            }
            while(brace);
        }
    }
    return func_head;
}
//函数体判断函数
bool Judge_body(char str[MAX])
{
    bool flag;
    if(strstr(str,"(")!=NULL)
    {
        if(strstr(str,"char")!=NULL || strstr(str,"int")!=NULL || strstr(str,"long")!=NULL || strstr(str,"float")!=NULL || strstr(str,"double")!=NULL || strstr(str,"void")!=NULL)
        {
            if(strstr(str,";")==NULL)
                flag = true;
            else
                flag = false;
        }
        else
            flag = false;
    }
    else
        flag = false;
    return flag;
}
//字符出现次数计算函数
int Count_Char(char str_1[200], char str_2[])
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
//变量分析函数
void Judge_variate_analyze(char str[MAX],struct Variate* var)
{
    char temp_1[100]={0};
    char temp_2[100]={0};
    
    if(strstr(str,"[")!=NULL) //数组变量
    {
        if(strstr(str,"char ")!=NULL || strstr(str,"int ")!=NULL || strstr(str,"long ")!=NULL || strstr(str,"float ")!=NULL || strstr(str,"double ")!=NULL)
            sscanf(str,"%[^ ]",var->type);
        
        str=strstr(str," ");
        str++;
        sscanf(str,"%[^[]",var->name);
        str=strstr(str,"[");
        str++;
        if(*str != ']')          //直接给出数组定义
        {
            sscanf(str,"%[^]]",temp_1);
            var->size=atoi(temp_1);
        }
        else                   //初始化数组
        {
            //暂时没有考虑其他类型数组
            str=strstr(str,"=");
            sscanf(str,"%[^;]",temp_2);
            var->size=strlen(temp_2)-2;
        }
    }
    else //普通变量
    {
        if(strstr(str,"char ")!=NULL || strstr(str,"int ")!=NULL || strstr(str,"long ")!=NULL || strstr(str,"float ")!=NULL || strstr(str,"double ")!=NULL)
        {
            sscanf(str,"%[^ ]",var->type); //变量类型
            //变量存储空间大小
            if(!strcmp(var->type,"char"))
                var->size=1;
            if(!strcmp(var->type,"int"))
                var->size=4;
            if(!strcmp(var->type,"double"))
                var->size=8;
            if(!strcmp(var->type,"long"))
                var->size=4;
            if(strstr(str,"=")==NULL) //没有初始化
            {
                str=strstr(str," ");
                str++;
                sscanf(str,"%[^;]",var->name);
            }
            else //初始化
            {
                str=strstr(str," ");
                str++;
                sscanf(str,"%[^=]",var->name);
            }
        }
    }
}
//判断是否为敏感函数
bool Judge_func_m(char str[MAX])
{
    bool flag;
    if(strstr(str,"strcpy")!=NULL || strstr(str,"strncpy")!=NULL || strstr(str,"memcpy")!=NULL ||strstr(str,"strcat")!=NULL || strstr(str,"strncpy")!=NULL || strstr(str,"sscacnf")!=NULL)
        flag = true;
    else
        flag = false;
    return flag;
}
//敏感函数分析
void Func_m_analyze(char str[MAX],struct Func_m* m_func)
{
    char temp[20] = {0};
    if(strstr(str,"strcpy")!=NULL || strstr(str,"strncpy")!=NULL || strstr(str,"memcpy")!=NULL ||strstr(str,"strcat")!=NULL || strstr(str,"sscanf")!=NULL)
    {
        sscanf(str,"%[^(]",m_func->name);
        if(!strcmp(m_func->name,"strcpy") || !strcmp(m_func->name,"strcat"))
        {
            str=strstr(str,"(");
            str++;
            sscanf(str,"%[^,]",m_func->des); //目的参数
            str=strstr(str,",");
            str++;
            sscanf(str,"%[^)]",m_func->sou); //源参数
        }
        else
        {
            if(!strcmp(m_func->name,"strncpy") || !strcmp(m_func->name,"memcpy"))
            {
                str=strstr(str,"(");
                str++;
                sscanf(str,"%[^,]",m_func->des);
                str=strstr(str,",");
                str++;
                sscanf(str,"%[^,]",m_func->sou);
                str=strstr(str,",");
                str++;
                sscanf(str,"%[^)]",temp);
                m_func->n=atoi(temp);
            }
            else
            {
                if(!strcmp(m_func->name,"sscanf"))
                {
                    str=strstr(str,"(");
                    str++;
                    sscanf(str,"%[^,]",m_func->sou);
                    str=strstr(str,",");
                    str++;
                    str=strstr(str,",");
                    str++;
                    sscanf(str,"%[^)]",m_func->des);
                }
            }
        }
    }
}

void Show(FILE* pf,int row,char buf[MAX])
{
    int i=0;
    char buf_1[MAX];
    while(i!=row)
    {
        fgets(buf,MAX,pf);
        i++;
    }
    strcpy(buf_1,buf);
    printf("%s",buf_1);
    rewind(pf);
}
