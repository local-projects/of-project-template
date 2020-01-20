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
    	# call your procedure/other scripts here below
    	#echo "$i"

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

# for i in $(echo $variable | sed "s/,/ /g")
# do
#     # call your procedure/other scripts here below
#     echo "$i"
# done

echo Creating directories

echo Attempting to clone all repos

