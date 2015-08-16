*	Make new OSX user called “user”, make it standard user. Log in as that user.
*	Make sure you edited "LaunchCtl/Wall.plist" to include the correct paths
*	Run $defaults write com.apple.CrashReporter DialogType Server #to avoid crash report windows

*	Create a LocalProjects folder at the Primary Partition Root


```
sudo chmod 777 /
sudo mkdir /LocalProjects
sudo chmod 777 /LocalProjects
```

*	Use the build.command script to create a "deployment pack". This will create a folder named "Release" at the repo root.
	
*	Copy all contents of “Release” into the "/LocalProjects" directory of the deployment computer. It will look like this:

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


*	make aliases of the /LocalProjects/start.command and /LocalProjects/stop.command scripts to the desktop
*	edit /LocalProjects/Scripts/sendCrashReport.sh with the email / password info to get automated crash reports
*	add start.command to the "user" startup items.
*	start the app by 2-clicking the start.command on the desktop
*	stop the app by 2-clicking the stop.command on the desktop
*	the app will be re-launched if its quit/crashes.
*	Add a hidden keyboard command to force a crash to test the crash report email going through. I usually do it like this:
```
ofApp::keyPressed(int key){
	with(key){
		case 'K': abort(); ///'K' for kill
	}
}
```

