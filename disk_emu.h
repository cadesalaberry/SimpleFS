int init_fresh_disk(char *filename, int block_size, int num_blocks);
int init_disk(char *filename, int block_size, int num_blocks);
int read_blocks(int start_address, int nblocks, void *buffer);
int write_blocks(int start_address, int nblocks, void *buffer);
int close_disk();
