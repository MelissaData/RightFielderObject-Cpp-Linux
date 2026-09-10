/**
 * @file Main.cpp
 * @brief RightFielder Object will identify, parse and reorganize input data into usable data types,
 * assuring that even the most inconsistent data entry will be properly validated and stored.
 *
 * High-level flow of this sample:
 *   1. SETUP     - create an mdRightFielder instance, hand it the license string and
 *                  the path to the data files, then InitializeDataFiles() (one time).
 *   2. INPUT     - feed one free-form contact string in.
 *   3. PROCESS   - Parse() splits the string into typed fields.
 *   4. READ      - pull the sorted fields back out with the Get* getters
 *                  (GetAddress, GetCity, GetState, GetPostalCode, ...).
 *   5. INTERPRET - GetResults() returns comma-separated result codes describing
 *                  what the object did/found; each code has a human description.
 *
 * The pieces of this sample map onto that flow:
 *   - main / ParseArguments / RunAsConsole : console harness (argument parsing + the interactive loop).
 *   - RightFielderObject : thin wrapper around mdRightFielder that owns setup + the call sequence.
 *   - DataContainer      : plain holder for one record's input and output.
 *
 * Where mdRightFielder comes from:
 *   There is no generated wrapper source for C++. mdRightFielder.h and
 *   mdRightFielderEnums.h declare the API, and libmdRightFielder.so carries the implementation. The
 *   accompanying MelissaRightFielderObjectLinuxCpp.sh script downloads all three on every run.
 *
 * Reference:
 *   Quickstart    : https://docs.melissa.com/on-premise-api/rightfielder-object/rightfielder-object-quickstart.html
 *   Release notes : https://releasenotes.melissa.com/on-premise-api/rightfielder-object/
 *   Result codes  : https://docs.melissa.com/on-premise-api/rightfielder-object/result-codes.html
 */

#include <iostream>
#include <cstring>
#include <cstdlib>
#include <list>

#include "mdRightFielder.h"
#include "RightFielderObject.h"
#include "DataContainer.h"

using namespace std;

// function declarations
void ParseArguments(string& license, string& testInput, string& dataPath, int argc, char** argv);
void RunAsConsole(string license, string testInput, string dataPath);
list<string> SplitResultCodes(string s, string delimiter);

/**
 * Entry point. Reads the optional command-line arguments, then hands control to
 * RunAsConsole, which performs the actual Right Fielder Object setup and processing.
 *
 * @param argc The count of command-line arguments.
 * @param argv The raw command-line arguments.
 */
int main(int argc, char* argv[])
{
	// Populated by ParseArguments below.
	string license = "";
	string testInput = "";
	string dataPath = "";

	ParseArguments(license, testInput, dataPath, argc, argv);
	RunAsConsole(license, testInput, dataPath);

	return 0;
}

/**
 * Reads the supported command-line options into the reference parameters.
 *
 * Recognized flags (each followed by its value, e.g. "--rfinput \"John Smith 22382 Avenida Empresa\""):
 *   --license / -l   : the Melissa license string
 *   --rfinput / -r   : a free-form contact string to test in one-shot mode
 *   --dataPath / -d  : path to the Right Fielder Object data files
 *
 * @param license   Receives the Melissa license string.
 * @param testInput Receives the free-form contact string to test in one-shot mode.
 * @param dataPath  Receives the path to the Right Fielder Object data files.
 * @param argc      The count of command-line arguments to parse.
 * @param argv      The raw command-line arguments to parse.
 */
void ParseArguments(string& license, string& testInput, string& dataPath, int argc, char* argv[])
{
	for (int i = 1; i < argc; i++)
	{
		if (string(argv[i]) == "--license" || string(argv[i]) == "-l")
		{
			if (argv[i + 1] != NULL)
			{
				license = argv[i + 1];
			}
		}
		if (string(argv[i]) == "--rfinput" || string(argv[i]) == "-r")
		{
			if (argv[i + 1] != NULL)
			{
				testInput = argv[i + 1];
			}
		}
		if (string(argv[i]) == "--dataPath" || string(argv[i]) == "-d")
		{
			if (argv[i + 1] != NULL)
			{
				dataPath = argv[i + 1];
			}
		}
	}
}

