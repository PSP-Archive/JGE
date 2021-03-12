//-------------------------------------------------------------------------------------
//
// JGE++ is a hardware accelerated 2D game SDK for PSP/Windows.
//
// Licensed under the BSD license, see LICENSE in JGE root for details.
// 
// Copyright (c) 2007 James Hui (a.k.a. Dr.Watson) <jhkhui@gmail.com>
// 
//-------------------------------------------------------------------------------------

#ifndef _FILE_SYSTEM_H_
#define _FILE_SYSTEM_H_

#include <stdio.h>
#include <vector>
#include <map>
#include <string>

#ifdef WIN32

#else
	#include <pspiofilemgr.h>
	#include <pspiofilemgr_fcntl.h>
#endif

#include "unzip/unzip.h"

using namespace std;

enum FileSystemActiveMode
{
	eNormal=0,
	eZip,
	eMpk
};

#define TILESIZE 64
struct tile
{
	char path[TILESIZE-8];
	int  size;
	long pos;
};

//////////////////////////////////////////////////////////////////////////
/// Interface for low level file access with ZIP archive support. All
/// file operations in JGE are handled through this class so if a ZIP
/// archive is attached, all the resources will be loaded from the
/// archive file.
///
//////////////////////////////////////////////////////////////////////////

class JFileSystem
{
public:

	//////////////////////////////////////////////////////////////////////////
	/// Get the singleton instance
	///
	//////////////////////////////////////////////////////////////////////////
	static JFileSystem* GetInstance();

	static void Destroy();

	
	//////////////////////////////////////////////////////////////////////////
	/// Attach ZIP archive to the file system.
	///
	/// @param zipfile - Name of ZIP archive.
	/// @param password - Password for the ZIP archive. Default is NULL.
	/// 
	/// @return Status of the attach operation.
	/// 
	//////////////////////////////////////////////////////////////////////////
	bool AttachZipFile(const string &zipfile, char *password = NULL);

	//////////////////////////////////////////////////////////////////////////
	/// Release the attached ZIP archive.
	/// 
	//////////////////////////////////////////////////////////////////////////
	void DetachZipFile();

	//////////////////////////////////////////////////////////////////////////
	/// Attach MPK archive to the file system.
	///
	/// @param hbrfile -  Name of hbr file archive.
	/// @param listfile - Name of list file archive.
	/// 
	/// @return Status of the attach operation.
	/// 
	//////////////////////////////////////////////////////////////////////////
	bool AttachMpkFile(const string &hbrfile, const string &listfile);

	//////////////////////////////////////////////////////////////////////////
	/// Release the attached MPK archive.
	/// 
	//////////////////////////////////////////////////////////////////////////
	void DetachMpkFile();
	
	//////////////////////////////////////////////////////////////////////////
	/// Open file for reading.
	/// 
	//////////////////////////////////////////////////////////////////////////
	bool OpenFile(const string &filename);

	//////////////////////////////////////////////////////////////////////////
	/// Read data from file.
	/// 
	/// @param buffer - Buffer for reading.
	/// @param size - Number of bytes to read.
	/// 
	/// @return Number of bytes read.
	/// 
	//////////////////////////////////////////////////////////////////////////
	int ReadFile(void *buffer, int size);

	//////////////////////////////////////////////////////////////////////////
	/// Get size of file.
	/// 
	//////////////////////////////////////////////////////////////////////////
	int GetFileSize();

	//////////////////////////////////////////////////////////////////////////
	/// Close file.
	/// 
	//////////////////////////////////////////////////////////////////////////
	void CloseFile();
	void CloseZipFile();
	void CloseMpkFile();

	//////////////////////////////////////////////////////////////////////////
	/// Set root for all the following file operations
	/// 
	/// @resourceRoot - New root.
	/// 
	//////////////////////////////////////////////////////////////////////////
	void SetResourceRoot(const string& resourceRoot);

protected:
	JFileSystem();
	~JFileSystem();

private:
	static JFileSystem* mInstance;

	string mResourceRoot;
	string mZipFileName;
	char *mPassword;
	string mHbrFileName;
	string mListFileName;
	//bool mZipAvailable;
	FileSystemActiveMode mActiveMode;
#ifdef WIN32
	FILE *mFile;
	FILE *mMpkHbrFile;
	FILE *mMpkListFile;
#else
	SceUID mFile;
	SceUID mMpkHbrFile;
	SceUID mMpkListFile;
#endif
	unzFile mZipFile;
	int mFileSize;

#ifdef WIN32
	bool GetMid(long &start, long &end, long &mid);
	bool gettile(long s, long e, FILE* fp, tile &t);
	bool findtile(tile &t);
	FILE* getfilepointer(const char * filename, int &size);
#else
	bool GetMid(long &start, long &end, long &mid);
	bool gettile(long s, long e, SceUID fp, tile &t);
	bool findtile(tile &t);
	SceUID getfilepointer(const char * filename, int &size);
#endif

};

#endif
