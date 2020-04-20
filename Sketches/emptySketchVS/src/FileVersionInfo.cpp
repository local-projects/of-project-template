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

#include "FileVersionInfo.h"

//-------------------------------------------------------------------
// FileVersionInfo
//-------------------------------------------------------------------

FileVersionInfo::FileVersionInfo()
{
	reset();
}


FileVersionInfo::~FileVersionInfo()
{}


bool FileVersionInfo::getTranslationId(LPVOID lpData, UINT unBlockSize, WORD wLangId, DWORD &dwId, bool bPrimaryEnough/*= FALSE*/)
{
	for (LPWORD lpwData = (LPWORD)lpData; (LPBYTE)lpwData < ((LPBYTE)lpData)+unBlockSize; lpwData+=2)
	{
		if (*lpwData == wLangId)
		{
			dwId = *((DWORD*)lpwData);
			return TRUE;
		}
	}

	if (!bPrimaryEnough)
		return FALSE;

	for (LPWORD lpwData = (LPWORD)lpData; (LPBYTE)lpwData < ((LPBYTE)lpData)+unBlockSize; lpwData+=2)
	{
		if (((*lpwData)&0x00FF) == (wLangId&0x00FF))
		{
			dwId = *((DWORD*)lpwData);
			return TRUE;
		}
	}

	return FALSE;
}


bool FileVersionInfo::create(HMODULE hModule /*= NULL*/)
{
	CString	strPath; 
	GetModuleFileName(hModule, strPath.GetBuffer(_MAX_PATH), _MAX_PATH);
	strPath.ReleaseBuffer();
	return create(strPath);
}

bool FileVersionInfo::create(std::string strFileName) {

	return create(CA2W(strFileName.c_str()));
}

bool FileVersionInfo::create(LPCTSTR lpszFileName)
{
	reset();

	DWORD	dwHandle;
	DWORD	dwFileVersionInfoSize = GetFileVersionInfoSize((LPTSTR)lpszFileName, &dwHandle);
	if (!dwFileVersionInfoSize)
		return FALSE;

	LPVOID	lpData = (LPVOID)new BYTE[dwFileVersionInfoSize];
	if (!lpData)
		return FALSE;

	try
	{
		if (!GetFileVersionInfo((LPTSTR)lpszFileName, dwHandle, dwFileVersionInfoSize, lpData))
			throw FALSE;

		// catch default information
		LPVOID	lpInfo;
		UINT		unInfoLen;
		if (VerQueryValue(lpData, _T("\\"), &lpInfo, &unInfoLen))
		{
			assert(unInfoLen == sizeof(m_FileInfo));
			if (unInfoLen == sizeof(m_FileInfo))
				memcpy(&m_FileInfo, lpInfo, unInfoLen);
		}

		// find best matching language and codepage
		VerQueryValue(lpData, _T("\\VarFileInfo\\Translation"), &lpInfo, &unInfoLen);
		
		DWORD	dwLangCode = 0;
		if (!getTranslationId(lpInfo, unInfoLen, GetUserDefaultLangID(), dwLangCode, FALSE))
		{
			if (!getTranslationId(lpInfo, unInfoLen, GetUserDefaultLangID(), dwLangCode, TRUE))
			{
				if (!getTranslationId(lpInfo, unInfoLen, MAKELANGID(LANG_NEUTRAL, SUBLANG_NEUTRAL), dwLangCode, TRUE))
				{
					if (!getTranslationId(lpInfo, unInfoLen, MAKELANGID(LANG_ENGLISH, SUBLANG_NEUTRAL), dwLangCode, TRUE))
						// use the first one we can get
						dwLangCode = *((DWORD*)lpInfo);
				}
			}
		}
		

		CString	strSubBlock;
		strSubBlock.Format(_T("\\StringFileInfo\\%04X%04X\\"), dwLangCode&0x0000FFFF, (dwLangCode&0xFFFF0000)>>16);
		
		// catch string table
		if (VerQueryValue(lpData, (LPTSTR)(LPCTSTR)(strSubBlock + _T("CompanyName")), &lpInfo, &unInfoLen))
			_companyName = CW2A((LPCTSTR)lpInfo);
		if (VerQueryValue(lpData, (LPTSTR)(LPCTSTR)(strSubBlock+_T("FileDescription")), &lpInfo, &unInfoLen))
			_fileDescription = CW2A((LPCTSTR)lpInfo);
		if (VerQueryValue(lpData, (LPTSTR)(LPCTSTR)(strSubBlock+_T("FileVersion")), &lpInfo, &unInfoLen))
			_fileVersion = CW2A((LPCTSTR)lpInfo);
		if (VerQueryValue(lpData, (LPTSTR)(LPCTSTR)(strSubBlock+_T("InternalName")), &lpInfo, &unInfoLen))
			_internalName = CW2A((LPCTSTR)lpInfo);
		if (VerQueryValue(lpData, (LPTSTR)(LPCTSTR)(strSubBlock+_T("LegalCopyright")), &lpInfo, &unInfoLen))
			_legalCopyright = CW2A((LPCTSTR)lpInfo);
		if (VerQueryValue(lpData, (LPTSTR)(LPCTSTR)(strSubBlock+_T("OriginalFileName")), &lpInfo, &unInfoLen))
			_originalFileName = CW2A((LPCTSTR)lpInfo);
		if (VerQueryValue(lpData, (LPTSTR)(LPCTSTR)(strSubBlock+_T("ProductName")), &lpInfo, &unInfoLen))
			_productName = CW2A((LPCTSTR)lpInfo);
		if (VerQueryValue(lpData, (LPTSTR)(LPCTSTR)(strSubBlock+_T("ProductVersion")), &lpInfo, &unInfoLen))
			_productVersion = CW2A((LPCTSTR)lpInfo);
		if (VerQueryValue(lpData, (LPTSTR)(LPCTSTR)(strSubBlock+_T("Comments")), &lpInfo, &unInfoLen))
			_comments = CW2A((LPCTSTR)lpInfo);
		if (VerQueryValue(lpData, (LPTSTR)(LPCTSTR)(strSubBlock+_T("LegalTrademarks")), &lpInfo, &unInfoLen))
			_legalTrademarks = CW2A((LPCTSTR)lpInfo);
		if (VerQueryValue(lpData, (LPTSTR)(LPCTSTR)(strSubBlock+_T("PrivateBuild")), &lpInfo, &unInfoLen))
			_privateBuild = CW2A((LPCTSTR)lpInfo);
		if (VerQueryValue(lpData, (LPTSTR)(LPCTSTR)(strSubBlock+_T("SpecialBuild")), &lpInfo, &unInfoLen))
			_specialBuild = CW2A((LPCTSTR)lpInfo);

		delete[] lpData;
	}
	catch (bool)
	{
		delete[] lpData;
		return FALSE;
	}

	return TRUE;
}


