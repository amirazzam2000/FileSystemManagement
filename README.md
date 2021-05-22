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

  - /find : checks if a file exists in the filesystem recursively and returns its size incase it exisits.

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
  Ext2 (the second extended file system) is a file system for the linux kernel. The data in this file system is devided into blocks, these blocks are then grouped into groups. 
  The main structure that stores the files informations and enteries is known as inode (node index)
  
  
  The bloks and groups are structured as shown in the image below:
  
  ![image of Ext 2 sample groups/blocks structure](https://user-images.githubusercontent.com/45884568/119158873-f8429900-ba56-11eb-9711-598e5b0e817e.png)

  the most important block is the superblock which is located in the first block of group 0 after the boot records. This block always starts on the offset 1024.
  
   in the superblock you can find general information about the filesystem. For instance, you can find block sizes, total number of blocks, the number of inodes, the number of  the first inode ...etc.
  
<h3>FAT 16</h3>
  

3. Explanation of the practice
(a) Requirements: what to do.
(b) Design: explanation of how you designed and structured.
(c) Data structures used and their justification.
(d) Tests performed.
(e) Observed problems and how they have been solved.
(f) Temporal estimation.
4. Explanation and assessment of the GIT.
5. General conclusions.
