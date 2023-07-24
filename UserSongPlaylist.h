#pragma once
#include "Playlist.h"
class UserSongPlaylist :
    public Playlist
{
    int songCount;
public:
    UserSongPlaylist();
    UserSongPlaylist(string, string, songs&);
    virtual void addSong(songs&) override;
    virtual void deleteSong(wstring) override;
    virtual wstring* ListOfSongs() override;
    virtual void readfile() override;
    int getNoOfSong() override;
};

