#include <iostream>
#include <windows.h>
#include <fileapi.h>

void SeeDiscs() {
	setlocale(LC_ALL, "Russian");

	int pos = 0;
	DWORD disc = GetLogicalDrives();

	wchar_t path[] = L"A:\\";

	//получить все имена дисков

	const DWORD volNameMaxLength = 50, fileSystemNameLength = 10;

	UINT driveType;
	wchar_t volName[volNameMaxLength], fileSystemName[fileSystemNameLength];
	DWORD sectorPerCluster, bytesPerSector, numOfFreeClusters, totalNumOfClusters, maxComponentLength, serialNumber;


	for (DWORD i = 1; pos < (sizeof(DWORD) * 8); i <<= 1, ++pos) {
		if(disc & i) {
			std::cout << "Disc " << char('A' + pos) << "\n";
		}
	}

	std::cout << "Введите диск (например C): ";
	wchar_t selectDisk = 'c';
	std::wcin >> selectDisk;
	selectDisk = towupper(selectDisk);
	std::cin.ignore(INT_MAX, '\n');

	if (selectDisk >= 'A' && selectDisk <= 'Z' && disc & (1 << (selectDisk - 'A'))) {

		path[0] = selectDisk;
		
		//Тип диска
		driveType = GetDriveType(path);
		switch (driveType) {
		case 0:
			std::cout << "\nНеопределимый\n";
			break;
		case DRIVE_REMOVABLE:
			std::cout << "\nСъемный диск\n";
			break;
		case DRIVE_FIXED:
			std::cout << "\nЖесткий диск\n";
			break;
		case DRIVE_REMOTE:
			std::cout << "\nСетевой диск\n";
			break;
		case DRIVE_CDROM:
			std::cout << "\nCD-ROM\n";
			break;
		case DRIVE_RAMDISK:
			std::cout << "\nRAM-диск\n";
			break;
		default:
			std::cout << "\nЧто-то неожиданное...\n";
		}

		//Имя
		GetVolumeInformationW(path, volName, volNameMaxLength, &serialNumber, &maxComponentLength, NULL, fileSystemName, fileSystemNameLength);
		std::wcout	<< "Drive name: " << selectDisk
					<< "\nSerial number: " << serialNumber
					<< "\nMax file name length: " << maxComponentLength
					<< "\nFile system: " << fileSystemName;

		//Пространство
		GetDiskFreeSpace(path, &sectorPerCluster, &bytesPerSector, &numOfFreeClusters, &totalNumOfClusters);
		std::cout	<< "\nОбщее количество кластеров: " << totalNumOfClusters
					<< "\nКоличество свободных кластеров: " << numOfFreeClusters
					<< "\nСекторов на кластер: " << sectorPerCluster
					<< "\nБайтов на сектор: " << bytesPerSector << '\n' << std::endl;
	}
	else {
		std::cout << "Неправильный диск\n";
	}
	
}

