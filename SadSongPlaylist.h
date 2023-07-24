#pragma once
#include "Playlist.h"

using namespace std;
class SadSongPlaylist :
    public Playlist
{
    int songCount;
public:
    SadSongPlaylist();
     SadSongPlaylist(string, string, songs&);
     virtual void addSong(songs&) override;
     virtual void deleteSong(wstring) override;
     virtual wstring* ListOfSongs() override;
     virtual void readfile() override;
     int getNoOfSong() override;
};

