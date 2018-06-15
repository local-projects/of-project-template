#!/bin/bash

#cd into the path where the .command file resides
repoRoot=$(dirname "$0");
echo "Building Release for Repo: $repoRoot"
cd "$repoRoot" 

## CONFIG - EDIT HERE ################################################################
binaryName="SampleApp"; 	#the binary name minus ".app"
appFolderName="SampleApp"; #the folder name that hosts your projects (inside /Apps/)
XcodePrjName="SampleApp"; #the Xcode Project name (in /Apps/$appFolderName/)
###################################################################################### d

#echo "This will build all required apps for a complete CWRU_WALL front-end install." | tee >(say)
#sleep 7

#echo "Switching to Master branch" | tee >(say)
#swithcing to master branch
#git checkout master

#echo "Fetching submodules..." | tee >(say)
#git submodule init;
#git submodule sync;
#git submodule update;
#sleep 3

#clean old releases and re-make required folders
rm -rf Release
mkdir -p Release/$appFolderName 

#complile all projects #

echo "Building $binaryName" | tee >(say)
xcodebuild -scheme Release -project "./Apps/$binaryName/$XcodePrjName.xcodeproj" clean build CONFIGURATION_BUILD_DIR="../../Release/$appFolderName"
#This will build the Xcode Project under the "Release" scheme;
#This means the Xcode Project MUST contain a scheme named "Release" (usually its called "projectName Release" so make sure you rename it)

echo "Cleaning up" | tee >(say)
rm -rf Release/*.dSYM
sleep 2;


echo "Copying Start and Stop Scripts, remember to make aliases to start and stop command files to desktop" | tee >(say)
cp -R Deployment/LaunchCtl Release/ #cp launchctl plists
cp -R Deployment/Scripts Release/ #cp crash report scripts
cp Deployment/start.command Release #cp start and stop commands
cp Deployment/stop.command Release
sleep 8;

echo "Remember to type in a password in the crash report script" | tee >(say)
sleep 4;

###### OPTIONAL ###########################################################################
#this might need to change from app to app

echo "Copying required assets" | tee >(say)
rsync -av -q "./apps/$appFolderName/bin/data" "./Release/$binaryName/" --exclude "objectData" --exclude "objectRemoteData" --exclude "textureCache"

rm Release/$appFolderName/data/configs/*.xml #delete possibly messy configs if present
rm Release/$appFolderName/data/logs/* #delete possibly messy old logs

#copy Master Config files into this release
cp -p Configs/* Release/$appFolderName/data/configs

#set pretty finder label and open finder window with results
osascript -e "tell application \"Finder\" to set label index of alias POSIX file \"Release\" to 1" &> /dev/null 
open "Release/"

sleep 3;
echo "All Done!" | tee >(say)
