# Software-Security-Project
Design code of software security course, School of Computer science, Huazhong University of Science and Technology

## String Matching

**File Name: string.cpp**

- Function: Homology detection using string matching

- Principle: Analyze the copy ratio between samples by comparing and matching valid code strings

- Data: In "同源性检测样本库.zip"

- Input:

	In\_name_1: Source file1 to test  
	
	Out\_name_1: Source file1 after preprocessing

	In\_name_2: Source file2 for homology detection with file1
	
	Out\_name_2: Source file2 after preprocessing

## CFG 

**File Name: CFG.cpp**

- Function: The control flow chart CFG was used to detect source code homology

- Principle: By extracting the call diagram of the code, the similarity of each function call diagram among the samples is detected and the probability of similarity is obtained.

- Input:

	In\_name_1: Source file1 to test  
	
	Out\_name_1: Source file1 after preprocessing

	In\_name_2: Source file2 for homology detection with file1
	
	Out\_name_2: Source file2 after preprocessing

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

## CFG Test

- Function: A test procedure for homology detection based on CFG graph

- Input: 

	In\_name_1: Source file1 to test  
	
	Out\_name_1: Source file1 after preprocessing

- Output:

	CFG figure
	
	the similarity

## Leak Detection

- Function: The test program of stack overflow vulnerability detection is realized by using vulnerability sample library

- Input: 

	In\_name_1: Source file1 to test  
	
	Out\_name_1: Source file1 after preprocessing

- Output: Where the program is likely to overflow
