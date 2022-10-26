#pragma once
#include<iostream>
#include<windows.h>
#include <fileapi.h>

void CreateNewFile(){
	HANDLE file;
	wchar_t path[MAX_PATH];
	std::wcin.ignore(INT_MAX, '\n');

	std::cout << "������� ������ ��� ����� (�������� D:\Folder\File.txt):: ";
	std::wcin.getline(path, MAX_PATH, L'\n');

	file = CreateFile(path, GENERIC_READ | GENERIC_WRITE, 0, NULL, CREATE_NEW, FILE_ATTRIBUTE_NORMAL, NULL);
	if (file != INVALID_HANDLE_VALUE) {
		CloseHandle(file);
		std::cout << "���� ������" << std::endl;
	}
	else {
		if (GetLastError() == ERROR_FILE_EXISTS) {
			std::cout << "���� � ����� ������ ��� ����������" << std::endl;
		}
		else {
			std::cout << "������!" << std::endl;
		}
	}
}

