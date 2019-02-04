//
//  main.cpp
//  A_1
//
//  Created by 郭倜维 on 2018/10/17.
//  Copyright © 2018 郭倜维. All rights reserved.
//

#include <iostream>
#include <string>
#include <fstream>
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <stack>
#include <cstdio>
#include <algorithm>

using namespace std;

int anay_code_1(string in_name);
int anay_code_2(string in_name);
void clean_1(string in_name, string out_name);
void clean_2(string in_name, string out_name);

int main()
{
    string In_name_1, Out_name_1;
    string In_name_2, Out_name_2;
    cout<<"文件1:\n";
    cin>>In_name_1;
    cin>>Out_name_1;
    clean_1(In_name_1, Out_name_1);
    //ifstream in_2("2.txt");
    ifstream in_1(Out_name_1);
    string filename_1;
    string filename_2;
    string line_1[1000];
    //string line_2[100];
    int i = 0;
    int j = 0;
    int k = 0;
    if(in_1) // 有该文件
    {
        cout<<"文件2:\n";
        cin>>In_name_2;
        cin>>Out_name_2;
        clean_2(In_name_2, Out_name_2);
        while (getline (in_1, line_1[i])) // line中不包括每行的换行符
        {
            string::iterator it = line_1[i].begin();
            while ((it=find(it, line_1[i].end(), ' '))!=line_1[i].end())
            {
                
                line_1[i].erase(it);
                if (it == line_1[i].end())
                    break;
            }
            if(line_1[i].length() != 0)
            {
                //line_1 = str.replaceAll(regex, "");
                if(line_1[i] != "\\s+")
                {
                    //cout << line_1[i] << endl;
                    ifstream in_2(Out_name_2);
                    string line_2[1000];
                    if(in_2) // 有该文件*/
                    {
                        while (getline (in_2, line_2[j])) // line中不包括每行的换行符
                        {
                            string::iterator it2 = line_2[j].begin();
                            while ((it2=find(it2, line_2[j].end(), ' '))!=line_1[j].end())
                            {
                                
                                line_2[j].erase(it2);
                                if (it2 == line_2[j].end())
                                    break;
                            }
                            if(line_2[j].length() != 0)
                            {
                                if(line_2[j] != "\\s+")
                                {
                                    if(line_1[i]==line_2[j])
                                    {
                                        k++;
                                        break;
                                    }
                                }
                            }
                            //cout << line_2[j] << endl;
                            j++;
                        }
                        j = 0;
                    }
                    else // 没有该文件
                    {
                        cout <<"no such file" << endl;
                        break;
                    }
                }
                i++;
            }
        }
    }
    else // 没有该文件
    {
        cout <<"no such file" << endl;
    }
    printf("\nk = %d\ni = %d\n",k, i);
    printf("rate = %.10f\n",(double)k/(double)i);
    return 0;
}

vector<string> level0, level1,level2;   //分level0, level1,level2输出在新建的文件中

int anay_code_1(string in_name)               //函数名及其内部指针
{
    int n;
    ifstream fin(in_name);         //读取"无注释.cpp"
    ofstream outfile2("1_l.cpp");      //把运行的数据输入到"分类.cpp"
    if(!fin.is_open() )                 //如果文件没有打开
    {
        return -1;                      //返回-1
    }
    string str;                         //定义字符串 str
    while (getline(fin, str))           //读取文件内容以字符串的格式
    {
        size_t pos = str.find("class");//对字符串pos初赋值
        if(string::npos != pos)        //如果string::npos != pos
        {
            string class_name = "";  //初始化class_name为空格
            pos += 4;                //跳过class ，pos=pos+4
            while(str[++pos] == ' ');//跳过空格时
            while(isalpha(str[pos]))
            {
                class_name += str[pos]; //找类名串给str[pos]
                ++pos;                  //下一个字符串
            }
            if(str.find("public") != string::npos || str.find("private") != string::npos)
            {
                level1.push_back(class_name);  //调用push_back(class_name)函数，为派生类
            }
            else //否则
            {
                level0.push_back(class_name); //调用push_back(class_name)函数，为基类
            }
        }
        size_t pos1 = str.find("::"); //调用fing函数，给size_t pos1
        if(string::npos != pos1)//如果string::npos != pos1
        {         string class_name = ""; //初始化class_name为空格
            pos1+=2;//跳过:: ，pos1=pos1+2
            while(isalpha(str[pos1])) //当找类名的字符串是，执行以下语句
            {
                class_name+= str[pos1];
                ++pos1;
            }
            level2.push_back(class_name); //调用push_back(class_name)函数，为子类
        }
    }
    //cout << "基类:" <<endl; //打印出“基类”
    outfile2<<"基类:"<<endl;//把“基类”保存在outfile2
    for (int n = 0; n < level0.size(); ++n) //输出是基类的类名
    {
        //cout << level0[n] << endl;//输出level0[n]
        outfile2<<level0[n]<<endl;//把level0[n]保存在outfile2
    }
    //cout << "子类:" << endl; //输出“子类”
    outfile2<<"子类:"<<endl;//把"子类:"保存在outfile2
    for ( n = 0; n < level1.size(); ++n)  //输出是子类的类名
    {
        //cout << level2[n]<< endl; //输出level2[n]
        outfile2<<level2[n]<<endl;//把level2[n]保存在outfile2
    }
    //cout << "派生类:" << endl; //输出“派生类”
    outfile2<<"派生类:"<<endl;//把“基类”保存在outfile2
    for ( n = 0; n < level1.size(); ++n)//输出是派生类的类名
    {
        //cout << level1[n]<< endl; //输出level1[n]
        outfile2<<level1[n]<<endl;//把level1[n]保存在outfile2
    }
    return 0; //返回0
}

