#pragma once
#include<iostream>
#include<windows.h>
#include <fileapi.h>

void CopyTheFile()
{
	wchar_t path[MAX_PATH], new_path[MAX_PATH];
	std::wcin.ignore(INT_MAX, '\n');

	std::cout << "������� ������ ��� ����� (�������� D:\Folder\File.txt): ";
	std::wcin.getline(path, MAX_PATH, L'\n');

	std::cout << "������� ������ ��� ����� (�������� D:\Folder\File.txt): ";
	std::wcin.getline(new_path, MAX_PATH, L'\n');

	if (CopyFile(path, new_path, true)) {
		std::cout << "�������!" << std::endl;
	}
	else {
		if (GetLastError() == 80L) {
			std::cout << "���� ��� ����������" << std::endl;
		}
		else {
			std::cout << "������!" << std::endl;
		}
	}
}
