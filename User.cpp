#include <iostream>
#include "User.h"
#include"OldSongPlaylist.h"
#include"FolkSongPlaylist.h"
#include"SadSongPlaylist.h"
#include"UserSongPlaylist.h"
#include<conio.h>
#include"songs.h"
#include<string>
using namespace std;
User::User()
{
	song.setPath(L"\0");
	song.setGenre('\0');
	song.setSongId("000");
	PL[0] = new FolkSongPlaylist();
	PL[1] = new SadSongPlaylist();
	PL[2] = new OldSongPlaylist();
	setName("\0");
	setUserId("\0");
}
User::User(string a_name, string a_Id)
{
	setName(a_name);
	setUserId(a_Id);
}
void User::InputFunc()
{
	char ch;
	int choice;
	do {

		cout << endl;
		cout << "  \toooo  oooo oo  oo ooooooo oo oooooo     oooooo oo      ooooooo oo    oo ooooooo ooooooo ";
		cout << "\n\too  ooo oo oo  oo oo      oo oo         oo   o oo      oo   oo  oo  oo  oo      oo   oo";
		cout << "\n\too  ooo oo oo  oo ooooooo oo oo     oo  oooooo oo      ooooooo   oo o   ooooo   ooooooo";
		cout << "\n\too      oo oo  oo      oo oo oo         oo     oo      oo   oo    oo    oo      oo  oo";
		cout << "\n\too      oo oooooo ooooooo oo ooooooo    oo     ooooooo oo   oo    oo    ooooooo oo    oo";
		cout << endl;
		cout << endl;
		cout << "Which Playlist Do you Want to Play: " << endl;
		cout << "\t\t 1: For Folk Songs Playlist.\n";
		cout << "\t\t 2: For Sad Songs Playlist.\n";
		cout << "\t\t 3: For Old Songs Playlist.\n ";
		cout << "\t\t 4: To Creat Your Own Playlist OR To Access Existing One.\n ";
		cout << "Enter Your Choice: ";
		cin >> choice;
		switch (choice)
		{
		case 1:
		{
			FolkPlaylist();
			break;
		}
		case 2:
		{
			SadPlaylist();
			break;
		}
		case 3:
		{
			OldPlaylist();
			break;
		}
		case 4:
		{
			UserPlaylist();
			break;
		}

		}
		cout << "Do You want Run the code again?.... if 'yes' then press Y/y otherwise N/n: ";
		cin >> ch;
		system("CLS");
	} while (ch == 'Y' || ch == 'y');
}

