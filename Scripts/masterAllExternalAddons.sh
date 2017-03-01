#!/bin/bash

#this script will checkout master and will pull from origin for all submods
#this is a dumb script; run it from /Scripts with ./masterAllExternalAddons.sh


cd ..

for i in ExternalAddons/* ; do
	if [ -d "$i" ]; then
		cd "$i"
		echo "##### Updating $i #######################################"
		git remote -v | grep origin | grep fetch
		git checkout master
		git pull origin master
		cd -
	fi
done
