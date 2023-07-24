#ifndef User_H
#define User_H
#include<iostream>
#include<string>
#include<Windows.h>
#include "songs.h"
#include<mciapi.h>
#include<fstream>
#include"Playlist.h"
#include"MusicPlayer.h"
using namespace std;
class User
{
	string Name;
	string UserId;
	songs song;
	Playlist *PL[4];
public:
	User();
	User(string, string);
	void InputFunc();
	void Display();
	void FolkPlaylist();
	void SadPlaylist();
	void OldPlaylist();
	void UserPlaylist();
	void setName(string);
	string getName();
	void setUserId(string);
	string getId();
	~User();
};

#endif // User_H !

#pragma once

