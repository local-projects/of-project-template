#!/bin/bash

#cd into the path where the .command file resides
repoRoot=$(dirname "$0");
echo "Building Release for Repo: $repoRoot"
cd "$repoRoot" 


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


echo-blue "This script will build all the xcode projects inside \"AddonsExamples\" and \"Sketches\""

mdfind "kMDItemDisplayName == *.xcodeproj" -onlyin ../AddonsExamples -onlyin ../Sketches | while read line; do
    echo-green "Building project at \"$line\""
     xcodebuild  -project "$line" 2>/dev/null  | egrep '^(/.+:[0-9+:[0-9]+:.(error|warning):|fatal|===|\*\*)'
done


