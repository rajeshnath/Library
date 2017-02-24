// Storage.cpp : Defines the entry point for the Storage and Elements data structures.
//

#include "Storage.h"

using namespace std;

namespace SetOperations
{
	//Define SetElementStorage Class members here

	SetElementStorage::SetElementStorage()
	{
	}

	SetElementStorage::~SetElementStorage()
	{
		elementmap.clear();
	}

	//Inserts a SetElement into SetElementStorage
	bool SetElementStorage::InsertElement(std::shared_ptr<ElementBase> inputelem)
	{
		SetStorageMap::iterator outelemiter;
		if (IsElementDuplicate(inputelem, outelemiter))
		{
			outelemiter->second->AddElementCount();
		}
		else
		{
			AddToSetStorage(inputelem);
		}
		return false;
	}

	//Checks if the input set is already a duplicate
	bool SetElementStorage::IsElementDuplicate(std::shared_ptr<ElementBase> inputelem)
	{
		bool bIsElementMatched = false;
		if (CheckDuplicate(inputelem) == elementmap.end()) bIsElementMatched = false;
		else bIsElementMatched = true;

		return bIsElementMatched;
	}

	//Gets the count of duplicate sets and unique sets
	bool SetElementStorage::GetDuplicateCount(int& duplicates, int& uniques)
	{
		duplicates = count_if(elementmap.begin(), elementmap.end(), [](SetStorageMap::value_type& elem) {
			if (elem.second.get()->GetDuplicateElementCount() > 1) return true;
			return false;
		});
		uniques = elementmap.size() - duplicates;
		return true;
	}

	//List the elements of the most frequent duplicates
	void SetElementStorage::ListFrequentDuplicate()
	{
		SetStorageMap::iterator elemiter = elementmap.end();

		std::list<SetStorageMap::iterator> elemlist;
		int largest = 0;
		for (auto it = elementmap.begin(); it != elementmap.end(); ++it)
		{
			if (it->second->GetDuplicateElementCount() > largest)
			{
				largest = it->second->GetDuplicateElementCount();
			}
		}

		if (largest > 0)
		{
			cout << "The below sets have been seen " << largest << " times each."<< endl;
			int count = 0;
			for_each(elementmap.begin(), elementmap.end(), [&largest, &count](SetOperations::SetStorageMap::value_type& elem) {
				if (elem.second->GetDuplicateElementCount() == largest)
				{
					cout << "===================================================================" << endl;
					cout << "Most Frequent set#" << ++count << "." << endl;
					elem.second->PrintElementData();
					cout << endl;
				}
			});
			cout << endl;
		}
		else cout << "No Elements to print" << endl;

	}

	//Checks if inputelem is duplicate and returns a iterator to the duplicate element
	bool SetElementStorage::IsElementDuplicate(std::shared_ptr<ElementBase> inputelem, SetStorageMap::iterator& elemiter)
	{
		bool bIsElementMatched = false;

		elemiter = CheckDuplicate(inputelem);
		if (elemiter == elementmap.end()) bIsElementMatched = false;
		else bIsElementMatched = true;

		return bIsElementMatched;
	}

	//Internal function to check duplicate SetElement
	SetStorageMap::iterator SetElementStorage::CheckDuplicate(std::shared_ptr<ElementBase> inputelem)
	{
		bool bIsElementMatched = false;
		SetStorageMap::iterator elemiter = elementmap.end();

		SetElement* elemobj = dynamic_cast<SetElement*>(inputelem.get());
		if (elemobj != nullptr)
		{
			if (elementmap.count(elemobj->GetSetElementValue()) > 0)
			{
				auto range = elementmap.equal_range(elemobj->GetSetElementValue());
				auto foundelem = find_if(range.first, range.second, [inputelem](SetStorageMap::value_type& elem) {
					if (elem.second.get()->IsElementMatched(*inputelem)) return true;
					return false;
				});
				if (foundelem != elementmap.end()) elemiter = foundelem;
			}
		}
		return elemiter;
	}

	//Add SetElement into SetElementStorage data structure
	bool SetElementStorage::AddToSetStorage(std::shared_ptr<ElementBase> inputelem)
	{
		SetElement* elem = dynamic_cast<SetElement*>(inputelem.get());
		if (elem != nullptr)
		{
			elementmap.insert(make_pair(elem->GetSetElementValue(), inputelem));
		}
		return true;
	}

