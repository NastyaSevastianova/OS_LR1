#pragma once
#include<iostream>
#include<windows.h>
#include <fileapi.h>

void CreateNewFolder() {
	wchar_t path[MAX_PATH];
	std::wcin.ignore(INT_MAX, '\n');
	std::cout << "Введите полное имя файла (например D:\Folder): ";
	std::wcin.getline(path, MAX_PATH, L'\n');

	if (CreateDirectory(path, NULL)) {
		std::cout << "Каталог создан" << std::endl;
	}
	else {
		std::cout << "Ошибка!" << std::endl;
	}
}
