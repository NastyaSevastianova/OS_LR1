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
	DWORD sectorPerCluster, bytesPerSector, numOfFreeClusters, totalNumOfClusters, maxComponentLength, serialNumber, flags;


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
		GetVolumeInformationW(path, volName, volNameMaxLength, &serialNumber, &maxComponentLength, &flags, fileSystemName, fileSystemNameLength);
		std::wcout	<< "��� �����: " << selectDisk
					<< "\n�������� ����� : " << serialNumber
					<< "\n������������ ����� ����� ����� : " << maxComponentLength
					<< "\n�������� ������� : " << fileSystemName;

		//�����
		if (flags & FILE_CASE_SENSITIVE_SEARCH)
			std::cout << "\n��������� ��� ������������ ����� ������ � ������ ��������.";
		if (flags & FILE_CASE_PRESERVED_NAMES)
			std::cout << "\n��������� ��� ������������ ����������� ������� ���� ������ ��� ���������� ����� �� �����.";
		if (flags & FILE_UNICODE_ON_DISK)
			std::cout << "\n��������� ��� ������������ Unicode � ������ ������, ������� ���������� �� �����.";
		if (flags & FILE_PERSISTENT_ACLS)
			std::cout << "\n��������� ��� ��������� � ������������ ���������� ������� ���������� �������� (ACL).";
		if (flags & FILE_FILE_COMPRESSION)
			std::cout << "\n��������� ��� ������������ ������ �� ������ ������.";
		if (flags & FILE_VOLUME_QUOTAS)
			std::cout << "\n��������� ��� ������������ �������� �����.";
		if (flags & FILE_SUPPORTS_SPARSE_FILES)
			std::cout << "\n��������� ��� ������������ ����������� �����.";
		if (flags & FILE_SUPPORTS_REPARSE_POINTS)
			std::cout << "\n��������� ��� ������������ ����� ��������� ���������.";
		if (flags & FILE_SUPPORTS_REMOTE_STORAGE)
			std::cout << "\n��������� ��� ������������ ��������� ���������.";
		if (flags & FILE_RETURNS_CLEANUP_RESULT_INFO)
			std::cout << "\n��������� ��� ���������� ���������� � ���������� �������.";
		if (flags & FILE_SUPPORTS_POSIX_UNLINK_RENAME)
			std::cout << "\n��������� ��� ������������ �������������� posix unlink.";
		if (flags & FILE_VOLUME_IS_COMPRESSED)
			std::cout << "\n��������� ��� �������� ������ �����, �������� ����� DoubleSpace.";
		if (flags & FILE_SUPPORTS_OBJECT_IDS)
			std::cout << "\n��������� ��� ������������ �������������� ��������.";
		if (flags & FILE_SUPPORTS_ENCRYPTION)
			std::cout << "\n��������� ��� ������������ ������������� �������� ������� (EFS).";
		if (flags & FILE_NAMED_STREAMS)
			std::cout << "\n��������� ��� ������������ ����������� ������.";
		if (flags & FILE_READ_ONLY_VOLUME)
			std::cout << "\n��������� ��� �������� ������ ��� ������.";
		if (flags & FILE_SEQUENTIAL_WRITE_ONCE)
			std::cout << "\n��������� ��� ������������ ���� ���������������� ������.";
		if (flags & FILE_SUPPORTS_TRANSACTIONS)
			std::cout << "\n��������� ����� ������������ ����������.";
		if (flags & FILE_SUPPORTS_HARD_LINKS)
			std::cout << "\n��������� ��� ������������ ������� ������.";
		if (flags & FILE_SUPPORTS_EXTENDED_ATTRIBUTES)
			std::cout << "\n��������� ��� ������������ ����������� ��������.";
		if (flags & FILE_SUPPORTS_OPEN_BY_FILE_ID)
			std::cout << "\n�������� ������� ������������ �������� �� FileID.";
		if (flags & FILE_SUPPORTS_USN_JOURNAL)
			std::cout << "\n��������� ��� ������������ ������� ���������� � ����������� �������� (USN).";
		if (flags & FILE_SUPPORTS_INTEGRITY_STREAMS)
			std::cout << "\n��������� ��� ������������ ������ �����������.";
		if (flags & FILE_SUPPORTS_BLOCK_REFCOUNTING)
			std::cout << "\n��������� ��� ������������ ���������� ������������� ���������� ��������� ������� �� ����� ����.";
		if (flags & FILE_SUPPORTS_SPARSE_VDL)
			std::cout << "\n��������� ��� ������������ ����������� VDL.";
		if (flags & FILE_DAX_VOLUME)
			std::cout << "\n��������� ��� �������� ����� ������� ������� (DAX).";
		if (flags & FILE_SUPPORTS_GHOSTING)
			std::cout << "\n��������� ��� ������������ ������������";

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

