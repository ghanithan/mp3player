# mp3player

This is a MP3 library manager with playlist editor and playback options written purely in C++ during our college (pre-final year) in 2010.

***This is uploaded here to preserve the source code and as reference material to others. If anyone is interested in learning to build a console application in C++ or to understand how media files are handled or to understand how linked list can be used in an application, please feel free to use this resource.***

***We are not looking to maintain this repository.***

Even thought this application was build a decade earlier, it still works in the current windows 10 environment without any rebuild (This is insane !!). We have preserved the decade old executable in the repository.

Note: The song in the player needs to be played using the 'space bar' before using the other playback controls like next and previous. If not the application breaks. We could have just made the first song in the playlist play but we didn't. Wondering why and if there was any roadblock in implementing it. We wish we had a time machine.

## THE FLOW OF CONTROL:
- The user first is asked to select the Drive from which the library is created .
- A playlist is created from the library by the user
- Then  the entries in the playlist can be played by the user 
- The library can be sorted based on the fields in their tag  .
- The MP3 DECODER used is the inbuild music player in all the windows OS (Media Control Interface) .
![Control Flow](/doc/pics/controlFlow.png)

## The Basic Architecture Of The Software:
- The system consists of the three major modules 1) Library ,2) playlist editor and 3)playback module.
- The modules are connected like this:  library -> playlist editor -> playback .
- The library is the base , the other 2 modules are its derivatives.i.e., the  playlist editor depends on library for its operations and the playback depends on the playlist for its operations.
- The linked list used for the library and the playlist are interlined .i.e the playlist creates its list from the library linkedlist .
![Software Arch](/doc/pics/arch.png)

## Modules and thier hierarchy:
![modules](/doc/pics/modules.png)

## Screenshots:

### 1. The Initial screen prompting user for the path of the drive or folder containing music 
![Screenshot 1](/doc/pics/1.png)


### 2. The library is being displayed after being populated by scaning the drive 
![Screenshot 2](/doc/pics/2.png)

### 3. The library is being scrolled to the right to see the remaining fields. It can be scrolled up , down , left and right within that pane. We have used buffer to display the particular section of the library. 
![Screenshot 3](/doc/pics/3.png)

### 4. The playlist has been created and one of its entries is being played (the one that is highlighted in green ). The green cursor shows which entry is being played.
![Screenshot 4](/doc/pics/4.png)

### 5. The library has been sorted by its TITLE field (by pressing ‘t’ in when in the library pane )and its clearly visible.
![Screenshot 5](/doc/pics/5.png)

### 6. The playlist is being filled and it has no limitations in number of entries that it can hold , it can be browsed using then arrow keys  and page up and page down.
![Screenshot 6](/doc/pics/6.png)

### 7. The playlist is being saved in the name specified by the user. The playlist is save in the directory or drive that was given as the input by the user in the start
![Screenshot 7](/doc/pics/7.png)
