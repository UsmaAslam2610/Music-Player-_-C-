#include "songs.h"
#include<iostream>
#include<string>
#include<Windows.h>
#include<mciapi.h>
using namespace std;
songs::songs()
{
	setPath(L"\0");
	setSongId("\0");
	setGenre('\0');
}
songs::songs(wstring a_path, string a_songId, char a_genre)
{
	setPath(a_path);
	setSongId(a_songId);
	setGenre(a_genre);
}
songs::songs(const songs& a)
{
	setPath(a.path);
	setSongId(a.songId);
	setGenre(a.genre);
}
songs::~songs()
{
	path = L"\0";
	songId = "\0";
	genre = '\0';
}
void songs::setPath(wstring a_path)
{
	path = a_path;
}
wstring songs::getPath() const
{
	return path;
}
void songs::setSongId(string a_songId)
{
	songId = a_songId;
}
string songs::getSongId() const
{
	return songId;
}
void songs::setGenre(char a_genre)
{
	genre = a_genre;
}
char songs::getGenre() const
{
	return genre;
}