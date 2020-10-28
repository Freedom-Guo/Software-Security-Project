# Software-Security-Project
Design code of software security course, School of Computer science, Huazhong University of Science and Technology

## A_1

**File Name: string.cpp**

- Function: Homology detection using string matching

- Principle: Analyze the copy ratio between samples by comparing and matching valid code strings

- Data: In "同源性检测样本库.zip"

- Input:

	In\_name_1: Source file1 to test  
	
	Out\_name_1: Source file1 after preprocessing

	In\_name_2: Source file2 for homology detection with file1
	
	Out\_name_2: Source file2 after preprocessing

## A_2
该程序为基于CFG图进行同源性检测程序

程序的输入为：

文件1: 进行检测的源文件1\n 源文件1预处理后写入的文件\n

文件2: 与文件1进行同源性检测的源文件2\n 源文件2预处理后写入的文件\n

## A_3
该程序为使用同源性代码库实现基于CFG图进行同源性检测的测试程序

程序的输入为：

文件1: 进行检测的源文件1\n 源文件1预处理后写入的文件\n

程序会将所有文件的CFG图输出，并输出相似度

## A_4

Function: 
该程序为使用漏洞样本库实现栈溢出漏洞检测的测试程序

程序的输入为：

文件1: 进行检测的源文件1\n 源文件1预处理后写入的文件\n

程序会将溢出可能的地方输出


## Stack buffer detection

**File Name: stack overflow.cpp**

- Function: Stack buffer overflow detection

- Principle: According to the principle of stack buffer, the overflow problem of allocated stack data area is analyzed, and the number of suspicious lines and columns is given.

- Data: In "漏洞检测样本库.zip"

## Heap buffer detection

**File Name: heap overflow.cpp**

- Function: Heap buffer overflow detection

- Principle: According to the principle of heap buffer, the overflow problem of allocated heap data area is analyzed, and the number of suspicious lines and columns is given.

- Data: In "漏洞检测样本库.zip"

## Integer width overflow detection

**File Name: Integer width overflow.cpp**

- Function: Integer width overflow detection

- According to the principle of integer width overflow, the overflow problem of allocated data is analyzed, and the number of suspicious lines and columns is given.

- Data: In "漏洞检测样本库.zip"

## Integer arithmetic overflow detection

**File Name: integer arithmetic overflow.cpp**

- Function: Integer arithmetic overflow detection

- Principle: According to the overflow principle of integer operation, the overflow problem of allocated data is analyzed, and the number of suspicious lines and columns is given.

- Data: In "漏洞检测样本库.zip"
