 
 #include"wintry2.hpp"
 #include<time.h>


 //Bitrates, assuming MPEG 1 Audio Layer 3
const int bitrates[16] = {
         0,  32000,  40000,  48000,  56000,  64000,  80000,   96000,
    112000, 128000, 160000, 192000, 224000, 256000, 320000,       0
  };

int time_pre=time(NULL)+100000;

int reverse(int i)
{
    int toReturn = 0;
    toReturn |= ((i & 0x000000FF) << 24);
    toReturn |= ((i & 0x0000FF00) << 8);
    toReturn |= ((i & 0x00FF0000) >> 8);
    toReturn |= ((i & 0xFF000000) >> 24);
    return toReturn;
}

/*In short, data in ID3v2 tags are stored as
 *"syncsafe integers". This is so the tag info
 *isn't mistaken for audio data, and attempted to
 *be "played"*/
int syncsafe(int i)
{
 int toReturn = 0;
 toReturn |= ((i & 0x7F000000) >> 24);
 toReturn |= ((i & 0x007F0000) >>  9);
 toReturn |= ((i & 0x00007F00) <<  6);
 toReturn |= ((i & 0x0000007F) << 21);
 return toReturn;     
}

//How much room does ID3 version 1 tag info
//take up at the end of this file (if any)?
int id3v1size(ifstream& infile)
{
   streampos savePos = infile.tellg(); 

   //set pointer to 128 bytes from end of file 
   infile.seekg(0, ios::end);
   streampos length = infile.tellg() - (streampos)128;
   infile.seekg(length);

   int size;
   char buffer[3] = {0};
   infile.read(buffer, 3);
   if( buffer[0] == 'T' && buffer[1] == 'A' && buffer[2] == 'G' )
     size = 128; //found tag data
   else
     size = 0; //nothing there

   infile.seekg(savePos);

   return size;

}

//how much room does ID3 version 2 tag info
//take up at the beginning of this file (if any)
int id3v2size(ifstream& infile)
{
   streampos savePos = infile.tellg(); 
   infile.seekg(0, ios::beg);

   char buffer[6] = {0};
   infile.read(buffer, 6);
   if( buffer[0] != 'I' || buffer[1] != 'D' || buffer[2] != '3' )
   {   
       //no tag data
       infile.seekg(savePos);
       return 0;
   }

   int size = 0;
   infile.read(reinterpret_cast<char*>(&size), sizeof(size));
   size = syncsafe(size);

   infile.seekg(savePos);
   //"size" doesn't include the 10 byte ID3v2 header
   return size + 10;
}
/*To determine the duration of the mp3file
*calculater from the bitrate and the file size
*/
int duration(char *path)
{
     ifstream infile(path, ios::binary);

     if(!infile.is_open())
   {
        infile.close();
     
        return 0;
  }

  //determine beginning and end of primary frame data (not ID3 tags)
  infile.seekg(0, ios::end);
  streampos dataEnd = infile.tellg();

  infile.seekg(0, ios::beg);
  streampos dataBegin = 0;

  dataEnd -= id3v1size(infile);
  dataBegin += id3v2size(infile);

  infile.seekg(dataBegin,ios::beg);

  //determine bitrate based on header for first frame of audio data
  int headerBytes = 0;
  infile.read(reinterpret_cast<char*>(&headerBytes),sizeof(headerBytes));

  headerBytes = reverse(headerBytes);
  int bitrate = bitrates[(int)((headerBytes >> 12) & 0xF)];
  //calculate duration, in seconds
  int duration = ((dataEnd ))/(bitrate/8);
  infile.close();

  //return duration in seconds
  return duration;
  
}
  clock_t endwait,present;
  int seconds;
  bool play_stat=false,play_=false;
  plylst *present_ply;//to point to the entry that is being played at present
 char *disp_array[22];//display array which holds the string to be displayed on screen
 char *disp_array_ply[22];
 entry *disp_acs[22];//stores the pointer to the entries that are being displayed 
 plylst *disp_acs_ply[22];
 entry *pageup,*pagedwn;//point to the entry at the begining of the page
 plylst *pageup_ply,*pagedwn_ply;
 int vol=500; //to control volume
 int ma=0,ma_ply=0;//to keep track of the length of the string
 bool ply_exist=false;// to decide whether the playlist exists or not
 
 int play_tot=0,line_ply=0;
