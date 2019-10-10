add any util scripts that you might need here

##createSubmodules.sh

allows you to easily add submodules you used in another repo into this repo. Edit the .gitmodules file at the root of the repo, and run this script. This will make a new submodule for each entry specified in the file


##XcodeAttachGitInfoToBinary.sh
Used from Xcode to add compile current Git repo data to attach to the compiled binary. You can see how by looking at the project "Build Phases", in the phase "Attach Git Info to Binary".