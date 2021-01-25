//
// Created by Kacper on 04/12/2020.
//

#include <cstdlib>

int main(){
	#ifdef _WIN32
	system("rmdir /s Core6");
	system("mkdir Core6");
	system("mkdir Core6\\bin");
	system("mkdir Core6\\include");
	system("xcopy /s /EXCLUDE:excludeWin.txt src Core6\\include");
	system("xcopy bin\\libCore6.dll Core6\\bin");
	#elif unix
	system("rm -r Core5");
	system("mkdir Core5");
	system("mkdir Core5/bin");
	system("mkdir Core5/include");
	//system("rsync -rv --exclude=.cpp src/* include");
	#endif
}