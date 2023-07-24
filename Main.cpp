#include <iostream>
#include<Windows.h>
#include<conio.h>
#include<string>
#include"songs.h"
#include"Playlist.h"
#include"MusicPlayer.h"
#include"User.h"
#include <mmsystem.h>
using namespace std;
int main()
{
	User TA;
	TA.setName("Ali");
	TA.setUserId("1234");
	TA.Display();
	TA.InputFunc();
}