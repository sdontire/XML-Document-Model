/////////////////////////////////////////////////////////////////
// Utilities.cpp - collection of title and logging functionality //
//                                                             //
// Application: Help for CSE687 Pr#2, Spring 2015              //
// Platform:    Dell XPS 2720, Win 8.1 Pro, Visual Studio 2013 //
// Author:      Jim Fawcett, CST 4-187, 443-3948               //
//              jfawcett@twcny.rr.com                          //
/////////////////////////////////////////////////////////////////
/*
* Package Operations:
* -------------------
* This package contains:
* - Global function title(const std::string& text, char underline='-')
*   used to display underlined titles for displaying output headings.
* - Class logit used to start and stop logging during execution.
*   It captures text from member functions and test stubs to help
*   understand and debug code.  When stopped no text is logged,
*   allowing for selective data collection.
* - Class Cosmetic emits two line feeds at the end of execution,
*   after all other objects are destroyed.  Used to provide a bit
*   of space before the Visual Studio prompt to end.
*
* Required Files:
* ---------------
*   - Utilities.h and Utilities.cpp
*
* Build Process:
* --------------
*   devenv MTree.sln /debug rebuild
*
* Maintenance History:
* --------------------
* Ver 1 : 8 Feb 15
* - first release
*
*/


#include "utilities.h"
#include <iostream>

void title(const std::string& text, char underline)
{
	std::cout << "\n  " << text;
	std::cout << "\n " << std::string(text.size() + 2, underline);
	if (underline == '=')
		std::cout << "\n";
}

void logit::show()
{
	std::cout << "\n--start of log:";
	std::cout << out_.str() << "\n--end of log\n";
	out_.clear();
}

void logit::start() { running_ = true; }

void logit::stop() { running_ = false; }

void logit::clear() { out_.str(""); }

bool logit::running() { return running_; }

void logit::put(char ch) { out_.put(ch); }

logit& operator<<(logit& out, const std::string& in)
{
	if (out.running())
	for (auto ch : in)
		out.put(ch);
	return out;
}

logit mtLog;

Cosmetic::~Cosmetic() { std::cout << "\n\n"; }

Cosmetic cosmetic;
#ifdef TEST_MTREE
int main()
{
	title("Utilites.cpp", '=');
	logit::show();
	logit::start();
	logit::stop();
	logit::clear();
	bool val11=logit::running();
	logit::put('a');
	return 0;
}

#endif
