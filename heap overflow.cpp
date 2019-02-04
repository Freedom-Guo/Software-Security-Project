//
//  main.cpp
//  B_4
//
//  Created by 郭倜维 on 2018/10/25.
//  Copyright © 2018 郭倜维. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX 200

//结构体定义
//定义普通变量结构体
typedef struct Variate
{
    char type[10];
    char name[20];
    int size;
    int row;
    struct Variate* v_next;
}Variate;
//定义缓冲区变量结构体
typedef struct Buffer
{
    char type[20];
    char name[20];
    int size;
    struct Buffer* buf_next;
}Buffer;
//定义边界检查语句结构体
typedef struct Border
{
    int row;
    char type[10];
    char cont[50];
    struct Border* b_next;
}Border;
//定义敏感函数结构体
typedef struct Func_m
{
    int row;
    char name[10];
    char des[20];
    char sou[20];
    int n;
    struct Func_m* m_next;
}Func_m;
//定义函数体结构体
typedef struct Func
{
    int start_row;
    int end_row;
    struct Variate* va_chain;
    struct Func_m* mf_chain;
    struct Buffer* buf_chain;
    struct Border* b_chain;
    struct Func* func_next;
}Func;
//函数list
void Pre_Func_deal(FILE* F_In,FILE* F_Out,char In_name[30],char Out_name[20]);//预处理函数
bool Judge_body(char str[MAX]);
int Count_char(char str_1[200],char str_2[]);
bool Judge_func_m(char str[MAX]);
void Func_m_analyze(char str[MAX],struct Func_m* m_func);
void Buffer_analyze(char str[MAX],struct Buffer* buf);
void Variate_analyze(char str[MAX],struct Variate* var);
void Border_analyze(char str[MAX],struct Border* bd);
struct Func* Func_chain(FILE *pf);
void Show(FILE* pf,int row,char buf[MAX]);

int main(int argc, const char * argv[])
{
    FILE *pf1, *pf2;
    char In_name[30]={0};
    char Out_name[30]={0};
    char str_des[20]={0};
    char str_sou[20]={0};
    char str_output[MAX];
    int v_size_des=0;
    int v_size_sou=0;
    int over_flow=0;
    int of;
    int n=0, flag_m=0, flag_b=0;
    struct Func *f;
    struct Variate *v;
    struct Func_m *m;
    struct Buffer *buf;
    struct Border *bd;
    
    //文件操作
    printf("请输入要检查的文件名：\n");
    scanf("%s",In_name);
    printf("请输入要存入的文件名：\n");
    scanf("%s",Out_name);
    pf1=fopen(In_name,"r");
    pf2=fopen(Out_name,"w");
    Pre_Func_deal(pf1,pf2,In_name,Out_name);
    fclose(pf1);
    fclose(pf2);
    
    //链表生成
    pf2=fopen(Out_name,"r");
    f=(struct Func*)malloc(sizeof(struct Func));
    v=(struct Variate*)malloc(sizeof(struct Variate));
    m=(struct Func_m*)malloc(sizeof(struct Func_m));
    buf=(struct Buffer*)malloc(sizeof(struct Buffer));
    bd=(struct Border*)malloc(sizeof(struct Border));
    f=Func_chain(pf2);
    rewind(pf2);
    
    while(f->func_next != NULL)
    {
        //链表首节点
        f = f->func_next;
        v = f->va_chain;
        m = f->mf_chain;
        buf = f->buf_chain;
        bd = f->b_chain;
        
        while(m->m_next != NULL)
        {
            flag_m = 1;
            m = m->m_next;
            //取出敏感函数的实参
            strcpy(str_des,m->des);
            strcpy(str_sou,m->sou);
            n = m->n;
            while(buf->buf_next != NULL)
            {
                buf = buf->buf_next;
                if(!strcmp(str_des,buf->name))
                    v_size_des=buf->size;
                if(!strcmp(str_sou,buf->name))
                    v_size_sou=buf->size;
            }
            if(!strcmp(m->name,"strcpy") || !strcmp(m->name,"sscanf"))
            {
                if(v_size_des<v_size_sou)
                    flag_m=1;              //明显大于缓冲空间的，一定会溢出
                else
                    flag_m=3;              //没有明显大于，不会溢出
            }
            else
            {
                if(!strcmp(m->name,"strncpy") || !strcmp(m->name,"memcpy"))
                {
                    if(v_size_des<n)
                        flag_m=1;
                    else
                        flag_m=3;
                }
                else
                {
                    if(!strcmp(m->name,"strcat"))
                    {
                        if(v_size_des<(v_size_des+v_size_sou))
                            flag_m=1;
                        else
                            flag_m=3;
                    }
                }
            }
        }
        while (bd->b_next != NULL)
        {
            bd = bd->b_next;
            flag_b = 1;
            v = f->va_chain;
            while(v->v_next != NULL)
            {
                v = v->v_next;
                if(strstr(bd->cont, v->name))
                {
                    flag_b = 2;
                    break;
                }
            }
        }
        
        if(flag_m==1 && flag_b==0)
            over_flow=1;
        if(flag_m==1 && flag_b==2)
            over_flow=2;
        if((flag_m==0) || (flag_m==3 && flag_b==0))
            over_flow=3;
        switch(over_flow)
        {
            case 1:
                printf("Overflow in line %d:\n",m->row);
                Show(pf2,m->row,str_output);
                break;
            case 2:
                printf("Possibility of overflow in line %d:\n",m->row);
                Show(pf2,m->row,str_output);
                break;
            case 3:
                printf("No overflow!\n");
                break;
        }
    }
    
    return 0;
}

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

