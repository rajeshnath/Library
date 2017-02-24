// SetOperation.h : Declares the entry point for the SetOperations library.
//

#pragma once

#include <string>
#include <algorithm>
#include "InputHandler.h"
#include "CommonUtils.h"

namespace SetOperations 
{
	class SetOperation
	{
	public:
		SetOperation(void);
		~SetOperation();

		void HandleInput(InputElement inputline);
		bool IsDuplicate(InputElement inputline);
		void GetCount(int& duplicate, int& unique);
		void ListMostFrequentDuplicate();
		void GetInvalidInputsReport(InvalidElementsReport&);
	private:
		std::unique_ptr<InputHandler> handler;
		std::unique_ptr<StorageBase> setelemstorage;
		std::unique_ptr<StorageBase> invalidelemstorage;

		void TrimInput(InputElement&);
	};
}