/**
 * Sets up the Right Fielder Object once, then drives the input -> process -> output cycle.
 *
 * In interactive mode (no --rfinput) it loops, asking for a new string each pass until
 * the user answers "N". In one-shot mode (--rfinput supplied) it runs a single pass
 * and exits.
 *
 * @param license   The Melissa license string used to initialize the object.
 * @param testInput A free-form contact string to process in one-shot mode; if empty, the program prompts interactively.
 * @param dataPath  Path to the Right Fielder Object data files.
 */
void RunAsConsole(string license, string testInput, string dataPath)
{
	cout << "\n========= WELCOME TO MELISSA RIGHT FIELDER OBJECT LINUX C++ ========\n" << endl;
	
	// Construct the wrapper. This is where the object is licensed, pointed at the
	// data files, and initialized (see the RightFielderObject constructor below).
	RightFielderObject* rightFielderObject = new RightFielderObject(license, dataPath);

	bool shouldContinueRunning = true;

	while (shouldContinueRunning)
	{
		// Holder for this pass's input and result codes.
		DataContainer dataContainer = DataContainer();

		if (testInput.empty())
		{
			// Interactive mode: prompt the user for a free-form contact string.
			cout << "\nFill in each value to see the Right Fielder Object results" << endl;
			cout << "Right Fielder Input: ";

			string input;
			getline(cin, input);

			strcpy(dataContainer.Input, input.c_str());
		}
		else
		{
			// One-shot mode: use the string passed on the command line.
			strcpy(dataContainer.Input, testInput.c_str());
		}

		// Print user input
		cout << "\n============================== INPUTS ==============================\n" << endl;
		cout << "\t   Right Fielder Input: " + string(dataContainer.Input)                 << endl;

		// Execute Right Fielder Object
		// Runs the Parse and stores the result codes on dataContainer.
		rightFielderObject->ExecuteObjectAndResultCodes(dataContainer);

		// Print output
		// Each Get* getter below returns one field the object pulled out of the input
		// string. These read directly from the mdRightFielder instance, which still holds
		// the results from the Execute call above. (Many more getters are available - see
		// the commented lines for the full set.)
		cout << "\n============================== OUTPUT ==============================\n"                       << endl;
		cout << "\n\tRightFielder Object Information:"                                                           << endl;
		cout << "\t          AddressLine1: " + string(rightFielderObject->mdRightFielderObj->GetAddress())       << endl;
		cout << "\t          AddressLine2: " + string(rightFielderObject->mdRightFielderObj->GetAddress2())      << endl;
		cout << "\t          AddressLine3: " + string(rightFielderObject->mdRightFielderObj->GetAddress3())      << endl;
		cout << "\t                  City: " + string(rightFielderObject->mdRightFielderObj->GetCity())          << endl;
		cout << "\t                 State: " + string(rightFielderObject->mdRightFielderObj->GetState())         << endl;
		cout << "\t                   Zip: " + string(rightFielderObject->mdRightFielderObj->GetPostalCode())    << endl;
		//rightFielderObject->mdRightFielderObj->GetFullNameNext();
		//cout << "\t              FullName: " + string(rightFielderObject->mdRightFielderObj->GetFullName())      << endl;
		//rightFielderObject->mdRightFielderObj->GetDepartmentNext();
		//cout << "\t            Department: " + string(rightFielderObject->mdRightFielderObj->GetDepartment())    << endl;
		//rightFielderObject->mdRightFielderObj->GetCompanyNext();
		//cout << "\t               Company: " + string(rightFielderObject->mdRightFielderObj->GetCompany())       << endl;
		//cout << "\t               Country: " + string(rightFielderObject->mdRightFielderObj->GetCountry())       << endl;
		//cout << "\t              LastLine: " + string(rightFielderObject->mdRightFielderObj->GetLastLine())      << endl;
		//rightFielderObject->mdRightFielderObj->GetPhoneNext();
		//cout << "\t                 Phone: " + string(rightFielderObject->mdRightFielderObj->GetPhone())         << endl;
		//rightFielderObject->mdRightFielderObj->GetPhoneTypeNext();
		//cout << "\t             PhoneType: " + string(rightFielderObject->mdRightFielderObj->GetPhoneType())     << endl;
		//rightFielderObject->mdRightFielderObj->GetEmailNext();
		//cout << "\t                 Email: " + string(rightFielderObject->mdRightFielderObj->GetEmail())         << endl;
		//rightFielderObject->mdRightFielderObj->GetURLNext();
		//cout << "\t                   Url: " + string(rightFielderObject->mdRightFielderObj->GetURL())           << endl;
		//rightFielderObject->mdRightFielderObj->GetUserFieldNext("SSN");
		//cout << "\t             UserField: " + string(rightFielderObject->mdRightFielderObj->GetUserField("SSN"))<< endl;
		//rightFielderObject->mdRightFielderObj->GetUnrecognizedNext();
		//cout << "\t          Unrecognized: " + string(rightFielderObject->mdRightFielderObj->GetUnrecognized())  << endl;
		cout << "\t          Result Codes: " + dataContainer.ResultCodes                                         << endl;

		// Result codes come back as a single comma-separated string (e.g. "RA01,RF01").
		// Split it and ask the object for a readable description of each code.
		// ResultCodeDescriptionLong requests the long-form text; a short form is also
		// available via ResultCodeDescriptionShort.
		list<string> rs = SplitResultCodes(dataContainer.ResultCodes, ",");
		list<string>::iterator it;

		for (it = rs.begin(); it != rs.end(); it++)
		{
			printf("        %s: %s", it->c_str(), rightFielderObject->mdRightFielderObj->GetResultCodeDescription(it->c_str(), rightFielderObject->mdRightFielderObj->ResultCodeDescriptionLong));
			cout << endl;
		}

		bool isValid = false;

		// In one-shot mode there is nothing more to do after a single pass: mark the
		// input handled and stop the outer loop.
		if (!testInput.empty()) 
		{
			isValid = true;
			shouldContinueRunning = false;
		}

		// Interactive mode: ask whether to process another string. Keep prompting until
		// we get a valid Y/N. "N" ends the program; "Y" falls through to another pass.
		while (!isValid)
		{
			string testAnotherResponse;

			cout << "\nTest Right Fielder Again? (Y/N)" << endl;
			getline(cin, testAnotherResponse);

			if (!testAnotherResponse.empty())
			{
				if (testAnotherResponse == "y" || testAnotherResponse == "Y")
				{
					isValid = true;
				}
				else if (testAnotherResponse == "n" || testAnotherResponse == "N")
				{
					isValid = true;
					shouldContinueRunning = false;
				}
				else
				{
					cout << "Invalid Response, please respond 'Y' or 'N'" << endl;
				}
			}
		}
	}
	cout << "\n=============== THANK YOU FOR USING MELISSA C++ OBJECT =============\n" << endl;
}

/**
 * Splits the comma-separated result-code string into individual codes.
 *
 * @param s         The result-code string (e.g. "RA01,RF01").
 * @param delimiter The delimiter string to split on.
 * @return A list holding each individual result code.
 */
list<string> SplitResultCodes(string s, string delimiter) {
	list<string> resultCodes;

	size_t pos = 0;
	string token;

	while ((pos = s.find(delimiter)) != string::npos) {
		token = s.substr(0, pos);
		resultCodes.push_back(token);
		s.erase(0, pos + delimiter.length());
	}

	// push back the last resultCode
	resultCodes.push_back(s);

	return resultCodes;
}
