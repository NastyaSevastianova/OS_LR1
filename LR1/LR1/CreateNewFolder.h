#pragma once
#include<iostream>
#include<windows.h>
#include <fileapi.h>

void CreateNewFolder() {
	wchar_t path[MAX_PATH];
	std::wcin.ignore(INT_MAX, '\n');
	std::cout << "������� ������ ��� ����� (�������� D:\Folder): ";
	std::wcin.getline(path, MAX_PATH, L'\n');

	if (CreateDirectory(path, NULL)) {
		std::cout << "������� ������" << std::endl;
	}
	else {
		std::cout << "������!" << std::endl;
	}
}
