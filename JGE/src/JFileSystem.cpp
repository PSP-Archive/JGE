//-------------------------------------------------------------------------------------
//
// JGE++ is a hardware accelerated 2D game SDK for PSP/Windows.
//
// Licensed under the BSD license, see LICENSE in JGE root for details.
// 
// Copyright (c) 2007 James Hui (a.k.a. Dr.Watson) <jhkhui@gmail.com>
// 
//-------------------------------------------------------------------------------------

#pragma warning(disable : 4786)

#include "../include/JGE.h"
#include "../include/JFileSystem.h"
#include "tinyxml/tinyxml.h"
#include "unzip/unzip.h"

#include <stdio.h>
#include <vector>
#include <map>
#include <string>

JFileSystem* JFileSystem::mInstance = NULL;

JFileSystem* JFileSystem::GetInstance()
{
	if (mInstance == NULL)
	{
		mInstance = new JFileSystem();
	}

	return mInstance;
}


void JFileSystem::Destroy()
{
	if (mInstance)
	{
		delete mInstance;
		mInstance = NULL;
	}
}


JFileSystem::JFileSystem()
{
	mActiveMode = eNormal;
#ifdef WIN32
	mFile = NULL;
	mMpkHbrFile = NULL;
	mMpkListFile = NULL;
#else
	mFile = -1;
	mMpkHbrFile = -1;
	mMpkListFile = -1;
#endif
	mPassword = NULL;
	mZipFile = NULL;
	mFileSize = 0;

	mResourceRoot = "Res/";				// default root folder 
}


JFileSystem::~JFileSystem()
{
	CloseFile();
	CloseZipFile();
	CloseMpkFile();
}


bool JFileSystem::AttachZipFile(const string &zipfile, char *password /* = NULL */)
{
	CloseFile();
	CloseZipFile();
	CloseMpkFile();
	mActiveMode = eNormal;
	
	mZipFileName = zipfile;
	mPassword = password;

	mZipFile = unzOpen(mZipFileName.c_str());

	if (mZipFile != NULL)
	{
		mActiveMode = eZip;
		return true;
	}

	return false;
}


void JFileSystem::DetachZipFile()
{
	if (mActiveMode!=eZip)
		return;

	CloseZipFile();
	mActiveMode = eNormal;
}

bool JFileSystem::AttachMpkFile( const string &hbrfile, const string &listfile )
{
	CloseFile();
	CloseZipFile();
	CloseMpkFile();
	mActiveMode = eNormal;

	mHbrFileName = hbrfile;
	mListFileName = listfile;

	string path = mResourceRoot + mHbrFileName;
#ifdef WIN32
	mMpkHbrFile = fopen(path.c_str(), "rb");
	path = mResourceRoot + mListFileName;
	mMpkListFile = fopen(path.c_str(), "rb");
	if(mMpkHbrFile!=NULL && mMpkListFile!=NULL)
	{
		mActiveMode=eMpk;
		return true;
	}
#else
	mMpkHbrFile = sceIoOpen(path.c_str(), PSP_O_RDONLY, 0777);
	path = mResourceRoot + mListFileName;
	mMpkListFile = sceIoOpen(path.c_str(), PSP_O_RDONLY, 0777);
	if(mMpkHbrFile > 0 && mMpkListFile > 0)
	{
		mActiveMode=eMpk;
		return true;
	}
#endif

	return false;
}

void JFileSystem::DetachMpkFile()
{
	if (mActiveMode!=eMpk)
		return;

	CloseMpkFile();
	mActiveMode = eNormal;
}