int Count_char(char str_1[200], char str_2[])
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

bool Judge_func_m(char str[MAX])
{
    bool flag;
    if(strstr(str,"strcpy")!=NULL || strstr(str,"strncpy")!=NULL || strstr(str,"memcpy")!=NULL ||strstr(str,"strcat")!=NULL || strstr(str,"strncpy")!=NULL || strstr(str,"sscacnf")!=NULL)
        flag = true;
    else
        flag = false;
    return flag;
}

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

void Buffer_analyze(char str[MAX],struct Buffer* buf)
{
    char temp[MAX]={0};
    if(strstr(str,"[")!=NULL)    //数组变量
    {
        if(strstr(str,"char ")!=NULL || strstr(str,"int ")!=NULL || strstr(str,"long ")!=NULL)
            sscanf(str,"%[^ ]",buf->type);
        str=strstr(str," ");
        str++;
        sscanf(str,"%[^[]",buf->name);
        str=strstr(str,"[");
        str++;
        if(*str!=']')          //直接给出数组定义
        {
            sscanf(str,"%[^]]",temp);
            buf->size=atoi(temp);
        }
        else                   //初始化数组
        {
            str=strstr(str,"=");
            sscanf(str,"%[^;]",temp);
            buf->size=strlen(temp)-2;
        }
    }
    if(strstr(str,"char*")!=NULL || strstr(str,"short*")!=NULL || strstr(str,"int*") || strstr(str,"long*")!=NULL)
    {
        if(strstr(str,"HeapAlloc")==NULL)
        {
            sscanf(str,"%[^*]",buf->type);
            str=strstr(str,"* ");
            str++;str++;
            sscanf(str,"%[^=]",buf->name);
        }
        else
        {
            sscanf(str,"%[^=]",buf->name);
            str=strstr(str,"(");
            str++;
            sscanf(str,"%[^)]",buf->type);
            str=strstr(str,",");
            str++;
            str=strstr(str,",");
            str++;
            sscanf(str,"%[^)]",temp);
            buf->size=atoi(temp);
        }
    }
}

void Variate_analyze(char str[MAX],struct Variate* var)
{
    if(strstr(str,"char ")!=NULL || strstr(str,"int ")!=NULL || strstr(str,"long ")!=NULL || strstr(str,"double ")!=NULL || strstr(str,"float ")!=NULL)
    {
        sscanf(str,"%[^ ]",var->type);
        if(!strcmp(var->type,"char"))
            var->size=1;
        if(!strcmp(var->type,"int"))
            var->size=4;
        if(!strcmp(var->type,"double"))
            var->size=8;
        if(!strcmp(var->type,"long"))
            var->size=4;
        if(strstr(str,"=")==NULL)
        {
            str=strstr(str," ");
            str++;
            sscanf(str,"%[^;]",var->name);
        }
        else
        {
            str=strstr(str," ");
            str++;
            sscanf(str,"%[^=]",var->name);
        }
    }
}

