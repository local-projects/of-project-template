#!/usr/bin/env bash

#This is a script that CJ wrote and that Oriol hacked into to make managing several remotes for each submodule easier

###############################################
#   _____       _     __  __           _      #
#  / ____|     | |   |  \/  |         | |     #
# | (___  _   _| |__ | \  / | ___   __| |___  #
#  \___ \| | | | '_ \| |\/| |/ _ \ / _` / __| #
#  ____) | |_| | |_) | |  | | (_) | (_| \__ \ #
# |_____/ \__,_|_.__/|_|  |_|\___/ \__,_|___/ #
#                                             #
###############################################                                          

#######################################################################
# Change this if you want to change the name of your additional remotes
#######################################################################
remote_name="upstream"

#################################################################################
# UTILS :: one-Liners that may be handy when preparing content to run this script
#################################################################################

# Create list of all remotes with custom name as they are currently set in the repo
# $ git submodule foreach git remote -v | grep fetch | grep -v Entering | grep -v origin | sort | xargs -L1 | awk ' { print $1 "?" $2 } '

# List every submodule in the project
# $ git submodule foreach git remote -v | grep fetch | grep -v Entering  | grep  origin | sort | xargs -L1 | awk ' { print $2 } ' | awk -F\/ ' { print $5 } ' | awk -F. ' { print $1 } '

# Given a file named "addonsList", create what SubMods() should have for this script to create repos for all of them
#
# $ cat addonsList | sort | xargs -L1 | awk ' { print "SubModule: ExternalAddons/" $1 " https://github.com/local-projects/" $1 ".git armadillu?https://github.com/armadillu/" $1 ".git"} '

#############################################################################
#
# Register your modules here following the format:
#     SubModule: [path for module (relative to git root)] [origin url] [upstream] [upstream2] ...
#
# And then kindly pretend that no horrible bash scripting exists in this file.
#
##############################################################################

SubMods() {
SubModule: ExternalAddons/ofxRemoteUI https://github.com/local-projects/ofxRemoteUI.git
SubModule: ExternalAddons/ofxScreenSetup https://github.com/local-projects/ofxScreenSetup.git
SubModule: ExternalAddons/ofxSuperLog https://github.com/local-projects/ofxSuperLog.git
SubModule: ExternalAddons/ofxTimeMeasurements https://github.com/local-projects/ofxTimeMeasurements.git
}




##########################
# Nothing to see here... #
##########################

###############
# Git Minutia #
###############
#############################################################################################
#
# SubModule: => [ SubModule Path ] [ URL to Main Repo ] { Other Upstrams }
#
# The star of our show. Is it terrible practice to suffix a colon to a function name
# to give the user the impression that this is anything other than a shell script?
# You better believe it.
#
# As the only real interface for the user, "SubModule:" is responsible for 2 main things:
#
# * Ensuring that the submodule, does indeed, exist at the specified path.
# * That all of the registered upstreams are configured in that submodule's git configuration
#
# Modest goals for a modest program. But in bash, nothing is ever as simple as it seems.
#
#############################################################################################
SubModule:() {
    modpath=$1
    origin=$2
    upstreams=${@:3}
    
    Ensure-SubModule-Exists $modpath $origin

    # Iterate through each additional upstream and make sure it is properly set
    index=1
    for upstream in ${upstreams}; do

    	if [[ $upstream == *$'?'* ]] #see if the upstream string contains "?" > which indicates a custom name for upstream
		then #upstream URL contains "?" which means user wants a specific upstream name
			
			upstreamURL=$(echo "$upstream" | awk -F\? ' { print $2 } ')
			upstreamName=$(echo "$upstream" | awk -F\? ' { print $1 } ')
			
			Ensure-SubModule-Upstream $modpath $upstreamURL $upstreamName
		
		else #no "?" found in upstream, meaning no custom upstram name was defined by the user
		
			# I'm going to assume that most of the time there will only be one additional remote
			# so we should make the name a bit easier to remember by not including the index.
			# For subsequent ones, however, we'll just append our index.
			
			name=$remote_name
			if [ "$index" -ne 1 ]; then
				name="${name}${index}"
			fi
	
			Ensure-SubModule-Upstream $modpath $upstream $name
	
			(( index++ ))

		fi

    done
}

#############################################################################################
#
# Ensure-SubModule-Exists: => [ SubModule Path ] [ URL to Main Repo ]
#
# Ensure-SubModule-Exists ensures that the submodule exists. Shocking, I know. If the
# submodule does not exist then it is responsible for adding it. If the submodule exists But
# is pointing to a different origin then what was passed in, it is responsible for updating
# it (dependent on the user's permission, naturally). If the submodule exists and is pointing
# to the right place, it is responsible for keeping its grubby paws off.
#
#############################################################################################
Ensure-SubModule-Exists() {
    modpath=$1
    origin=$2

    url_config_key="submodule.$(no-trailing-slashes $modpath).url"

    # The submodule's url as it is in the .gitmodules file
    submod_url=$(git config --file .gitmodules --get $url_config_key)

    # If there is no entry in the .gitmodules file then we should go ahead and add the submodule
    if [ -z "$submod_url" ]; then
        echo-info "Adding submodule $origin to $modpath"
        git submodule add $origin $modpath

    # If there is an entry in the .gitmodules file but it is different than what we have, then
    # we should ask the user if he/she wants to update it.
    elif [ "$submod_url" != "$origin" ]; then
        echo-info "SubModule at '$modpath' is currently pointing to '$submod_url' but has been specified as '$origin'"
        if prompt-user "Would you like to update the origin of '$modpath' from '$submod_url' to '$origin'?"; then
            git config --file .gitmodules --replace-all $url_config_key $origin
            git submodule sync
        fi
    fi
}