WORD FileVersionInfo::getFileVersion(int nIndex) const
{
	if (nIndex == 0)
		return (WORD)(m_FileInfo.dwFileVersionLS & 0x0000FFFF);
	else if (nIndex == 1)
		return (WORD)((m_FileInfo.dwFileVersionLS & 0xFFFF0000) >> 16);
	else if (nIndex == 2)
		return (WORD)(m_FileInfo.dwFileVersionMS & 0x0000FFFF);
	else if (nIndex == 3)
		return (WORD)((m_FileInfo.dwFileVersionMS & 0xFFFF0000) >> 16);
	else
		return 0;
}


WORD FileVersionInfo::getProductVersion(int nIndex) const
{
	if (nIndex == 0)
		return (WORD)(m_FileInfo.dwProductVersionLS & 0x0000FFFF);
	else if (nIndex == 1)
		return (WORD)((m_FileInfo.dwProductVersionLS & 0xFFFF0000) >> 16);
	else if (nIndex == 2)
		return (WORD)(m_FileInfo.dwProductVersionMS & 0x0000FFFF);
	else if (nIndex == 3)
		return (WORD)((m_FileInfo.dwProductVersionMS & 0xFFFF0000) >> 16);
	else
		return 0;
}


DWORD FileVersionInfo::getFileFlagsMask() const
{
	return m_FileInfo.dwFileFlagsMask;
}


DWORD FileVersionInfo::getFileFlags() const
{
	return m_FileInfo.dwFileFlags;
}


DWORD FileVersionInfo::getFileOs() const
{
	return m_FileInfo.dwFileOS;
}


DWORD FileVersionInfo::getFileType() const
{
	return m_FileInfo.dwFileType;
}


DWORD FileVersionInfo::getFileSubtype() const
{
	return m_FileInfo.dwFileSubtype;
}


CTime FileVersionInfo::getFileDate() const
{
	FILETIME	ft;
	ft.dwLowDateTime = m_FileInfo.dwFileDateLS;
	ft.dwHighDateTime = m_FileInfo.dwFileDateMS;
	return CTime(ft);
}


std::string FileVersionInfo::companyName() const
{
	return _companyName;
}


std::string FileVersionInfo::fileDescription() const
{
	return _fileDescription;
}


std::string FileVersionInfo::fileVersion() const
{
	return _fileVersion;
}


std::string FileVersionInfo::internalName() const
{
	return _internalName;
}


std::string FileVersionInfo::legalCopyright() const
{
	return _legalCopyright;
}


std::string FileVersionInfo::originalFileName() const
{
	return _originalFileName;
}


std::string FileVersionInfo::productName() const
{
	return _productName;
}


std::string FileVersionInfo::productVersion() const
{
	return _productVersion;
}


std::string FileVersionInfo::comments() const
{
	return _comments;
}


std::string FileVersionInfo::legalTrademarks() const
{
	return _legalTrademarks;
}


std::string FileVersionInfo::privateBuild() const
{
	return _privateBuild;
}


std::string FileVersionInfo::specialBuild() const
{
	return _specialBuild;
}


void FileVersionInfo::reset()
{
	ZeroMemory(&m_FileInfo, sizeof(m_FileInfo));
	_companyName.clear();
	_fileDescription.clear();
	_fileVersion.clear();
	_internalName.clear();
	_legalCopyright.clear();
	_originalFileName.clear();
	_productName.clear();
	_productVersion.clear();
	_comments.clear();
	_legalTrademarks.clear();
	_privateBuild.clear();
	_specialBuild.clear();
}

std::string FileVersionInfo::jsonInfo() {

	std::string out;
	out = "{";
	out += "\"Company Name\":\""+_companyName+"\"";
	out += ",\"File Description\":\"" + _fileDescription + "\"";
	out += ",\"File Version\":\"" + _fileVersion + "\"";
	out += ",\"Internal Name\":\"" + _internalName + "\"";
	out += ",\"Legal Copyright\":\"" + _legalCopyright + "\"";
	out += ",\"Original File Name\":\"" + _originalFileName + "\"";
	out += ",\"Product Name\":\"" + _productName + "\"";
	out += ",\"Product Version\":\"" + _productVersion + "\"";
	out += ",\"Comments\":\"" + _comments + "\"";
	out += ",\"Legal Trademarks\":\"" + _legalTrademarks + "\"";
	out += ",\"Private Build\":\"" + _privateBuild + "\"";
	out += ",\"Special Build\":\"" + _specialBuild + "\"";
	out += "}";
	return out;
}

