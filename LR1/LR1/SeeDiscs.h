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
	DWORD sectorPerCluster, bytesPerSector, numOfFreeClusters, totalNumOfClusters, maxComponentLength, serialNumber, flags;


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
		GetVolumeInformationW(path, volName, volNameMaxLength, &serialNumber, &maxComponentLength, &flags, fileSystemName, fileSystemNameLength);
		std::wcout	<< "Имя диска: " << selectDisk
					<< "\nСерийный номер : " << serialNumber
					<< "\nМаксимальная длина имени файла : " << maxComponentLength
					<< "\nФайловая система : " << fileSystemName;

		//Флаги
		if (flags & FILE_CASE_SENSITIVE_SEARCH)
			std::cout << "\nУказанный том поддерживает имена файлов с учетом регистра.";
		if (flags & FILE_CASE_PRESERVED_NAMES)
			std::cout << "\nУказанный том поддерживает сохраненный регистр имен файлов при размещении имени на диске.";
		if (flags & FILE_UNICODE_ON_DISK)
			std::cout << "\nУказанный том поддерживает Unicode в именах файлов, которые появляются на диске.";
		if (flags & FILE_PERSISTENT_ACLS)
			std::cout << "\nУказанный том сохраняет и обеспечивает соблюдение списков управления доступом (ACL).";
		if (flags & FILE_FILE_COMPRESSION)
			std::cout << "\nУказанный том поддерживает сжатие на основе файлов.";
		if (flags & FILE_VOLUME_QUOTAS)
			std::cout << "\nУказанный том поддерживает дисковые квоты.";
		if (flags & FILE_SUPPORTS_SPARSE_FILES)
			std::cout << "\nУказанный том поддерживает разреженные файлы.";
		if (flags & FILE_SUPPORTS_REPARSE_POINTS)
			std::cout << "\nУказанный том поддерживает точки повторной обработки.";
		if (flags & FILE_SUPPORTS_REMOTE_STORAGE)
			std::cout << "\nУказанный том поддерживает удаленное хранилище.";
		if (flags & FILE_RETURNS_CLEANUP_RESULT_INFO)
			std::cout << "\nУказанный том возвращает информацию о результате очистки.";
		if (flags & FILE_SUPPORTS_POSIX_UNLINK_RENAME)
			std::cout << "\nУказанный том поддерживает переименование posix unlink.";
		if (flags & FILE_VOLUME_IS_COMPRESSED)
			std::cout << "\nУказанный том является сжатым томом, например томом DoubleSpace.";
		if (flags & FILE_SUPPORTS_OBJECT_IDS)
			std::cout << "\nУказанный том поддерживает идентификаторы объектов.";
		if (flags & FILE_SUPPORTS_ENCRYPTION)
			std::cout << "\nУказанный том поддерживает зашифрованную файловую систему (EFS).";
		if (flags & FILE_NAMED_STREAMS)
			std::cout << "\nУказанный том поддерживает именованные потоки.";
		if (flags & FILE_READ_ONLY_VOLUME)
			std::cout << "\nУказанный том доступен только для чтения.";
		if (flags & FILE_SEQUENTIAL_WRITE_ONCE)
			std::cout << "\nУказанный том поддерживает одну последовательную запись.";
		if (flags & FILE_SUPPORTS_TRANSACTIONS)
			std::cout << "\nУказанный объем поддерживает транзакции.";
		if (flags & FILE_SUPPORTS_HARD_LINKS)
			std::cout << "\nУказанный том поддерживает жесткие ссылки.";
		if (flags & FILE_SUPPORTS_EXTENDED_ATTRIBUTES)
			std::cout << "\nУказанный том поддерживает расширенные атрибуты.";
		if (flags & FILE_SUPPORTS_OPEN_BY_FILE_ID)
			std::cout << "\nФайловая система поддерживает открытие по FileID.";
		if (flags & FILE_SUPPORTS_USN_JOURNAL)
			std::cout << "\nУказанный том поддерживает журналы обновлений с порядковыми номерами (USN).";
		if (flags & FILE_SUPPORTS_INTEGRITY_STREAMS)
			std::cout << "\nУказанный том поддерживает потоки целостности.";
		if (flags & FILE_SUPPORTS_BLOCK_REFCOUNTING)
			std::cout << "\nУказанный том поддерживает совместное использование логических кластеров файлами на одном томе.";
		if (flags & FILE_SUPPORTS_SPARSE_VDL)
			std::cout << "\nУказанный том поддерживает разреженный VDL.";
		if (flags & FILE_DAX_VOLUME)
			std::cout << "\nУказанный том является томом прямого доступа (DAX).";
		if (flags & FILE_SUPPORTS_GHOSTING)
			std::cout << "\nУказанный том поддерживает дублирование";

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

