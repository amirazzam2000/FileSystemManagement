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

  - /find : checks if a file exists in the filesystem recursively and returns its size in case it exists.

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

    

  The reserved region contains the boot sector and BPB (BIOS Parameter Block). these blocks contain important information about the file system like the number FATs, the size of the cluster, or the number of entries in the root directory. 

  the root directory entry is located in the root directory region. each directory/file entry follows the same format as shown below: 
    ![image of a the File structure](https://user-images.githubusercontent.com/45884568/119271839-a12df700-bc03-11eb-9bfb-cea78efb2ac1.png)

  there is a limitation presented with this structure as it doesn't allow files with a name longer than 8 bytes (note: 3 bytes of the name are reserved for the extinction). However, this problem is solved by setting a flag indicating that, and the name is saved in another section. 

  the directory entries are consecutive, and the last entry has a 0x0 in the first character in the file's name. 
 
<h3>Explanation of the project</h3>
  This program checks and modifies the information of an Ext2, or a FAT16 file system. As explained before, you can show meta information about the file system, search for a file in the file system, or delete a specific file.

  this is the class diagam of the project:
  ![image class diagram](https://user-images.githubusercontent.com/45884568/119272505-8ad56a80-bc06-11eb-9f52-0b4207814148.png)

  the Directory manager is the class that controls the main functionality of the system. When you create an instance of this class you need to provide it with a path to the file system. Then, it will check that file system and create a FAT or an Ext2 instance dependently. 

  both files systems implement the abstract class "FileSystem."

  the file reader class stores an fstream object and returns a pointer to it so other classes can use it.

  the main functionalities implemented in this program are:  

  <h4>/info</h4>
      this functionality will read the metadata of both Ext and FAT file systems. To be able to store this data 
        I created a structure in both file system that holds the necessary data.
      in order to test the functionality of this option, I had to open the file system in a hex editor
        and then read the bytes in the offsets needed, then comparing the value with the 
        values I read using the program I was able to determine the correctness of the results.

  <h4>/find</h4>
        this functionality allows the user to recursively search for a file in the file system. 
        In order to do this I had to explore all the files in the root directory and all of it's sub-directories
        looking for the file. this functionality did not require any additional data structures.
        <br><br>
        In FAT16, I first go to the begging to the Root region and start reading the files in it following the file entry structure in FAT16.
        if the file had the directory flag set (the entry DIR_Attr is equal to 16), then I will move to the offset indicated by the entry DIR_FstClusLO.
        Moreover, as I make the function recursively I am able to run the same function but instead of having the root region as my starting offset 
        I add the first cluster I read as the offset.
        <br><br>
        For Ext2, the process was a little different as Ext works with inodes. At first I navigated to the root inode (inode 2) and 
        then I started looking at the blocks that this inode points to. in each of those blocks there are many file entries, 
        so I check each file and if a file type indicated by the entry is set to Directory then I recursively look in that 
        directory but this time feeding the function the directory inode as the starting inode (which is stored in the inode entry of the file)    
        <br><br>
        in order to test the functionality of this option I mounted the file system and checked the file tree. 
        After that I search for the different files in the file system. Moreover, I tried adding files inside some nested
        directories and look for them using the program.

  <h4>/delete</h4>
        in order to delete a file I had to first find it, after that depending on the file system I removed the file in a different method.
        <br><br>
        for FAT16 in order to remove a file I had to mark the entry by putting a 0xE5 at the first character of the name. 
        this will result in ignoring this entry next time you read the file system.
        <br><br>
        However, in EXT2 in order to delete a file I had to increase the size of the preceding file entry to include the file in it. 
        Moreover, if the file you want to delete was the first entry, then I had to copy the information of the following file into the 
        current file, then repeat the same process to delete the second file by increasing the record length of the current file.
        <br><br>        
        In order to test the functionality of this option, I tried deleting some files then mounting the file system to check that they are actually deleted.
        Moreover, in order to test the file deletion in Ext for files that used up more than one block, I used a file with lots of long-named-files 
        which resulted in the inode needing 3 blocks to store this data.
        Then I tried deleting those file to make sure the algorithm worked correctly.


<h3>Observed problems</h3>


<h3>temporal estimation</h3>

![image time consumed in the practice](https://user-images.githubusercontent.com/45884568/119540057-42948480-bd8d-11eb-8811-18e097a26eea.png)

the first phase took me the longest out of all of them, but that is because it involved the designing of the classes and the initial set up of the project.
After everything was set up I solving the phases didn't take much time. 
Moreover, phase 2 was the most challenging even if it wasn't the most time consuming. This is because I had to spend some time understanding 
how each of the file systems worked, and thus how I should approach the search process in each.

<h3>Explanation and assessment of GIT</h3>

I divided the git into 3 main branches: Main, FAT, and Ext. The FAT and Ext branches held the currently in development files for each practice. 
once I was done with each I created a pull request to update the main branch. Moreover, for each phase I created a branch to hold the 
final files of that specific phase.

<h3>Conclusions</h3>
