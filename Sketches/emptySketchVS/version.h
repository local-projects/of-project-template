// This file is used by the application's .rc file.
// It defines the binary's version and other metadata. 
// See here for more info: 
// https://docs.microsoft.com/en-us/windows/win32/menurc/versioninfo-resource

// Utilities
#define STRINGIZE2(s) #s
#define STRINGIZE(s) STRINGIZE2(s)

// File Version
#define VERSION_MAJOR               0
#define VERSION_MINOR               0
#define VERSION_PATCH	              0
// #define VERSION_BUILD               0

// Prepare a string version of the file version
#ifdef VERSION_BUILD
#define VER_FILE_VERSION            VERSION_MAJOR, VERSION_MINOR, VERSION_PATCH, VERSION_BUILD
#define VER_FILE_VERSION_STR        STRINGIZE(VERSION_MAJOR)        \
                                    "." STRINGIZE(VERSION_MINOR)    \
                                    "." STRINGIZE(VERSION_PATCH) \
                                    "+" STRINGIZE(VERSION_BUILD)
#else
#define VER_FILE_VERSION            VERSION_MAJOR, VERSION_MINOR, VERSION_PATCH
#define VER_FILE_VERSION_STR        STRINGIZE(VERSION_MAJOR)        \
                                    "." STRINGIZE(VERSION_MINOR)    \
                                    "." STRINGIZE(VERSION_PATCH)
#endif

// Other application metadata
#define VER_COMPANY_NAME_STR        "Local Projects"
#define VER_FILE_DESCRIPTION_STR    "Description"
#define VER_PRODUCTNAME_STR         "myApp"
#define VER_PRODUCT_VERSION         VER_FILE_VERSION
#define VER_PRODUCT_VERSION_STR     VER_FILE_VERSION_STR
#define VER_ORIGINAL_FILENAME_STR   VER_PRODUCTNAME_STR ".exe"
#define VER_INTERNAL_NAME_STR       VER_ORIGINAL_FILENAME_STR
#define VER_COPYRIGHT_STR           "Copyright (C) 2020"

// Uncomment if this a debug application
// #define _DEBUG
// Prepare the filetype information
#ifdef _DEBUG
  #define VER_VER_DEBUG             VS_FF_DEBUG
#else
  #define VER_VER_DEBUG             0
#endif

// Filesystem information
#define VER_FILEOS                  VOS_NT_WINDOWS32
#define VER_FILEFLAGS               VER_VER_DEBUG
#define VER_FILETYPE                VFT_APP













