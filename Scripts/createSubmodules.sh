#!/bin/sh
#from http://stackoverflow.com/questions/11258737/restore-git-submodules-from-gitmodules
#
#this creates all git submodules listed in the local repo .gitmodules file.
#simplifies porting submodule sets from other repos / projects 
#run from the repo root, like this:
#
#./Scripts/createSubmodules.sh 


set -e

git config -f .gitmodules --get-regexp '^submodule\..*\.path$' |
    while read path_key path
    do
        url_key=$(echo $path_key | sed 's/\.path/.url/')
        url=$(git config -f .gitmodules --get "$url_key")
        git submodule add $url $path
    done