# project5-Starting-the-File-System
# image.c 

# image_open 

* this opens an image file or creates it if it does not exist  and truncates it 

# image close 
* closes the image file 


# block.c 

# bread 
* this takes a pointer to a buffer it loads an image to that buffer then returns that buffer 

# bwrite 
* takes a pointer to a buffer calculates the offset in memory using the block size and block num and the writes the data from the buffer to that spot 



# free.c 

# find_low_clear_bit() 
* finds the lowest bit and returns that value this is a helper function for find free 



# set_free()
* set a specific bit to the value in set (0 or 1)

# find free() 
*find a 0 bit and return its index 



## building

* Type make into the command line while you are in the same directory that the file is in and the make file will be created with the same name as the c file.

## files

* image.c 
* image.h 
* block.c 
* block.h 
* ctest.c 
* ctest.h 
* testfs.c 
* testfs.h

* free.c
* free.h
* inode.c
* inode.h 


## data

* there is buffer that stores temporary dat to be transferred, a file to be read and a file to be written to. 



## functions

* image_open 
* this opens an image file or creates it if it does not exist  and truncates it 

* image close 
* closes the image file

* bread 
* this takes a pointer to a buffer it loads an image to that buffer then returns that buffer 

* bwrite 
* takes a pointer to a buffer calculates the offset in memory using the block size and block num and the writes the data from the buffer to that spot 

* set_free()
* set a specific bit to the value in set (0 or 1)

* find free() 
*find a 0 bit and return its index 



## notes

* could not figure out alloc and ialloc will go to office hours to hopefully figure it out. # project-7-OS
# project-8-os
# project-9-cs
