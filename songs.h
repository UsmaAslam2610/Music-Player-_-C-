#ifndef songs_H
#define songs_H
#include<iostream>
#include<string>
#include<Windows.h>
#include<mciapi.h>
using namespace std;
class songs
{
	wstring path;
	string songId;
	char genre;
public:
	songs();
	songs(wstring, string,char);
	songs(const songs&);
	~songs();
	void setPath(wstring);
	wstring getPath() const;
	void setSongId(string);
	string getSongId() const;
	void setGenre(char);
	char getGenre() const;
};
#endif // !songs_H
#pragma once

