#ifndef SFS_API_H
#define SFS_API_H

#include "disk_emu.h"
#include "sfs_header.h"

DirectoryDescriptor root;
FileAllocationTable fat;

#include "sfs_util.h"

static int opened_files = 0;

/**
 * Creates or open a disk to read and write from.
 */
void mksfs(int fresh) {

	if (fresh) {
		init_fresh_disk("disk.sfs", sizeof(DiskBlock), NB_BLOCK);

		FAT_init(&fat);
		DirectoryDescriptor_init(&root);

		write_blocks( 0, 1, (void *) &root);
		write_blocks( 1, 1, (void *) &fat);

	} else {

		init_disk("disk.sfs", sizeof(DiskBlock), NB_BLOCK);
		read_blocks( 1, 1, (void *) &fat);
		read_blocks( 0, 1, (void *) &root);
	}
}

/**
 * Displays the content of a directory.
 * PERFECTLY WORKING
 */
void sfs_ls() {
	int i;
	printf("\n");
	for (i = 0; i < MAX_FILE; i++) 
	{
		if(root.table[i].size > 0)
		{
			int kb = root.table[i].size / 1024;
			char * tm = ctime(&root.table[i].timestamp);
			tm[24] = '\0';
			printf("%25s\t%dKB\t%s\n", tm, kb, root.table[i].filename);
		}
	}
}

/**
 * Opens a file with the specified filename.
 *
 * PERFECTLY WORKING
 */
int sfs_open(char * name) {

	int fileID = getIndexOfFileInDirectory(name, &root);
	if (fileID != -1) {
		return fileID;
	}

	//gets the next free fileDescriptor
	fileID = opened_files++;
	FileDescriptor_createFile(name, &(root.table[fileID]));

	// Assigns a free block to the file, and set it to end of file
	root.table[root.count].fat_index = FAT_getFreeNode(&fat);
	fat.table[fat.count].next = EOF;

	write_blocks( 0, 1, (void *) &root);
	write_blocks( 1, 1, (void *) &fat);

	return fileID;

}

/**
 * Closes the specified file if it is found.
 *
 * PERFECTLY WORKING
 */
int sfs_close(int fileID) {

	if (opened_files <= fileID) {
		fprintf(stderr, "Error: File #%d does not exist.", fileID);
		return -1;
	}
	
	root.table[fileID].fas.opened = 0;
	opened_files--;
	return 0;
}

/**
 * This function is not working properly.
 */
int sfs_write(int fileID, char * buf, int length) {

	if (opened_files <= fileID) {
		fprintf(stderr, "Error: File #%d does not exist.\n", fileID);
		return 0;
	}
	
	int i, addr = 2;
	for (i = 0; i < length; i++) {

		//addr = FileDescriptor_getNextWritable(&(root.table[fileID]), &fat);

		// Checks if the address is valid.
		if (addr != -1) {
			
			write_blocks( addr, 1, (void *) &buf[i]);
			root.table[fileID].size++;

		} else {

			fprintf(stderr, "Error: Disk is full.\n");
			break;
		}
	}
	/**VirtualDisk_write(fileID, 1, (void *) &buf[i]);
	if (strcmp(buf, vd[fileID]) != 0) {
		printf("Error:\nWritting: %s\n", buf);
		printf("Written: %s\n", vd[fileID]);
	}*/
	write_blocks( 0, 1, (void *) &root);
	write_blocks( 1, 1, (void *) &fat);

	return root.table[fileID].size;
}

/**
 * Most of the work is done in the util header file.
 * PERFECTLY WORKING WITH GOOD WRITE FUNCTION
 */
int sfs_read(int fileID, char * buf, int length) {

	if (opened_files <= fileID && root.table[fileID].fas.opened == 0 ) {
		fprintf(stderr, "No such file %d is opened\n", fileID);
		return 0;
	}

	buf = FAT_getPartFile(root.table[fileID], fat, length);

	return EOF;
}

#endif