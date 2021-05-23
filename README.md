# OpenFrameworks Project Template	

This repository sets forth a template that allows versioning of OpenFrameworks and its Addons. It has been used by [Local Projects](https://localprojects.com/) across many museum exhibits.



## Quick Setup

Run these commands in the command line. Replace `0.11.2` with your OF version and `vs2017` with your platform (for example, `osx`, `linux`, `vs2017`, etc). 

On Windows, make sure `unzip`, `curl`, `wget`, and `rsync` are installed.

``` bash
git clone -b version/0.11.2 --recursive https://github.com/local-projects/of-project-template.git
./of-project-template/OpenFrameworks/scripts/dev/download_libs.sh -p vs2017 -v 0.11.2
```

## Quick Links

[Create a new project](#create-new-project)

[Create](#create-new-app) or [rebuild](#rebuild-existing-app) an app

[Add](#add-addon-to-existing-app) or [remove](#remove-addon-from-app) an addon to/from an app

[Add a new external addon to a project](#add-new-external-addon-to-project) or [commit an external addon's changes](#commit-changes-to-an-external-addon)

[Add an app icon and version](#add-app-icon-and-version)



## Terminology

<u>*Project*</u> - This template is a project. A project can contain multiple apps. It represents the interactive for an exhibit, installtion, etc.

*<u>App</u>* - A single OpenFrameworks application. Perhaps counterintuitively, the *projectGenerator* creates apps. Elsewhere, this may be called a "project." It may be used to describe the folder that contains its files ("app files"), the *bin* folder, or the binary executable that begins program execution.

*<u>App Files</u>* - The files and folders within an app folder. Elsewhere, these may be called "project files." 

*<u>Core Addon</u>* - An addon that comes with OF. These are listed in *OpenFrameworks > Addons*.

*<u>External Addon</u>* - Also called "non-core addon", this is a [submodule](https://git-scm.com/book/en/v2/Git-Tools-Submodules) of an addon in the *ExternalAddons* folder.



## Setup Instructions and Usage

### Create New Project

This will create a new project, download its submodules (OF and external addons inlcuded), and download OF libraries.

1. [Create a new, empty Github repository](https://github.com/new) repository to copy the template into. For example, let' call this repo **myProject** in the Github user account **local-projects**.

2. Clone the template onto your computer. The branch should match your desired OF version (here, **0.11.2**). Supported versions include `0.11.2`, `0.11.1`, `0.11.0`. Passing the `--recursive` command will download all submodules, including OF and any external addons.

   ```bash
   git clone -b version/0.11.2 --recursive https://github.com/local-projects/of-project-template.git
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
   
5. Version **0.11.0** and up do not come prepackaged with all addon submodules. Instead, a script named *install_addons.sh* will download any addons you list within it as submodules to directories of your choice. This script is intended to make the process of adding your own addons and submodules easier. To run this script, issue the command:

   ```bash
   ./install_addons.sh
   ```

   Then, commit any changes you make to your **myProject** repo. This will secure these addons as submodules to your project. 

   To change the submodules or their url, open this script file and edit the contents according to the instructions inside.

6. Download OpenFrameworks libraries. Pass the platform (here, Visual Studio 2017) and the version (here, 0.11.0 — this should correspond with the template's branch version above). 

   ```bash
   ./OpenFrameworks/scripts/dev/download_libs.sh -p vs2017 -v 0.11.2
   ```

   Successful executation of this command indicates that files have been downloaded, uncompressed and copied into place. (Unsuccessful execution will be obvious).

   *Note: On some platforms, this steps requires a special bash environment. For Windows development, see the section [Downloading OF Libs with Cygwin](#downloading-of-libs-with-cygwin)*.

   *Note: Do not use any of the other download_libs scripts in this or any other directory within the "scripts" folder. Only this script has been changed to reflect correct library versioning.*

   *All available script flags include:*

| Flag               | Required? | Description                                                  |
| ------------------ | --------- | ------------------------------------------------------------ |
| -p, --platform     | Yes       | Available platforms include `android`, `emscritpen`, `ios`, ` linux`, `linux64`, `linuxarmv6l`, `linuxarmv7l`, `msys2`, `osx`, `tvos`, `vs2015`, `vs2017`. (Visual Studio 2019 will work with the `vs2017` flag.) |
| -v, --version      | Yes       | Version of OF libraries to download. Available libraries include `0.10.0`, `0.10.1`, `0.11.0`, `0.11.1`, `0.11.2` |
| -n, --no-overwrite | No        | Merge new libraries with exisiting ones, use only to download same version for different platforms. |
| -a, --arch         | No        | Available architectures include `32` or `64` for vs2015; `32` or `64` for vs2017; `32` for msys2; `armv7` or `x86` for android; and `64gcc4`, `64gcc5`, `64gcc6`, `armv6l`, or `armv7l` for linux. |
| -s, --silent       | No        | Slient download progress.                                    |
| -h, --help         | No        | Shows help message.                                          |

### Install projectGenerator

The *projectGenerator* GUI is required for creating and modifying apps. Each project can contain mutliple apps. Apps are usually kept in the *Apps* or *Sketches* folders. 

The *projectGenerator* that corresponds to your OF version must be downloaded to your system. Note: *projectGenerator* can only generate app files for the platform on which it is being used.

1. [Download](https://openframeworks.cc/download/) the prebuilt OpenFrameworks zip folder for your platform and desired OF version. See [here](https://openframeworks.cc/download/older/) for archived versions.

2. <u>OSX Instructions</u>

   Open the folder *projectGenerator*. Run the *_runMeFirst.command* script if it exists. Copy the executable *projectGenerator* into your *Applications* folder.

   <u>Windows Instructions</u>

   Copy the entire folder *projectGenerator* into your *Applications* folder. The executable *projectGenerator.exe* is contained inside.

   *Other platforms may require different setup instructions.*

3. Consider renaming the *projectGenerator* with the version of OF you downloaded in order to keep track of different versions of project generators. For example, we might rename this *projectGenerator_v0.11.2*.

4. Discard the rest of the zipped file. It is no longer needed.

5. Run the *projectGenerator*. The first time you run it and any subsequent time you change the project repo it points to, you shall provide the OpenFrameworks path. Click the gear icon in the top right and provide the appropriate path to the OpenFramworks folder. For example, here it would be `/Users/johndoe/Documents/myProject/OpenFrameworks`. If you began working on a different project called **mySecondProject**, then the OF path you would provide would be something like `/Users/johndoe/Documents/mySecondProject/OpenFrameworks`.

### Create New App

Follow this procedure if you would like to create a new app with no addons or with core addons only. The procedure for creating a new app with any external addons requires some initial app to already exist—in this case, skip to [Rebuild Existing App](#rebuild-existing-app).

1. Open the *projectGenerator*. Make sure the correct OpenFrameworks path is set in the settings tab (see the section [Install projectGenerator](#install-projectgenerator) for more instructions).
2. Choose a *Project Name* for your app.
3. Select *Project Path* for this app's folder. For initial sketches, this would be the *Sketches* folder. For final apps, this would be the *Apps* folder. 
4. Select the addons you would like to include from the *Addons* drop-down menu. Note: This drop down only includes the *Core Addons*. To include any (non-core) addons in the *ExternalAddons* folder, you must follow the instructions for importing an existing app. If you don't have a blank app to import, use the steps for creating a new app to generate a blank one.
5. Click *Update*.

### Rebuild Existing App

#### Reasons for Rebuilding an Existing App

1. You would like to include external addons in your <u>new</u> or existing app.
2. You would like to begin with an app that has already been developed but doesn't have its app files generated yet.
3. You would like to update an old app whose app files do not correspond with the version of your code editor. For example, you need to update an app from 
4. The app you want to work on was developed on a different platform. For example, you began developing an app on Mac, but now need to work on Windows.

#### Existing App Requirements

An app is represented by a folder with the name of the app. Rebuilding an app will regenerate its app files.

In order to import an existing app (say, **myApp**), it must contain at least the following files and folders in this directory structure, where [items] are optional. Any other items, including the folders *obj* and *.vs*; the files *\*.sln*,  *\*.vcxproj*, *\*.vcxproj.filters*, *\*.vcxproj.user*, *icon.rc*, *\*.xcodeproj*, *\*.plist*, *\*.xcconfig*, etc. in the main directory; and any *\*.dll*, *\*.exe*, *\*.exp*, *\*.lib*, *\*.ilk*, *\*.pdb*, *\*.app*, etc. in the *bin* folder <u>must be deleted</u>. Failing to do so may result in conflicts later on. Note: All preprocessor defintitions, additional includes, etc. that have been manually added to the project will be wiped and will need to be manually added again after new app files are generated.

- myApp
  - addons.make
  - [bin]
    - [data]
      - [*]
  - [config.make]
  - [Makefile]
  - src
    - main.h
    - ofApp.cpp
    - ofApp.h

#### Rebuilding Instructions

1. Obtain the app you want to import and place it in the *Sketches* or *Apps* folder (depending on your stage of development). Typically, *Sketches* is used for prototyping and *Apps* is used for final development. 

   **If you are beginning from scratch and don't have an app to import, copy the *emptySketch* app in the *Sketches* folder and rename it to the name of your app.**

2. Delete any files that are not included in the above directory structure. Doing so ensures that there will be no conflicts later on.

3. Edit the *addons.make* file to include any core and non-core addons you wish. Core addons are listed with just their name, for example `ofxXmlSettings` in the example below. Non-core addons (in the *ExternalAddons* folder) require more careful inclusion. Their relative path to your app folder must be listed in the *addons.make* file. For example, if our app is located in ***myProject*** > *Sketches* > ***myApp***, and we want to include *ofxRemoteUI*, which is located in ***myProject*** > *ExternalAddons* > *ofxRemoteUI*, then the relative path would be `../../ExternalAddons/ofxRemoteUI`, as listed below.

   *Example of an addons.make file including both core and non-core addons:*

   ```cmake
   ofxOsc
   ofxPoco
   ofxXmlSettings
   ../../ExternalAddons/ofxRemoteUI
   ../../ExternalAddons/ofxTimeMeasurements
   ```

   Note: Not all available external addons are listed in *ExternalAddons*. This folder includes those external addons we use most, but they or their specific hash might not be right for your application. If an external addon is listed in this *addons.make* file, but is not in the *ExternalAddons* folder, the *projectGenerator* will fail to build app files.

   Note: If you are trying to build an example that is provided as part of an external addon, this relative path will need to contain another `../` for any included included external addons, making the pats.

4. Open *projectGenerator*. Make sure the correct OpenFrameworks path is set in the settings tab (see the section [Install projectGenerator](#install-projectgenerator) for more instructions).

5. Click *Import*. Select your app's folder. For example, I might select *myApp* in the folder *Sketches*. If all addon paths have been correctly set and all addons exist, then no errors will be thrown. If they are, re-check the paths in *addons.make*.

6. Click *Generate*.

### Add Addon to Existing App

If the addon is non-core and does not yet exist in the *ExternalAddons* folder, follow the instructions in the section [Add New External Addon to Project](#add-new-external-addon-to-project).

To add an addon (core or non-core) to an existing app, follow the instructions in the section "Rebuild Existing App", except make sure to add your addon to the *addons.make* file in Step 3.

### Remove Addon from App

To remove an addon (core or non-core) from an existing app, follow the instructions in the section "Rebuild Existing App," except make sure to remove your addons from the *addons.make* file in Step 3.

### Add New External Addon to Project

*External Addons are included in this template as submodules (repos within repos) so they can be versioned.*

If you would like to use an external (non-core) addon that is not in the *ExternalAddons* folder, it must first be added to your project repo as a new submodule:

1. Obtain the web url of your addon, for example `https://github.com/local-projects/ofxMyAddon.git`.

2. Navigate into the top (main) level of your project repo and execute the following command:

   ```bash
   git submodule add https://github.com/local-projects/ofxMyAddon.git ExternalAddons/ofxMyAddon
   ```

3. Initialize the addon and update it recursively

   ```bash
   git submodule update --init --recursive
   ```

Now, the addon will be available to include in an app.

### Change the Remote of an Addon

If you would like to change the remote origin url of an addon (submodule), follow these steps:

1. Open the *.gitmodules* file at the top level of your repo.

2. Edit the `url` parameter for the addon of interest. The new url should reflect the url you want this addon's origin to point to.

3. Save the file and close it.

4. At the top level of your repo, run the following commands in the command line to syncronize this new url with the submodule:

```bash
git submodule sync
git submodule update --init --recursive
```

### Commit Changes to an External Addon

External addons are [submodules](https://git-scm.com/book/en/v2/Git-Tools-Submodules). This means they are their own "child" repos, contained within a "parent" repo. A submodule can be edited like any other repo, and changes pushed to it. However, the parent repo doesn't directly store these changes; it only stores the submodule's commit hash. Thus, in order to commit changes to a submodule "in the view of" the parent repo, two steps need to be performed: (1) changes are committed within the submodule, and (2) the submodule's current hash is committed in the parent repo. Let's illustrate this with an example:

Say that we have a project called **myProject** and within it is contained an app **myApp** in the folder *Apps*. **myApp** utilizes the external addon **ofxMyAddon**, which is located in the folder *ExternalAddons*. myAddon enacapsulates some reusable code that is currently used by **myApp**. Thus, we are concurrently developing **ofxMyAddon** in parallel with **myApp**. To save our changes to **ofxMyAddon** we follow these instructions:

1. Navigate into the external addon's directory.

   ```bash
   cd ExternalAddons/ofxMyAddon
   ```

   Calling `pwd` would print `/Users/local-projects/Documents/myProject/ExternalAddons/ofxMyAddon` or something similar.

2. Add the changes you wish (here, all are added), commit the changes, and push these commits to the <u>addon's</u> repo.

   ```bash
   git add .
   git commit -m "Updates to ofxMyAddon"
   git push
   ```

3. Navigate up into the project's main directory.

   ```bash
   cd ../../
   ```

   Calling `pwd` would print `/Users/local-projects/Documents/myProject` or something similar.

4. Add the update to this submodule, commit the changes, and push these commits to the <u>project's</u> repo.

   ```bash
   git add ExternalAddons/ofxMyAddon
   git commit -m "Updated ofxMyAddon"
   git push
   ```

Now, the addon and the project have been updated with said changes to the addon.

### Add App Icon and Version

***Note: These instructions apply only to Windows development using Visual Studios***

In deployment environments, it becomes very useful to have a custom application icon and to embed in the binary (.exe) file metadata like the app's version, creator, copyright, etc.

An example for Visual Studios (with project files) has been provided in *Sketches > emptySketchVS*. Three additional project files make it possible to include an icon and a version. These files are:

1. ***icon.ico*** -- This is the file that describes the icon to be used for this app. Regular image types are not acceptable. The icon must be of type "*.ico". Use a converter like [this one](https://convertio.co/png-ico/) to convert any png's to ico's. Your icon can be called whatever you want, so long as its name is reflected in the file below.

2. ***resource.rc*** -- This is a "resource control" file that describes all of the resources to be compiled into the binary. It is editable in a text-editor. Should you change the name of the icon, also change the name in this file to reflect it. For example, if I change the name of my icon to be "LP.ico", then "icon.ico" should be replaced with "LP.ico" on the following lines:

   ```c++
   #if defined(_DEBUG)
   MAIN_ICON               ICON                    "icon.ico"
   #else
   MAIN_ICON               ICON                    "icon.ico"
   #endif
   ```

3. ***version.h*** -- This is a version header file that defines the metadata of the application. Open it in a text editor and adjust values as you see fit. Version should follow [Semantic Versioning](http://semver.org/). Common user-editable values include:

   ```c++
   // Application version (e.g. 0.0.0)
   #define VERSION_MAJOR               0
   #define VERSION_MINOR               0
   #define VERSION_PATCH               0
   
   // Author, Name, Copyright
   #define VER_COMPANY_NAME_STR	       "Local Projects"
   #define VER_FILE_DESCRIPTION_STR    "Description"
   #define VER_PRODUCTNAME_STR         "myApp"
   #define VER_COPYRIGHT_STR           "Copyright (C) 2020"
   ```

To include an icon and version in a new or existing app, follow these steps

1. Make sure your app's project files have been built.

2. Collect the three files above and make sure their links are correct (for example, make sure the icon's filename is correct in the *resource.rc* file).

3. Copy these files to the target app's folder, alongside its project files.

4. Open the *.sln* file in Visual Studios.

5. In the *Solution Explorer* tab, open your app's directory. If an *icon.rc* file exists, right click on it and select "Remove." Then, select "Delete."

   *Note: This file is automatically generated by the ProjectGenerator to link OF's icon; however, it doesn't contain enough information to sufficiently describe versions, so we have no use for it here.*

6. Right click your app in the *Solution Explorer* and select *Add > Existing Item*. Navigate to the *resource.rc* file in your app folder. Select it and press *Add*.

7. Compile your project as you normally would.

To confirm that your app is build with the icon of your choice, navigate to your app's bin folder. Your app should now use this icon. To confirm the app's metadata has been set, right click your executable (*.exe) and select *Properties*. In the *Details* tab, your metadata should now be listed.

***How to Get Version From Within an App***

See *Sketches > emptySketchVS* for an example of how to retrieve version information from within an app. In short, you can retrieve this information by:

1. In the *Solution Explorer* window, right click your project and select *Properties*. While editing *All Configurations* and *All Platforms*, navigate to *Linker > Input*. Under *Additional Dependencies*, click the down arrow and select *Edit*. On a new line, add `version.lib`. Apply these changes.

2. Add the files `FileVersionInfo.h` and `FileVersionInfo.cpp` to your project. Your will need to copy them to your project's *src* folder and add them in the Solution Explorer. These files can be found in this repo in the directory *Sketches > emptySketchVS > src*.

3. Include the files, create a FileVersionInfo object, and print the version information as needed. See the example in *Sketches > emptySketchVS > src > ofApp.cpp* for reference.

   ```c++
   #include "FileVersionInfo.h"
   
   FileVersionInfo fvi;
   ofLogNotice("File Version Info") << (fvi.create() ? fvi.jsonInfo() : "{}");
   ```



## Philosophy / What is OF?

[OpenFrameworks](https://openframeworks.cc/) (OF) is an open-source arts engineering toolkit. It is commonly used by artists, engineers, students, educators, and creative agencies to make experimental interfaces, performances, interactive experiences, exhibits, hardware prototypes and more. It is widely recognized as an incredibly powerful creative coding tool, and rightly so—because of its implementation in C++. 

### Addons

Part of OF's power lies in its extensibility. In order to add more functionality to OF, it is common practice to add "Addons" to it. [Addons](http://www.ofxaddons.com/categories) are libraries of code that easily interface with the core code of OF. Addons always begin with the prefix "ofx", as in *ofxOpenCv* or *ofxGui*. As of 2019, there are only a few verified Addons that come prepackaged with OF (the aforementioned two included). The rest of the Addons in existence are contributed by the community. They still bear the prefix "ofx"; however, since they are not verified or pre-vetted, they are not guaranteed to work. 

Oftentimes, it only takes a few changes to unverified Addons' code to make them work. Good software practices instruct us to first [fork](https://help.github.com/en/articles/fork-a-repo) an Addon, then change it and push those changes to our fork. This fork would then be the Addon we use with OF, since we can be sure it works. With all these changes to code and so many different versions of the same Addons in existence, keeping tracking of which ones to use can quickly become a frustrating task. This template proposes one solution for tracking Addons by including them as a [submodule](https://git-scm.com/book/en/v2/Git-Tools-Submodules) in a parent repository (more on this later). 

### OF Version

OpenFrameworks has been around for more than a decade. As software standards change and new features are requested, improvements are contributed to the core codebase. Every now and then, OpenFrameworks posts a new official release. At present, the latest OF version is **0.11.2**.

OpenFrameworks consists of three main pieces: the **Project Generator**, the **source code** and the **libraries**. The source code consists of the core code (.h and .cpp files) that make OF run. These files are compiled when building an application. The libraries consist of pre-compiled code packages with very specific functionalities. For example, one library may encapsulate all core functions of opencv. It is possible to compile these libraries on your own with Apothecary (a submodule of OF located in OF > Scripts > Apothecary); however, these are notoriously difficult to compile, so downloading precompiled versions is *highly* recommended.

OF is most commonly setup by [downloading](https://openframeworks.cc/download/) a zipped file from OF's website, then unzipping it and placing it in an arbitrary location on your computer. Addons are downloaded similarly from their github repository and manually renamed and placed into the *OpenFrameworks > Addons* folder. Since this approach is quick and easy, it is the most common approach people take, especially in educational settings. This approach gives you everything you need to get started right away. However, it doesn't version OF or the Addons you use. Therefore, it can be difficult to keep, maintain, and share projects that use different versions of OF and/or Addons. 

Here are some use cases that would be difficult with a traditional approach, but easier using this template:
- OF releases a new version and you want to use your old projects with it. 
	- The traditional approach would force you to re-download the zipped folder and after extracting all files, manually copy your old app files over to this new instance of OF.
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

A quick note on submodules [TODO]

### Project Generator

--TODO--

### Expectations of Maintenance

This template expects a few things to be maintained on OF's end:

1. Project Generators will continue to be available in releases. All prior releases will be available from the downloads page.
2. OF libraries will continue to be kept on the OF Server at `http://ci.openframeworks.cc/libs/` in folders named with their respective versions (for example, `0.11.2`)



## Troubleshooting

### Visual Studios 2019

Visual Studios 2019 works with the OF `vs2017` flag; however, the first time you open a newly generated app in Visual Studios, you will be promted to update the app files to the v142 toolset. Proceed with this update every time you are prompted.

### Downloading OF Libs with Cygwin

Cygwin is a command line environment with a built-in package manager for Windows. Of all command line tools, it provides the easiest way to run the bash script to download OpenFrameworks libraries. An alternative would be to use Powershell or Git Bash; however, the former doesn't download all libraries necessary and the latter is missing common utilities the scripts use for downloading and unzipping files. Another option might be to use Choco, but this has not been verified to work.

#### Install Cygwin

1. Download Cygwin from [here](http://cygwin.com/).
2. Run the installation procedure. Include packages `unzip`, `curl`, `wget`, `rsync`, and `dos2unix` in the installation. The download script requires these packages.

#### Download OF Libs

Certain bash scripts will not run properly in Cygwin unless the line endings are converted from the Windows to the Linux style. Instead of running the `download_libs.sh` script in a bash environment of your choice, follow these steps

1. Open Cygwin.

2. Navigate to your project repo.

3. Convert the script to linux style:

   ```bash
   dos2unix OpenFrameworks/scripts/dev/download_libs.sh
   ```

4. Run the script as you normally would for your desired platform (for example, `vs2017`) and version (for example, `0.11.2`).

   ```bash
   ./OpenFrameworks/scripts/dev/download_libs.sh -p vs2017 -v 0.11.2
   ```

5. Close Cygwin and return to your preferred command line editor.

### Templatizing this Repo with Github Templates

Currently, templatizing this repo will not work, since Github templates do not support submodules.

### ofPackageManager

OpenFrameworks doesn't provide any way to version its addons; however, a 3rd party tool called [ofPackageManager](https://github.com/thomasgeissl/ofPackageManager) makes it easier to mange multiple addons. It isn't recommended to use it with this template, since it cannot version OF itself; however, it is useful to be aware of it and may be right tool for certain users who do not need OF versioning.

### OF Pre-10.0

Releases of OpenFrameworks prior to 10 come with OF libraries, so they don't need to be downloaded with the `download_libs.sh` script.

### CCache

[This section has not been verified to work as of Jan 2020]

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
