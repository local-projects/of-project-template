#!/bin/bash

cd "$(dirname "$0")" #cd to where the script command is (when 2-clicked from the fidner)

repoRoot=$(git rev-parse --show-toplevel); 
echo "Building Release for Repo: $repoRoot"
cd "$repoRoot"  #go to repo root

## CONFIG - EDIT HERE ################################################################
XcodePrjPath="AddonsExamples/ofxAppExample/ofxAppExample.xcodeproj"; #the Xcode Project name (in /Apps/$appFolderName/)
XcodeScheme="ofxAppExample Release"
openframeworksPath="./OpenFrameworks"; #where is OpenFrameworks in the repo?
shouldCleanBeforeBuild=false; #should cache from previous builds be used? Or a full build from scratch?

#note that this script will fail if xcode-select is not pointing to the right version of Xcode.
#run $ xcode-select -p; to see what version of Xcode will xcodebuild use.
#set what xcode version to use with $ sudo xocde-select -s /path/to/xcode/
###################################################################################### 



#test if OF is there...
if [ -d "$openframeworksPath/examples" ]; then #seems like the OF folder is fully there
	echo "Openframeworks seems to be there..."
else
	echo "Can not find OpenFrameworks! Trying to init & update submodules...";
	echo "running git submodule update --init;"
    git submodule update --init;

    if [ ! -d "$openframeworksPath/examples" ]; then #seems like the OF folder is still not there, exit
	    echo "Can't find OpenFramworks! exiting!"
	 	exit 1
	fi
fi

#test if the Openframeworks libs are in place - if not, download them
if [ ! -f "$openframeworksPath/libs/glm/include/glm/glm.hpp" ]; then
	echo "OpenFrameworks libs are not present!"
    if [ -f "$openframeworksPath/scripts/osx/download_libs.sh" ]; then #does this version of OF have a download_libs script?
    	echo "Downloading now..."
		echo "Running script '$openframeworksPath/scripts/osx/download_libs.sh'"
		eval "$openframeworksPath/scripts/osx/download_libs.sh"
	else
		echo "It seems this verion of OpenFramewoks doesn't require a separate download of lib files..."
	fi
else
	echo "OpenFrameworks libs are present..."
fi

buildCommand="build";
if [ "$shouldCleanBeforeBuild" = true ]; then
	buildCommand="clean build";
fi

#this is to handle a script that needs to build several binaries - add up all the build results so that if any build fails,
#the script returns fail (with exit $buildResult)
buildResult=0; #sum all the build results, one by one. The final sum must be zero for it all to be good.

#build the project - using cache objects from prev builds
xcodebuild -scheme "$XcodeScheme" -project "$XcodePrjPath" $buildCommand 
buildResult=$(($((buildResult)) + $(($?)))) #sum exit code of xcodebuild with total exit code sum

echo "All Done! Build Result: $buildResult"
exit $buildResult
