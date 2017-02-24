// InputHandler.h : Declares the entry point for the handling the inputs.
//

#pragma once

#include <memory>
#include "Storage.h"

namespace SetOperations
{
	class InputHandler
	{
	public:
		InputHandler();
		~InputHandler();
		bool ValidateInput(const InputElement& input);
		const std::shared_ptr<ElementBase> CreateElement(const InputElement& input, bool& bIsValidInput);
		bool InsertElement(StorageBase&, std::shared_ptr<ElementBase>);
		static const std::string allowedchars;
		static const std::string inputvalidateregex;
		static const std::regex inputvalidatergx;

	private:
		bool IsValidInput(const InputElement&);
		bool IsValidInput(const InputElements&);
	};
}