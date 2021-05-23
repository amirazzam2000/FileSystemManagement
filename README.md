# File System Management

<h2>Installation and Execution</h2>
  to run this you need to clone the directory and then run this inside the cloned directory:
  
``` bash
    cd ./src
    make
```
  then in order to execute the code you have to use the command ./shooter inside the src directory.
  the command has the format:

```
  ./shooter <option> <path to file system> [<filename>]
```

  possible options : 
  
  - /info : displays info about the file system.

```
  ./shooter /info <path to file system> 
```

  - /find : checks if a file exists in the filesystem recursively and returns its size incase it exists.

```
  ./shooter /find <path to file system> <filename>
```

  - /delete : checks if a file exists in the filesystem recursively and deletes it if it's found.

```
  ./shooter /delete <path to file system> <filename>
```

<h2>Explanation of file systems</h2>

this program only supports <i>EXT 2</i> and <i>FAT 16</i> file systems.

<h3>Ext 2</h3>
  Ext2 (the second extended file system) is a file system for the Linux kernel. The data in this file system is divided into blocks, these blocks are then grouped into groups. 
  The main structure that stores the files information and entries is known as inode (node index). each inode contains pointers to the blocks of the file system that stores the data of the file or directory. 

  
  The blocks and groups are structured as shown in the image below:
  
  ![image of Ext 2 sample groups/blocks structure](https://user-images.githubusercontent.com/45884568/119158873-f8429900-ba56-11eb-9711-598e5b0e817e.png)

  the most important block is the superblock which is located in the first block of group 0 after the boot records. This block always starts on the offset 1024.

  in the superblock you can find general information about the filesystem. For instance, you can find block sizes, total number of blocks, the number of inodes, or the number of  the first inode. 

  The Inode table contains inode entries, each inode entry is 124 bytes. each of these entries contains the information of a file, directory, or symbolic link that this inode points to. these are the information stored in each inode:

  ![image of the information stored in an inode](https://user-images.githubusercontent.com/45884568/119240304-fa881e80-bb4e-11eb-8720-36cef4d181af.png)

  if the inode points to a directory, each directory entry will follow the following structure:
  
  ![image of a directory entry](https://user-images.githubusercontent.com/45884568/119240323-1986b080-bb4f-11eb-9725-964860ba7519.png)

  each block stores as many sequential directory entries as it can fit. If the entries don't fit in one block, then the reset of the entries will be stored in another block which you can locate using the inode representing this directory.




<h3>FAT 16</h3>
  FAT (File Allocation Table) is a type of legacy file systems. FAT offers good performance but isn't very scalable and reliable. The 16 in the name refers to the number of bits used to identify each allocation unit (known as cluster).

  Fat file systems are divided into 4 main regions as shown in the figure below:
    ![image of a the FAT regions](https://user-images.githubusercontent.com/45884568/119271860-b571f400-bc03-11eb-9507-5274ae3de8f6.png)

    

  The reserved region contains the boot sector and BPB (BIOS Parameter Block). these blocks contain important information about he file system like the number FATs, the size of the cluster, or the number of entries in the root directory. 

  the root directory entry is located in the root directory region. each directory/file entry follows the same format as shown below: 
    ![image of a the File structure](https://user-images.githubusercontent.com/45884568/119271839-a12df700-bc03-11eb-9bfb-cea78efb2ac1.png)

  there is a limitation presented with this structure as it doesn't allow files with a name longer than 8 bytes (note: 3 bytes of the name are reserved for the extinction). However, this problem is solved by setting a flag indicating that and the name is saved in another section. 

  the directory entries are consecutive, and the last entry has a 0x0 in the first character in the file's name. 
  

<h3>Explination of the project</h3>
  This program allowes you to check and modify the information of an Ext2 or a FAT16 file system. As explained before, you can show meta information about the file system, search for a file in the file system, or delete a specific file.

  this is the class diagam of the project:
  ![image class diagram](https://user-images.githubusercontent.com/45884568/119272505-8ad56a80-bc06-11eb-9f52-0b4207814148.png)


  

  bellow you will find a detailed explination of the functionalities:

  <h4>/info</h4>
  
  <h4>/find</h4>

  <h4>/delete</h4>
  
(b) Design: explanation of how you designed and structured.
(c) Data structures used and their justification.
(d) Tests performed.
(e) Observed problems and how they have been solved.
(f) Temporal estimation.
4. Explanation and assessment of the GIT.
5. General conclusions.
