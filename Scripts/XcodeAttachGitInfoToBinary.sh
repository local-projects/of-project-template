#/bin/bash

gitCommitNum=$(git rev-list HEAD --count)
gitBranch=$(git rev-parse --abbrev-ref HEAD)
gitSubject=$(git log -1 --pretty=format:"%f")
gitCommitHash=$(git rev-parse --verify HEAD --short)
gitIsDirty=$([[ $(git diff --shortstat 2> /dev/null | tail -n1) != "" ]] && echo "\n*Repo was Dirty!*")
gitAuthor=$(git log -1 --pretty=format:"%an");
gitDate=$(git log -1 --pretty=format:"%aD");
year=$(date +"%Y");
 
if [ -z "$gitCommitNum" ]; then
gitCommitNum="-1"
fi
if [ -z "$gitBranch" ]; then
gitBranch="Unknown Branch"
fi
if [ -z "$gitCommitHash" ]; then
gitCommitHash="Unknown Commit"
fi
if [ -z "$gitAuthor" ]; then
gitAuthor="Unknown Author"
fi
if [ -z "$gitDate" ]; then
gitDate="Unknown Date"
fi


getInfoString=$(echo -e "v$gitCommitNum $gitCommitHash\n$gitAuthor\n$gitDate$gitIsDirty");
copyright=$(echo "LocalProjects © $year")

defaults write "${TARGET_BUILD_DIR}/$INFOPLIST_PATH" "CFBundleShortVersionString" -string "$getInfoString"
defaults write "${TARGET_BUILD_DIR}/$INFOPLIST_PATH" "NSHumanReadableCopyright" -string "$copyright"

mkdir -p "$SRCROOT/src"
touch "$SRCROOT/src/gitInfo.h"

echo -e "#pragma once\n#include <string>\n\nnamespace GIT_INFO {\n
\tconst std::string VerDate=\"$gitDate\";
\tconst std::string VerSubj=\"$gitSubject\";
\tconst std::string VerAuthor=\"$gitAuthor\";
\tconst std::string VerHash=\"$gitCommitHash\";
\tconst int VerCommitCount=$gitCommitNum;
\n}" > "$SRCROOT/src/gitInfo.h"

