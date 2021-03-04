#!/bin/bash

echo ---- Installing openframeworks ----

git submodule update --init --recursive

echo ---- Attempting to install all submodules ----

input="${PWD}/ExternalAddons.make"
echo "ExternalAddons Path: $input"

while IFS= read -r line
do
	counter=0

	for i in $(echo $line | sed "s/,/ /g")
	do

    	if [ "$counter" == "0" ]; then
    		addon_name="$i"
            path="ExternalAddons/${addon_name}"
    	else
    	   addon_url="$i"
    	   echo "${addon_url} to path ${path}"
           git submodule add $addon_url $path
        fi
    	 
    	((counter++))
	done

done < "$input"


echo  ---- Completed Submodule Install ---- 