	//Define StorageElementFactory members here
	std::shared_ptr<ElementBase> ElementFactory::CreateStorageElement(bool bIsValidInput, InputElement input)
	{
		// TODO: insert return statement here
		if (bIsValidInput)
		{
			return make_shared<SetElement>(input);
		}
		else
		{
			return make_shared<InvalidElement>(input);
		}
	}

	//Define SetElement class members here
	SetElement::SetElement(InputElement input) :inputelement{ input }
	{
		Initialize();
	}
	SetElement::~SetElement()
	{
	}

	//Checks if a this element is matched with input element
	bool SetElement::IsElementMatched(const ElementBase & input)
	{
		bool bIsMatched = false;
		ElementBase& sinput = const_cast<ElementBase&>(input);
		SetElement& vinput = dynamic_cast<SetElement&>(sinput);
		std::sort(vinput.intset.begin(), vinput.intset.end());

		IntElements tempset;
		if (vinput.intset.size() == this->intset.size())
		{
			bIsMatched = std::equal(vinput.intset.begin(), vinput.intset.end(), this->intset.begin());
		}
		else bIsMatched = false;
		return bIsMatched;
	}

	//Adds duplicate element count
	void SetElement::AddElementCount()
	{
		++duplicatecount;
	}

	//Returs this duplicate element count
	int SetElement::GetDuplicateElementCount()
	{
		return duplicatecount;
	}

	//Prints element data
	void SetElement::PrintElementData()
	{
		cout << "Element Values" << endl;
		copy(intset.begin(), intset.end(), ostream_iterator<int>(cout, "\n"));
	}

	//Get the element sum value (setvalue)
	int SetElement::GetSetElementValue()
	{
		return setvalue;
	}

	//Initializes the SetElement
	void SetElement::Initialize()
	{
		duplicatecount = 1;
		setvalue = 0;
		ParseInput();
		SortSetElement();
		UpdateSetValue();
	}

	//Parse the string to integer element set
	void SetElement::ParseInput()
	{
		size_t start = inputelement.find_first_not_of(DELIMITER), end = start;

		while (start != std::string::npos) {
			// Find next occurence of delimiter
			end = inputelement.find(DELIMITER, start);
			
			InputElement tempelem = inputelement.substr(start, end - start);
			CommonUtils::TrimInput(tempelem);
			// Push back the Integer found into IntSet
			//intset.push_back(std::stoi(inputelement.substr(start, end - start)));
			intset.push_back(std::stoi(tempelem));

			// Skip all occurences of the delimiter to find new start
			start = inputelement.find_first_not_of(DELIMITER, end);
		}
	}

	//Sorts the integers in this SetElement
	void SetElement::SortSetElement()
	{
		std::sort(intset.begin(), intset.end());
	}

	//Calculate the setvalue of this SetElement
	void SetElement::UpdateSetValue()
	{
		setvalue = std::accumulate(intset.begin(), intset.end(), 0);
	}

	//Define InvalidElement Members here
	InvalidElement::InvalidElement(InputElement input) :invalidelement{input}
	{
		Initialize();
	}
	InvalidElement::~InvalidElement()
	{
	}

	//Checks if this InvalidElement is matched
	bool InvalidElement::IsElementMatched(const ElementBase & input)
	{
		return false;
	}

	//Add duplicate element count
	void InvalidElement::AddElementCount()
	{
		++duplicatecount;
	}

	//Returns the duplicate element count
	int InvalidElement::GetDuplicateElementCount()
	{
		return duplicatecount;
	}

	//Print the InvalidElement data
	void InvalidElement::PrintElementData()
	{
		std::cout << "Invalid Element Values = "<< invalidelement.c_str() << endl;
	}

	//Get the invalid element
	std::string InvalidElement::GetElementData()
	{
		return invalidelement;
	}

	//Initialize the invalid element
	void InvalidElement::Initialize()
	{
		duplicatecount = 1;
	}

	//Define InvalidElementStorage members here
	InvalidElementStorage::InvalidElementStorage()
	{
	}

