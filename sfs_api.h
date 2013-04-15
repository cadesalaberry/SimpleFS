#include "disk_emu.h"
#include "sfs_header.h"

int 	i, j, k;

void	mksfs(int fresh);
void	sfs_ls(void);
int 	sfs_open(char * name);
int 	sfs_close(int fileID);
int 	sfs_write(int fileID, char * buf, int length);
int 	sfs_read(int fileID, char * buf, int length);


/**
 * Creates the file system.
 */
 void mksfs(int fresh) {

 	if(fresh){

        // Initializes file descriptor table
 		FileDescriptorTable_init();

        // Initializes file allocation table
 		FileAllocationTable_init();

        // Makes a new disk
 		init_fresh_disk("my_disk", BLOCK_SIZE, FAT_SIZE);
 		write_blocks(0, 1, fdt);
 		write_blocks(1, 1, fat);
 	}

 	else {
 		init_disk("my_disk", BLOCK_SIZE, FAT_SIZE);
 		read_blocks(0, 1, &fdt);
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

	/*Create:

    1. Allocate and initialize an FAT node.
    2. Write the mapping between the FAT node and file name in the root directory.
    3. Write this information to disk.
    4. No disk data block allocated. File size is set to 0.
	*/
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