int P=0,ca=0;
//To initialize the display array 
 void disp_init()
 {
      for(int i=0;i<22;i++)
      disp_array[i]=(char *)malloc(150*sizeof(char));
      ply_exist=false;
      return;     
 }
 
 //To initialize the playlist display array 
 void plylist_init()
 {
    for(int i=0;i<22;i++)
      disp_array_ply[i]=(char *)malloc(150*sizeof(char));
      return; 
 }
 
 // function to draw a rectangle of given size and position on the screen
 void rectangle(int len,int brth,int x,int y)
    {
    
    gotoxy(x, y);
    
       cout << (char)0xDa;
            for(int i=0; i<len; ++i)
            cout << (char)0xC4;//horizontal
            cout << (char)0xBF;//corners
           gotoxy(x, ++y);
            // vertical edges
            for(int i=0; i<brth; ++i)
            {
                    cout << (char)0xB3;    //vertical line
                    for(int j=0; j<len; ++j)
                    gotoxy(x+len+1, y);
                    cout << (char)0xB3;
                    gotoxy(x, ++y);
            }
            // bottom line and corners
             cout << (char)0xC0;
             for(int i=0; i<len; ++i)
             cout << (char)0xC4;
             cout << (char)0xD9;
             cout << '\n';
      }

/*function used to concat all the fields and 
 *store it in the display arrays for displaying 
 */
void concat_all(char *dis,char *c1,char *c2,char *c3,char *c4,char *c5,char *c6)
{
     concat_3(dis,c1,30);
     concat_2(dis," | ",3);
     concat_2(dis,c2,30);
     concat_2(dis," | ",3);
     concat_2(dis,c3,30);
     concat_2(dis," | ",3);
     concat_2(dis,c4,30);
     concat_2(dis," | ",3);
     concat_2(dis,c5,4);
     concat_2(dis," | ",3);
     concat_2(dis,c6,15);
     return;    
                
}

/*This function is used to split the file name from the 
 *path of the file
 */
char *fn_split(char *path)
{
   int i =0;
   int j=0;
     char temp[159];
     temp[149]='\0';
     while(path[strlen(path)-j]!= '\\')
     {     
           j++;                  
     }
     for(i=0;i<j;i++)
     {
        temp[i]=path[strlen(path)-j+1+i];
     }
     temp[j]='\0';
   
     return temp;
                   
}
/*Load the display array and pointers to the entries
 *that are displayed from the playlist (linkedlist)
 */
void load_disp_ply(plylst *list)
{
     plylst *temp;
     int i=0;
     int len=0;
     int fill=0;
     char *tmp;
     temp=list->next;
       while(i!=22)
     {
           if((temp->etr_num==-1)&&(i==0))
            {
               disp_acs_ply[0]=(plylst *)malloc(sizeof(plylst));     
                disp_acs_ply[0]->etr_num=-1;    
               concat_3(disp_array_ply[0],"Empty playlist",14);    
               i++;      
                fill=14;   
                while(fill<150)
             {
              concat_2(disp_array_ply[0]," ",1);
              fill++;
              }
              ply_exist=false;
              
            }
           if((temp->etr_num==-1)&&(i>0))
          {
            
            for(int j=i;j<22;j++)
            {
            
            disp_acs_ply[j]=(plylst *)malloc(sizeof(plylst));
            
             disp_acs_ply[j]->etr_num=-1;
      //                                                                                                                                                     ",150,0);
              fill=0;
                concat_3(disp_array_ply[j]," ",1);
               while(fill<150)
             {
              concat_2(disp_array_ply[j]," ",1);
              fill++;
              }
          
             len=strlen(disp_array_ply[j]);
            if(len>ma_ply)
            ma_ply=len;
             }
            break;
          }
          else if((temp->etr_num==-1)&&(i==0))
          {
               break;
          }
          disp_acs_ply[i]=temp;
          tmp=fn_split(disp_acs_ply[i]->fileName);
          str_cpy(disp_array_ply[i],tmp,strlen(tmp),0);
          
          len=strlen(disp_array[i]);
          fill=0;
          while((fill-len)<150)
          {
          concat_2(disp_array_ply[i]," ",1);
          fill++;
          }
       
          if(len>ma_ply)
          ma_ply=len;
          i++;
          present_ply=disp_acs_ply[0];
          temp=temp->next;    
     }
    
}
  
  /*Load the display array and pointers to the entries
 *that are displayed from the library (linkedlist)
 */    
