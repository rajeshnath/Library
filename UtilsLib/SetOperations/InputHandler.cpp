// InputHandler.cpp : Defines the entry point for the handling the inputs.
//

#include "InputHandler.h"

namespace SetOperations 
{
	const std::string InputHandler::allowedchars = " ,0123456789";

	//Original regex = "^\s*(-?\d+\s*(,\s*-?\d+\s*)*)?$"
	//After escape the backspace characters
	const std::string InputHandler::inputvalidateregex = "^\\s*(-?\\d+\\s*(,\\s*-?\\d+\\s*)*)?$"; 

	const std::regex InputHandler::inputvalidatergx("^\\s*(-?\\d+\\s*(,\\s*-?\\d+\\s*)*)?$");
	InputHandler::InputHandler()
	{
	}
	InputHandler::~InputHandler()
	{
	}

	//Check if input string is valid set or a invalid set
	bool InputHandler::ValidateInput(const InputElement & input)
	{
		return IsValidInput(input);
	}

	//Creates a element from the input string
	const std::shared_ptr<ElementBase> InputHandler::CreateElement(const InputElement & input, bool& bIsValidInput)
	{
		return ElementFactory::CreateStorageElement(bIsValidInput, input);
	}

	//Inserts the newly created element into storage
	bool InputHandler::InsertElement(StorageBase & storage, std::shared_ptr<ElementBase> elem)
	{
		storage.InsertElement(elem);
		return false;
	}

	//Checks if a string is a valid set or not
	bool InputHandler::IsValidInput(const InputElement & input)
	{
		//return input.find_first_not_of(allowedchars) == std::string::npos;
		return std::regex_match(input, inputvalidatergx);
	}
}