bool JFileSystem::OpenFile(const string &filename)
{
	string path = mResourceRoot + filename;

	switch(mActiveMode)
	{
	case eNormal:
		{
#ifdef WIN32
			mFile = fopen(path.c_str(), "rb");
			if (mFile != NULL)
			{
				fseek(mFile, 0, SEEK_END);
				mFileSize = ftell(mFile);
				fseek(mFile, 0, SEEK_SET);
				return true;
			}
			break;
#else
			mFile = sceIoOpen(path.c_str(), PSP_O_RDONLY, 0777);
			if (mFile > 0)
			{
				mFileSize = sceIoLseek(mFile, 0, PSP_SEEK_END);
				sceIoLseek(mFile, 0, PSP_SEEK_SET);
				return true;
			}
			break;
#endif	
		}
	case eZip:
		{
			if (unzLocateFile(mZipFile, path.c_str(), 0) != UNZ_OK)
				return false;

			char filenameInzip[256];
			unz_file_info fileInfo;

			if (unzGetCurrentFileInfo(mZipFile, &fileInfo, filenameInzip, sizeof(filenameInzip), NULL, 0, NULL, 0) == UNZ_OK)
				mFileSize = fileInfo.uncompressed_size;
			else
				mFileSize = 0;

			return (unzOpenCurrentFilePassword(mZipFile, mPassword) == UNZ_OK);
		}
	case eMpk:
		{
			mFile = getfilepointer(filename.c_str(),mFileSize);
#ifdef WIN32
			if(mFile != NULL)
				return true;
#else
			if(mFile > 0)
				return true;
#endif
			break;
		}
	default:
		break;
	}
	return false;

	//--------------------------------------------
/*
	if (mZipAvailable && mZipFile != NULL)
	{
		if (unzLocateFile(mZipFile, path.c_str(), 0) != UNZ_OK)
			return false;

		char filenameInzip[256];
		unz_file_info fileInfo;

		if (unzGetCurrentFileInfo(mZipFile, &fileInfo, filenameInzip, sizeof(filenameInzip), NULL, 0, NULL, 0) == UNZ_OK)
			mFileSize = fileInfo.uncompressed_size;
		else
			mFileSize = 0;

		return (unzOpenCurrentFilePassword(mZipFile, mPassword) == UNZ_OK);
	}
	else
	{
		#ifdef WIN32
			mFile = fopen(path.c_str(), "rb");
			if (mFile != NULL)
			{
				fseek(mFile, 0, SEEK_END);
				mFileSize = ftell(mFile);
				fseek(mFile, 0, SEEK_SET);
				return true;
			}
		#else
			mFile = sceIoOpen(path.c_str(), PSP_O_RDONLY, 0777);
			if (mFile > 0)
			{
				mFileSize = sceIoLseek(mFile, 0, PSP_SEEK_END);
				sceIoLseek(mFile, 0, PSP_SEEK_SET);
				return true;
			}
		#endif					
	}
	return false;*/		
}

int JFileSystem::ReadFile(void *buffer, int size)
{
	if (mActiveMode == eZip)
	{
		return unzReadCurrentFile(mZipFile, buffer, size);
	}
	else
	{
		#ifdef WIN32
			return fread(buffer, 1, size, mFile);
		#else
			return sceIoRead(mFile, buffer, size);
		#endif
	}
}


int JFileSystem::GetFileSize()
{
	return mFileSize;
}


void JFileSystem::SetResourceRoot(const string& resourceRoot)
{
	mResourceRoot = resourceRoot;
}

void JFileSystem::CloseFile()
{
#ifdef WIN32
	if(mFile != NULL)
	{
		fclose(mFile);
		mFile = NULL;
	}
#else
	if (mFile > 0)
	{
		sceIoClose(mFile);
		mFile = -1;
	}
#endif
}

void JFileSystem::CloseZipFile()
{
	if (mZipFile != NULL)
	{
		unzCloseCurrentFile(mZipFile);
		mZipFile=NULL;
	}
}

void JFileSystem::CloseMpkFile()
{
#ifdef WIN32
	if(mMpkHbrFile != NULL)
	{
		fclose(mMpkHbrFile);
		mMpkHbrFile = NULL;
	}

	if(mMpkListFile != NULL)
	{
		fclose(mMpkListFile);
		mMpkListFile = NULL;
	}

#else
	if (mMpkHbrFile > 0)
	{
		sceIoClose(mMpkHbrFile);
		mMpkHbrFile = -1;
	}

	if (mMpkListFile > 0)
	{
		sceIoClose(mMpkListFile);
		mMpkListFile = -1;
	}
#endif
}

