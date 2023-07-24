#ifndef MusicPlayer_H
#define MusicPlayer_H
#include<iostream>
#include<string>
#include<Windows.h>
#include "songs.h"
#include<mciapi.h>
#include<fstream>
using namespace std;
#include"Playlist.h"
class MusicPlayer
{
	Playlist* Pl;
	wstring Commandstring;
	int UserSongIndex;
public:
	MusicPlayer();
	MusicPlayer(int, string, string, songs, Playlist*);
	~MusicPlayer();
	void setPlaylistData(Playlist*);
	void Open();
	void Play();
	void Resume();
	void Pause();
	void Stop();
	string status();
	int getUserSongIndex();
	void setUserSongIndex(int);
};
#endif // MusicPlayer_H !
#pragma once