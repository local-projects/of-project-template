#!/bin/bash

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
