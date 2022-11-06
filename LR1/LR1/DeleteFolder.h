#pragma once
#include<iostream>
#include<windows.h>
#include <fileapi.h>

void DeleteFolder() {
	wchar_t path[MAX_PATH];
	std::wcin.ignore(INT_MAX, '\n');
	std::cout << "Введите полное имя файла (например D:\Folder):";
	std::wcin.getline(path, MAX_PATH, L'\n');
	if (RemoveDirectory(path)) {
		std::cout << "Каталог удален" << std::endl;
	}
	else {
		std::cout << "Ошибка!" << std::endl;
	}
}