	//Insert a InvalidElement into Storage data structure
	bool InvalidElementStorage::InsertElement(std::shared_ptr<ElementBase> inputelem)
	{
		InvalidInputs::iterator outelemiter;
		if (IsElementDuplicate(inputelem, outelemiter))
		{
			outelemiter->second->AddElementCount();
		}
		else
		{
			AddToInvalidInputsStorage(inputelem);
		}
		return false;
	}

	//Checks if input element is a duplicate of this element
	bool InvalidElementStorage::IsElementDuplicate(std::shared_ptr<ElementBase> inputelem)
	{
		bool bIsElementMatched = false;
		if (CheckDuplicate(inputelem) == invalidinputs.end()) bIsElementMatched = false;
		else bIsElementMatched = true;

		return bIsElementMatched;
	}

	//Gets the duplicate & unique counts of InvalidElements
	bool InvalidElementStorage::GetDuplicateCount(int & duplicates, int & uniques)
	{
		duplicates = count_if(invalidinputs.begin(), invalidinputs.end(), [](InvalidInputs::value_type& elem) {
			if (elem.second.get()->GetDuplicateElementCount() > 1) return true;
			return false;
		});
		uniques = invalidinputs.size() - duplicates;
		return true;
	}

	//List the most frequent duplicate from InvalidElements
	void InvalidElementStorage::ListFrequentDuplicate()
	{
		InvalidInputs::iterator elemiter = invalidinputs.end();

		int largest = 0;
		for (auto it = invalidinputs.begin(); it != invalidinputs.end(); ++it)
		{
			if (it->second->GetDuplicateElementCount() > largest)
			{
				largest = it->second->GetDuplicateElementCount();
				elemiter = it;
			}
		}

		if (elemiter != invalidinputs.end()) elemiter->second->PrintElementData();
		else cout << "No Elements to print" << endl;
	}

	//Gets the InvalidElements Report
	InvalidElementsReport InvalidElementStorage::GetInvalidInputsReport()
	{
		InvalidElementsReport report;
		int elemcount = 1;
		for_each(invalidinputs.begin(), invalidinputs.end(), [&elemcount,&report](InvalidInputs::value_type& elem) {
			InvalidElement* elemobj = dynamic_cast<InvalidElement*>(elem.second.get());
			if (elemobj != nullptr)
			{
				std::ostringstream stringStream;
				stringStream << "Invalid#" << elemcount << " \tData = " << elemobj->GetElementData() << " \tDuplicate Count = " << elemobj->GetDuplicateElementCount();
				std::string reportStr = stringStream.str();
				report.push_back(reportStr);
				++elemcount;
			}
		});
		return report;
	}

	//Checks if input element is a duplicate and returns the iterator to duplicate element
	bool InvalidElementStorage::IsElementDuplicate(std::shared_ptr<ElementBase> inputelem, InvalidInputs::iterator & elemiter)
	{
		bool bIsElementMatched = false;

		elemiter = CheckDuplicate(inputelem);
		if (elemiter == invalidinputs.end()) bIsElementMatched = false;
		else bIsElementMatched = true;

		return bIsElementMatched;
	}

	//Adds InvalidElements into InvalidInputsStorage data structure
	bool InvalidElementStorage::AddToInvalidInputsStorage(std::shared_ptr<ElementBase> inputelem)
	{
		InvalidElement* elem = dynamic_cast<InvalidElement*>(inputelem.get());
		if (elem != nullptr)
		{
			invalidinputs.insert(make_pair(elem->GetElementData(), inputelem));
		}
		return true;
	}

	//Checks if the input element is a duplicate of InvalidElementStorage
	InvalidInputs::iterator InvalidElementStorage::CheckDuplicate(std::shared_ptr<ElementBase> inputelem)
	{
		InvalidInputs::iterator elemiter = invalidinputs.end();
		// TODO: insert return statement here
		InvalidElement* elemobj = dynamic_cast<InvalidElement*>(inputelem.get());
		if (elemobj != nullptr)
		{
			InvalidInputs::iterator tempiter = invalidinputs.find(elemobj->GetElementData());
			if (tempiter != invalidinputs.end())
			{
				elemiter = tempiter;
			}
		}
		return elemiter;
	}
}