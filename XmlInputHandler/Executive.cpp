#include "XmlInputHandler.h"
#include <string>
#include <iostream>
#include <fstream>
using namespace std;
XmlInputHandler::XmlInputHandler()
{

}


XmlInputHandler::~XmlInputHandler()
{
}
int main(int argc, char *argv[])
{
	string filename; // input file
	ifstream inputfile;  
	filename = argv[1];

	//To read input file

	if (argc > 0)
	{
		ifstream inputfile(filename);
		inputfile.open(filename);

		if (inputfile.is_open())
		{
			cout << "reading file";
		}
		while (!inputfile.eof())
		{

		}
		inputfile.close();
	}
}
