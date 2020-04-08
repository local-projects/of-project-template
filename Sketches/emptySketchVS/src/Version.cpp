//
//  Version.cpp
//  g5_002
//
//  Created by Ben Snell on 1/17/19.
//

#include "Version.hpp"

// -------------------------------------------------
string getExeVersion(string filenameStr)
{
	// Convert string to char*
	const char* filename = filenameStr.c_str();

	// Attempt to get the version
	DWORD dwHandle, sz = GetFileVersionInfoSizeA(filename, &dwHandle);
	if (0 == sz)
	{
		return "Error in GetFileVersionInfoSizeA()";
	}
	char* buf = new char[sz];
	if (!GetFileVersionInfoA(filename, dwHandle, sz, &buf[0]))
	{
		delete[] buf;
		return "Error in GetFileVersionInfoA()";
	}
	VS_FIXEDFILEINFO* pvi;
	sz = sizeof(VS_FIXEDFILEINFO);
	if (!VerQueryValueA(&buf[0], "\\", (LPVOID*)& pvi, (unsigned int*)& sz))
	{
		delete[] buf;
		return "Error in VerQueryValueA()";
	}

	// Version can be read successfully
	string ver = "Version ";
	ver += ofToString((unsigned long)(pvi->dwProductVersionMS >> 16)) + ".";
	ver += ofToString((unsigned long)(pvi->dwFileVersionMS & 0xFFFF)) + ".";
	ver += ofToString((unsigned long)(pvi->dwFileVersionLS >> 16)) + ".";
	ver += ofToString((unsigned long)(pvi->dwFileVersionLS & 0xFFFF));
	delete[] buf;
	return ver;
}

// -------------------------------------------------
string getAppName() {

	// Find all exe's in this app's directory
	ofDirectory dir;
	dir.open("../");
	dir.allowExt("exe");
	dir.listDir();

	// Choose the first exe without the word "debug" in it
	for (int i = 0; i < dir.size(); i++) {
		string filename = dir.getName(i);
		if (filename.find("debug") == string::npos) {
			// Choose this file to be the representative
			return dir.getName(i);
		}
	}

	return "";
}

// -------------------------------------------------
string getThisAppVersion() {

	string name = getAppName();
	if (!name.empty()) {
		return getExeVersion(name);
	} 

	return "Error in finding exe";
}

// -------------------------------------------------

// -------------------------------------------------

// -------------------------------------------------

// -------------------------------------------------