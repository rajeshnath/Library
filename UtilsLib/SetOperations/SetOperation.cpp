// SetOperation.cpp : Defines the entry point for the SetOperations library.
//

#include "SetOperation.h"

namespace SetOperations
{
	
	SetOperation::SetOperation(void) :
		handler( new InputHandler() ),
		setelemstorage(new SetElementStorage()),
		invalidelemstorage(new InvalidElementStorage())
	{

	}

	SetOperation::~SetOperation()
	{
	}
	
	//Handle a input string and insert into the library
	void SetOperation::HandleInput(InputElement inputline)
	{
		if (inputline.empty()) return;
		TrimInput(inputline);

		bool bIsValid = false;
		bIsValid = handler->ValidateInput(inputline);
		std::shared_ptr<ElementBase> elem = handler->CreateElement(inputline, bIsValid);

		SetElement* setelem = dynamic_cast<SetElement*>(elem.get());
		if (setelem != nullptr) 
		{
			handler->InsertElement(dynamic_cast<StorageBase&>(*setelemstorage), elem);
		}
		else 
		{
			InvalidElement* invalidelem = dynamic_cast<InvalidElement*>(elem.get());
			if (invalidelem != nullptr) handler->InsertElement(dynamic_cast<StorageBase&>(*invalidelemstorage), elem);
		}
	}

	//Checks if the input line is a duplicate element
	bool SetOperation::IsDuplicate(InputElement inputline)
	{
		bool bIsValid = handler->ValidateInput(inputline);
		std::shared_ptr<ElementBase> elem = handler->CreateElement(inputline, bIsValid);
		
		if (setelemstorage->IsElementDuplicate(elem)) return true;
		else if (invalidelemstorage->IsElementDuplicate(elem)) return true;
		else return false;
		
	}

	//Gets the count of duplicate and unique elements
	void SetOperation::GetCount(int & duplicate, int & unique)
	{
		setelemstorage->GetDuplicateCount(duplicate, unique);
	}

	//Lists the integers inside most frequent duplicate element
	void SetOperation::ListMostFrequentDuplicate()
	{
		setelemstorage->ListFrequentDuplicate();
	}

	//Get the InvalidInputsReports in a list of strings
	void SetOperation::GetInvalidInputsReport(InvalidElementsReport& report)
	{
		InvalidElementStorage* invalidstg = dynamic_cast<InvalidElementStorage*>(invalidelemstorage.get());
		if (invalidstg != nullptr)
		{
			report = invalidstg->GetInvalidInputsReport();
		}
	}

	//WAP to trim input string
	void SetOperation::TrimInput(InputElement & inputline)
	{
		/*
		std::unique_ptr<CommonUtils> obj(new CommonUtils());
		obj->TrimInput(inputline);*/
		CommonUtils::TrimInput(inputline);
	}
}