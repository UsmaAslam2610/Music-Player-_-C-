#include "Playlist.h"
#include "songs.h"
#include<iostream>
#include<string>
#include<Windows.h>
#include<mciapi.h>
#include<fstream>
#include<cstdio>
using namespace std;
void Playlist::readfile()
{
	wifstream file(getPlaylistName());
	wstring abc;
	if (!file.is_open())
		cout << "?? File not found.";
	while (!file.eof())
	{
		getline(file, abc);
		if (abc != L"\0")
		{
			NoOfSong++;
		}
	}
	file.close();
}
int Playlist::getNoOfSong()
{
	return NoOfSong;
}
Playlist::Playlist()
{
	PlaylistName = "\0";
	PlaylistId = "\0";
	NoOfSong = 0;
}
bool Playlist::findPlaylist(string PlName)
{
	wifstream inPlaylist(PlName);
	if (!inPlaylist)
		return false;
	else
		return true;
}
Playlist::Playlist(string a_PlaylistName, string a_PlaylistId, songs& s)
{
	setPlaylistName(a_PlaylistName);
	setSongData(s);
	setPlaylistId(a_PlaylistId);
	if (findPlaylist(getPlaylistName()))
	{
		readfile();
		NoOfSong = getNoOfSong();
	}
	else
	{
		addPlaylist();
		addSong(s);
		readfile();
		NoOfSong = getNoOfSong();
	}
}
Playlist::~Playlist()
{
	PlaylistName = "\0";
	PlaylistId = "\0";
}
void Playlist::setSongData(songs ss)
{
	song = &ss;
}
void Playlist::addSong(songs& ss)
{
	setSongData(ss);
	wofstream ofs;
	ofs.open(getPlaylistName(), ios::app);
	ofs << song->getPath()<< endl;
	NoOfSong++;
	ofs.close();
}
void Playlist::deleteSong(wstring a_path)
{
	wstring record;
	//int count = 0;
	wifstream myPlaylist(getPlaylistName());
	wofstream temp;
	temp.open("temp.txt");
	while (getline(myPlaylist, record)) {
		if (record != a_path)
			temp << record << endl;
		else if(record == a_path)
		{
			//count++;
			NoOfSong--;
		}
	}
	myPlaylist.close();
	temp.close();
	remove(getPlaylistName().c_str());
	rename("temp.txt", getPlaylistName().c_str());
}
wstring* Playlist::ListOfSongs()
{
	wifstream file(getPlaylistName(), ios::in);
	wstring* arr = new wstring[getNoOfSong()];
	for (int i = 0; i < getNoOfSong() ; i++)
	{
		getline(file, arr[i]);
	}
	file.close();
	return arr;
}
void Playlist::setPlaylistId(string a_PlaylistId)
{
	PlaylistId = a_PlaylistId;
}
string Playlist::getPlaylistId() const
{
	return PlaylistId;
}
void Playlist::setPlaylistName(string a_PlaylistName)
{
	PlaylistName = a_PlaylistName + ".txt";
}
string Playlist::getPlaylistName() const
{
	return PlaylistName;
}
bool Playlist::addPlaylist()
{
	wofstream file;
	file.open(getPlaylistName());
	if (!file)
		return true;
	else
		return false;
}
bool Playlist::deletePlaylist(string file)
{
	bool flag = true;
	if (file == "FolkSongPlaylist.txt" || file == "SadSongPlaylist.txt" || file == "OldSongPlaylist.txt")
	{
		return false;
	}
	else
	{
		if (remove(file.c_str()) != 0)
		flag = false;
	else
		flag = true;
	return flag;
	}
}