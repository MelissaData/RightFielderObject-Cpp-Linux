# Melissa - Right Fielder Object Linux C++

## Purpose
This code showcases the Melissa Right Fielder Object using C++.

Please feel free to copy or embed this code to your own project. Happy coding!

For the latest Melissa Right Fielder Object release notes, please visit: https://releasenotes.melissa.com/on-premise-api/rightfielder-object/

The console will ask the user for:

- Right Fielder Input (rfinput)

And return 

- Address Line 1
- Address Line 2
- City
- State 
- Zip
- Result Codes

## Tested Environments
- Linux 64-bit g++ 9.4.0, Ubuntu 20.04.05 LTS
- GNU Make 4.2.1
- Melissa data files for 2023-07

## Required File(s) and Programs

#### libmdRightFielder.so
This is the code of the Melissa Object.

#### Data File(s)
- mdRightFielder.cfg
- mdRightFielder.dat

#### Dependencies
- mdRightFielderEnums.h
- mdRightFielder.h

## Getting Started
These instructions will get you a copy of the project up and running on your local machine for development and testing purposes.

#### Install g++ and make
Before starting, make sure that both g++ and make have been correctly installed on your machine. If you are unsure, you can check by opening up your linux terminal, and proceed to execute the commands listed below.

To check your g++ version:

`g++ --version`

To check your make version:

`make --version`

If g++ and make are already installed, you should see something like the following:

![alt text](/screenshots/gppv.png)

![alt text](/screenshots/makev.png)

If you see the logs above that indicate that you have g++ and make installed, then you may skip to the next step. If you do not see them, then you will need to execute the commands below in order to install g++ and make.

First, execute the command: 

`sudo apt update`

To install g++:

`sudo apt install g++`

To install make:

`sudo apt install make`

Once you have finished the installations, you should be able to verify that they have been correctly installed by executing the `g++ --version` and `make --version` commands.

----------------------------------------

#### Download this project
```
$ git clone https://github.com/MelissaData/RightFielderObject-Cpp-Linux
$ cd RightFielderObject-Cpp-Linux
```

#### Set up Melissa Updater 
Melissa Updater is a CLI application allowing the user to update their Melissa applications/data. 

- In the root directory of the project, create a folder called `MelissaUpdater` by using the command: 

  `mkdir MelissaUpdater`

- Enter the newly created folder using the command:

  `cd MelissaUpdater`

- Proceed to install the Melissa Updater using the curl command: 

  `curl -L -O https://releases.melissadata.net/Download/Library/LINUX/NET/ANY/latest/MelissaUpdater`

- After the Melissa Updater is installed, you will need to change the Melissa Updater to an executable using the command:

  `chmod +x MelissaUpdater`

- Now that the Melissa Updater is set up, you can now proceed to move back into the project folder by using the command:
  
   `cd ..`

#### Different ways to get data file(s)
1.  Using Melissa Updater
    - It will handle all of the data download/path and .so file(s) for you. 
2.  If you already have the latest DQS Release (ZIP), you can find the data file(s) and .so file(s) in there
    - Use the location of where you copied/installed the data and update the "DataPath" variable in the bash script.
    - Navigate into the `MelissaRightFielderObjectLinuxCpp` project folder, create a folder named `Build`, and copy all the dll(s) mentioned above into the `Build` folder.
    - Copy all dependencies mentioned above into the `MelissaRightFielderObjectLinuxCpp` project folder.

#### Change Bash Script Permissions
To be able to run the bash script, you must first make it an executable using the command:

`chmod +x MelissaRightFielderObjectLinuxCpp.sh`

As an indicator, the filename will change colors once it becomes an executable.

## Run Bash Script
Parameters:
- -r or --rfinput: a test right fielder input to parse
 	
  This is convenient when you want to get results for a specific right fielder input in one run instead of testing multiple right fielder inputs in interactive mode.  

- -l or --license (optional): a license string to test the Right Fielder Object  
- -q or --quiet (optional): add to the command if you do not want to get any console output from the Melissa Updater

When you have modified the script to match your data location, let's run the script. There are two modes:
- Interactive 

	The script will prompt the user for the right fielder input, then use the provided right fielder input to test the Right Fielder Object. For example:
  ```
  $ ./MelissaRightFielderObjectLinuxCpp.sh
  ```
  For quiet mode:
  ```
  $ ./MelissaRightFielderObjectLinuxCpp.sh --quiet
  ```
- Command Line 

	You can pass a right fielder input in ```--rfinput``` parameter and a license string in ```--license``` parameter to test Right Fielder Object. For example:
  ```
  $ ./MelissaRightFielderObjectLinuxCpp.sh --rfinput "22382 Avenida Empresa, Rancho Santa Margarita, CA 92688"
  $ ./MelissaRightFielderObjectLinuxCpp.sh --rfinput "22382 Avenida Empresa, Rancho Santa Margarita, CA 92688" --license "<your_license_string>" 
  ```
	For quiet mode:
  ```
  $ ./MelissaRightFielderObjectLinuxCpp.sh --rfinput "22382 Avenida Empresa, Rancho Santa Margarita, CA 92688" --quiet
  $ ./MelissaRightFielderObjectLinuxCpp.sh --rfinput "22382 Avenida Empresa, Rancho Santa Margarita, CA 92688" --license "<your_license_string>" --quiet
  ```
This is the expected output from a successful setup for interactive mode:

![alt text](/screenshots/output.png)

## Troubleshooting
Troubleshooting for errors found while running your program.

### C# Errors:
| Error      | Description |
| ----------- | ----------- |
| ErrorRequiredFileNotFound      | Program is missing a required file. Please check your Data folder and refer to the list of required files above. If you are unable to obtain all required files through the Melissa Updater, please contact technical support below. |
| ErrorDatabaseExpired   | .db file(s) are expired. Please make sure you are downloading and using the latest release version. (If using the Melissa Updater, check the bash script for 'RELEASE_VERSION = {version}' and change the release version if you are using an out of date release).     |
| ErrorFoundOldFile   | File(s) are out of date. Please make sure you are downloading and using the latest release version. (If using the Melissa Updater, check the bash script for 'RELEASE_VERSION = {version}' and change the release version if you are using an out of date release).    |
| ErrorLicenseExpired   | Expired license string. Please contact technical support below. |

## Contact Us
For free technical support, please call us at 800-MELISSA ext. 4 (800-635-4772 ext. 4) or email us at tech@melissa.com.

To purchase this product, contact the Melissa sales department at 800-MELISSA ext. 3 (800-635-4772 ext. 3).