bool JFileSystem::GetMid(long &start, long &end, long &mid)
{
	if(end < start)
		return false;//error
	if(end==start)
	{
		mid = start;
		return true;//
	}
	if(end==start+1)
	{
		mid = start;
		return true;
	}
	if(end > start+1)
	{
		mid=start + (end-start)/2;
		return true;
	}
	return false;
}
#ifdef WIN32
bool JFileSystem::gettile(long s, long e, FILE* fp, tile &t)
{
	long m;
	if(GetMid(s,e,m))
	{
		fseek(fp,m*TILESIZE,SEEK_SET);
		char buf[TILESIZE];
		memset(buf,0,TILESIZE);
		fread(buf, 1, TILESIZE, fp);
		tile *pt = (tile *)buf;
		int cmp = stricmp(pt->path,t.path);
		if(cmp==0)
		{
			t.size = pt->size;
			t.pos = pt->pos;
			return true;
		}
		else if(cmp<0)
		{
			return gettile(m+1,e,fp,t);
		}
		else if(cmp>0)
		{
			return gettile(s,m-1,fp,t);
		}
		else
			return false;
	}
	return false;
}
bool JFileSystem::findtile(tile &t)
{
	FILE *fp = mMpkListFile;
	if(fp==NULL)
		return false;

	fseek(fp,0L,SEEK_END);
	long pos = ftell(fp);
	long fullnum = (pos+1)/(TILESIZE);

	long startPos=0;
	long endPos = fullnum-1;
	if(gettile(startPos,endPos,fp,t))
	{
		//printf("Finded %s\n",t.path);
		//fclose(fp);
		return true;
	}

	//printf("Can't find %s\n",t.path);
	//fclose(fp);
	return false;
}

FILE* JFileSystem::getfilepointer(const char * filename, int &size)
{
	tile t;
	strcpy(t.path,filename);
	if(findtile(t))
	{
		FILE* fp=mMpkHbrFile;
		if(fp==NULL)
			return NULL;
		fseek(fp,t.pos,SEEK_SET);
		size = t.size;
		return fp;
	}
	return NULL;
}
#else
bool JFileSystem::gettile(long s, long e, SceUID fp, tile &t)
{
	long m;
	if(GetMid(s,e,m))
	{
		sceIoLseek(fp, m*TILESIZE, PSP_SEEK_SET);
		char buf[TILESIZE];
		memset(buf,0,TILESIZE);
		sceIoRead(fp, buf, TILESIZE);
		tile *pt = (tile *)buf;
		int cmp = stricmp(pt->path,t.path);
		if(cmp==0)
		{
			t.size = pt->size;
			t.pos = pt->pos;
			return true;
		}
		else if(cmp<0)
		{
			return gettile(m+1,e,fp,t);
		}
		else if(cmp>0)
		{
			return gettile(s,m-1,fp,t);
		}
		else
			return false;
	}
	return false;
}
bool JFileSystem::findtile(tile &t)
{
	SceUID fp = mMpkListFile;
	if(fp < 0)
		return false;

	long pos = sceIoLseek(fp, 0, PSP_SEEK_END);

	//long pos = ftell(fp);
	//long pos = ftell(fp);
	long fullnum = (pos+1)/(TILESIZE);

	long startPos=0;
	long endPos = fullnum-1;
	if(gettile(startPos,endPos,fp,t))
	{
		//printf("Finded %s\n",t.path);
		//fclose(fp);
		return true;
	}

	//printf("Can't find %s\n",t.path);
	//fclose(fp);
	return false;
}

SceUID JFileSystem::getfilepointer(const char * filename, int &size)
{
	tile t;
	strcpy(t.path,filename);
	if(findtile(t))
	{
		SceUID fp=mMpkHbrFile;
		if(fp < 0)
			return -1;
		sceIoLseek(fp,t.pos,PSP_SEEK_SET);
		size = t.size;
		return fp;
	}
	return NULL;
}
#endif