int anay_code_2(string in_name)               //函数名及其内部指针
{
    int n;
    ifstream fin("2_c.cpp");         //读取"无注释.cpp"
    ofstream outfile2("2_l.cpp");      //把运行的数据输入到"分类.cpp"
    if(!fin.is_open() )                 //如果文件没有打开
    {
        return -1;                      //返回-1
    }
    string str;                         //定义字符串 str
    while (getline(fin, str))           //读取文件内容以字符串的格式
    {
        size_t pos = str.find("class");//对字符串pos初赋值
        if(string::npos != pos)        //如果string::npos != pos
        {
            string class_name = "";  //初始化class_name为空格
            pos += 4;                //跳过class ，pos=pos+4
            while(str[++pos] == ' ');//跳过空格时
            while(isalpha(str[pos]))
            {
                class_name += str[pos]; //找类名串给str[pos]
                ++pos;                  //下一个字符串
            }
            if(str.find("public") != string::npos || str.find("private") != string::npos)
            {
                level1.push_back(class_name);  //调用push_back(class_name)函数，为派生类
            }
            else //否则
            {
                level0.push_back(class_name); //调用push_back(class_name)函数，为基类
            }
        }
        size_t pos1 = str.find("::"); //调用fing函数，给size_t pos1
        if(string::npos != pos1)//如果string::npos != pos1
        {         string class_name = ""; //初始化class_name为空格
            pos1+=2;//跳过:: ，pos1=pos1+2
            while(isalpha(str[pos1])) //当找类名的字符串是，执行以下语句
            {
                class_name+= str[pos1];
                ++pos1;
            }
            level2.push_back(class_name); //调用push_back(class_name)函数，为子类
        }
    }
    //cout << "基类:" <<endl; //打印出“基类”
    outfile2<<"基类:"<<endl;//把“基类”保存在outfile2
    for (int n = 0; n < level0.size(); ++n) //输出是基类的类名
    {
        //cout << level0[n] << endl;//输出level0[n]
        outfile2<<level0[n]<<endl;//把level0[n]保存在outfile2
    }
    //cout << "子类:" << endl; //输出“子类”
    outfile2<<"子类:"<<endl;//把"子类:"保存在outfile2
    for ( n = 0; n < level1.size(); ++n)  //输出是子类的类名
    {
        //cout << level2[n]<< endl; //输出level2[n]
        outfile2<<level2[n]<<endl;//把level2[n]保存在outfile2
    }
    //cout << "派生类:" << endl; //输出“派生类”
    outfile2<<"派生类:"<<endl;//把“基类”保存在outfile2
    for ( n = 0; n < level1.size(); ++n)//输出是派生类的类名
    {
        //cout << level1[n]<< endl; //输出level1[n]
        outfile2<<level1[n]<<endl;//把level1[n]保存在outfile2
    }
    return 0; //返回0
}

