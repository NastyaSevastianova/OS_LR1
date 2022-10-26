#pragma once
#include<iostream>
#include<windows.h>
#include<fileapi.h>

void Flags(DWORD flags) {
	if (flags & FILE_ATTRIBUTE_READONLY)				std::cout << "file is readonly;\n";
	if (flags & FILE_ATTRIBUTE_RECALL_ON_DATA_ACCESS)	std::cout << "file is not fully present locally;\n";
	if (flags & FILE_ATTRIBUTE_RECALL_ON_OPEN)			std::cout << "file is virtual;\n";
	if (flags & FILE_ATTRIBUTE_REPARSE_POINT)			std::cout << "file is a symbolic link;\n";
	if (flags & FILE_ATTRIBUTE_SPARSE_FILE)				std::cout << "file is sparse;\n";
	if (flags & FILE_ATTRIBUTE_SYSTEM)					std::cout << "system uses only a part of this file;\n";
	if (flags & FILE_ATTRIBUTE_TEMPORARY)				std::cout << "file is being used for temporary storage;\n";
	if (flags & FILE_ATTRIBUTE_VIRTUAL)					std::cout << "file is reserved for system use;\n";
	if (flags & FILE_ATTRIBUTE_PINNED)					std::cout << "file should be kept fully present locally even when not being actively accessed;\n";
	if (flags & FILE_ATTRIBUTE_UNPINNED)				std::cout << "file should not be kept fully present locally except when being actively accessed;\n";
	if (flags & FILE_ATTRIBUTE_ARCHIVE)					std::cout << "file is an archive;\n";
	if (flags & FILE_ATTRIBUTE_COMPRESSED)				std::cout << "file is compressed;\n";
	if (flags & FILE_ATTRIBUTE_DEVICE)					std::cout << "file is reserved for system use;\n";
	if (flags & FILE_ATTRIBUTE_DIRECTORY)				std::cout << "file is a directory;\n";
	if (flags & FILE_ATTRIBUTE_ENCRYPTED)				std::cout << "file is encrypted;\n";
	if (flags & FILE_ATTRIBUTE_HIDDEN)					std::cout << "file is hidden;\n";
	if (flags & FILE_ATTRIBUTE_INTEGRITY_STREAM)		std::cout << "file is configured with integrity;\n";
	if (flags & FILE_ATTRIBUTE_NORMAL)					std::cout << "file has no special attributes;\n";
	if (flags & FILE_ATTRIBUTE_NOT_CONTENT_INDEXED)		std::cout << "file not to be indexed by the content indexing service;\n";
	if (flags & FILE_ATTRIBUTE_NO_SCRUB_DATA)			std::cout << "file is not to be read by the background data integrity scanner;\n";
	if (flags & FILE_ATTRIBUTE_OFFLINE)					std::cout << "file is not available immediately;\n";
}

void fillTime(SYSTEMTIME* time) {
	WORD value;
	std::cout << "������� ��� (��������, 2000): ";
	std::wcin >> value;
	std::wcin.ignore(INT_MAX, '\n');
	time->wYear = value;
	std::cout << "������� ����� (��������, 12): ";
	std::wcin >> value;
	std::wcin.ignore(INT_MAX, '\n');
	time->wMonth = value;
	std::cout << "������� ���� (��������, 3): ";
	std::wcin >> value;
	std::wcin.ignore(INT_MAX, '\n');
	time->wDay = value;
	std::cout << "������� ��� (��������, 6): ";
	std::wcin >> value;
	std::wcin.ignore(INT_MAX, '\n');
	time->wHour = value;
	std::cout << "������� ������ (��������, 18): ";
	std::wcin >> value;
	std::wcin.ignore(INT_MAX, '\n');
	time->wMinute = value;
	std::cout << "������� ������� (��������, 8): ";
	std::wcin >> value;
	std::wcin.ignore(INT_MAX, '\n');
	time->wSecond = value;
}

