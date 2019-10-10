#!/bin/bash

cd "$(dirname "$0")" #cd to where the script command is (when 2-clicked from the fidner)

repoRoot=$(git rev-parse --show-toplevel); 
echo "Building Release for Repo: $repoRoot"
cd "$repoRoot"  #go to repo root

echo-color() {
    color=$1
    message=${@:2}

    nocolor='\033[0m'
    echo -e "${color}${message}${nocolor}"
}

echo-green() {
    green='\033[0;32m'
    echo-color ${green} $@
}

echo-blue() {
    blue='\033[0;34m'
    echo-color ${blue} $@
}

echo-blue "This script will build the ofxApp Example"

buildResult=0; #sum all the build results, one by one. The final sum must be zero for it all to be good.

ofxExamplePath="$repoRoot/AddonsExamples/ofxAppExample/ofxAppExample.xcodeproj";

echo-green "Building project at \"$ofxExamplePath\""
xcodebuild -project "$ofxExamplePath"; 
buildResult=$?

echo "ofxApp Example build finished! Build Result: $buildResult"
exit $buildResult
