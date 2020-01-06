# OpenFrameworks Project Template	

This repository sets forth a template that allows versioning of OpenFrameworks and its Addons. It has been used by [Local Projects](https://localprojects.com/) across many museum exhibits.



## Quickstart Setup

### Step A: Copy Template

1. [Create a new, empty Github repository](https://github.com/new) repository to copy the template into. For example, let' call this repo **myProject** in the Github user account **local-projects**.

2. Clone the template onto your computer. The branch should match your desired OF version (here, **0.10.1**). Supported versions include `0.10.1`, `0.11.0`.

   ```bash
   git clone -b version/0.10.1 https://github.com/local-projects/of-project-template.git
   ```

3. Rename this template folder to the name of your repo. Navigate into the repo.

   ```bash
   mv of-project-template myProject
   cd myProject
   ```

4. Set the remote origin to your project repo. Push the template files to your repo.

   ```bash
   git remote set-url origin https://github.com/local-projects/myProject.git
   git push
   ```

### Step B: Setup Repo

1. Update all submodules. (This downloads OpenFrameworks and all addons).

   ```bash
   git submodule update --init --recursive
   ```

2. Download OpenFrameworks libraries. Pass the platform (here, Visual Studios 2017) and the version (here, 0.10.1 — this should correspond with the template's branch version above). 

   Available platforms include `android`, `emscritpen`, `ios`,` linux`, `linux64`, `linuxarmv6l`, `linuxarmv7l`, `msys2`, `osx`, `tvos`, `vs2015`, `vs2017`. (Visual Studio 2019 will work with the `vs2017` flag.)

   *Note: On some platforms, this steps requires a special bash environment.*

   ```bash
   ./OpenFrameworks/scripts/dev/download_libs.sh -p vs2017 -v 0.10.1
   ```



## What is OF?

[OpenFrameworks](https://openframeworks.cc/) (OF) is an open-source arts engineering toolkit. It is commonly used by artists, engineers, students, educators, and creative agencies to make experimental interfaces, performances, interactive experiences, exhibits, hardware prototypes and more. It is widely recognized as an incredibly powerful creative coding tool, and rightly so—because of its implementation in C++. 

### Addons

Part of OF's power lies in its extensibility. In order to add more functionality to OF, it is common practice to add "Addons" to it. [Addons](http://www.ofxaddons.com/categories) are libraries of code that easily interface with the core code of OF. Addons always begin with the prefix "ofx", as in *ofxOpenCv* or *ofxGui*. As of 2019, there are only a few verified Addons that come prepackaged with OF (the aforementioned two included). The rest of the Addons in existence are contributed by the community. They still bear the prefix "ofx"; however, since they are not verified or pre-vetted, they are not guaranteed to work. 

Oftentimes, it only takes a few changes to unverified Addons' code to make them work. Good software practices instruct us to first [fork](https://help.github.com/en/articles/fork-a-repo) an Addon, then change it and push those changes to our fork. This fork would then be the Addon we use with OF, since we can be sure it works. With all these changes to code and so many different versions of the same Addons in existence, keeping tracking of which ones to use can quickly become a frustrating task. This template proposes one solution for tracking Addons by including them as a [submodule](https://git-scm.com/book/en/v2/Git-Tools-Submodules) in a parent repository (more on this later). 

### OF Version

OpenFrameworks has been around for more than a decade. As software standards change and new features are requested, improvements are contributed to the core codebase. Every now and then, OpenFrameworks posts a new official release. At present, the latest OF version is **0.10.1**.

OpenFrameworks consists of three main pieces: the **Project Generator**, the **source code** and the **libraries**. The source code consists of the core code (.h and .cpp files) that make OF run. These files are compiled when building an application. The libraries consist of pre-compiled code packages with very specific functionalities. For example, one library may encapsulate all core functions of opencv. It is possible to compile these libraries on your own with Apothecary (a submodule of OF located in OF > Scripts > Apothecary); however, these are notoriously difficult to compile, so downloading precompiled versions is *highly* recommended.

OF is most commonly setup by [downloading](https://openframeworks.cc/download/) a zipped file from OF's website, then unzipping it and placing it in an arbitrary location on your computer. Addons are downloaded similarly from their github repository and manually renamed and placed into the *OpenFrameworks > Addons* folder. Since this approach is quick and easy, it is the most common approach people take, especially in educational settings. This approach gives you everything you need to get started right away. However, it doesn't version OF or the Addons you use. Therefore, it can be difficult to keep, maintain, and share projects that use different versions of OF and/or Addons. 

Here are some use cases that would be difficult with a traditional approach, but easier using this template:
- OF releases a new version and you want to use your old projects with it. 
	- The traditional approach would force you to re-download the zipped folder and after extracting all files, manually copy your old project files over to this new instance of OF.
	- This template allows you to pull new versions of OF from the command line, since your OF repo is a versioned git repository.
- You want to save some changes you've made to OF's core or to an Addon.
	- The traditional approach would not allow you to save changes to OF, nor to addons. Sorry!
	- This template allows you to make changes to OF and to Addons, and to commit these changes to a remote code repository, thereby saving your changes for all posterity!
- You want to share your project with a friend, so they can run it on their own computer.
	- The traditional approach forces you to manually send your files through a file transfer service like WeTransfer, Google Drive, etc. If you've made any changes to Addons or to the core, it will be difficult to keep track of everything without sending the entire OpenFrameworks folder.
	- This template is versioned, so as long as you commit any changes you make, you will be able to send your friend a link to your repo. If they follow the same directions to setup your project as those defined below, then their repository will look exactly the same as yours, and they should be able to run your project. Note: if they use a different operating system, some changes may be needed.
- You want your project to last a *long* time. You're not sure how long it will last, but you want to be able to maintain your project for the next 5 years, or to replicate it in 5 years time on a different machine.
	- The traditional approach doesn't provide you any tools to do this. Sorry!
	- This template versions nearly everything, with the exception of the Project Generator. So, you should much more easily be able to maintain your code and any changes to any addons or the OF core. 
	

Versioning your projects using a platform like Github allows your code to be saved, maintained and shared much more easily. This is why we made this template—because we want our projects to last a long time. If you're using OF for quick prototypes or have no need for your projects to last years, this template may not be right for you. This template makes OF more flexible; however, it also requires familiarity with command line tools, git workflows, and a few extra steps to get setup correctly.

### "Project" Terminology

The traditional approach to working with OF uses the word "project" to denote a single application. These "projects" are stored in folders two levels down in the OF directory. For example, *myProject* might live here: *OpenFrameworks > apps > myApps > myProject*. In the template set forth in this repository, we use "project" to denote the collection of *all* code encompassing an exhibition, installation, etc., and the word "application" to define a single application of OF. For example, say we are creating a new museum. Each exhibit in this museum will be its own "project" by our definition. Therefore, we would use this template for *each* exhibit in the museum. Since each exhibit is a self-contained piece of software, sometimes developed by different people, each exhibit (project) may use a different version of OF and/or different versions of the same addons. This template allows for just this. Furthermore, this template is capable of containing multiple "applications," either in the *Sketches* or *Apps* folder. Traditionally, the folder *Sketches* is used for quick applications, prototypes, proof of concepts, etc., while *Apps* contains the final (or in-progress) applications deployed in an exhibit.

##### Submodules

A quick note on submodules





### Project Generator

(Does not align with the name of this template...)

















Create New Project

Import Existing Project









Note: Github templates do not work, since they do not copy submodules








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


ExternalAddons
How to add?
How to change / update / save?
How to point to new repo / etc

Other options? ofPackageManager


How to generate a new project
Download project generator
Link correct OF version
Make sure addons.make has correct relative links (esp to External Addons)
Generate
For vs2019, allow upgrade to v142 toolset


What are all of the other folders used for? Deployment, Scripts, etc.







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
