
 #include "display.hpp"

int main(int argc, char *argv[])
{
        
// Copy a file   
YY: 
      initialize();//to initalise the linked list used in ;library and playlist
      //cout<<head->path;
     //   getch();
       char p;
        head=_push(head);       
        command_line_init();
        
        
      HIT:
     // cout<<"do u want to Enter the path of the music folder manually  : ( y or n) :";
    // cin>>p;
    p='y';
      switch (p)
      {
         case 'y':      
              {  
                   cout<<"Enter the path of the music folder or drive :";
                   cin>>head->path;
                           XX:                   // to check the path given is a valid path
                              if(_chdir(head->path)==-1)
                                 {
                                   clrscr();
                                   cout<<"The drive does not exist . Please enter the correct drive label :  ";
                                   cin>>head->path;
                                    goto XX;
                                 }
      
      
                 open_directory(); // to browse the subfolders automatically and populate the library
              if(start->next->etr_num==-1)
                 {
                   cout<<"\n There is no mp3 file in the specified path ";
                   getch();
                   clrscr();
                   free(head);
                   free(end);
                   free(start);
                    goto YY;
                   }        
             
                tag_disp_all();// actually used to count the no. of entries in the library
                 cout<<"closed successully";
                 break;
                
                 }
     case 'n':// this whole part was written to search the whole hard disk for mp3 file but was dropped as it had a stack overflow error it would be made available in the next version
         {
          char path[5];
    
      for(int i=4;i<10;i++)
    {
       if (_chdrive(i) == 0)
    {
                  _getcwd (path,5);
          cout<<"Changed to drive :"<<path<<"\n";
           head->path=path;
                                              
                              if(_chdir(head->path)!=-1)
                                 {
                                     open_directory();
                                     tag_disp_all();
                                 }
      
      
                 
          

       }
 
       }
    }
     default:
             goto HIT;
             break;
     }
     
    content_disp(); // to go to the user interface operations
    clrscr();
    gotoxy(2,27);
    clrscr();
    cout<<"Do u wanna store the libraray : ( y or n) :";
    cin >>p;
    switch(p)
    {
    case 'y':
         write_to_file();
         break;
    case 'n':
           cout<<"hav a good time ......";
           break;
    default:
            cout<<"hav a good time folks.....";
            break;
     }
  
    cout<<"finished ";
    getch();
         system("PAUSE");
       return EXIT_SUCCESS;
      //  getch();
    //head->path="E:\\Songs\\Tamil";
       
}
