#!/usr/bin/env bash

# ReadMe
# this script sets up the repo for it to be ready for development!
# run this just once, when you first clone the repo
# run this script from its location! (the Git Repository root) 
# ie ./setupOSX.sh

# Check if on OSX
if [[ "$OSTYPE" == "darwin"* ]]; then
	echo "Running on Mac OS X"
else
	echo "Not Running on Mac OS X!"
	exit 1
fi

# Check if running from the repo root
if [ ! -f submods.sh ]; then
    echo "Can't run the script from this location. Run this script from the repo root!"
fi

# Check if homebrew is installed - installed otherwise
which -s brew
if [[ $? != 0 ]] ; then
	echo "installing homebrew"
    # Install Homebrew https://brew.sh
	/usr/bin/ruby -e "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/master/install)"
else
	echo "Homebrew is Installed"
fi

# Check if Ccache is installed
if brew ls --versions ccache > /dev/null; then
	# The package is installed
	echo "Ccache is Installed!"
else
	echo "Ccache is not Installed! Installing..."
	brew install ccache;
fi

# Setup submodules
echo "setting up and downloading submodules"
submods.sh

# OpenFrameworks in repo-form doesn't come with static libs
echo "downloading OF static libs for OSX"
OpenFrameworks/scripts/osx/download_libs.sh


