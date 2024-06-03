#include <string.h>
#include "inode.h"
#include "block.h"
#include "dir.h"
#include <stdlib.h>
#include "pack.h"
#include <stdio.h>

void mkfs()
{

    struct inode *inode_num = ialloc();

    int block_num = alloc();

    struct inode *root_inode = iget(inode_num->inode_num);

    root_inode->flags = 2;
    root_inode->size = 64;
    root_inode->block_ptr[0] = block_num;
    iput(root_inode);

    unsigned char block[BLOCK_SIZE];

    int offset = 0;

    write_u16(block + offset, inode_num->inode_num);
    offset += DIRECTORY_NAME_OFFSET;
    strcpy((char *)(block + offset), ".");
    offset += DIR_ENTRY_SIZE;
    write_u16(block + offset, inode_num->inode_num);
    offset += DIRECTORY_NAME_OFFSET;
    strcpy((char *)(block + offset), "..");
    offset += DIR_ENTRY_SIZE;

    bwrite(block_num, block);

    iput(root_inode);
}

struct directory *directory_open(int inode_num)
{
    struct inode *dir_inode = iget(inode_num);
    if (dir_inode == NULL)
    {
        return NULL; // Error: Failed to get the inode
    }

    struct directory *dir = malloc(sizeof(struct directory));

    dir->offset = 0;
    dir->inode = dir_inode;

    return dir;
}

int directory_get(struct directory *dir, struct directory_entry *ent)
{
    if (dir->offset >= dir->inode->size)
    {
        return -1; // Off the end of the directory
    }

    int data_block_index = dir->offset / BLOCK_SIZE;
    int data_block_num = dir->inode->block_ptr[data_block_index];

    unsigned char block[BLOCK_SIZE];
    bread(data_block_num, block);

    int offset_in_block = dir->offset % BLOCK_SIZE;

    ent->inode_num = read_u16(block + offset_in_block);
    strcpy(ent->name, (char *)(block + offset_in_block + 2));

    return 0;
}

void directory_close(struct directory *d)
{
    iput(d->inode);
    free(d);
}

struct inode *namei(char *path)
{
    struct inode *root = iget(ROOT_INODE_NUM);

    if (strcmp(path, "/") == 0)
    {

        return root;
    }
    return NULL;
}

// char *token = strtok(path, "/");

// char *new_token = "hello";

//     while ((token = strtok(NULL, "/")) != NULL)
//     {

//         new_token= token;

//     }

//     if (strcmp(new_token, "hello" )== 0){
//         return NULL;
//     }
//     else{
//         return iget(ROOT_INODE_NUM);
//     }
// }

int directory_make(char *path)
{

    char dirname[1024];
    get_dirname(path, dirname);

    struct inode *parent_inode = namei(dirname);
    if (parent_inode == NULL)
    {
        return -1; // Error: Failed to get the parent directory inode
    }
    struct inode *new_idirectory = ialloc();

    int data_block = alloc();
    unsigned char new_block[BLOCK_SIZE];

    int offset = 0;

    write_u16(new_block + offset, new_idirectory->inode_num);
    offset += DIRECTORY_NAME_OFFSET;
    strcpy((char *)(new_block + offset), ".");
    offset += DIR_ENTRY_SIZE;
    write_u16(new_block + offset, parent_inode->inode_num);
    offset += DIRECTORY_NAME_OFFSET;
    strcpy((char *)(new_block + offset), "..");
    offset += DIR_ENTRY_SIZE;



    new_idirectory->flags = 2; 
    new_idirectory->size = 64; 
    new_idirectory->block_ptr[0] = data_block; 
    
    bwrite(data_block, new_block);
   
    int parent_block_index = parent_inode-> size/BLOCK_SIZE;
    int parent_block_num = parent_inode->block_ptr[parent_block_index];

    unsigned char *parent_block = bread(parent_block_num, new_block);
    

    offset = parent_block_index * DIR_ENTRY_SIZE;

    write_u16(parent_block + offset, new_idirectory->inode_num);
    // write the new inode number 
    offset += DIRECTORY_NAME_OFFSET;
    strcpy((char *)(parent_block + offset), get_basename(path, NULL));
    //write the inode name 

    bwrite(parent_block_num, parent_block);

    parent_inode->size += DIR_ENTRY_SIZE;



    iput(new_idirectory);
    iput(parent_inode); 
    return 0 ; 
}   

// Inspired by the `dirname` and `basename` Unix utilities
//
// But doesn't handle a trailing '/' on the path correctly.
//
// So don't do that.

char *get_dirname(const char *path, char *dirname)
{
    strcpy(dirname, path);

    char *p = strrchr(dirname, '/');

    if (p == NULL)
    {
        strcpy(dirname, ".");
        return dirname;
    }

    if (p == dirname) // Last slash is the root /
        *(p + 1) = '\0';

    else
        *p = '\0'; // Last slash is not the root /

    return dirname;
}

char *get_basename(const char *path, char *basename)
{
    if (strcmp(path, "/") == 0)
    {
        strcpy(basename, path);
        return basename;
    }

    const char *p = strrchr(path, '/');

    if (p == NULL)
        p = path; // No slash in name, start at beginning
    else
        p++; // Start just after slash

    strcpy(basename, p);

    return basename;
}