#############################################################################################
#
# Ensure-SubModule-Upstream: => [ SubModule Path ] [ Upstream URL ] [ Remote Name ]
#
# Ensure-SubModule-Upstream is responsible for making sure that the passed in url is set
# as a remote of the submodule at the passed in name.
#
#############################################################################################
Ensure-SubModule-Upstream() {
    modpath=$1
    upstream=$2
    name=$3

    # Save our current working directory so we can come back to it at the end of the function
    cwd=$(pwd)

    # Let's cd into our submodule so we can more easily investigate its configuration
    cd $modpath

    remote_url=$(git config --get remote.$name.url)

    # If there is no entry for the remote url then we should go ahead and add it
    if [ -z "$remote_url" ]; then
        echo-info "Adding a remote to '$modpath' pointing towards '$upstream' under the name '$name'"
        git remote add $name $upstream

    # If the remote already exists but pointing to another location, let's see if we can update
    # it
    elif [ "$remote_url" != "$upstream" ]; then
        echo-info "'$modpath' already has a remote '$name' but it is pointing towards '$submod_url', not '$upstream' as specified."
        if prompt-user "For '$modpath', would you like to update the url from '$submod_url' to '$upstream'?"; then
            git remote set-url $name $upstream
        fi
    fi
    
    # Finally, let's make sure that we cd back to where we started
    cd $cwd 
}

###########
# Helpers #
###########

######################################################################################
#
# no-trailing-slashes => { Path }
#
# Ah, the beauties of shell scripting, eh? We need the submodule path without trailing
# slashes and this gives it to us, try not to think too much about it.
#
######################################################################################
no-trailing-slashes() {
    param=$1

    echo $(shopt -s extglob; echo "${param%%+(/)}")
}

######################################################################################
#
# prompt-user => { Message }
#
# Poses a prompt to the user, generally asking for permission to perform some action,
# and returns a status of 0 for a response of "yes" or a 1 for a response of "no".
#
# Unless, of course, you're one of those fatalists who believes that free will is an
# illusion. In which case this function just pointlessly writes your prompt to standard
# out and awaits a deterministic response.
#
######################################################################################
prompt-user() {
    prompt=$1

    orange='\033[0;33m'
    nocolor='\033[0m'


    while true
    do
        echo -en "$orange$prompt (y/n)?$nocolor"
        read -n 1 -s choice
        echo
        case "$choice" in
            y|Y ) return 0;;
            n|N ) return 1;;
        esac
    done
}

#############################
#         Logging           #
#                           #
# (Because colors are nice) #
#############################

######################################################################################
#
# echo-color => [COLOR CODE] { Message }
#
# Couldn't be simpler, echo out the passed in color command to the terminal, echo our
# message, and then tell the terminal to go back to its default. Only logs to standard
# out because I'm lazy.
#
######################################################################################
echo-color() {
    color=$1
    message=${@:2}

    nocolor='\033[0m'
    echo -e "${color}${message}${nocolor}"

}

######################################################################################
#
# echo-info => { Message }
#
# Logs a message in a cool, soft, baby's blue.
# 
# Should be used to calm and comfort the user that everything is going according to
# plan and we are not, in fact, hijacking their computer (while, in actuality, we may
# very well may be. echo-info does not, as a rule, discriminate).
#
######################################################################################
echo-info() {
    blue='\033[0;34m'
    echo-color ${blue} $@
}

#######################################################################################
#
# echo-success => { Message }
#
# Logs a message in strong, cocky, emerald green.
# 
# A rather forceful affair, echo-success
# is. It should evoke a feeling of confidence and pride. "Don't worry, boys, we pulled it
# off," addressed with a sly, self-sure smile. Think of the USS Abraham Lincoln with it's
# "Mission Accomplished" sign.
#
#######################################################################################
echo-success() {
    green='\033[0;32m'
    echo-color ${green} $@
}

#######################################################################################
#
# echo-warning => { Message }
#
# Logs a message in a distressing, frightful, oxblood red.  
#
# This is it, friends, the hubristic human experiment has been for naught. Go home and
# be with your family while you can, it appears as though we were not able to update a
# git submodule. "Woe to you depraved souls. Bury here and forever all hope of Paradise."
#
#######################################################################################
echo-warning() {
    red='\033[0;31m'
    echo-color ${red} $@
}

###############
# Entry Point #
###############

# First things first, let's change our current working directory to the location of
# this file so we know where we are.
cd "$(dirname "$0")"

# We'll also want to make sure that we're actually in the root of a git repo
if ! ls .git &> /dev/null; then
    echo-warning "It doesn't look like this script is in the root of an initialized git repo."
    if prompt-user "Would you like to initialize this directory as a git repo? If not this script will be aborted (Nothing personal. It's not you, it's me.)"; then
        git init
    else
        exit 1
    fi
fi

echo-info "Performing basic git submodule initialization and updates"
git submodule init
git fetch --recurse-submodules=yes --jobs=10
git submodule update --jobs=10

# Manage our submodules
SubMods
echo-success "Your git submodules have been managed"