struct Func* Func_chain(FILE *pf)
{
    int row=0;
    int brace_l=0, brace_r=0, brace=0;
    char buf_1[MAX]={0};
    char buf_2[MAX]={0};
    struct Func *func_head,*func_tail,*func_new;
    struct Variate *v_head,*v_tail,*v_new;
    struct Func_m *m_head,*m_tail,*m_new;
    struct Buffer *buf_head,*buf_tail,*buf_new;
    struct Border *b_head,*b_tail,*b_new;
    
    func_head = (struct Func*)malloc(sizeof(struct Func));
    func_tail = func_head;
    func_tail->func_next = NULL;
    
    while (!feof(pf))
    {
        fgets(buf_1, MAX, pf);
        row++;
        
        func_new = (struct Func*)malloc(sizeof(struct Func));
        func_new->start_row = row;
        
        buf_head = (struct Buffer*)malloc(sizeof(struct Buffer));
        buf_tail = buf_head;
        buf_tail->buf_next = NULL;
        
        v_head = (struct Variate*)malloc(sizeof(struct Variate));
        v_tail = v_head;
        v_tail->v_next = NULL;
        
        b_head = (struct Border*)malloc(sizeof(struct Border));
        b_tail = b_head;
        b_tail->b_next = NULL;
        
        m_head = (struct Func_m*)malloc(sizeof(struct Func_m));
        m_tail = m_head;
        m_tail->m_next = NULL;
        
        func_new->va_chain = v_head;
        func_new->mf_chain = m_head;
        func_new->buf_chain = buf_head;
        func_new->b_chain = b_head;
        
        func_tail->func_next=func_new;
        func_tail=func_new;
        func_tail->func_next=NULL;
        
        brace_l = Count_char(buf_1,"{");
        brace = brace + brace_l;
        
        do
        {
            fgets(buf_2,MAX,pf);
            row++;
            brace_l = Count_char(buf_2,"{");
            brace = brace + brace_l;
            brace_r = Count_char(buf_2,"}");
            brace = brace - brace_r;
            
            if(strstr(buf_2,"char")!=NULL ||strstr(buf_2,"short")!=NULL || strstr(buf_2,"int")!=NULL || strstr(buf_2,"long")!=NULL)
            {
                if(strstr(buf_2,"*")!=NULL || strstr(buf_2,"[")!=NULL)
                {
                    buf_new = (struct Buffer*)malloc(sizeof(struct Buffer));
                    Buffer_analyze(buf_2, buf_new);
                    buf_tail->buf_next = buf_new;
                    buf_tail = buf_new;
                    buf_tail->buf_next = NULL;
                }
                else
                {
                    v_new = (struct Variate*)malloc(sizeof(struct Variate));
                    Variate_analyze(buf_2, v_new);
                    v_tail->v_next = v_new;
                    v_tail = v_new;
                    v_tail->v_next = NULL;
                }
            }
            if(Judge_func_m(buf_2))
            {
                m_new = (struct Func_m*)malloc(sizeof(struct Func_m));
                m_new->row = row;
                Func_m_analyze(buf_2, m_new);
                m_tail->m_next = m_new;
                m_tail = m_new;
                m_tail->m_next = NULL;
            }
            if(strstr(buf_2,"if")!=NULL)
            {
                b_new = (struct Border*)malloc(sizeof(struct Border));
                Border_analyze(buf_2, b_new);
                b_new->row = row;
                b_tail->b_next = b_new;
                b_tail = b_new;
                b_tail->b_next = NULL;
            }
        }
        while(brace);
    }
    return func_head;
}

void Border_analyze(char str[MAX],struct Border* bd)
{
    if(strstr(str,"if"))
    {
        sscanf(str,"%[^(]",bd->type);
        str=strstr(str,"(");
        str++;
        sscanf(str,"%[^)]",bd->cont);
    }
}

void Show(FILE* pf,int row,char buf[MAX])
{
    int i=0;
    char buf_1[MAX];
    while(i!=row)
    {
        fgets(buf_1,MAX,pf);
        i++;
    }
    strcpy(buf,buf_1);
    printf("%s\n",buf);
    rewind(pf);
}
