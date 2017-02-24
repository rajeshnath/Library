## Solution Overview

Solution Name	Description
UtilsLib.sln	Solution created using Visual Studio 2015 Pro (v14.0)


## Solution folder structure:
UtilsLib  
|________ build    Utilslib.sln solution file & binaries build are inside this folder  
|________ SetOperations  Library project  
|________ UnitTestClient  Unit test client project  
|________ Client  Dummy project  

## UtilsLib solution contains the below projects:

A)	“SetOperations” Lib project  This is the main C++ static library (.lib). This is a pure C++ static library. SetOperation class (inside SetOperation.h) exposes 5 basic APIs:

1)	void HandleInput(string)  To parse input string and insert a valid/invalid element into storage  
2)	bool IsDuplicate(string)  To check if a input string is duplicate. It doesn't insert the set.  
3)	void GetCount(duplicates, uniques)  Gets the count of duplicates and uniques elements amongst valid inputs  
4)	void ListMostFrequentDuplicate()  Lists the elements of most frequent duplicate(s)  
5)	void GetInvalidInputsReport(out list of strings)  Gets human readable report on the invalid inputs received so far  

## Data Structures:
For Valid Integer Sets: The datastructure used to store valid integer sets is below:
	unordered_multiset<int, shared_ptr<ElementBase>>

Here, int (key) is the sum of integers received in a valid set. ElementBase is an abstract class for storing the set and other information such as duplicatecount. For example if input is "1,2,3,4" then value of int-key = 10 = 1+2+3+4. The values 1,2,3,4 are stored in a vector inside SetElement class. 
Multiset is used as two sets can have same sum, for example, both inputs “1,2,3,4” and “2,2,2,4” has a sum value of 10
Please refer the source code for more details.

For Invalid inputs: The datastructure used to store the invalid inputs is below:
	unordered_map<string, shared_ptr<ElementBase>>  

Here, string (key) is the actual input string.
 
B)	“UnitTestClient” Exe project  This is a simple console application (.exe) used to test the functional and boundary conditions of SetOperations.lib. This UT application tests the APIs exposed by SetOperations.lib. This UT application can also read an ANSI/ASCII file "input.txt" and create integer sets out of it. It will print output on console.

C)	“Client” Exe project  This is just a dummy client exe aiding in the library development.

## How To Test

A)	Inside Binaries folder, run the UnitTestClient.exe file to see output.

B)	Build and execute the UnitTestClient project. After build, the binaries can be found inside “build” folder. Place an “input.txt” file inside the appropriate binaries folder and execute.

## Complexity
Time Complexity:

1)	Add set to DS = Summation of below two items:  
a.	O(N) => Parsing of each set elements and create InputElement. N is the number of valid elements.  
b.	O(1) ~ O(n) => Insert set element in unordered_multimap DS. O(1) when no collision, O(N) when collision. N is the no of elements  

2)	GetCount ==> To get the number of duplicate sets seen so far  
a.	O(N) [or] O(container.size()) => Since N [or] container.size() denotes the number of unique sets  

3)	ListMostFrequentDuplicate ==>  
a.	O(N+M) => N is number of sets and M is number of integer elements in most frequent set  

## Space Complexity:

1)	Overall space complexity of library is linear complexity. It can be denoted as O(N*M+K) where N is the number of Valid input sets and M is the average number of elements in each valid set. K is the number of invalid input sets. This amortized space is required to store the sets and elements.

2)	All algorithms are working in-place on elements/containers. No new intermediate/temporary containers are created, hence it effectively doesn't add up to space complexity.

## Points to Note:
1)	SetOperations library is a pure C++ library. It also uses some C++11 constructs such as lambda functions and auto specifier and requires a compiler supporting C++11.  

2)	Inputs are classified valid and invalid as below (delimiter comma):  
a.	“1,2,2” [or] “1, 2, 2” [or] “1 ,1 ,2”  This is valid input  
b.	“1,-2,2” or “1,2-,2”  is considered invalid due to dash ‘-‘ character.  
c.	“1”  By definition, single number is not a “set”. Hence, it’s considered an invalid input.  

3)	By definition, duplicate sets are considered without strict input order of elements, hence the elements are stored in sorted order (without preserving the input order)  

4)	UnitTestClient project tests the SetOperations() APIs for boundary and functional conditions by directly invoking the interface APIs only. (Due to limited time for completion, I did not use any standard UT framework)  

5)	I have created the solution using Visual Studio 2015 Professional edition. The project needs some reconfiguration to build in previous versions of Visual Studio.  

6)	My main focus was on design, correctness and performance of the solution.  

7)	UnitTestClient.exe supports ASCII "input.txt" file only. Unicode or related encoding files are not supported.  


## Identified Improvement Points for Code:

a)	Provide support for –ve integer sets. Such as “1,-1,2,-2”  
b)	Provide support for Unicode (UTFXX) input  
c)	Reserve the size of vector based on the number of delimiters found in input string. Will save memory.  
d)	Refactor the code in better files  




