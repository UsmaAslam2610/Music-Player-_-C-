#ifndef Playlist_H
#define Playlist_H
#include<iostream>
#include<string>
#include<Windows.h>
#include "songs.h"
#include<mciapi.h>
#include<fstream>
using namespace std;
#pragma once
class Playlist
{
	string PlaylistName;
	string PlaylistId;
	songs* song;
	int NoOfSong;
public:
	virtual void readfile();
	Playlist();
	virtual int getNoOfSong();
	Playlist(string, string, songs&);
	~Playlist();
	virtual void setSongData(songs);
	virtual void addSong(songs&);
	bool findPlaylist(string);
	virtual void deleteSong(wstring);
	virtual wstring* ListOfSongs();
	void setPlaylistId(string a_userPlaylistId);
	string getPlaylistId() const;
	void setPlaylistName(string a_userPlaylistName);
	string getPlaylistName() const;
	bool addPlaylist();
	bool deletePlaylist(string);
};
#endif // !Playlist_H

