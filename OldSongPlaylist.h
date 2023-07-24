#pragma once
#include "Playlist.h"
using namespace std;
class OldSongPlaylist :
    public Playlist
{
    int songCount;
public: 
    OldSongPlaylist();
    OldSongPlaylist(string, string, songs&);
    virtual void addSong(songs&) override;
    virtual void deleteSong(wstring) override;
    virtual wstring* ListOfSongs() override;
    virtual void readfile() override;
    int getNoOfSong() override;
};

