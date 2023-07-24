#pragma once
#include "Playlist.h"
using namespace std;
class FolkSongPlaylist :
    public Playlist
{
    int songCount;
public:
    FolkSongPlaylist();
    FolkSongPlaylist(string, string, songs &s);
    virtual void addSong(songs&) override;
    virtual void deleteSong(wstring) override;
    virtual wstring* ListOfSongs() override;
    virtual void readfile() override;
    int getNoOfSong() override;
};

