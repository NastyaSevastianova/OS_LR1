#include <iostream>
#include <windows.h>
#include <fileapi.h>

void SeeDiscs() {
	setlocale(LC_ALL, "Russian");

	int pos = 0;
	DWORD disc = GetLogicalDrives();

	wchar_t path[] = L"A:\\";

	//�������� ��� ����� ������

	const DWORD volNameMaxLength = 50, fileSystemNameLength = 10;

	UINT driveType;
	wchar_t volName[volNameMaxLength], fileSystemName[fileSystemNameLength];
	DWORD sectorPerCluster, bytesPerSector, numOfFreeClusters, totalNumOfClusters, maxComponentLength, serialNumber;


	for (DWORD i = 1; pos < (sizeof(DWORD) * 8); i <<= 1, ++pos) {
		if(disc & i) {
			std::cout << "Disc " << char('A' + pos) << "\n";
		}
	}

	std::cout << "������� ���� (�������� C): ";
	wchar_t selectDisk = 'c';
	std::wcin >> selectDisk;
	selectDisk = towupper(selectDisk);
	std::cin.ignore(INT_MAX, '\n');

	if (selectDisk >= 'A' && selectDisk <= 'Z' && disc & (1 << (selectDisk - 'A'))) {

		path[0] = selectDisk;
		
		//��� �����
		driveType = GetDriveType(path);
		switch (driveType) {
		case 0:
			std::cout << "\n�������������\n";
			break;
		case DRIVE_REMOVABLE:
			std::cout << "\n������� ����\n";
			break;
		case DRIVE_FIXED:
			std::cout << "\n������� ����\n";
			break;
		case DRIVE_REMOTE:
			std::cout << "\n������� ����\n";
			break;
		case DRIVE_CDROM:
			std::cout << "\nCD-ROM\n";
			break;
		case DRIVE_RAMDISK:
			std::cout << "\nRAM-����\n";
			break;
		default:
			std::cout << "\n���-�� �����������...\n";
		}

		//���
		GetVolumeInformationW(path, volName, volNameMaxLength, &serialNumber, &maxComponentLength, NULL, fileSystemName, fileSystemNameLength);
		std::wcout	<< "Drive name: " << selectDisk
					<< "\nSerial number: " << serialNumber
					<< "\nMax file name length: " << maxComponentLength
					<< "\nFile system: " << fileSystemName;

		//������������
		GetDiskFreeSpace(path, &sectorPerCluster, &bytesPerSector, &numOfFreeClusters, &totalNumOfClusters);
		std::cout	<< "\n����� ���������� ���������: " << totalNumOfClusters
					<< "\n���������� ��������� ���������: " << numOfFreeClusters
					<< "\n�������� �� �������: " << sectorPerCluster
					<< "\n������ �� ������: " << bytesPerSector << '\n' << std::endl;
	}
	else {
		std::cout << "������������ ����\n";
	}
	
}

