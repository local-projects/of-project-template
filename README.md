What is OpenFrameworks?

What is it good for? installations, things that last a long time, things that don't need licensed software and never will

What do you need to do this? Working knowledge of OF. However, of currently doesn't have a good versioning / package solution to ensure that old projects will be backwards compatible, addons of the right kind will work, etc...

This repo addresses a need for OF. It:

- versions OF (as a submodule)
- versions OF libraries (modified download script)
- versions packages as submodules (allows you to work on submodules as distinct repos and push/pull to/from them)
- automatically downloads submodules
- if someone else gets your version of this repo, they should be able to reproduce your system

Expectations for this repo moving forward

- each OF release will be concurrent here and will download the respective OF libraries

How to use this repo. What is the process like for setting it up?

- git clone
- git submodule update --init --recursive
- ./download_libs.sh (per-platform instructions) (per-version instructions?)









This repo is your starting point for any OpenFrameworks-based project. It follows the recommendations found [here](https://www.assembla.com/spaces/lp-internal/wiki/Openframeworks_Project_Organization).  

In short, this repo doesn't contain OpenFrameworks per se, it uses submodules to handle dependencies like OpenFrameworks and OF Addons.

# Using Git Submodules

Usually you would get all the submodules in the repo with:

```
git submodule update --init --recusive
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

You will have to first install chocolatey (follow the instructions on their site), then install wiget and rsync;

```
choco install wget
choco install rsync
```

and then run the script in ```./OpenFrameworks/scripts/vs```. To run the script, open a git bash window in that directory, and type ```./download_libs.sh```.

#Installing Git

If you are on Windows, you will need to install git. Get it from [here](https://git-scm.com/download/win) and go though the installation with all the default options, don't change anything on any of the prompt screens.

# CCache
Required for Ccode project compilation - ccache caches your obj files to speed up compiling. Handy when we have as many addons as we do. Just install it with [Homebrew](https://brew.sh):

```
brew install ccache
```

For more info, see this [forum thread](https://forum.openframeworks.cc/t/speeding-up-compilation-with-ccache-xcode-tip/23492/7).

To get CCache working with OF, we added these 2 lines at the end of ```CoreOF.xcconfig```  (in `OpenFrameworks/libs/openFrameworksCompiled/project/osx`) to our [fork](https://github.com/local-projects/openFrameworks/tree/LP/0.10.0_ccache) of OpenFrameworks, note its the branch ```LP/0.10.0_ccache```.

```
CC = $(OF_PATH)/libs/openFrameworksCompiled/project/osx/ccache-clang.sh
CXX = $(OF_PATH)/libs/openFrameworksCompiled/project/osx/ccache-clang++.sh
```

**if you dont care / dont want to deal with ccache, just remove/comment-out these 2 lines mentioned above from ```CoreOF.xcconfig```**

**Note that Xcode will fail to compile using ccache if you enable the ```Address Sanitiser```; just comment out those two lines in ```CoreOF.xcconfig ``` if you need a build with it.**


# Xcode 8 plugins

If you want to have plugins in Xcode 8, try [this](https://github.com/XVimProject/XVim/blob/master/INSTALL_Xcode8.md).
