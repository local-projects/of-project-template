/********************************************************************
*
* Copyright (C) 1999-2000 Sven Wiegand
* Copyright (C) 2000-2001 ToolsCenter
* 
* This file is free software; you can redistribute it and/or
* modify, but leave the headers intact and do not remove any 
* copyrights from the source.
*
* If you have further questions, suggestions or bug fixes, visit 
* our homepage
*
*    http://www.ToolsCenter.org
*
********************************************************************/

// Modified by Ben Snell (2020) for ease of use

#if !defined(FILE_VERSION_INFO)
#define FILE_VERSION_INFO

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <atltime.h>
#include <cassert>
#include <string>

class FileVersionInfo
{
// construction/destruction
public:
	FileVersionInfo();
	virtual ~FileVersionInfo();

// operations
public:
	bool create(HMODULE hModule = NULL);
	bool create(LPCTSTR lpszFileName);
	bool create(std::string strFileName);

// attribute operations
public:
	WORD getFileVersion(int nIndex) const;
	WORD getProductVersion(int nIndex) const;
	DWORD getFileFlagsMask() const;
	DWORD getFileFlags() const;
	DWORD getFileOs() const;
	DWORD getFileType() const;
	DWORD getFileSubtype() const;
	CTime getFileDate() const;

	std::string companyName() const;
	std::string fileDescription() const;
	std::string fileVersion() const;
	std::string internalName() const;
	std::string legalCopyright() const;
	std::string originalFileName() const;
	std::string productName() const;
	std::string productVersion() const;
	std::string comments() const;
	std::string legalTrademarks() const;
	std::string privateBuild() const;
	std::string specialBuild() const;

	// Get all information in a string json format
	std::string jsonInfo();

// implementation helpers
protected:
	virtual void reset();
	bool getTranslationId(LPVOID lpData, UINT unBlockSize, WORD wLangId, DWORD &dwId, bool bPrimaryEnough = FALSE);

// attributes
private:
	VS_FIXEDFILEINFO m_FileInfo;
	
	std::string _companyName;
	std::string _fileDescription;
	std::string _fileVersion;
	std::string _internalName;
	std::string _legalCopyright;
	std::string _originalFileName;
	std::string _productName;
	std::string _productVersion;
	std::string _comments;
	std::string _legalTrademarks;
	std::string _privateBuild;
	std::string _specialBuild;

};

#endif // !defined(FILE_VERSION_INFO)
