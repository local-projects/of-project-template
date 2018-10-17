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



buildResult=0; #sum all the build results, one by one. The final sum must be zero for it all to be good.

#if you are wondering about the {} wraping around the foor loop, its command grouping; and I'm using it to
#be able to keep the valie of $buildResult otuside the loop
# http://mywiki.wooledge.org/BashFAQ/024
mdfind "kMDItemDisplayName == *.xcodeproj" -onlyin ../AddonsExamples -onlyin ../Sketches |
{
    while read line; do
        echo-green "Building project at \"$line\""
        #xcodebuild  -project "$line" 2>/dev/null  | egrep '^(/.+:[0-9+:[0-9]+:.(error|warning):|fatal|===|\*\*)' #nice output with just errors printed
        xcodebuild  -project "$line"; #xcodebuild with all it the verbosity unleashed - we keep this as we need to capture the status code result and piping negates that
        buildResult=$(($((buildResult)) + $(($?)))) 
    done

    echo "All Done! Build Result: $buildResult"
    exit $buildResult
}


