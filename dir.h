#ifndef DIR_H

#define FLAG_ISDIRECTORY 2
#define DIRECTORY_NAME_OFFSET 2
#define DIR_ENTRY_SIZE 32
struct directory {
    struct inode *inode;
    unsigned int offset;
};

struct directory_entry {
    unsigned int inode_num;
    char name[16];
};

void mkfs(void); 
struct directory *directory_open(int inode_num);
int directory_get(struct directory *dir, struct directory_entry *ent);
void directory_close(struct directory *d);


struct inode *namei(char *path);
int directory_make(char *path);
char *get_dirname(const char *path, char *dirname);
char *get_basename(const char *path, char *basename);





extern struct directory dir; 
extern int dir_num;



#endif