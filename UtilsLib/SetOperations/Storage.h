// Storage.h : Declares the entry point for the Storage and Elements data structures.
//

#pragma once

#include <iostream>
#include <iterator>
#include <unordered_map>
#include <deque>
#include <list>
#include <string>
#include <tuple>
#include <vector>
#include <memory>
#include <algorithm>
#include <numeric>
#include <functional>
#include <sstream>
#include <regex>

#include "CommonUtils.h"

namespace SetOperations
{
	typedef std::vector<int> IntElements;
	typedef std::string InputElement;
	typedef std::list<std::string> InputElements;
	typedef std::list<std::string> InvalidElementsReport;

	/*
	* Interface for SetElements of InvalidElements
	*/
	class ElementBase
	{
	public:
		virtual bool IsElementMatched(const ElementBase&) = 0;
		virtual void AddElementCount() = 0;
		virtual int GetDuplicateElementCount() = 0;
		virtual void PrintElementData() = 0;

	private:

	};

	/*
	* Factory method to create SetElements or InvalidElements
	*/
	class ElementFactory
	{
	public:
		//Factory Method
		static std::shared_ptr<ElementBase> CreateStorageElement(bool bIsValidInput, InputElement input);
	};

	/*
	* Actual class used to store individual sets of integers
	*/
	class SetElement :public ElementBase
	{
	public:
		SetElement(InputElement input);
		~SetElement();

		bool IsElementMatched(const ElementBase& input);
		void AddElementCount();
		int GetDuplicateElementCount();
		void PrintElementData();

		int GetSetElementValue();

		const std::string DELIMITER = ",";
	private:
		int duplicatecount;
		int setvalue;
		InputElement inputelement;
		IntElements intset;

		void Initialize();
		void ParseInput();
		void SortSetElement();
		void UpdateSetValue();
		bool IsValidIntToken(std::string token);
	};

	/*
	* Actual class used to store Invalid Elements
	*/
	class InvalidElement :public ElementBase
	{
	public:
		InvalidElement(InputElement input);
		~InvalidElement();

		bool IsElementMatched(const ElementBase& input);
		void AddElementCount();
		int GetDuplicateElementCount();
		void PrintElementData();

		std::string GetElementData();
	private:
		int duplicatecount;
		InputElement invalidelement;
		
		void Initialize();
	};

	typedef std::unordered_multimap<int, std::shared_ptr<ElementBase>> SetStorageMap;
	typedef std::unordered_map<std::string, std::shared_ptr<ElementBase>> InvalidInputs;

	/*
	* Interface for Storage of SetElements or InvalidElements
	*/
	class StorageBase
	{
	public:
		virtual bool InsertElement(std::shared_ptr<ElementBase>) = 0;
		virtual bool IsElementDuplicate(std::shared_ptr<ElementBase>) = 0;
		virtual bool GetDuplicateCount(int& duplicates, int& uniques) =0;
		virtual void ListFrequentDuplicate() = 0;

	private:

	};

	/*
	* Actual class for storing all SetElements received as input
	*/
	class SetElementStorage :public StorageBase
	{
	public:
		SetElementStorage();
		~SetElementStorage();

		//Get number of duplicates and non duplicates
		std::tuple<int, int> GetDuplicateNum();

		//Interface methods
		bool InsertElement(std::shared_ptr<ElementBase>);
		bool IsElementDuplicate(std::shared_ptr<ElementBase>);

		bool GetDuplicateCount(int& duplicates, int& uniques);
		void ListFrequentDuplicate();

	private:
		//Is the element already a duplicate
		bool IsElementDuplicate(std::shared_ptr<ElementBase>, SetStorageMap::iterator&);

		SetStorageMap::iterator CheckDuplicate(std::shared_ptr<ElementBase>);

		//Add a new set to storage
		bool AddToSetStorage(std::shared_ptr<ElementBase>);
		SetStorageMap elementmap;
	};

	/*
	* Actual class for storing all InvalidElements received as input
	*/
	class InvalidElementStorage :public StorageBase
	{
	public:
		InvalidElementStorage();
		~InvalidElementStorage();

		//Interface methods
		bool InsertElement(std::shared_ptr<ElementBase>);
		bool IsElementDuplicate(std::shared_ptr<ElementBase>);

		bool GetDuplicateCount(int& duplicates, int& uniques);
		void ListFrequentDuplicate();
		std::list<std::string> GetInvalidInputsReport();
		
	private:
		InvalidInputs invalidinputs;

		bool IsElementDuplicate(std::shared_ptr<ElementBase>, InvalidInputs::iterator&);
		bool AddToInvalidInputsStorage(std::shared_ptr<ElementBase>);
		InvalidInputs::iterator CheckDuplicate(std::shared_ptr<ElementBase> inputelem);
	};
}