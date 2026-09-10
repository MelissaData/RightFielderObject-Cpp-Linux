#include "RightFielderObject.h"

RightFielderObject::RightFielderObject(string license, string dataPath)
{
	// Set license string and set path to data files
	mdRightFielderObj->SetLicenseString(license.c_str());
	dataFilePath = dataPath;

	// Load the data files. The returned ProgramStatus reports whether initialization succeeded.
	// If you see a different date than expected, check your license string and either download the new data files
	// or use the Melissa Updater program to update your data files.
	mdRightFielderObj->SetPathToRightFielderFiles(dataFilePath.c_str());
	mdRightFielder::ProgramStatus pStatus = mdRightFielderObj->InitializeDataFiles();

	// If an issue occurred, please investigate the common causes.
	// Common causes: an invalid/expired license, or missing/wrong-path data files.
	if (pStatus != mdRightFielder::NoError)
	{
		cout << "Failed to Initialize Object." << endl;
		cout << pStatus << endl;
		return;
	}

	// Diagnostic information, handy for confirming the object loaded the data you expect:

	// Build date of the data files
	cout << "                 DataBase Date: " + string(mdRightFielderObj->GetDatabaseDate()) << endl;

	// When the license stops working
	cout << "               Expiration Date: " + string(mdRightFielderObj->GetLicenseExpirationDate()) << endl;

	/**
	 * This number should match with the file properties of the Melissa Object binary file.
	 * If TEST appears with the build number, there may be a license key issue.
	 */
	cout << "                Object Version: " + string(mdRightFielderObj->GetBuildNumber()) << endl;
}

// This will call the functions to process the input as well as generate the result codes
void RightFielderObject::ExecuteObjectAndResultCodes(DataContainer& data)
{
	// Optional: register a custom field pattern (e.g. a Social Security Number) so the
	// object recognizes and extracts it. Uncomment the SetUserPattern call to use one.
	//mdRightFielderObj->SetUserPattern("SSN", "[0-9]{3}-[0-9]{2}-[0-9]{4}");

	// Split the free-form input into typed fields
	mdRightFielderObj->Parse(data.Input);

	// Collect the result codes for this run
	// ResultsCodes explain any issues Right Fielder Object has with the object.
	// List of result codes for Right Fielder Object
	// https://docs.melissa.com/on-premise-api/rightfielder-object/result-codes.html
	data.ResultCodes = mdRightFielderObj->GetResults();
}
