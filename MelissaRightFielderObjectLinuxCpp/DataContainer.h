#include<iostream>

using namespace std;

#ifndef DATACONTAINER_H
#define DATACONTAINER_H

/**
 * Data holder for a single record: carries the input string in and the result codes out.
 */
class DataContainer
{
public:
	// Input: the free-form contact string to parse.
	char Input[256] = "";

	// Output: comma-separated result codes from GetResults().
	string ResultCodes;

	DataContainer() {};
};

#endif