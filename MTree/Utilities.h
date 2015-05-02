#ifndef UTILITIES_H
#define UTILITIES_H
/////////////////////////////////////////////////////////////////
// Utilities.h - collection of title and logging functionality //
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

#include <sstream>

void title(const std::string& text, char underline = '-');

/////////////////////////////////////////////////////////////////////////////
// logit class

class logit
{
public:
	void start();
	void stop();
	void show();
	void clear();
	bool running();
	void put(char ch);
private:
	std::ostringstream out_;
	bool running_;
};

logit& operator<<(logit& out, const std::string& in);

extern logit mtLog;

struct Cosmetic
{
	~Cosmetic();
};

extern Cosmetic cosmetic;

#endif
