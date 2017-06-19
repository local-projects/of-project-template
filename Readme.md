This repo is your starting point for any OpenFrameworks-based project. 

It follows the recommendations found [here](https://www.assembla.com/spaces/lp-internal/wiki/Openframeworks_Project_Organization).

random notes below:

#OF needs libs!
OF now doesnt compile out of the box, you must download the libs manually
```./OpenFrameworks/scripts/osx/download_libs.sh```


#CCache! 
required for xcode project compilation

```
brew install ccache
```
[forum thread](https://forum.openframeworks.cc/t/speeding-up-compilation-with-ccache-xcode-tip/23492/7)

add these 2 lines at the end of ```CoreOF.xcconfig```
 
```
CC = $(OF_PATH)/libs/openFrameworksCompiled/project/osx/ccache-clang.sh
CXX = $(OF_PATH)/libs/openFrameworksCompiled/project/osx/ccache-clang++.sh
```

AND drop these 2 files (```ccache-clang.sh``` and```ccache-clang++.sh```) in ```$(OF_PATH)/libs/openFrameworksCompiled/project/osx```


**if you dont care / dont want to deal with ccache, just remove/comment-out these 2 lines mentioned above from ```CoreOF.xcconfig```**

**Note that Xcode will fail to compile using ccache if you enable the ```Address Sanitiser```; just comment out those two lines in ```CoreOF.xcconfig ``` if you need a build with it.**


# Xcode 8 plugins

https://github.com/XVimProject/XVim/blob/master/INSTALL_Xcode8.md


# Submodules

There's this script called ```submods.sh``` in the repo root. Run it when you first clone the repo to setup your submodules. Edit it and run it again to add extra submodules, syntax should be self-explanatory.


