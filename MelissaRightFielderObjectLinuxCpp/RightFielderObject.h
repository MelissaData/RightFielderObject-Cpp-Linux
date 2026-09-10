#include<iostream>
#include <string>

#include "mdRightFielder.h"
#include "DataContainer.h"

using namespace std;

#ifndef RIGHTFIELDER_H
#define RIGHTFIELDER_H

/**
 * Wrapper that owns a single Melissa Right Fielder Object instance and encapsulates the
 * two things every Melissa object needs: one-time setup (license + data files) and the
 * per-record processing sequence. Reuse one instance across many inputs; do NOT
 * re-initialize per input.
 */
class RightFielderObject
{
public:
	// Path to the Right Fielder Object data files.
	string dataFilePath;

	// The underlying Melissa Right Fielder Object instance.
	mdRightFielder* mdRightFielderObj = new mdRightFielder;

	/**
	 * Performs the mandatory one-time setup, in this required order:
	 *   1. SetLicenseString            - authorize the object.
	 *   2. SetPathToRightFielderFiles  - tell it where the data files live.
	 *   3. InitializeDataFiles         - load the data into memory.
	 *
	 * @param license  The Melissa license string used to authorize the object.
	 * @param dataPath Path to the folder containing the Right Fielder Object data files.
	 */
	RightFielderObject(string license, string dataPath);

	/**
	 * Runs the full Right Fielder Object processing sequence for one input string and
	 * captures its result codes. This is the canonical per-record call pattern to copy
	 * into your own application:
	 *   Parse -> GetResults
	 *
	 * @param data The record to process. Its Input is read as input, and ResultCodes is
	 *             populated with this run's result codes.
	 */
	void ExecuteObjectAndResultCodes(DataContainer& data);
};

#endif
