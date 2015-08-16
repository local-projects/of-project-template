#!/bin/bash

# EDIT HERE #####################################
binaryName="SampleApp"; 	#the binary name
#################################################

#unload the app
launchctl unload /LocalProjects/LaunchCtl/Wall.plist

#just to be sure, kill the process
killall $binaryName;

sleep 2;
