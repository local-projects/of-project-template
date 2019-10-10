#!/bin/bash

#this script will compile the UMASS project from the command line - to be used from the git bash.
#It assumes the repo has been cloned, with all the submodules checked out

# SCRIPT CONFIGURATION #########################################################################

projectPath="./AddonsExamples/ofxAppExample/ofxAppTest.sln"; #where in the repo is the project solution file? (sln)
shouldCleanBeforeBuild=false; #should cache from previous builds be used?
buildConfiguration="Release"; #can be either Release or Debug
buildPlatform="x64"; #can be either x64 or Win32 (64bit vs 32bit build)
visualStudioVersion="2017" #valid values are: 2011, 2012, 2015, 2017
openframeworksPath="./OpenFrameworks"; #where is OpenFrameworks in the repo?
verbose=false; #print more stuff!


# SCRIPT EXECUTION ##############################################################################


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
    if [ -f "$openframeworksPath/scripts/vs/download_libs.sh" ]; then #does this version of OF have a download_libs script?
    	echo "Downloading now..."
		echo "Running script '$openframeworksPath/scripts/vs/download_libs.sh'"
		eval "$openframeworksPath/scripts/vs/download_libs.sh"
	else
		echo "It seems this verion of OpenFramewoks doesn't require a separate download of lib files..."
	fi
else
	echo "OpenFrameworks libs are present..."
fi


#Parse visual studio version, set vars accordingly
case "$visualStudioVersion" in
		2010)
			echo "Visual Studio 2010"
			vcvarsVersion="10.0";
			vsVersion="v100";
			msbuildPath="/c/Windows/Microsoft.NET/Framework64/v4.0.30319/MSbuild.exe"
			targetsPath="C:/Program\ Files\ \(x86\)/MSBuild/Microsoft.Cpp/v4.0/"
			;;
		2012)
			echo "Visual Studio 2012"
			vcvarsVersion="11.0";
			vsVersion="v110";
			msbuildPath="/c/Windows/Microsoft.NET/Framework64/v4.0.30319/MSbuild.exe"
			targetsPath="C:/Program\ Files\ \(x86\)/MSBuild/Microsoft.Cpp/v4.0/$vsVersion"
			;;
		2015)
			echo "Visual Studio 2015"
			vcvarsVersion="14.0";
			vsVersion="v140";
			msbuildPath="/c/Windows/Microsoft.NET/Framework64/v4.0.30319/MSbuild.exe"
			targetsPath="C:/Program\ Files\ \(x86\)/MSBuild/Microsoft.Cpp/v4.0/$vsVersion"
			;;
		2017)
			echo "Visual Studio 2017"
			if [ ! -d "/c/Program Files (x86)/Microsoft Visual Studio/2017/Community/Common7/IDE/VC/VCTargets" ]; then
  				echo "Visual Studio 2017 needs to be installed!"
  				exit 1;
			fi
			vcvarsVersion="14.1";
			vsVersion="v141";
			msbuildPath="/c/Program\ Files\ \(x86\)/Microsoft\ Visual\ Studio/2017/Community/MSBuild/15.0/Bin/MSBuild.exe"
			targetsPath="C:/Program\ Files\ \(x86\)/Microsoft\ Visual\ Studio/2017/Community/Common7/IDE/VC/VCTargets"
			;;
		*)
			echo $"Unknown Visual Studio version! valid versions are 2011, 2012, 2015, 2017"
			exit 1
esac


#run VS env setup batch file - as stated in its docs.
#note we supply what version to use (14.0 == VS 2015)
'/c/Program Files (x86)/Microsoft Visual Studio/2017/Community/VC/Auxiliary/Build/vcvarsall.bat' x64 8.1 -vcvars_ver=$vcvarsVersion


if [ "$shouldCleanBeforeBuild" = true ]; then
	buildCommand="Rebuild"
else
	buildCommand="Build"
fi

echo -e "\nBUILDING...\n"

#build using user requested command - verbose or not
if [ "$verbose" = true ]; then
	eval $msbuildPath "$projectPath" -t:$buildCommand -v:diag -nologo -p:Configuration=$buildConfiguration -p:Platform=$buildPlatform -p:PlatformToolset=$vsVersion -p:"VCTargetsPath=$targetsPath"
else
	eval $msbuildPath "$projectPath" -t:$buildCommand -nologo -p:Configuration=$buildConfiguration -p:Platform=$buildPlatform -p:PlatformToolset=$vsVersion -p:"VCTargetsPath=$targetsPath" 
fi

#Check for compilation success!
if [ $? -eq 0 ]; then 
	echo "Compilation Succeeded!"
	exit 0
else
   echo "Compilation Failed!"
   exit 1
fi
