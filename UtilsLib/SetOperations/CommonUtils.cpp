#include "CommonUtils.h"

using namespace std;
namespace SetOperations
{
	void CommonUtils::TrimInput(std::string &inputline)
	{
		inputline = inputline.substr(inputline.find_first_not_of(" "));
		inputline.erase(inputline.find_last_not_of(" \n\t\r") + 1);
	}
}