void clean_1(string in_name, string out_name)
{
    ifstream infile(in_name.c_str()); //读取输入文件
    ofstream outfile1(out_name);     //把消除注释后的程序保存到"无注释.cpp"中
    unsigned long i, j, size;  //整型初始值
    string instring,outstring;          ////字符串 instring,outstring
    bool flag;                          //标记
    while(getline(infile,instring))     //读取文件内容
    {
        outstring="";                 //outstring为空格
        size=instring.size();          //字符串大小
        flag=false;                    //flag为false
        for(i=0;i<size;)  //循环语句
        {
            switch(instring[i])//swich语句
            {
                case '/':
                    if(instring[i+1]=='/')  //如果找到“//”
                        flag=true; //flag为true
                    else if(instring[i+1]=='*') //如果找到“/**/”中的 “/*”
                    {
                        i=instring.find("*/",i+2); //查找“*/”的位置，用i表示
                        while(i==-1) //找到当的不是“*/”时
                        {
                            if(!getline(infile,instring))//读取文件内容
                            {
                                //cout<<"not matching"<<endl; //打印出"not matching"
                                return  ;    //返回0
                            }
                            size=instring.size();  //继续查找
                            flag=false; //flag为false
                            i=instring.find("*/"); //查找“*/”的位置，用i表示
                        }
                        i+=2;      //i=i+2
                    }
                    else //否则
                        outstring+=instring[i++]; //把非注释字符存放到outstring
                    break;  //跳出
                case '"':
                    for(j=i+1;j<size;++j)
                    {
                        if(instring[j]=='"'&&instring[j-1]!='\\') //如果查找“"”
                            break;                             //跳出
                    }
                    if(j==size) //若找不到
                    {
                        //cout<< "not matching"<<endl;    //输出"not matching"
                        return  ;  //返回0
                    }
                    outstring+=instring.substr(i,j-i+1); //把非注释字符保存到outstring中
                    i=j+1;
                    break;
                default:     outstring+=instring[i++];    //其他，将非注释字符存放到outstring中
            }
            if(flag) break;        //如果标记为0，跳出
        }
        //cout <<outstring<<endl;    //输出outstring输出
        outfile1<<outstring<<endl;  //把字符串outstring保存到outfile1
        
    }
    ifstream fin(out_name); //读取"无注释.cpp"
    anay_code_1(out_name); //调用int anay_code(char *path)
    return  ; //返回0
}

void clean_2(string in_name, string out_name)
{
    ifstream infile(in_name.c_str()); //读取输入文件
    ofstream outfile1(out_name);     //把消除注释后的程序保存到"无注释.cpp"中
    unsigned long i, j, size;  //整型初始值
    string instring,outstring;          ////字符串 instring,outstring
    bool flag;                          //标记
    while(getline(infile,instring))     //读取文件内容
    {
        outstring="";                 //outstring为空格
        size=instring.size();          //字符串大小
        flag=false;                    //flag为false
        for(i=0;i<size;)  //循环语句
        {
            switch(instring[i])//swich语句
            {
                case '/':
                    if(instring[i+1]=='/')         //如果找到“//”
                        flag=true;                 //flag为true
                    else if(instring[i+1]=='*')    //如果找到“/**/”中的 “/*”
                    {
                        i=instring.find("*/",i+2); //查找“*/”的位置，用i表示
                        while(i==-1)               //找到当的不是“*/”时
                        {
                            if(!getline(infile,instring))       //读取文件内容
                            {
                                //cout<<"not matching"<<endl; //打印出"not matching"
                                return  ;    //返回0
                            }
                            size=instring.size();              //继续查找
                            flag=false;                        //flag为false
                            i=instring.find("*/");             //查找“*/”的位置，用i表示
                        }
                        i+=2;                                  //i=i+2
                    }
                    else //否则
                        outstring+=instring[i++];             //把非注释字符存放到outstring
                    break;  //跳出
                    case '"':
                     for(j=i+1;j<size;++j)
                     {
                     if(instring[j]=='"'&&instring[j-1]!='\\') //如果查找“"”
                     break;                             //跳出
                     }
                     if(j==size)                            //若找不到
                     {
                     cout<< "not matching"<<endl;    //输出"not matching"
                     return  ;  //返回0
                     }
                     outstring+=instring.substr(i,j-i+1); //把非注释字符保存到outstring中
                     i=j+1;
                     break;
                default:     outstring+=instring[i++];    //其他，将非注释字符存放到outstring中
            }
            if(flag) break;        //如果标记为0，跳出
        }
        //cout <<outstring<<endl;    //输出outstring输出
        outfile1<<outstring<<endl;  //把字符串outstring保存到outfile1
        
    }
    
    //cout<<"消除注释后的cpp文件存放在‘name_c.cpp’中"<<endl;     //存放消除注释后的源程序,打印出文件位置
    ifstream fin(out_name); //读取"无注释.cpp"
    anay_code_2(out_name); //调用int anay_code(char *path)
    //cout<<"消除注释后的cpp文件存放在‘lei.cpp’中"<<endl; //提示分类结果的文件
    //system("pause"); //系统结束
    return  ; //返回0
}