void InfoAttributes(){
	_BY_HANDLE_FILE_INFORMATION fileInfo;
	SYSTEMTIME time;
	FILETIME fileTime;
	HANDLE file;

	DWORD newFlags;

	int select;

	wchar_t path[MAX_PATH];
	std::wcin.ignore(INT_MAX, '\n');

	std::cout << "������� ������ ��� ����� (�������� D:\Folder\File.txt): ";
	std::wcin.getline(path, MAX_PATH, L'\n');
	file =	CreateFile(path,
			GENERIC_READ | FILE_WRITE_ATTRIBUTES,
			FILE_SHARE_DELETE | FILE_SHARE_WRITE | FILE_SHARE_READ,
			NULL,
			OPEN_EXISTING,
			FILE_ATTRIBUTE_NORMAL,
			NULL);
	if (file == INVALID_HANDLE_VALUE) {
		std::cout << "���� �� ����������" << std::endl;
		return;
	}

	if (!GetFileInformationByHandle(file, &fileInfo)) {
		std::cout << "���������� �������� ���������� � �����" << std::endl;
		return;
	}

	// ����������� ������
	Flags(fileInfo.dwFileAttributes);

	// ����� �������
	FileTimeToSystemTime(&(fileInfo.ftCreationTime), &time);
	std::cout << "���� ��� ������ �: " << time.wDay << "." << time.wMonth << "." << time.wYear
		<< ", " << time.wHour << "� : " << time.wMinute << "� : " << time.wSecond << "� UTC 0,\n";
	FileTimeToSystemTime(&(fileInfo.ftLastAccessTime), &time);
	std::cout << "��������� ��� � ����� ���������� �: " << time.wDay << "." << time.wMonth << "." << time.wYear
		<< ", " << time.wHour << "� : " << time.wMinute << "� : " << time.wSecond << "� UTC 0,\n";
	FileTimeToSystemTime(&(fileInfo.ftLastWriteTime), &time);
	std::cout << "��������� ��� ���� ��� ������� �: " << time.wDay << "." << time.wMonth << "." << time.wYear
		<< ", " << time.wHour << "� : " << time.wMinute << "� : " << time.wSecond << "� UTC 0,\n";

	// ������ ����������
	std::cout << "���� �������� �� ���� � �������� �������: " << fileInfo.dwVolumeSerialNumber;
	std::cout << ",\n������ �����: " << fileInfo.nFileSizeHigh << fileInfo.nFileSizeLow;
	std::cout << " ������,\n���������� ������ �� ���� ����: " << fileInfo.nNumberOfLinks;
	std::cout << ",\n������������� �����: " << fileInfo.nFileIndexHigh << fileInfo.nFileIndexLow << std::endl;

	while (true) {
		std::cout << ".\n1-�������� ����� ������?";
		std::cout << ".\n2-�������� ����� �������� �����?";
		std::cout << ".\n3-�������� ����� ���������� ������� � �����?";
		std::cout << ".\n4-�������� ����� ���������� ��������� �����?";
		std::cout << ".\n����� ������ ������ ��� ������";

		std::cin >> select;

		switch (select) {
		case 1:
			std::cout << "������� ����� ������. ������ ���� - ���� ��� ����� �����. �����: https://learn.microsoft.com/en-us/windows/win32/fileio/file-attribute-constants";
			std::wcin >> newFlags;
			if (SetFileAttributes(path, newFlags))
				std::cout << "����� �����������\n";
			else
				std::cout << "�� ������� ���������� �����\n";
			break;
		case 2:
			fillTime(&time);
			SystemTimeToFileTime(&time, &fileTime);
			if (SetFileTime(file, &fileTime, NULL, NULL))
				std::cout << "����� �����������\n";
			else
				std::cout << "�� ������� ���������� �����\n";
			break;
		case 3:
			fillTime(&time);
			SystemTimeToFileTime(&time, &fileTime);
			if (SetFileTime(file, NULL, &fileTime, NULL))
				std::cout << "����� �����������\n";
			else
				std::cout << "�� ������� ���������� �����\n";
			break;
		case 4:
			fillTime(&time);
			SystemTimeToFileTime(&time, &fileTime);
			if (SetFileTime(file, NULL, NULL, &fileTime))
				std::cout << "����� �����������\n";
			else
				std::cout << "�� ������� ���������� �����\n";
			break;
		default:
			return;
			break;
		}
	}

	CloseHandle(file);
}



