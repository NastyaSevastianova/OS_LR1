#pragma once
#include<iostream>
#include<windows.h>
#include<fileapi.h>

//���������� ��������������� �������� �����-������
const int OverlappingOperationsAmount = 16;
//���������, ������������ ��� ��������������� ������� �����, ������������� �� ���� �������� �����-������
const int BlockSizeClustersMultiplier = 16;

//��� ��������� ������������� ��� �������� �������� ������ � �������� � ����� ���������� � ������������ ����� �� ������� � ������� �����
typedef union {
	unsigned long long total;
	struct {
		DWORD lesser;
		DWORD higher;
	};
} size;

//��� ��������� ������������� ��� �������� ������ � �������� � ��������� ��������� ������ (��������� �� ��������� ����������� ��������������� ���� hEvent � OVERLAPPED)
typedef struct {
	void* buffer;
	size currentOffset;
} threadProps;

HANDLE file1, file2;
size filesize, clustersize;

void _stdcall afterWriteRoutine(DWORD errorCode, DWORD bytesTransfered, LPOVERLAPPED props);
void _stdcall afterReadRoutine(DWORD errorCode, DWORD bytesTransfered, LPOVERLAPPED props);

//������������ ���������� ����� �������� ������; 
//����� �� ����������, ����� �� ��� ���������� ����������� � ������� ������, � ���������� ���, ���� ��� ����������

void _stdcall afterWriteRoutine(DWORD errorCode, DWORD bytesTransfered, LPOVERLAPPED props) {
	//��������� threadProps ���������� ����� hEvent, ������� �� ��������� ���
	threadProps* tprop = static_cast<threadProps*>(props->hEvent);

	//�������� �����
	tprop->currentOffset.total += clustersize.total * OverlappingOperationsAmount;
	props->Offset = tprop->currentOffset.lesser;
	props->OffsetHigh = tprop->currentOffset.higher;

	//��� ����� ���������� �����������, ������ ���� �������� ����� ��������� � �������� ������ �����
	if (filesize.total > tprop->currentOffset.total)
		ReadFileEx(file1,
			tprop->buffer,
			clustersize.total,
			props,
			afterReadRoutine);
}

//������������ ���������� ����� �������� ������;
//����� �� ���������� ����������� ������ � ���� �����������

void _stdcall afterReadRoutine(DWORD errorCode, DWORD bytesTransfered, LPOVERLAPPED props) {
	//��������� threadProps ���������� ����� hEvent, ������� �� ��������� ���
	threadProps* tprop = static_cast<threadProps*>(props->hEvent);

	WriteFileEx(file2,
		tprop->buffer,
		bytesTransfered,
		props,
		afterWriteRoutine);
}

void AsynchronousFileCopying()
{
	wchar_t file1Path[MAX_PATH], file2Path[MAX_PATH], srcRoot[] = L"A:\\";

	threadProps tprops[OverlappingOperationsAmount];
	OVERLAPPED props[OverlappingOperationsAmount];

	DWORD sectorPerCluster, bytesPerSector, mock, startTime, endTime;

	std::cout << "������� ������ ��� �����, �� ����� 255 ��������(�������� C : \\Users\\User\\file.mp4): ";
	std::wcin.getline(file1Path, MAX_PATH, L'\n');

	//����������� ������ ����������
	std::cout << "������� ������ ��� ����� �����, �� ����� 255 ��������(�������� C : \\Users\\User\\newfile.mp4): ";
	std::wcin.getline(file2Path, MAX_PATH, L'\n');

	//�������� ������
	file1 = CreateFile(file1Path,
			FILE_GENERIC_READ,
			FILE_SHARE_READ,
			NULL,
			OPEN_EXISTING,
			FILE_FLAG_NO_BUFFERING | FILE_FLAG_OVERLAPPED,
			NULL);
	file2 =	CreateFile(file2Path,
			FILE_GENERIC_WRITE,
			FILE_SHARE_WRITE,
			NULL,
			CREATE_NEW,
			FILE_FLAG_OVERLAPPED,
			NULL);

	//�������� ������������ ��������
	if (file1 == INVALID_HANDLE_VALUE || file2 == INVALID_HANDLE_VALUE) {
		std::cout << "�������� ���� �� ��� ������ ��� ����� �� ���� �������\n"
			<< "��������� ������������ �����, �������� ����������, � ����� � ���." << std::endl;
		return;
	}

	//����������� �������
	filesize.lesser = GetFileSize(file1, &filesize.higher);

	//����������� ������� ��������
	srcRoot[0] = file1Path[0];

	//�������������� �������� �������� ������������ ����� ���������
	GetDiskFreeSpace(srcRoot, &sectorPerCluster, &bytesPerSector, &mock, &mock);
	clustersize.total = sectorPerCluster * bytesPerSector * BlockSizeClustersMultiplier;

	startTime = GetTickCount();

	for (int i = 0; i < OverlappingOperationsAmount; ++i) {
		tprops[i].buffer = malloc(clustersize.total + 1);
		tprops[i].currentOffset.total = i * clustersize.total;

		props[i].Internal = 0;
		props[i].InternalHigh = 0;
		props[i].Pointer = 0;
		props[i].Offset = tprops[i].currentOffset.lesser;
		props[i].OffsetHigh = tprops[i].currentOffset.higher;

		props[i].hEvent = tprops + i;

		ReadFileEx(file1,
			tprops[i].buffer,
			clustersize.total,
			props + i,
			afterReadRoutine);
	}

	//��������� ��������� ��������
	while (SleepEx(100, true));

	endTime = GetTickCount();
	std::cout << "�������! �������� ����������. " << endTime - startTime << " ��." << std::endl;

	//�������� ������, ������������ ������
	CloseHandle(file1);
	CloseHandle(file2);
	for (int i = 0; i < OverlappingOperationsAmount; ++i) free(tprops[i].buffer);
}

