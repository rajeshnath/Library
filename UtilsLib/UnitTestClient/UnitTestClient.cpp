// UnitTestClient.cpp : Defines the entry point for the Unit Test console application.
//

#include "stdafx.h"

#include <fstream>
#include <string>
#include <cstdlib>
#include "..\SetOperations\SetOperation.h"
#include <Shlwapi.h>
#include <PathCch.h>

#pragma comment(lib, "pathcch.lib")

using namespace std;

TCHAR* GetThisPath(TCHAR* dest, size_t destSize)
{
	if (!dest) return NULL;

	DWORD length = GetModuleFileName(NULL, dest, destSize);
#ifdef NTDDI_WIN8
	PathCchRemoveFileSpec(dest, destSize);
#else
	if (MAX_PATH > destSize) return NULL;
	PathRemoveFileSpec(dest);
#endif
	return dest;
}

void ReadInputFile(SetOperations::InputElements& lines)
{
	size_t numconverted = 0;
	TCHAR filepath[MAX_PATH] = { 0 };
	CHAR filepatha[MAX_PATH] = { 0 };
	GetThisPath(filepath, MAX_PATH);
	wcstombs_s(&numconverted, filepatha, (size_t)MAX_PATH, filepath, (size_t)MAX_PATH);
	strcat_s(filepatha, "\\input.txt");
	//std::ifstream file("C:\\Users\\User1\\Desktop\\Rajesh\\Docs\\MyProjects\\UtilsLib\\build\\Debug\\input.txt");
	std::ifstream file(filepatha);
	if (!file)
	{
		cout << "Could not open input.txt file" << endl;
		return;
	}
	std::string line;
	std::list<std::string> liness;
	while (std::getline(file,line))
	{		
		if (!line.empty())
			lines.push_back(line);
	}
	file.close();
}

void EmptyTest()
{
	std::unique_ptr<SetOperations::SetOperation> obj(new SetOperations::SetOperation());

	int duplicate = 0, unique = 0;
	obj->GetCount(duplicate, unique);
	cout << "Number of Duplicates = " << duplicate << endl;
	cout << "Number of Uniques = " << unique << endl;
	obj->ListMostFrequentDuplicate();

	SetOperations::InvalidElementsReport repobj;

	obj->GetInvalidInputsReport(repobj);
	SetOperations::InvalidElementsReport::iterator it = repobj.begin();

	if (repobj.end() != repobj.begin())
	{
	cout << "Invalid Elements Report" << endl;
	std::copy(repobj.begin(), repobj.end(), std::ostream_iterator<std::string>(std::cout, "\n"));
	}
	
}

void FunctionalTest()
{
	std::unique_ptr<SetOperations::SetOperation> obj(new SetOperations::SetOperation());

	//obj->HandleInput("");
	//obj->HandleInput(" 1,1,1 ");
	obj->HandleInput(" 1, 2, 2");
	obj->HandleInput(" 1, -99, 16786, -7766 "); //Valid signed integer
	obj->HandleInput(" 1, -9,9, 167 86, -7 766 "); //Invalid input

	bool bIsDup = obj->IsDuplicate(std::string(" -99, 1, , 16786, -7766 ")); //Valid signed integer
	bool bIsDup2 = obj->IsDuplicate(std::string(" -99, 1, 16786, -7766 ")); //Valid signed integer

	obj->HandleInput(std::string("1,2,3,4"));
	bool bIsDuplicate = obj->IsDuplicate(std::string("1,2,3,4"));
	if (bIsDuplicate) obj->HandleInput(std::string("1,2,3,4"));
	bool bIsDuplicate2 = obj->IsDuplicate(std::string("2,1,3,4"));
	if (bIsDuplicate2) obj->HandleInput(std::string("2,1,3,4"));

	bool bIsDuplicate3 = obj->IsDuplicate(std::string("1,2,3"));
	obj->HandleInput(std::string("1,2,3"));
	obj->HandleInput(std::string("3,2,1"));

	obj->HandleInput("a,b,c,d");
	obj->HandleInput("a,1,2,3");
	obj->HandleInput("a,1,2,3");

	int duplicate = 0, unique = 0;
	obj->GetCount(duplicate, unique);
	cout << "Number of Duplicates = " << duplicate << endl;
	cout << "Number of Uniques = " << unique << endl;
	obj->ListMostFrequentDuplicate();

	SetOperations::InvalidElementsReport repobj;

	obj->GetInvalidInputsReport(repobj);
	SetOperations::InvalidElementsReport::iterator it = repobj.begin();

	if (repobj.end() != repobj.begin())
	{
		cout << "Invalid Elements Report" << endl;
		std::copy(repobj.begin(), repobj.end(), std::ostream_iterator<std::string>(std::cout, "\n"));
	}
	return;
}

void TestFileInput()
{
	/*
	*File Input, Get Duplicate Count and Get Reports here
	*/
	std::unique_ptr<SetOperations::SetOperation> obj(new SetOperations::SetOperation());

	SetOperations::InputElements lines;
	ReadInputFile(lines);
	if (lines.size() > 0)
	{
		for_each(lines.begin(), lines.end(), [&obj](SetOperations::InputElements::value_type& elem) {
			obj->HandleInput(elem);
		});
	}
	obj->HandleInput("");

	int duplicate = 0, unique = 0;
	obj->GetCount(duplicate, unique);
	cout << "Number of Duplicate sets (which are seen more than one time) = " << duplicate << endl;
	cout << "Number of Unique sets (seen only once) = " << unique << endl << endl;
	obj->ListMostFrequentDuplicate();

	SetOperations::InvalidElementsReport repobj;

	obj->GetInvalidInputsReport(repobj);
	SetOperations::InvalidElementsReport::iterator it = repobj.begin();

	if (repobj.end() != repobj.begin())
	{
		cout << "Invalid Elements Report" << endl;
		std::copy(repobj.begin(), repobj.end(), std::ostream_iterator<std::string>(std::cout, "\n"));
	}
	return;
}

int main()
{
	/*
	cout << "######################################################################" << endl;
	cout << "######################################################################" << endl << endl;
	cout << "Test Input.txt file here..." << endl << endl;
	TestFileInput();
	*/

	/*
	*Test empty inputs here
	cout << "######################################################################" << endl;
	cout << "######################################################################" << endl << endl;
	cout << "Perform empty elements test here..." << endl << endl;
	EmptyTest();
	*/

	/*
	* Test functional inputs here
	*/
	cout << "######################################################################" << endl;
	cout << "######################################################################" << endl << endl;
	cout << "Perform functional test here..." << endl << endl;
	FunctionalTest();
	

	cout <<endl << "Press any key to exit" << endl;
	cin.get();
	
    return 0;
}