void load_disp(entry *list)
{
     entry *temp;
     char *genre;
     genre=(char *)malloc(16);
     int i=0,len=0;
     
     temp=list->next;
     
     
     while(i!=22)
     {
           
           if((temp->etr_num==-1)&&(i>0))
          {
            
            for(int j=i;j<22;j++)
            {
            
            disp_acs[j]=(entry *)malloc(sizeof(entry));
           
             disp_acs[j]->etr_num=-1;
             
             str_cpy(disp_array[j],"                               |                                |                                |                                |      |            ",150,0);
             len=strlen(disp_array[j]);
            if(len>ma)
            ma=len;
             }
            break;
          }
          else if((temp->etr_num==-1)&&(i==0))
          {
               break;
          }
          str_cpy(genre,genere_det(temp->genre),15,0);
          concat_all(disp_array[i],temp->title,temp->album,temp->artist,temp->comment,temp->year,genre);
          disp_acs[i]=temp;
          len=strlen(disp_array[i]);
          if(len>ma)
          ma=len;
          i++;
          
          temp=temp->next;    
     }
      return;  
}
//search for the entr_num field for a perfect match from the end 
entry * search_etr_num_back(int pg)
{
    entry *temp;
    int fnd,i=0;
    temp=disp_acs[0];
  if(temp->next==NULL)
    return temp;
    while(1)
    {  
            if(temp->prev==NULL)
            {
             return temp;                   
            }
       fnd=temp->etr_num; 
     
       if(fnd==pg)
       return temp->prev;
       else
       temp=temp->prev;
                
    }
}
    
  plylst * search_etr_num_back_ply(int pg)
{
    plylst *temp;
    int fnd,i=0;
    temp=disp_acs_ply[0];
  
    while(1)
    {  
       fnd=temp->etr_num; 
      
       if(fnd==pg)
       return temp->prev;
       else
       temp=temp->prev;
                
    }
    
    return pageup_ply;
    
        
}
entry * search_etr_num_from_end(int pg)
{
    entry *temp;
    int fnd,i=0;
    temp=end->prev;
   
    do
    {  
       fnd=temp->etr_num; 
       if(fnd==pg)
       return temp->prev;
       else
       temp=temp->prev;
        i++;
        if(i==23)
        break;             
    }while(temp->prev!=NULL);
    
    return pageup;
    
        
}
plylst * search_etr_num_from_end_ply(int pg)
{
    plylst *temp;
    int fnd,i=0;
    temp=cls->prev;
  
    do
    {  
            
       fnd=temp->etr_num; 
      
       if(fnd==pg)
       return temp->prev;
       else
       temp=temp->prev;
        i++;
        if(i==23)
        break;             
    }while(temp->prev!=NULL);
    
    return pageup_ply;
    
        
}
//To delete entries in the library
void del_lib(entry *temp)
{
     entry *temp1;
     
         temp1=temp->prev;
         temp1->next=temp->next;
         temp->next->prev=temp1;
         free_ent(temp);
         free(temp);                            
    
 return;
     
}
//to delete entries in the playlist
void del_ply(plylst *temp)
{
     plylst *temp1;
     int  i=0;
         temp1=temp->prev;
         temp1->next=temp->next;
         temp->next->prev=temp1;
         free(temp->fileName);
         free(temp);
       temp=opn->next;
       while(temp->etr_num!=-1)
       {
            temp->etr_num=++i;
            temp=temp->next;                  
       }
 return;
     
}

//add entries to the playlist
void add_play(int num)
{
     
        plylst *temp;
        temp=(plylst *)malloc(sizeof(plylst ));
        temp->fileName=(char *)malloc(1024*sizeof(char));
        str_cpy(temp->fileName,disp_acs[num]->fileName,strlen(disp_acs[num]->fileName),0);
        temp->etr_num=++ply_tot;
        
        cls->prev->next=temp; 
        temp->prev=cls->prev;  
        temp->next=cls;
        cls->prev=temp;
        ply_exist=true;
        return;
         
}
//to open a mp3 file and assign it common name to allow the MCI to control the playback
void openmp3(char *path)
{
     char *temp;
     temp=(char *)malloc(1024);
     mciSendString("close myFile", NULL, 0, 0);
     concat_3(temp,"open \"",6);
     concat_2(temp,path,strlen(path));
     concat_2(temp,"\" type mpegvideo alias myFile",29);
     mciSendString( temp , NULL, 0, 0);
    
     present_ply=disp_acs_ply[line_ply];
      seconds=duration(path);
      time_pre=time(NULL)+seconds;
     
}

//so instruct the MCI to start playing the mp3file
void play()
 {
      endwait = clock () + seconds * CLK_TCK ;
      mciSendString("play myFile", NULL, 0, 0);
      play_=true;
      
}
void stop()
{
     mciSendString("stop myFile", NULL, 0, 0);
     play_=false;
}

