#include"UserSongPlaylist.h"
UserSongPlaylist::UserSongPlaylist(string name, string id, songs& s)
{
	setPlaylistName(name);
	setPlaylistId(id);
	setSongData(s);
}
UserSongPlaylist::UserSongPlaylist()
{
	setPlaylistName("\0");
	setPlaylistId("\0");
}
void UserSongPlaylist::readfile()
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
			songCount++;
		}
	}
	file.close();
}
void UserSongPlaylist::addSong(songs& ss)
{
	setSongData(ss);
	wofstream ofs;
	ofs.open(getPlaylistName(), ios::app);
	ofs << ss.getPath() << endl;
	songCount++;
	ofs.close();
}
void UserSongPlaylist::deleteSong(wstring a_path)
{
	wstring record;
	int count = 0;
	wifstream myPlaylist(getPlaylistName());
	wofstream temp;
	temp.open("temp.txt");
	while (getline(myPlaylist, record)) {
		if (record != a_path)
			temp << record << endl;
		else if (record == a_path)
		{
			count++;
			songCount--;
		}
	}
	myPlaylist.close();
	temp.close();
	remove(getPlaylistName().c_str());
	rename("temp.txt", getPlaylistName().c_str());
}
wstring* UserSongPlaylist::ListOfSongs()
{
	wifstream file(getPlaylistName(), ios::in);
	wstring* arr = new wstring[getNoOfSong()];
	for (int i = 0; i < getNoOfSong(); i++)
	{
		getline(file, arr[i]);
	}
	file.close();
	return arr;
}
int UserSongPlaylist::getNoOfSong()
{
	return songCount;
}