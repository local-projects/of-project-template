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
https://forum.openframeworks.cc/t/speeding-up-compilation-with-ccache-xcode-tip/23492/7

add these 2 lines at the end of ```CoreOF.xcconfig```
 
```
CC = $(OF_PATH)/libs/openFrameworksCompiled/project/osx/ccache-clang.sh
CXX = $(OF_PATH)/libs/openFrameworksCompiled/project/osx/ccache-clang++.sh
```

AND drop these 2 files (```ccache-clang.sh``` and```ccache-clang++.sh```) in ```$(OF_PATH)/libs/openFrameworksCompiled/project/osx```


**if you dont care / dont want to deal with ccache, just remove/comment-out these 2 lines mentioned above from ```CoreOF.xcconfig```


####ccache-clang.sh

```
#!/bin/sh
if type -p /usr/local/bin/ccache >/dev/null 2>&1; then
  export CCACHE_MAXSIZE=10G
  export CCACHE_CPP2=true
  export CCACHE_HARDLINK=true
  export CCACHE_SLOPPINESS=file_macro,time_macros,include_file_mtime,include_file_ctime,file_stat_matches
  exec /usr/local/bin/ccache /usr/bin/clang "$@"
else
  exec clang "$@"
fi
```

####ccache-clang++.sh

```
#!/bin/sh
if type -p /usr/local/bin/ccache >/dev/null 2>&1; then
  export CCACHE_MAXSIZE=10G
  export CCACHE_CPP2=true
  export CCACHE_HARDLINK=true
  export CCACHE_SLOPPINESS=file_macro,time_macros,include_file_mtime,include_file_ctime,file_stat_matches
  exec /usr/local/bin/ccache /usr/bin/clang++ "$@"
else
  exec clang++ "$@"
fi
```

# Xcode 8 plugins

https://github.com/XVimProject/XVim/blob/master/INSTALL_Xcode8.md