//to control the volume 
void volume(int n)
{
     char *len;
     char *pl;
     char c[]="setaudio myFile volume to ";
     pl=(char *)malloc(31*sizeof(char));
     len=(char *)malloc(5*sizeof(char));
     str_cpy(len,"    ",strlen("    "),0);
     len = itoa(n,len,10);
     str_cpy(pl,c,strlen(c),0);
     concat_2(pl,len,4);
    mciSendString(pl, NULL, 0, 0);
    return;
     
}
//for the static displays on the screen 
void static_disp()
{
     textbackground(MAGENTA);
     int fill=0;
     //rectangle(78,7,1,28);
     gotoxy(2,29);
    
          char s[7][80];/*={" use <- , -> , up and down arrows to scroll through the library.",
                         " Page up and down can also be used ... ",
                          " use \"ENTER\" to add the track to the playlist;",
                          " use \"TAB\" to toggle between the library and the playlist..",
                          " use < and > to select next track or use ENTER in the playlist..."};*/
            char *c1=" use <- , -> , up , down arrows and Pgup &dwn to scroll through the library.";
           char *c2=" 'z' -VOLUME DOWN : 'x'-VOLUME UP : SPACE - play/pause :";
           char *c3=" use \"ENTER\" to add the track to the playlist;";
           char *c4=" use \"TAB\" to toggle between the library and the playlist..";
           char *c5=" use < and > to select next track or use ENTER in the playlist...";
           char *c6=" SORTING : t-title ,r-artist, a- album, c-comments, y-year, g-genre .";
           char *c7=" press END in playlist editor to go to save options. F5 to Refresh the screen";
          // char *c8="";
           concat_3(s[0],c1,strlen(c1));
          concat_3(s[1],c2,strlen(c2));
          concat_3(s[2],c3,strlen(c3));
          concat_3(s[3],c4,strlen(c4));
          concat_3(s[4],c5,strlen(c5));
          concat_3(s[5],c6,strlen(c6));
          concat_3(s[6],c7,strlen(c7));
         // concat_3(s[7],c8,strlen(c8));
          for(int i=0;i<7;i++)
          {  
            fill=0;
            int len=strlen(s[i]);
          while(strlen(s[i])<78)
          {
          concat_2(s[i]," ",1);
          }
        }
     cout<<s[0];
     gotoxy(2,30);
     cout<<s[1];
     gotoxy(2,31);
     cout<<s[2];
     gotoxy(2,32);
     cout<<s[3];
     gotoxy(2,33);
     cout<<s[4];
     gotoxy(2,34);
     cout<<s[5];
     gotoxy(2,35);
     cout<<s[6];
    
};
// for the scrolling display indicating the field names
void static_up_lib(int n)
{
     textbackground(MAGENTA);
    
     int fill=0;
     int i=0;
     //rectangle(78,7,1,28);
     gotoxy(2,2);
    
          char s[150],*c[7];
             c[0]="TITLE";
            c[1]="ALBUM";
            c[2]="ARTIST";
            c[3]="COMMENT";
            c[4]="YEAR";
            c[5]="GENRE";
            c[6]="Playlist Editor";
             char *pl;
            pl=(char *)malloc(27);
            str_cpy(pl,c[6],strlen(c[6]),0);
           *s='\0';
          for(int i=0;i<4;i++)
          {  
           concat_2(s,c[i],strlen(c[i])); 
            fill=0;
           while((strlen(c[i])+fill)<30)
           {
            concat_2(s," ",1);
            fill++;
           }
         //  cout<<s;
         //  getch();
           concat_2(s," | ",3);
         }
         concat_2(s,c[4],strlen(c[4])); 
            fill=0;
           while((fill+strlen(c[4]))<4)
           {
            concat_2(s," ",1);
            fill++;
           }
         concat_2(s," | ",3);
         concat_2(s,c[5],strlen(c[5])); 
            fill=0;
           while((fill+strlen(c[5]))<15)
           {
            concat_2(s," ",1);
            fill++;
           }
           fill=0;
            while((fill+strlen(c[6]))<26)
           {
            concat_2(pl," ",1);
            fill++;
           }
     gotoxy(2,2);
                 
              textbackground(MAGENTA);
         //     cout<<s;
              for(int j=n;j<50+n;j++)
              putchar(*(s+j));         
              gotoxy(54,2);
              textbackground(MAGENTA);
              for(int j=0;j<26;j++)
              putchar(*(pl+j));          
     
     
};

//For displaying the save option in the playlist section
void save_pane()
{
     xx:
     FILE * pFile;
     char *c;
     char s[22][26];
     char path[25];
     char p;
     int fill=0,i=0;
     for(int i=0;i<22;i++)
     {
        *(s[i])='\0';
        fill=0;
        while((strlen(s[i]))<26)
           {
            concat_2(s[i]," ",1);
            fill++;
           }       
  
     }
     str_cpy(s[3]," Enter the file name in ",25,0);
     str_cpy(s[4]," you wish to save the   ",25,0);
     str_cpy(s[5]," playlist: (max 25 char)",25,0);
  
     i=0;
     gotoxy(54, 5);
     while(i!=22)
           {
                 textbackground(MAGENTA);
              for(int j=0;j<26;j++)
              putchar(*(s[i]+j));
               i++; 
              gotoxy(54, 5+i);           
           }     
      i=0;
       p=getch();    
      if(p==27)
      return ;
      gotoxy(54,11);
      cin>>path;
      if(strlen(path)<=25)
      {
      write_ply(path);
   
      
      }
      else
      {
         gotoxy(54,11);
         cout<<"invalid name length"; 
         p=getch();
      if(p==27)
      return ;
      else   
      goto xx;
      }
      return;
      
}

