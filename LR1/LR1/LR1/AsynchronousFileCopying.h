#pragma once
#include<iostream>
#include<windows.h>
#include<fileapi.h>

//Количество перекрывающихся операций ввода-вывода
const int OverlappingOperationsAmount = 16;
//Множитель, используемый для масштабирования размера блока, передаваемого за одну операцию ввода-вывода
const int BlockSizeClustersMultiplier = 16;

//Эта структура предназначена для хранения размеров файлов и смещений в одной переменной с возможностью брать их старшие и младшие слова
typedef union {
	unsigned long long total;
	struct {
		DWORD lesser;
		DWORD higher;
	};
} size;

//Эта структура предназначена для передачи буфера и смещения в процедуры обратного вызова (указатель на экземпляр назначается неиспользуемому полю hEvent в OVERLAPPED)
typedef struct {
	void* buffer;
	size currentOffset;
} threadProps;

HANDLE file1, file2;
size filesize, clustersize;

void _stdcall afterWriteRoutine(DWORD errorCode, DWORD bytesTransfered, LPOVERLAPPED props);
void _stdcall afterReadRoutine(DWORD errorCode, DWORD bytesTransfered, LPOVERLAPPED props);

//Подпрограмма вызывается после операции записи; 
//Здесь мы определяем, нужно ли нам дальнейшее копирование в текущем потоке, и организуем его, если это необходимо

void _stdcall afterWriteRoutine(DWORD errorCode, DWORD bytesTransfered, LPOVERLAPPED props) {
	//Экземпляр threadProps передается через hEvent, поэтому мы извлекаем его
	threadProps* tprop = static_cast<threadProps*>(props->hEvent);

	//Смещение роста
	tprop->currentOffset.total += clustersize.total * OverlappingOperationsAmount;
	props->Offset = tprop->currentOffset.lesser;
	props->OffsetHigh = tprop->currentOffset.higher;

	//нам нужно дальнейшее копирование, только если смещение роста находится в пределах границ файла
	if (filesize.total > tprop->currentOffset.total)
		ReadFileEx(file1,
			tprop->buffer,
			clustersize.total,
			props,
			afterReadRoutine);
}

//Подпрограмма вызывается после операции чтения;
//Здесь мы записываем прочитанные данные в файл копирования

void _stdcall afterReadRoutine(DWORD errorCode, DWORD bytesTransfered, LPOVERLAPPED props) {
	//Экземпляр threadProps передается через hEvent, поэтому мы извлекаем его
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

	std::cout << "Введите полное имя файла, не более 255 символов(например C : \\Users\\User\\file.mp4): ";
	std::wcin.getline(file1Path, MAX_PATH, L'\n');

	//Определение пункта назначения
	std::cout << "Введите полное имя копии файла, не более 255 символов(например C : \\Users\\User\\newfile.mp4): ";
	std::wcin.getline(file2Path, MAX_PATH, L'\n');

	//Открытие файлов
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

	//Проверка правильности открытия
	if (file1 == INVALID_HANDLE_VALUE || file2 == INVALID_HANDLE_VALUE) {
		std::cout << "Исходный файл не был открыт или копия не была создана\n"
			<< "Проверьте правильность путей, оригинал существует, а копия — нет." << std::endl;
		return;
	}

	//Определение размера
	filesize.lesser = GetFileSize(file1, &filesize.higher);

	//Определение размера кластера
	srcRoot[0] = file1Path[0];

	//Неиспользуемые выходные значения записываются одним фиктивным
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

	//Дождаться окончания операций
	while (SleepEx(100, true));

	endTime = GetTickCount();
	std::cout << "Успешно! Операция состоялась. " << endTime - startTime << " мс." << std::endl;

	//Закрытие файлов, освобождение буфера
	CloseHandle(file1);
	CloseHandle(file2);
	for (int i = 0; i < OverlappingOperationsAmount; ++i) free(tprops[i].buffer);
}

