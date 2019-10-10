#HOW TO BUILD

The "build.command" is all you need to build a "deployment pack". When running "build.command" a "Release" folder will be created at the repo root, ready to be copied over the the production machine and run.

*	You can build by 2-clicking the "build.command" file
*	This will only build on OSX!
*	This will create a folder called "Release" at the repo root
*	This folder should not be checked in the repo
*	The folder MUST contain EVERYTHING you need for a deployment; for you to copy its contents over to the release machine in /LocalProjects/
*	By EVERYTHING I mean configuration files, etc. The creation of a "deployment pack" should be fully automated.
*	See the ReadMe inside the Deployment folder for more info

The final deployment computer file structure should look like this: 

```
/LocalProjects
	/LaunchCtl
		/Wall.plist
	/ProjectName
		/ProjectName.app
		/data
	/Scripts
		/runAndReportOnCrash.sh
		/sendCrashReport.sh	
	/start.command
	/stop.command
```