void User::UserPlaylist()
{
	wstring path;
	char ch;
	string sID;
	char genre;
	int choice1;
	string plname;
	string plId;
	char chr;
	cout << "Enter The Name of Your Playlist: ";
	cin.ignore();
	getline(cin, plname);
	cout << "Enter Playlist Id: ";
	cin.ignore();
	getline(cin, plId);
	PL[3] = new UserSongPlaylist(plname, plId, song);
	cout << "Do you have already a playlist(y/n)!!";
	cin >> chr;
	if (chr == 'y' || chr == 'Y')
	{
		PL[3]->readfile();
		wstring* abc = PL[3]->ListOfSongs();
		cout << "\tSongs....." << endl;
		for (int i = 0; i < PL[3]->getNoOfSong(); i++)
		{
			wcout << "\t\t" << i + 1 << ": " << abc[i] << endl;
		}
		delete[]abc;
	}
	else
	{
		PL[3]->addPlaylist();
	}
	if (PL[3]->getNoOfSong() > 0)
	{
		cout << "Enter the No of Song you want to Play: ";
		cin >> choice1;
		while (!(choice1 > 0 && choice1 <= PL[3]->getNoOfSong()))
		{
			cout << "Please Enter Valid Song Index....: ";
			cin >> choice1;
		}
		MusicPlayer mp(choice1 - 1, plname, plId, song, PL[3]);
		mp.Open();
		mp.Play();
		while (PL[3]->getNoOfSong() > mp.getUserSongIndex())
		{

			char ch;
			do {
				wcout << "\n\nCurrent Song: " << PL[3]->ListOfSongs()[mp.getUserSongIndex()] << endl << endl;
				cout << "Hit \"P\" to PAUSE or  \"R\" to RESUME or \"S\" to STOP\n or \"N\" to Play Next or \"V\" to Play Previous Media.\n";
				ch = _getch();
				if (ch == 'p' || ch == 'P')
					mp.Pause();
				else if (ch == 'r' || ch == 'R')
					mp.Resume();
				else if (ch == 's' || ch == 'S')
				{
					mp.Stop();
				}
				else if ((ch == 'n' || ch == 'N'))
				{
					mp.Stop();
					mp.setUserSongIndex(mp.getUserSongIndex() + 1);
					if (PL[3]->getNoOfSong() == mp.getUserSongIndex())
					{
						cout << "Playlist has no song yet!!" << endl;
						ch = 's';
					}
					else
						mp.Play();
				}
				else if ((ch == 'v' || ch == 'V'))
				{
					mp.Stop();
					mp.setUserSongIndex(mp.getUserSongIndex() - 1);
					if (PL[3]->getNoOfSong() == mp.getUserSongIndex())
					{
						cout << "Playlist has no song yet!!" << endl;
						ch = 's';
					}
					else
						mp.Play();
				}
				system("CLS");

			} while ((ch != 's' && ch != 'S'));
		}
	}
	cout << "\nPress 1: To Add Song." << endl;
	cout << "Press 2: To Delete Song." << endl;
	cout << "Press 3: To Delete Playlist." << endl;
	cout << "Press any int To Close Playlist." << endl;
	cout << "Enter Choice: ";
	cin >> choice1;
	if (choice1 == 1)
	{
		cout << "Enter Song Path: ";
		cin.ignore();
		getline(wcin, path);
		cout << "Enter Song Genre(a/b/c...etc): ";
		cin >> genre;
		cout << "Enter Song ID: ";
		cin.ignore();
		getline(cin, sID);
		songs s(path, sID, genre);
		PL[3]->addSong(s);
	}
	else if (choice1 == 2)
	{
		cout << "Enter Song Path: ";
		cin.ignore();
		getline(wcin, path);
		PL[3]->deleteSong(path);
	}
	else if (choice1 == 3)
	{
		if (PL[3]->deletePlaylist(PL[3]->getPlaylistName()))
			cout << "Playlist Deleted!!" << endl;
		else
			cout << "Playlist is not Deleted!!" << endl;
	}
	else
	{
		cout << "Playlist Closed....." << endl;
	}
}
void User::FolkPlaylist()
{
	wstring path;
	char ch;
	string sID;
	char genre;
	int choice1;
	PL[0]->readfile();
	wstring* abc = PL[0]->ListOfSongs();
	cout << "\tSongs....." << endl;
	for (int i = 0; i < PL[0]->getNoOfSong(); i++)
	{
		wcout << "\t\t" << i + 1 << ": " << abc[i] << endl;
	}
	delete[]abc;
	if (PL[0]->getNoOfSong() > 0)
	{
		cout << "Enter the No of Song you want to Play: ";
		cin >> choice1;
		while (!(choice1 > 0 && choice1 <= PL[0]->getNoOfSong()))
		{
			cout << "Please Enter Valid Song Index....: ";
			cin >> choice1;
		}
		MusicPlayer mp(choice1 - 1, "FolkSongPlaylist", "1001", song, PL[0]);
		mp.Open();
		mp.Play();
		while (PL[0]->getNoOfSong() > mp.getUserSongIndex())
		{
			char ch;
			do {
				wcout << "\n\nCurrent Song: " << PL[0]->ListOfSongs()[mp.getUserSongIndex()] << endl << endl;
				cout << "Hit \"P\" to PAUSE or  \"R\" to RESUME or \"S\" to STOP\n or \"N\" to Play Next or \"V\" to Play Previous Media.\n";
				ch = _getch();
				if (ch == 'p' || ch == 'P')
					mp.Pause();
				else if (ch == 'r' || ch == 'R')
					mp.Resume();
				else if (ch == 's' || ch == 'S')
				{
					mp.Stop();
				}
				else if ((ch == 'n' || ch == 'N'))
				{
					mp.Stop();
					mp.setUserSongIndex(mp.getUserSongIndex() + 1);
					if (PL[0]->getNoOfSong() == mp.getUserSongIndex())
					{
						cout << "Playlist has no song yet!!" << endl;
						ch = 's';
					}
					else
						mp.Play();
				}
				else if ((ch == 'v' || ch == 'V'))
				{
					mp.Stop();
					mp.setUserSongIndex(mp.getUserSongIndex() - 1);
					if (PL[0]->getNoOfSong() == mp.getUserSongIndex())
					{
						cout << "Playlist has no song yet!!" << endl;
						ch = 's';
					}
					else
						mp.Play();
				}
				system("CLS");
			} while ((ch != 's' && ch != 'S'));
		}
	}
	cout << "\nPress 1: To Add Song." << endl;
	cout << "Press 2: To Delete Song." << endl;
	cout << "Press any int To Close Playlist." << endl;
	cout << "Enter Choice: ";
	cin >> choice1;
	if (choice1 == 1)
	{
		cout << "Enter Song Path: ";
		cin.ignore();
		getline(wcin, path);
		genre = 'f';
		cout << "Enter Song ID: ";
		cin.ignore();
		getline(cin, sID);
		songs s(path, sID, genre);
		PL[0]->addSong(s);
	}
	else if (choice1 == 2)
	{
		cout << "Enter Song Path: ";
		cin.ignore();
		getline(wcin, path);
		PL[0]->deleteSong(path);
	}
	else
	{
		cout << "Playlist Closed....." << endl;
	}
}
void User::SadPlaylist()
{
	wstring path;
	char ch;
	string sID;
	char genre;
	int choice1;
	PL[1]->readfile();
	wstring* abc = PL[1]->ListOfSongs();
	cout << "\tSongs....." << endl;
	for (int i = 0; i < PL[1]->getNoOfSong(); i++)
	{
		wcout << "\t\t" << i + 1 << ": " << abc[i] << endl;
	}
	delete[]abc;
	if (PL[1]->getNoOfSong() > 0)
	{
		cout << "Enter the No of Song you want to Play: ";
		cin >> choice1;
		while (!(choice1 > 0 && choice1 <= PL[1]->getNoOfSong()))
		{
			cout << "Please Enter Valid Song Index....: ";
			cin >> choice1;
		}
		MusicPlayer mp(choice1 - 1, "SadSongPlaylist", "1002", song, PL[1]);
		mp.Open();
		mp.Play();
		while (PL[1]->getNoOfSong() > mp.getUserSongIndex())
		{
			char ch;
			do {
				wcout << "\n\nCurrent Song: " << PL[1]->ListOfSongs()[mp.getUserSongIndex()] << endl << endl;
				cout << "Hit \"P\" to PAUSE or  \"R\" to RESUME or \"S\" to STOP\n or \"N\" to Play Next or \"N\" to Play Previous Media\n";
				ch = _getch();
				if (ch == 'p' || ch == 'P')
					mp.Pause();
				else if (ch == 'r' || ch == 'R')
					mp.Resume();
				else if (ch == 's' || ch == 'S')
					mp.Stop();
				else if ((ch == 'n' || ch == 'N'))
				{
					mp.Stop();
					mp.setUserSongIndex(mp.getUserSongIndex() + 1);
					if (PL[1]->getNoOfSong() == mp.getUserSongIndex())
					{
						cout << "Playlist has no song yet!!" << endl;
						ch = 's';
					}
					else
						mp.Play();
				}
				else if ((ch == 'v' || ch == 'V'))
				{
					mp.Stop();
					mp.setUserSongIndex(mp.getUserSongIndex() - 1);
					if (PL[1]->getNoOfSong() == mp.getUserSongIndex())
					{
						cout << "Playlist has no song yet!!" << endl;
						ch = 's';
					}
					else
						mp.Play();
				}
				system("CLS");
			} while ((ch != 's' && ch != 'S'));
		}
	}
	cout << "\nPress 1: To Add Song." << endl;
	cout << "Press 2: To Delete Song." << endl;
	cout << "Press any int To Close Playlist." << endl;
	cout << "Enter Choice: ";
	cin >> choice1;
	if (choice1 == 1)
	{
		cout << "Enter Song Path: ";
		cin.ignore();
		getline(wcin, path);
		genre = 'f';
		cout << "Enter Song ID: ";
		cin.ignore();
		getline(cin, sID);
		songs s(path, sID, genre);
		PL[1]->addSong(s);
	}
	else if (choice1 == 2)
	{
		cout << "Enter Song Path: ";
		cin.ignore();
		getline(wcin, path);
		PL[1]->deleteSong(path);
	}
	else
	{
		cout << "Playlist Closed....." << endl;
	}
}
void User::OldPlaylist()
{
	wstring path;
	char ch;
	string sID;
	char genre;
	int choice1;
	PL[2]->readfile();
	wstring* abc = PL[2]->ListOfSongs();
	cout << "\tSongs....." << endl;
	for (int i = 0; i < PL[2]->getNoOfSong(); i++)
	{
		wcout << "\t\t" << i + 1 << ": " << abc[i] << endl;
	}
	delete[]abc;
	if (PL[2]->getNoOfSong() > 0)
	{
		cout << "Enter the No of Song you want to Play: ";
		cin >> choice1;
		while (!(choice1 > 0 && choice1 <= PL[2]->getNoOfSong()))
		{
			cout << "Please Enter Valid Song Index....: ";
			cin >> choice1;
		}
		MusicPlayer mp(choice1 - 1, "OldSongPlaylist", "1003", song, PL[2]);
		mp.Open();
		mp.Play();
		while (PL[2]->getNoOfSong() > mp.getUserSongIndex())
		{
			char ch;
			do {
				wcout << "\n\nCurrent Song: " << PL[2]->ListOfSongs()[mp.getUserSongIndex()] << endl << endl;
				cout << "Hit \"P\" to PAUSE or  \"R\" to RESUME or \"S\" to STOP\n or \"N\" to Play Next or \"V\" to Play Previous Media\n";
				ch = _getch();
				if (ch == 'p' || ch == 'P')
					mp.Pause();
				else if (ch == 'r' || ch == 'R')
					mp.Resume();
				else if (ch == 's' || ch == 'S')
					mp.Stop();
				else if ((ch == 'n' || ch == 'N'))
				{
					mp.Stop();
					mp.setUserSongIndex(mp.getUserSongIndex() + 1);
					if (PL[2]->getNoOfSong() == mp.getUserSongIndex())
					{
						cout << "Playlist has no song yet!!" << endl;
						ch = 's';
					}
					else
						mp.Play();
				}
				else if ((ch == 'v' || ch == 'V'))
				{
					mp.Stop();
					mp.setUserSongIndex(mp.getUserSongIndex() - 1);
					if (PL[2]->getNoOfSong() == mp.getUserSongIndex())
					{
						cout << "Playlist has no song yet!!" << endl;
						ch = 's';
					}
					else
						mp.Play();
				}
				system("CLS");
			} while ((ch != 's' && ch != 'S'));
		}
	}
	cout << "\nPress 1: To Add Song." << endl;
	cout << "Press 2: To Delete Song." << endl;
	cout << "Press any int To Close Playlist." << endl;
	cout << "Enter Choice: ";
	cin >> choice1;
	if (choice1 == 1)
	{
		cout << "Enter Song Path: ";
		cin.ignore();
		getline(wcin, path);
		genre = 'f';
		cout << "Enter Song ID: ";
		cin.ignore();
		getline(cin, sID);
		songs s(path, sID, genre);
		PL[2]->addSong(s);
	}
	else if (choice1 == 2)
	{
		cout << "Enter Song Path: ";
		cin.ignore();
		getline(wcin, path);
		PL[2]->deleteSong(path);
	}
	else
	{
		cout << "Playlist Closed....." << endl;
	}
}
void User::Display()
{
	system("Color 89");
	cout << " $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$" << endl;
	cout << " #################################################################################################################" << endl;
	cout << " $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$" << endl;
	cout << "$$$ " << "o o               __                 _       o o o o o o     o o o o o o o o o     o o o o o o o o   " << "\t$$$" << endl;
	cout << "$$$ " << "o   o            o  o   o  o          o  o  *  o  o o o o o  o o o o   o o o o    /    o o o o o o  " << "\t$$$" << endl;
	cout << "$$$ " << "o o  o          o   o   o  o          o  o  o*                      o o         /  /" << "\t\t\t$$$" << endl;
	cout << "$$$ " << "o  o  o        o o  o   o  o        _ _ _ _   _           * *    _     _  _ _ _ _   " << "\t\t\t$$$" << endl;
	cout << "$$$ " << "o  o o  o     o  o  o   o  o       |   _   | |  |        * _ *   * *_/ / |  _ _ _| *  *_*" << "\t\t\t$$$" << endl;
	cout << "$$$ " << "o  o  o  o   o  o   o   o  o       |  |_/ /  |  |       * * * *   *   /  |  |_ _   *  |_/  *" << "\t\t$$$" << endl;
	cout << "$$$ " << "o  o   o  o o  o    o   o  o       | _ _ /   |  |      * *__ * *   | |   |  _ _ |  *  _ _ *" << "\t\t\t$$$" << endl;
	cout << "$$$ " << "o  o    o o  o      o   o  o       | |       |  |_ _  * *     * *  | |   |  |_ _ _ * *   * * " << "\t\t$$$" << endl;
	cout << "$$$ " << "o  o                o   o  o       |_|       |_ _ _ |* *       *_* |_|   |_ _ _ _ |* *    *_* " << "\t\t$$$" << endl;
	cout << "$$$ " << "o  o                o   o  o          o  o  o o o o o o o           o o           o  o" << "\t\t\t$$$" << endl;
	cout << "$$$ " << "o  o                o   o  o          o  o   o o o o o o o          o o           o  o" << "\t\t\t$$$" << endl;
	cout << "$$$ " << "o  o                o   o  o          o  o             o o          o o           o  o" << "\t\t\t$$$" << endl;
	cout << "$$$ " << "o  o                o   o  o          o  o             o o          o o           o  o" << "\t\t\t$$$" << endl;
	cout << "$$$ " << "o  o                o   o  oo o o o o o  o   o o o o o / /    o o o o  o o o o    o  o o o o o o" << "\t\t$$$" << endl;
	cout << "$$$ " << "o_ o                o   o o o o o o o o /   o o o o o o /     o o o o o o o o     o o o o o o o o " << "\t\t$$$" << endl;
	cout << " $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$" << endl;
	cout << " #################################################################################################################" << endl;
	cout << " $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$" << endl;
	system("pause");
	system("Color 0B");
	char a[] = "MODE 100,65";
	system(a);
	cout << "Instruction for using Audio Music Player...." << endl;
	cout << "Rule 1:You can only deal .mp3 or .wav songs in this music Player." << endl;
	cout << "\tIf you violate this rule this music Player will not work.." << endl;
	cout << "We are giving you 3 built in Playlist " << endl;
	cout << "\t1. FOLK Playlist" << endl;
	cout << "\t2. OLD Playlist" << endl;
	cout << "\t3. SAD Playlist" << endl;
	cout << "Rule 2: We are providing you IDs for these 3 built in Playlists just " << endl;
	cout << "\tfor your information you want to add Playlist You can enter ID of your" << endl;
	cout << "\town choice" << endl;
	cout << "\t1001 for FOLK" << endl;
	cout << "\t1002 for OLD" << endl;
	cout << "\t1003 for SAD" << endl;
	cout << "Rule 3: Name of Playlist should be unique when you enter new playlist" << endl;
	cout << "Rule 4: You can also create your new playlist or you can access your existing playlist by" << endl;
	cout << "\tentering Name and ID of It." << endl;
	cout << "Rule 5: Except 3 built In Playlist" << endl;
	cout << "you can also delete Playlist which you have added recently" << endl;
	cout << "\texcept FOLK,OLD and Sad" << endl;
	cout << "Rule 6: We are providing you some song in built in PlayList" << endl;
	cout << "For OLD you have songs" << endl;
	cout << "\t1. Uthe_Sabke_Kadam_Tara.mp3" << endl;
	cout << "\t2. O_Sanam_Sunoh.mp3" << endl;
	cout << "\t3. Dil_ki_lagi.mp3" << endl;
	cout << "\t4. Laiyan_Laiyan.mp3" << endl;
	cout << "\t5. Bin_Tere_Kya_Hai_jeena.mp3" << endl;
	cout << "For SAD you have songs" << endl;
	cout << "\t1. Birds.mp3 " << endl;
	cout << "\t2. We_Dont_Talk_Anymore.mp3" << endl;
	cout << "\t3. Ghalat_Fehmi.mp3" << endl;
	cout << "\t4. So_Far_Away.mp3" << endl;
	cout << "\t5. Musafir.mp3" << endl;
	cout << "\t6. Demons.mp3" << endl;
	cout << "\t7. Mann_Bharrya.mp3" << endl;
	cout << "For FOLK you have songs" << endl;
	cout << "\t1. Maula_Maaf_Karin.mp3" << endl;
	cout << "\t2. Mere_Rashke_Qamar.mp3" << endl;
	cout << "\t3. Tajdar_E_Haram.mp3" << endl;
	cout << "\t4. Kali_kali_zulfo.mp3" << endl;
	cout << "Rule 7: You can add Song in any existing Playlist" << endl;
	cout << "Rule 8: You can delete Song from any existing Playlist" << endl;
	cout << "Rule 9: We will give you information when you select choices" << endl;
	cout << "\taccording to our information..." << endl;
	cout << "\t\t...Thank you for reading this.Now you are ready to Play this Music Player..." << endl;
	system("pause");
	system("Color 0E");
	if (!_kbhit())
	{
		char a[] = "MODE 100,25";
		system(a);
		cout << "Hi..." << getName() << endl;
		cout << "\too      oo      ";
		cout << "\n\too      oo ooooooo oo      oooooo  oooooo oooo  oooo ooooooo";
		cout << "\n\too      oo oo      oo      oo      oo  oo oo  ooo oo oo   ";
		cout << "\n\too  oo  oo ooooo   oo      oo      oo  oo oo  ooo oo ooooo ";
		cout << "\n\too  oo  oo oo      oo      oo      oo  oo oo      oo oo    ";
		cout << "\n\toooooooooo ooooooo ooooooo ooooooo oooooo oo      oo ooooooo";
		cout << endl;
		cout << endl << endl;
	}
}
void User::setName(string name)
{
	Name = name;
}
string User::getName()
{
	return Name;
}
void User::setUserId(string a_ID)
{
	UserId = a_ID;
}
string User::getId()
{
	return UserId;
}
User::~User()
{
	if (PL)
	{
		for (int i = 0; i < 4; i++)
		{
			delete PL[i];
			PL[i] = NULL;
		}
		//delete []PL;
	}
	Name = "\0";
	UserId = "\0";
}
