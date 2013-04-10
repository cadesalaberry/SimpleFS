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

}

/**
 * Closes the given file.
 */
int sfs_close(int fileID) {
	
	// Closes a file, i.e., removes the
	// entry from the open file descriptor table.

}


/**
 * Writes buffered characters onto disk.
 */
int sfs_write(int fileID, char * buf, int length) {
	
	// Writes length bytes of buffered data in buf onto the open file,
	// starting from the current file pointer.
	// This in effect increases the size of the file by “length” bytes.

}

/**
 * Reads characters from disk into buffer.
 */
int sfs_read(int fileID, char * buf, int length) {
	
}