plylst *play_ent;
//for the whole User interface in the playlist section 
void disp_playlist()
{
       char press;
           int j=0,n=0,now;
           int i=0,page=0;
           int play_tot=0;
           int tem=0;
           plylst *temp;
           tem=(play_ent->etr_num)/22+1;
           temp=opn;
           while(temp->etr_num!=tem)
           temp=temp->next;
           load_disp_ply(temp->prev);
           line_ply=(play_ent->etr_num)%22;
           
           while(1)
       { 
           
        press=getch();
      
              if(time_pre<=time(NULL)) //for autoplay option but this works only when the user is active in the app/
          {
          clrscr();
          textbackground(MAGENTA);        
           rectangle(50,22,1,4);
           rectangle(50,1,1,1);
           static_up_lib(P);
           static_disp();
             rectangle(26,22,53,4);
             rectangle(26,1,53,1);
             rectangle(78,7,1,28);
             static_disp();
             gotoxy(2, 5);
             line_ply++;
            play_tot++;
            if(play_tot>=ply_tot)
            {
                      line_ply--;
            play_tot--;          
            }
            if(line_ply>play_tot)
            line_ply=play_tot;
          while(i!=22)                            //for displayint the whole playlist section with the cursors
           {
              
              textbackground(BLACK);
              if(i==line_ply)
              textbackground(RED);
              for(j=n;j<50+n;j++)
              putchar(*((disp_array[i])+j));
               i++; 
              gotoxy(2, 5+i);           
           } 
           stop();
            if(present_ply->next->etr_num!=-1)
                present_ply=present_ply->next;
            openmp3(present_ply->fileName);
            play();   
                
          }
        if(press==83)//del key
        {
                 plylst *temp;  
                 int pl;        
               ply_tot--;
                if(opn->next->etr_num==-1)
                {
                 load_disp_ply(opn); 
                }
                else 
               {
                     if(ply_tot>=0)
                     {
                                    if(play_ent==disp_acs_ply[line_ply])
                                    {
                                       pl=play_ent->etr_num;
                                       stop();
                                        if(play_ent->next->etr_num!=-1)
                                        play_ent=play_ent->next;
                                        else
                                        play_ent=opn;
                                    }
                               temp=disp_acs_ply[0]->prev;
                               del_ply(disp_acs_ply[line_ply]);
                               load_disp_ply(temp); 
                     }else
                     {  
                                load_disp_ply(disp_acs_ply[0]->prev); 
                    
                      }
               }
             /*   if(opn->next->etr_num==-1)
                {
                load_disp_ply(opn); 
                }*/
               // line_ply++;
                play_tot=pl;
          
              if(line_ply>=22)
             {
               pagedwn_ply=disp_acs_ply[21];
               if(disp_acs_ply[21]->etr_num!=-1)
               load_disp_ply(pagedwn_ply);
               line_ply=0;
             }
            // cout<<ply_tot;
            // cout<<"\t"<<play_tot;
           // getch();
             if(play_tot>ply_tot)
            {
                 line_ply=0;
                 play_tot=0;
                 load_disp_ply(opn);
           }
           if(play_tot>ply_tot+1)
          {
                     line_ply=0;
                     play_tot=0;
                     load_disp_ply(opn);
          }
                    if((ply_tot<0)||(opn->next->etr_num==-1))
                    { 
                     ply_exist=false;    
                     return;
                     }
        }
        
          if(errno!=0)
          {
             clrscr(); 
             textbackground(MAGENTA);       
             rectangle(50,22,1,4);
             rectangle(50,1,1,1);
             static_up_lib(P);
             static_disp();
             rectangle(26,22,53,4);
             rectangle(26,1,53,1);
             rectangle(78,7,1,28);
             static_disp();
             gotoxy(2, 5);
             errno=0;         
         }
        if(press==46)//>>>
        {
             stop();
             if(play_ent->next->etr_num!=-1)
                play_ent=play_ent->next;
            openmp3(play_ent->fileName);
              play(); 
              play_tot++;
              if(play_tot>ply_tot)
              play_tot=ply_tot;         
              
        }
        if(press==44)//<<<
        {
              stop();
              if(play_ent->prev->etr_num!=-1)
                play_ent=play_ent->prev;
             openmp3(play_ent->fileName);
             play();          
              play_tot--;
              if(play_tot<0)
              play_tot=0;     //It is used to keep in track which entry is being played in the whole playlist
        }
          
         if(press==80)//down
        {
          line_ply++;
          play_tot++;
          
          if(line_ply>=22)
          {
           pagedwn_ply=disp_acs_ply[21];
             if(disp_acs_ply[21]->etr_num!=-1)
             load_disp_ply(pagedwn_ply);
          line_ply=0;
          }
          else if(play_tot>=ply_tot)
          {
          line_ply=0;
          play_tot=0;
          load_disp_ply(opn);
          }
          if(play_tot>=ply_tot)
          {
          line_ply=0;
          play_tot=0;
          load_disp_ply(opn);
          }
         
        }
        if(press==72)//up
        {
                       
       
         line_ply--;
         play_tot--;
         
          if(line_ply<0)
         {
             pageup_ply=disp_acs_ply[0]->prev;
             page=disp_acs_ply[1]->etr_num;
             if((page-22)>=1)                
             pageup_ply=search_etr_num_back_ply(page-22);
             load_disp_ply(pageup_ply);
             
              if(ply_tot<22)
            {
                      line_ply=ply_tot-1;
                      play_tot=ply_tot-1;                  
                   load_disp_ply(opn);   
                                     
             }else
             {
                    line_ply=21;
              }    
        
          }      
          if((play_tot<0)&&(ply_tot>0))
          {
                         
             if(pageup_ply=search_etr_num_from_end_ply(ply_tot-(ply_tot%22)+1))
             load_disp_ply(pageup_ply);
             else
             load_disp_ply(opn);
             if(ply_tot<22)
            {
                      line_ply=ply_tot-1;
                      play_tot=ply_tot-1;                  
                   load_disp_ply(opn);  
                                    
             }else{
                    play_tot=ply_tot;
                    line_ply=(ply_tot%22)-1;
                   } 
            
          } 
           if((play_tot<0)&&(ply_tot<=0))
           {
                      line_ply=0;
                      play_tot=0;                  
                   load_disp_ply(opn);  
                                        
        }
       
            
          
        }
        if(press==77)//right
        {
          n++;
          if(n>ma_ply-50)
          n=ma_ply-50;
          
        }
        if(press==75)//left
        {
          n--;
          if(n<0)
          n=0;
          
        }
        if(press==27)
        return;
        if(press==81)//pgdown
           {
             pagedwn_ply=disp_acs_ply[21];
            if(disp_acs_ply[21]->etr_num!=-1)
             load_disp_ply(pagedwn_ply);
             else
             load_disp_ply(opn);
             play_tot=play_tot-(play_tot%22)+22;
             line_ply=0;
            // pagedwn==disp_acs[0]->prev;
            
             
           }
           if(press==73)//pgup
           {
             pageup_ply=disp_acs_ply[0]->prev;
             page=disp_acs_ply[0]->etr_num;
             if(page==1)
             {
             pageup_ply=search_etr_num_from_end_ply(ply_tot-(ply_tot%22)+1);
             line_ply=ply_tot%22-1;
             }
             else if((page%22)==1)                
             {
             pageup_ply=search_etr_num_back_ply(page-22);
             line_ply=21;
             }
            /*if(page==1)
             {
             pageup_ply=search_etr_num_from_end_ply(ply_tot-(ply_tot%22));
             line=ply_tot%22;
             }*/
             load_disp_ply(pageup_ply);
             play_tot=play_tot-(play_tot%22)-22;
             
           }
          if(press==9)//tab 
          {
          // line_ply=line;
           ca=n;
           return;
          
          }
           if(press=='z'||press=='Z')//volume down
       {
                                 
          vol=vol-50;
          if(vol<0)
          vol=0;
          volume(vol);
       }
       if(press=='x'||press=='X')//volume up
       {
                                 
          vol=vol+50;
          if(vol>1000)
          vol=1000;
          volume(vol);
       }
       if(press==13)//enter
       {
                           
         
         if(disp_acs_ply[line_ply]->etr_num!=-1)
         present_ply=disp_acs_ply[line_ply];
         openmp3(present_ply->fileName);
            play(); 
            play_ent=present_ply; // to know which 
            play_tot=play_ent->etr_num; 
           // next=disp_acs_ply[0]->prev;
            //line=line_ply;
                  
       }
        if(press==32)//space
       {
        if(play_==true)
            stop(); 
            else
            play();
                  
       }
       if(press==79)
       {
         save_pane();
       }
       
          gotoxy(54, 5);
          while(i!=22)
           {
              
              textbackground(BLACK);
              if(i==line_ply)
              textbackground(BLUE);
              if(play_ent==disp_acs_ply[i])
              textbackground(GREEN);
              for(j=n;j<26+n;j++)
              putchar(*((disp_array_ply[i])+j));
               i++; 
              gotoxy(54, 5+i);           
           } 
            gotoxy(2, 5);
           
           
           i=0;      
                       
	   }     
       
       
}





