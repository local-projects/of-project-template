This repo is your starting point for any OpenFrameworks-based project. It follows the recommendations found [here](https://www.assembla.com/spaces/lp-internal/wiki/Openframeworks_Project_Organization).  

In short, this repo doesn't contain OpenFrameworks per se, it uses submodules to handle dependencies like OpenFrameworks and OF Addons. 

# Using Git Submodules

Usually you would get all the submodules in the repo with:

```
git submodule update --init
```

But we built a custom script that handles all of it. If you look at the script named ```submods.sh``` in the repo root, you can see it contains a custom definition of a list of submodules, just below the initial comments.

```
SubMods() {
	SubModule: ExternalAddons/WeightedObject https://github.com/local-projects/WeightedObject.git 
	SubModule: ExternalAddons/ofxAnimatable https://github.com/local-projects/ofxAnimatable.git 
	...
	SubModule: OpenFrameworks https://github.com/local-projects/OpenFrameworks.git OF?https://github.com/OpenFrameworks/OpenFrameworks.git
}
```

This custom syntax can be deciphered like this:

```
SubModule: pathToSubmodule submoduleURL upstreamName1?anotherSubmoduleURL upstreamName2?anotherSubmoduleURL
```

The idea behind this is to have a full submodules definition in a single file for the whole repo. This means that if you need to add new submodules, you can just edit this file and re-run the script, and it will take care of it all.

So, instead of using git directly to handle the submodules, just invoke the script:

```
./submods.sh
```

This will clone OpenFrameworks as a submodule inside the ```/OpenFrameworks``` folder, together with all the addons we use frequently. All the non-standard addons (ie non core OF addons) go in the ```/ExternalAddons``` folder.

You can read more about Git Submodules [here](https://github.com/blog/2104-working-with-submodules), or just Google about it.  

# OpenFrameworks - downloading libs!
The Git version of OpenFrameworks is not ready to run out of the box, you must download the libs for your platform manually; For OSX:

```
./OpenFrameworks/scripts/osx/download_libs.sh
```

On Windows, the download script will fail as ```wget``` and ```rsync``` don't exist. I've used [chocolatey](https://chocolatey.org/) to install both and it worked.


# CCache 
Required for Ccode project compilation - ccache caches your obj files to speed up compiling. Handy when we have as many addons as we do. Just install it with [Homebrew](https://brew.sh):

```
brew install ccache
```

For more info, see this [forum thread](https://forum.openframeworks.cc/t/speeding-up-compilation-with-ccache-xcode-tip/23492/7).

add these 2 lines at the end of ```CoreOF.xcconfig```
 
```
CC = $(OF_PATH)/libs/openFrameworksCompiled/project/osx/ccache-clang.sh
CXX = $(OF_PATH)/libs/openFrameworksCompiled/project/osx/ccache-clang++.sh
```

AND drop these 2 files (```ccache-clang.sh``` and
```ccache-clang++.sh```) in ```$(OF_PATH)/libs/openFrameworksCompiled/project/osx```


**if you dont care / dont want to deal with ccache, just remove/comment-out these 2 lines mentioned above from ```CoreOF.xcconfig```**

**Note that Xcode will fail to compile using ccache if you enable the ```Address Sanitiser```; just comment out those two lines in ```CoreOF.xcconfig ``` if you need a build with it.**


# Xcode 8 plugins

If you want to have plugins in Xcode 8, try [this](https://github.com/XVimProject/XVim/blob/master/INSTALL_Xcode8.md).

