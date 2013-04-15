#define BLOCK_SIZE  256
#define FAT_SIZE 30
#define FDT_SIZE 20

#define FILENAME_LENGTH 64

typedef struct FileDescriptor {
	int 	id;
	char	name[FILENAME_LENGTH];
	int 	FATindex;
	int 	wPtr;
	int 	rPtr;
} FileDescriptor;

typedef struct FileAllocation {
	int 	id;
	int 	nxt;
	int 	index;
} FileAllocation;

///Global variables
FileDescriptor	fdt[FDT_SIZE];
FileAllocation	fat[FAT_SIZE];

int fatID = 0, fdtID = 0;

void FileAllocationTable_init() {

	for (fatID = 0; fatID < FAT_SIZE; fatID++) {

		fat[fatID].id 		= fatID;
		fat[fatID].nxt		= -1;
		fat[fatID].index	= -1;
	}
}

int FileAllocationTable_get_free() {

	for (fatID = 0; fatID < FAT_SIZE; fatID++) {

		if (fat[fatID].index == -1) {
			return fatID;
		}
	}
	return -1;
}

void FileDescriptorTable_init() {

	for(fdtID = 0; fdtID < FDT_SIZE; fdtID++) {
		fdt[fdtID].id 		= fdtID;
		fdt[fdtID].name[0] 	= '\0';
		fdt[fdtID].wPtr 	= -1;
		fdt[fdtID].rPtr 	= -1;
		fdt[fdtID].FATindex = -1;
	}
}

int FileDescriptorTable_get_free() {

	for (fdtID = 0; fdtID < FDT_SIZE; fdtID++) {

		if (fdt[fdtID].FATindex == -1) {
			return fdtID;
		}
	}
	return -1;
}