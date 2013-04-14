#include "disk_emu.h"

#define BLOCK_SIZE  256
#define BLOCK_NUMBER 30
#define MAX_FILES 20

#define FREE -2
#define TAKEN -3

#define OPEN -4
#define CLOSE -5
#define LARGE 35000

#define MAX_FNAME_LENGTH 12

typedef struct FileDescriptorTable {
	char filename[32];
	int fat_index;
	void * writePtr;
	void * readPtr;
	int open_file;
} FileDescriptorTable;


typedef struct RootDirectoryTable {
	char filename[32];
	size_t size;
	void * fat_root;
	time_t created;
	int flag;
	int file_ID;
	int write_memo;
} RootDirectoryTable;


typedef struct FileAllocationTable {
	size_t nbBlock;
	void * ptr;
	size_t remaining_size;
} FileAllocationTable;


///Global variables
FileDescriptorTable fdt[MAX_FILES];
RootDirectoryTable rdt[MAX_FILES];
FileAllocationTable fat[BLOCK_NUMBER];
void * fbl[BLOCK_NUMBER];
int i, j, k;

void mksfs(int fresh);
void sfs_ls(void);
int sfs_open(char *name);
int sfs_close(int fileID);
int sfs_write(int fileID, char *buf, int length);
int sfs_read(int fileID, char *buf, int length);


/**
 * Creates the file system.
 */
 void mksfs(int fresh) {

 	if(fresh){

        // Initializes root directory table
 		for(i=0;i<MAX_FILES;i++){
 			rdt[i].filename[0] = '\0';
 			rdt[i].size = 0;
 			rdt[i].created = 0;
            rdt[i].fat_root = NULL;
            rdt[i].flag = -1;
            rdt[i].file_ID = -1;
 		}

        // Initializes file allocation table
 		for(j=0;j<BLOCK_NUMBER;j++){
 			fat[j].nbBlock = j+2;
 			fat[j].ptr = NULL;
 			fat[j].remaining_size = BLOCK_SIZE;
 		}

        // Initializes file descriptor table
 		for(k=0;k<MAX_FILES;k++){
 			fdt[k].filename[0] = '\0';
 			fdt[k].fat_index = -1;
 			fdt[k].readPtr = 0;
 			fdt[k].writePtr = NULL;
 			fdt[k].open_file = CLOSE;
 		}

        // Makes a new disk
 		init_fresh_disk("my_disk", BLOCK_SIZE, BLOCK_NUMBER);

 		write_blocks(0, 1, rdt);
 		write_blocks(1, 1, fat);
 	}

 	else {
 		init_disk("my_disk", BLOCK_SIZE, BLOCK_NUMBER);
 		read_blocks(0, 1, &rdt);
 		read_blocks(1, 1, &fat);
 	}
 }

/**
 * Lists files in the root directory.
 */ 
 void sfs_ls(void) {

	// List the contents of the directory in details, i.e.,
	// including the information stored in the file control blocks.

 }

/**
 * Opens the given file.
 */
 int sfs_open(char * name) {

	// Opens a file and returns the index on the file descriptor table.
	// If file does not exist, create the new file and set size to 0.
 	return 0;
 }

/**
 * Closes the given file.
 */
 int sfs_close(int fileID) {

	// Closes a file, i.e., removes the
	// entry from the open file descriptor table.
 	return 0;
 }


/**
 * Writes buffered characters onto disk.
 */
 int sfs_write(int fileID, char * buf, int length) {

	// Writes length bytes of buffered data in buf onto the open file,
	// starting from the current file pointer.
	// This in effect increases the size of the file by “length” bytes.
 	return 0;
 }

/**
 * Reads characters from disk into buffer.
 */
 int sfs_read(int fileID, char * buf, int length) {

 	return 0;
 }
