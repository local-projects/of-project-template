#!/bin/bash

# EDIT HERE #####################################
binaryName="SampleApp"; 
#################################################

#disable persistent window state or "resume" to avoid OS dialog
rm -rf "$HOME/Library/Saved Application State/com.LocalProjects.$binaryName.savedState" 

#launch the app
launchctl load /LocalProjects/LaunchCtl/Wall.plist
sleep 2;