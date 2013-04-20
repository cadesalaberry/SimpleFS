#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "sfs_api.h"

/* The maximum file name length. We assume that filenames can contain
 * upper-case letters and periods ('.') characters. Feel free to
 * change this if your implementation differs.
 */
#define MAX_FNAME_LENGTH 12   /* Assume at most 12 characters (8.3) */

/* The maximum number of files to attempt to open or create.  NOTE: we
 * do not _require_ that you support this many files. This is just to
 * test the behavior of your code.
 */
#define MAX_FD 100 

/* The maximum number of bytes we'll try to write to a file. If you
 * support much shorter or larger files for some reason, feel free to
 * reduce this value.
 */
#define MAX_BYTES 30000 /* Maximum file size I'll try to create */
#define MIN_BYTES 10000         /* Minimum file size */

/* Just a random test string.
*/
//static char test_str[] = "I am the new tester. I am the replacement for much maligned old tester!\n";

/* rand_name() - return a randomly-generated, but legal, file name.
 *
 * This function creates a filename of the form xxxxxxxx.xxx, where
 * each 'x' is a random upper-case letter (A-Z). Feel free to modify
 * this function if your implementation requires shorter filenames, or
 * supports longer or different file name conventions.
 * 
 * The return value is a pointer to the new string, which may be
 * released by a call to free() when you are done using the string.
 */

char *rand_name() 
{
    char fname[MAX_FNAME_LENGTH];
    int i;

    for (i = 0; i < MAX_FNAME_LENGTH; i++) {
        if (i != 8) {
            fname[i] = 'A' + (rand() % 26);
        }
        else {
            fname[i] = '.';
        }
    }
    fname[i] = '\0';
    return (strdup(fname));
}

/* The main testing program
*/
    int
main(int argc, char **argv)
{
    int i, j, k;
    int chunksize;
    char *buffer;
//    char fixedbuf[1024];
    int fds[MAX_FD];
    char *names[MAX_FD];
    int filesize[MAX_FD];
//    int nopen;                    /* Number of files simultaneously open */
//    int ncreate;                  /* Number of files created in directory */
    int error_count = 0;
    int tmp;

    mksfs(1);                     /* Initialize the file system. */

    /* First we open five files and attempt to write data to them.
    */
    for (i = 0; i < 5; i++) {
        names[i] = rand_name();
        fds[i] = sfs_open(names[i]);
        if (fds[i] < 0) {
            fprintf(stderr, "ERROR: creating first test file %s\n", names[i]);
            error_count++;
        }
        tmp = sfs_open(names[i]);
        if (tmp >= 0 && tmp != fds[i]) {
            fprintf(stderr, "ERROR: file %s was opened twice\n", names[i]);
            error_count++;
        }
        filesize[i] = (rand() % (MAX_BYTES-MIN_BYTES)) + MIN_BYTES;
    }

    for (i = 0; i < 5; i++) {
        for (j = i + 1; j < 2; j++) {
            if (fds[i] == fds[j]) {
                fprintf(stderr, "Warning: the file descriptors probably shouldn't be the same?\n");
            }
        }
    }

    printf("Five files created with zero length:\n");
    sfs_ls();
    printf("\n");

    for (i = 0; i < 5; i++) {
        for (j = 0; j < filesize[i]; j += chunksize) {
            if ((filesize[i] - j) < 10) {
                chunksize = filesize[i] - j;
            }
            else {
                chunksize = (rand() % (filesize[i] - j)) + 1;
            }

            if ((buffer = malloc(chunksize)) == NULL) {
                fprintf(stderr, "ABORT: Out of memory!\n");
                exit(-1);
            }
            for (k = 0; k < chunksize; k++) {
                buffer[k] = (char) (j+k);
            }
            sfs_write(fds[i], buffer, chunksize);
            free(buffer);
        }
    }

    for (i = 0; i < 5; i++)
      sfs_close(fds[i]);

    sfs_ls();

    for (i = 0; i < 5; i++)
      fds[i] = sfs_open(names[i]);

    printf("Reopened the files again.. the read/write pointers should be set to front\n");

    for (i = 0; i < 5; i++) {
        for (j = 0; j < filesize[i]; j += chunksize) {
            if ((filesize[i] - j) < 10) {
                chunksize = filesize[i] - j;
            }
            else {
                chunksize = (rand() % (filesize[i] - j)) + 1;
            }
            if ((buffer = malloc(chunksize)) == NULL) {
                fprintf(stderr, "ABORT: Out of memory!\n");
                exit(-1);
            }
            sfs_read(fds[i], buffer, chunksize);
            for (k = 0; k < chunksize; k++) {
                if (buffer[k] != (char)(j+k)) {
                    fprintf(stderr, "ERROR: data error at offset %d in file %s (%i,%i)\n",
                            j+k, names[i], buffer[k], (char)(j+k));
                    error_count++;
                    break;
                }
            }
            free(buffer);
        }
    }

    fprintf(stderr, "Test program exiting with %d errors\n", error_count);

    /**for (i = 0; i < MAX_FILE; i++) {
        char * file = FileAllocationTable_getFullFile(root.table[i], fat);
        printf("%s\n", file);
    }**/
    return (error_count);
}
