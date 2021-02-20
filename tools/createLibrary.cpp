/**
 * Core6
 * Copyright (C) 2020 Kacper Chętkowski (kacper.chetkowski@gmail.com)
 *
 * This software is provided 'as-is', without any express or implied warranty.
 * In no event will the authors be held liable for any damages arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it freely,
 * subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented;
 *    you must not claim that you wrote the original software.
 *    If you use this software in a product, an acknowledgment
 *    in the product documentation would be appreciated but is not required.
 *
 * 2. Altered source versions must be plainly marked as such,
 *    and must not be misrepresented as being the original software.
 *
 * 3. This notice may not be removed or altered from any source distribution.
*/

#include <cstdlib>

int main(){
	#ifdef _WIN32
	system("echo Preparing project tree");
	system("rmdir /s /q ..\\Core6");
	system("mkdir ..\\Core6");
	system("mkdir ..\\Core6\\bin");
	system("mkdir ..\\Core6\\include");
	system("rmdir /s /q ..\\tests\\mods");
	system("rmdir /s /q ..\\tests\\bin");
	system("mkdir ..\\tests\\mods");
	system("mkdir ..\\tests\\bin");
	
	system("echo Building Core6");
	system("cmake -G \"CodeBlocks - MinGW Makefiles\" -B..\\cmake_files ..\\");
	system("cmake --build ..\\cmake_files\\ --target Core6");
	system("xcopy /s /EXCLUDE:excludeWin.txt ..\\src ..\\Core6\\include /Y /q");
	system("xcopy ..\\cmake_files\\libCore6.dll ..\\Core6\\bin /Y /q");
	
	
	system("echo Building test project");
	system("echo Copying binaries");
	system("xcopy ..\\libraries\\win\\SFML-2.5.1\\bin ..\\tests\\bin\\ /Y /q");
	system("xcopy ..\\Core6\\bin ..\\tests\\bin\\ /Y /q");
	
	system("echo Building test binary");
	system("cmake --build ..\\cmake_files\\ --target Core6debugLib");
	system("xcopy ..\\cmake_files\\libCore6debugLib.dll ..\\tests\\bin /Y /q");
	
	system("echo Building plugin");
	system("cmake --build ..\\cmake_files\\ --target Core6plugin");
	system("xcopy ..\\cmake_files\\libCore6plugin.dll ..\\tests\\mods /Y /q");
	
	system("echo Building executable");
	system("cmake --build ..\\cmake_files\\ --target Core6debug");
	#elif unix
	system("rm -r Core5");
	system("mkdir Core5");
	system("mkdir Core5/bin");
	system("mkdir Core5/include");
	//system("rsync -rv --exclude=.cpp src/* include");
	#endif
}