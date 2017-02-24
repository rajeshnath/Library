// Client.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "..\SetOperations\SetOperation.h"

using namespace std;
int main()
{
	std::unique_ptr<SetOperations::SetOperation> obj(new SetOperations::SetOperation());
	obj->HandleInput("");
	obj->HandleInput(" 1,1,1 ");
	obj->HandleInput("2,1,0");
	obj->HandleInput("0,1,2");
	obj->HandleInput(" 1, 2, 2");

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

	cout << "Invalid Elements Report" << endl;
	std::copy(repobj.begin(), repobj.end(), std::ostream_iterator<std::string>(std::cout, "\n"));

	cout << "Press any key to exit" << endl;
	cin.get();
    return 0;
}