void in_lib()
      { 
           char press;
           int j=0,n=0;
           int i=0,page=0;
           int line_tot=0,line=0,line_pl=0;
            plylst *temp;
           while(1)
       { 
          
         press=getch();  
         if(errno!=0)
         {
             clrscr();        
             textbackground(MAGENTA);
               rectangle(50,23,1,4);
          rectangle(50,22,1,4);
           rectangle(50,1,1,1);
           static_disp();
           static_up_lib(P);
             rectangle(26,22,53,4);
             rectangle(26,1,53,1);
             rectangle(78,7,1,28);
             static_disp();
             gotoxy(2, 5);
             errno=0;         
         }
           
              if(time_pre<=time(NULL))
          {
          clrscr();        
          textbackground(MAGENTA);
           rectangle(50,22,1,4);
           rectangle(50,1,1,1);
           static_disp();
           static_up_lib(P);
             rectangle(26,22,53,4);
             rectangle(26,1,53,1);
             rectangle(78,7,1,28);
             static_disp();
             gotoxy(2, 5);
             
              
           gotoxy(2, 5);
           stop();
            if(present_ply->next->etr_num!=-1)
                present_ply=present_ply->next;
            openmp3(present_ply->fileName);
            play();   
            line_pl++;
            play_tot++;
          if(play_tot>=ply_tot)
          {
           line_pl--;
           play_tot--; 
           load_disp_ply(opn);
          }
           if(line_pl>22)
         {
             pagedwn_ply=disp_acs_ply[21];
             if(disp_acs_ply[21]->etr_num!=-1)
             load_disp_ply(pagedwn_ply);
             line_pl=0;
             }
          gotoxy(54, 5);
            while(i!=22)
           {
              textbackground(BLACK);
              for(j=n;j<26+n;j++)
              putchar(*((disp_array_ply[i])+j));
               i++; 
              gotoxy(54, 5+i);           
           } 
                
          }
          if(press==46)//>>>
        {
            if(ply_exist==true)
            {
            //load_disp_ply(next);
             stop();
            if(play_ent->next->etr_num!=-1)
                play_ent=play_ent->next;
            openmp3(play_ent->fileName);
            play();
            //play_ent=present_ply;   
            line_pl++;
            play_tot++;
            if(line_pl>=22)
         {
             pagedwn_ply=disp_acs_ply[21];
             //next=disp_acs_ply[0]->prev; 
             if(disp_acs_ply[21]->etr_num!=-1)
             load_disp_ply(pagedwn_ply);
             line_pl=0;
          }
          if((play_tot>ply_tot)&&(play_ent->next->etr_num==-1))
          {
           line_pl--;
           play_tot--; 
        //   load_disp_ply(opn);
          }
           
          
             gotoxy(54, 5);
             i=0;
          while(i!=22)
           {
              
              textbackground(BLACK);
              if(i==line_pl)
              textbackground(GREEN);
              for(j=ca;j<26+ca;j++)
              putchar(*((disp_array_ply[i])+j));
               i++; 
              gotoxy(54, 5+i);           
           } 
            i=0;          
            }
        }
        if(press==32)//space
       {
       if(play_==true)
            stop(); 
            else
            play();
                     
       }
       if(press=='z'||press=='Z')//volume down
       {
                                 
          vol=vol-50;
          if(vol<0)
          vol=0;
          volume(vol);
       }
       if(press=='x'||press=='X')//volume up
       {
                                 
          vol=vol+50;
          if(vol>1000)
          vol=1000;
          volume(vol);
       }
        if(press==44)//<<<
        {
            if(ply_exist==true)
            {            
             stop();
           //  load_disp_ply(next);
              
             if(play_ent->prev->etr_num!=-1)
              play_ent=play_ent->prev;
            openmp3(play_ent->fileName);
            play();   
          //  play_ent=present_ply; 
            line_pl--;
            play_tot--;
            if(play_tot<0)
            {
                      line_pl++;
                 play_tot++;          
            }                  
         if(line_pl<0)
         {
             pageup_ply=disp_acs_ply[0]->prev;
              //next=disp_acs_ply[0]->prev;
             page=disp_acs_ply[0]->etr_num;
             if((page-22)>=1)                
             pageup_ply=search_etr_num_back_ply(page-22);
             load_disp_ply(pageup_ply);
             line_pl=21;
          } 
           
    
            gotoxy(54, 5);
             i=0;
          while(i!=22)
           {
              
              textbackground(BLACK);
              if(i==line_pl)
              textbackground(GREEN);
              for(j=ca;j<26+ca;j++)
              putchar(*((disp_array_ply[i])+j));
               i++; 
              gotoxy(54, 5+i);           
           } 
            i=0;
            }           
        }
          if(press==83)//del
        {
               del_lib(disp_acs[line]);
               total--;
               load_disp(disp_acs[0]->prev);   
               
        }
         if(press==80)//down
        {
           line++;
           line_tot++;
          
          if(line>=22)
          {
             pagedwn=disp_acs[21];
             if(disp_acs[21]->etr_num!=-1)
             load_disp(pagedwn);
             line=0;
          }else if(line_tot>total)
          {
           line=0;
           line_tot=0;
           load_disp(start);
          }
          if(line_tot>total+1)
          {
           line=0;
           line_tot=0;
           load_disp(start);
          }
          
        }
        if(press==72)//up
        {
         line--;
         line_tot--;
         if(line<0)
         {
          pageup=disp_acs[0]->prev;
             page=disp_acs[1]->etr_num;
             if((page-22)>=1)                
             pageup=search_etr_num_back(page-22);
             load_disp(pageup);
             line=21;
          } 
          if(line_tot<0)
          {
             pageup=search_etr_num_from_end(total-(total%22)+1);
             load_disp(pageup);
             line_tot=total;
             line=(total%22)-1;
                                     
          }                
          
        }
        if(press==27)
        {
         stop();            
        return;
        }
        if(press==77)//right
        {
          n++;
          if(n>ma-50)
          n=ma-50;
          
        }
        if(press==75)//left
        {
          n--;
          if(n<0)
          n=0;
          
        }
        if(press==81)//pgdown
           {
             pagedwn=disp_acs[21];
            if(disp_acs[21]->etr_num!=-1)
             load_disp(pagedwn);
             else
             load_disp(start);
             line_tot=line_tot-(line_tot%22)+22;
             line=0;
            // pagedwn==disp_acs[0]->prev;
            
             
           }
           if(press==73)//pgup
           {
             pageup=disp_acs[0]->prev;
             page=disp_acs[0]->etr_num;
             
             if(page==1)
             {
             pageup=search_etr_num_from_end(total-(total%22)+1);
             line=total%22-1;
             }
             else if((page%22)==1)                
             {
             pageup=search_etr_num_back(page-22);
             line=21;
             }
             load_disp(pageup);
             line_tot=line_tot-(line_tot%22)-22;
             }
             if(press==63)
             {
                 textbackground(MAGENTA);
                 rectangle(50,22,1,4);
                 rectangle(50,1,1,1);
                 static_disp();
                 rectangle(26,22,53,4);
                 rectangle(26,1,53,1);
                 static_up_lib(P);
                 rectangle(78,7,1,28);
                 gotoxy(2, 5);
             }
          if(press==9)//tab 
          {
            int tem=0;
           if(ply_exist==true)
           {
           play_ent=disp_acs_ply[line_pl];
           disp_playlist();
           }
          
           if(ply_exist==true)
           {
           tem=(play_ent->etr_num)-(play_ent->etr_num)%22+1;
           temp=opn;
           while(temp->etr_num!=tem)
           temp=temp->next;
           load_disp_ply(temp->prev);
           line_pl=(play_ent->etr_num)%22-1;
         }
           if(ply_exist==false)
           {
               line_pl=line_ply=play_tot=0;
               free(opn->next);
               load_disp_ply(opn);                
           }
          
          }
       if(press==13)//enter
       {
       if(ply_exist!=true)
       {
       ply_exist=true;
        play_ent=opn;
       }
         add_play(line);
        load_disp_ply(opn);
       
        
        //next=disp_acs_ply[0]->prev; 
         gotoxy(54, 5);
          while(i!=22)
           {
              
              textbackground(BLACK);
              for(j=0;j<26;j++)
              putchar(*((disp_array_ply[i])+j));
                i++; 
              gotoxy(54, 5+i);           
           } 
           
       }
      if((press=='t')||(press=='T'))
       {
        sort_title(); 
        load_disp(start);                           
       }
       if((press=='r')||(press=='R'))
       {
        sort_artist(); 
        load_disp(start);                           
       }
       if((press=='a')||(press=='A'))
       {
        sort_album(); 
        load_disp(start);                           
       }
       if((press=='c')||(press=='C'))
       {
        sort_comment(); 
        load_disp(start);                           
       }
       if((press=='y')||(press=='Y'))
       {
        sort_year(); 
        load_disp(start);                           
       }
       if((press=='g')||(press=='G'))
       {
        sort_genre(); 
        load_disp(start);                           
       }
       static_up_lib(n);
          gotoxy(2, 5);
          while(i!=22)
           {
              
              P=n;
              textbackground(BLACK);
              if(i==line)
              textbackground(RED);
              for(j=n;j<50+n;j++)
              putchar(*((disp_array[i])+j));
               i++; 
              gotoxy(2, 5+i);           
           } 
            gotoxy(2, 5);
          /* if(ply_exist==true)
           {
           i=0;                   
           gotoxy(54, 2);
            while(i!=25)
           {
              textbackground(BLACK);
              for(j=n;j<26+n;j++)
              putchar(*((disp_array_ply[i])+j));
               i++; 
              gotoxy(54, 2+i);           
           } 
           gotoxy(2, 2);
           
          }      */
          i=0;             
	   }
	   return;
}
  
  
  void content_disp()
  {
         int i=0;
         int j=0;
         console = GetConsoleWindow();
         GetWindowRect(console, &r);
         disp_init();
          plylist_init();
         MoveWindow(console, r.left, r.top, 1200, 500, TRUE);
         load_disp(start);
         clrscr();        
         textbackground(MAGENTA);
           rectangle(50,22,1,4);
           rectangle(50,1,1,1);
           static_disp();
             rectangle(26,22,53,4);
             rectangle(26,1,53,1);
             static_up_lib(P);
             rectangle(78,7,1,28);
           gotoxy(2, 5);
          while(i!=22)
           {
              
              textbackground(BLACK);
              for(j=0;j<50;j++)
              putchar(*((disp_array[i])+j));
               i++; 
              gotoxy(2, 5+i);           
           } 
           gotoxy(2, 5);
            // load_disp(start);
           /*while(i!=25)
           {
              for(j=0;j<50;j++)
              putchar(*((disp_array[i])+j));
               i++; 
              gotoxy(2, 2+i); 
                       
           } */
                 
           in_lib();
         
           
           
           getch();   
       return;
       
}
