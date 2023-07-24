#include "MusicPlayer.h"
#include <Windows.h>
#include "Playlist.h"
#include <iostream>
#include <string>
using namespace std;
void MusicPlayer::setPlaylistData(Playlist* s)
{
	Pl = s;
}
MusicPlayer::MusicPlayer()
{
	Pl->setPlaylistId("\0");
	Pl->setPlaylistName("\0");
	Commandstring = L"\0";
}
string MusicPlayer::status()
{
	LPWSTR buffL = new TCHAR[50];
	Commandstring = L"status " + Pl->ListOfSongs()[getUserSongIndex()] + L" mode";
	mciSendString(Commandstring.c_str(), buffL, 8, 0);
	string ret;
	char* buff = new char[50];
	size_t rets;
	wcstombs_s(&rets, buff, (size_t)50, buffL, (size_t)50);
	if (strncmp(buff, "open", 4) == 0) ret = "open";
	else if (strncmp(buff, "playing", 7) == 0) ret = "playing";
	else if (strncmp(buff, "paused", 6) == 0) ret = "paused";
	else if (strncmp(buff, "stopped", 7) == 0) ret = "stopped";
	else ret = "unknown";
	delete[] buff;
	delete[] buffL;
	return ret;
}
MusicPlayer::MusicPlayer(int x,string a_PlaylistName, string a_PlaylistId, songs s, Playlist* p)
{
	this->Pl = p;
	Pl->setPlaylistId(a_PlaylistId);
	Pl->setPlaylistName(a_PlaylistName);
	Pl->setSongData(s);
	setUserSongIndex(x);
}
MusicPlayer::~MusicPlayer()
{
}
void MusicPlayer::Open()
{	
	Commandstring = L"open " + Pl->ListOfSongs()[getUserSongIndex()];
	mciSendString(Commandstring.c_str(), NULL, 0, SND_SYNC);
}
void MusicPlayer::Play()
{
	Commandstring = L"play " + Pl->ListOfSongs()[getUserSongIndex()];
	mciSendString(Commandstring.c_str(), NULL, 0, SND_SYNC);
}
void MusicPlayer::Resume()
{
	Commandstring = L"resume " + Pl->ListOfSongs()[getUserSongIndex()];
	mciSendString(Commandstring.c_str(), NULL, 0, SND_SYNC);
}
void MusicPlayer::Pause()
{
	Commandstring = L"pause " + Pl->ListOfSongs()[getUserSongIndex()];
	mciSendString(Commandstring.c_str(), NULL, 0, SND_SYNC);
}
void MusicPlayer::Stop()
{
	Commandstring = L"stop " + Pl->ListOfSongs()[getUserSongIndex()];
	mciSendString(Commandstring.c_str(), NULL, 0, SND_SYNC);
}
int  MusicPlayer::getUserSongIndex()
{
	return UserSongIndex;
}
void  MusicPlayer::setUserSongIndex(int x)
{
	if (x < 0)
		UserSongIndex = 0;
	else
		UserSongIndex = x;
}