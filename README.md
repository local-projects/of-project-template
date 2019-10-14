# OpenFrameworks Project Template	

This repository sets forth a template that allows versioning of OpenFrameworks and its Addons. It has been used by [Local Projects](https://localprojects.com/) across many museum exhibits.



###### What is OF?

[OpenFrameworks](https://openframeworks.cc/) (OF) is an open-source arts engineering toolkit. It is commonly used by artists, engineers, students, educators, and creative agencies to make experimental interfaces, performances, interactive experiences, exhibits, hardware prototypes and more. It is widely recognized as an incredibly powerful creative coding tool, and rightly so—because of its implementation in C++. 

###### Addons

Part of OF's power lies in its extensibility. In order to add more functionality to OF, it is common practice to add "Addons" to it. [Addons](http://www.ofxaddons.com/categories) are libraries of code that easily interface with the core code of OF. Addons always begin with the prefix "ofx", as in *ofxOpenCv* or *ofxGui*. As of 2019, there are only a few verified Addons that come prepackaged with OF (the aforementioned two included). The rest of the Addons in existence are contributed by the community. They still bear the prefix "ofx"; however, since they are not verified or pre-vetted, they are not guaranteed to work. 

Oftentimes, it only takes a few changes to unverified Addons' code to make them work. Good software practices instruct us to first [fork](https://help.github.com/en/articles/fork-a-repo) an Addon, then change it and push those changes to our fork. This fork would then be the Addon we use with OF, since we can be sure it works. With all these changes to code and so many different versions of the same Addons in existence, keeping tracking of which ones to use can quickly become a frustrating task. This template proposes one solution for tracking Addons by including them as a [submodule](https://git-scm.com/book/en/v2/Git-Tools-Submodules) in a parent repository (more on this later). 

###### OF Version

OpenFrameworks has been around for more than a decade. As software standards change and new features are requested, improvements are contributed to the core codebase. Every now and then, OpenFrameworks posts a new official release. At present, the latest OF version is **0.10.1**.

OpenFrameworks consists of three main pieces: the **Project Generator**, the **source code** and the **libraries**. The source code consists of the core code (.h and .cpp files) that make OF run. These files are compiled when building an application. The libraries consist of pre-compiled code packages with very specific functionalities. For example, one library may encapsulate all core functions of opencv.

OF is most commonly setup by [downloading](https://openframeworks.cc/download/) a zipped file from OF's website, then unzipping it and placing it in an arbitrary location on your computer. Since this approach is quick and easy, it is the most common approach people take, especially in education. This approach gives you everything you need to get started right away. However, it doesn't version OF or the Addons you use.



However, this source code is not linked to any versioned code respository -- it is just a folder on your computer. What happens if OF releases a new version and you want to use it? You would have to re-download the zip and move all of your files over. What happens if you want to save the edits to your addon in the cloud? You would have to manually upload these changes. 

Using a versioning service like github to manage changes to code allows it to be maintained, organized and updated much more easily. The same is true for OF's core, even if it doesn't change very often, especially if you are creating projects that you want to last a long time. This is why we made this template—because we want our projects to be easily maintained years into the future. If you're using OF for quick prototypes and have no desire or need for your projects to last years, this template may not be right for you.

While this template allows for more flexibility of OF, it also requires a few extra steps to get OF setup correctly. 

###### Submodules

A quick note on submodules







Setting up your own project repo

```C++
git clone [template]
git remote set-url origin [project -- blank]
git push
```









Status: Documentation incomplete; however, version 0.10.1 has been confirmed working on VS2017/19 64bit



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



Run this script with the correct platform. Currently, only version 0.10.1 is supported. Must use terminal or command line to run these commands:

```c++
git clone -b version/0.10.1 https://github.com/local-projects/of-project-template.git
cd of-project-template
git submodule update --init --recursive
OpenFrameworks/scripts/dev/download_libs.sh -p vs2017 -v 0.10.1

```



Project Template <--> OF (source code and libraries)
In order to version OF, must use git. In order to use git, must manually download libraries



What does this expect to be maintained? (location of libs on ci.of.cc)

What needs to be maintained moving forward? (location of libs. access to past project gens?)





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