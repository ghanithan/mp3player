#include<conio2.h>
#include <errno.h>

#include <iostream>

#include<stdio.h>
#include<conio.h>

#include<string.h>
#include"genre.hpp"
#include"linklist.hpp"


#define _WIN32_WINNT 0x0500
#include <windows.h>
HWND console; 
    RECT r;
void reopen_directory();
int total;
    
//the following line is necessary for the
//  GetConsoleWindow() function to work!
//it basically says that you are running this
//  program on Windows 2000 or higher


//it is important that the above line be typed
//  BEFORE <windows.h> is included


 
//mp3reader.cpp
//snags the tag off the last 128 bytes of an MP3 file.









//int lib_cnt=0;






void open_directory();
void reopen_directory();

bool IsDirectory(char path[]) 
{
    int i = strlen(path) - 1;
  //  int d = strlen(path) - 1;
    //int d=strlen(head->pdiren->d_name)-1;
   if (path[strlen(path)] == '.') 
    {
       return false;
    } // exception for directories*/
    // such as \. and \..
   for(i; i >= 0; i--) 
    {
        if (path[i] == '.')
        {
                    

                    for(int j=1;j<=4;j++)
                     {
                       if (path[strlen(path)-j] == '.') 
                         {  
                             return true;
                         }
                         else false;      
                     }
                  
        }
        else if (path[i] == '\\' || path[i] == '/') return false; // if we first encounter a \ it's a dir
    }
    path[i];
}

bool split_ext(char *path,char *ext)// to check whether the file is an mp3 file , we check the extension
{
     int i = strlen(path) - 1;
     char temp[4];
     temp[3]='\0';
     for(int j=1;j<=4;j++)
     {
              if (path[strlen(path)-j] == '.') 
               {
                 break;
               } 
              temp[3-j]= path[strlen(path)-j];     
     }
    
    if (strcmp(ext,temp)==0)
    {
      
      return true;
      }
    else 
      return false;
    
                           
}

void display_library_init()
{
    gotoxy(2,2);
    
}
void display_library(char path[],int y)//not used
{  
     gotoxy(2,2+y);
     int i;
     char ext[5];
      char drive[3];
       char dir[66];
       char name[9];
     if(!(IsDirectory(path)))
                 {
                           head=_push(head);
                           head->path=path;
                           open_directory();
                     
                                                                        
                 }
                  else
                {
              
                     if(split_ext(path,"mp3"))
                     {
                       // cout<<head->pdiren->d_name;
                        tag(path);
                        if(start->next==NULL)
                        {
                         append();
                         start->next=end->prev;
                          outfile.seekp (0);
                         }
                         else
                         {
                          if(append())
                           getch();
                          }
                        
                     }
                    // cout<<head->pdiren->d_name;
                                          
                }
}
void populate_library(char path[]) // the function used to populate the library 
{  
     if(!(IsDirectory(path)))
                 {
                           head=_push(head);
                           head->path=path;
                           open_directory();
                     
                                                                        
                 }
                  else
                {
              
                     if(split_ext(path,"mp3"))
                     {
                       // cout<<head->pdiren->d_name;
                        tag(path);
                        if(start->next==NULL)
                        {
                         append();
                         start->next=end->prev;
                         //tag_disp();
                         outfile.seekp(0,ios_base::end);
                      //   write_to_file();
                         }
                         else
                         {
                          if(append());
                        //  tag_disp();
                       //  write_to_file();
                          }
                       // getch();
                     }
                    // cout<<head->pdiren->d_name;
                                          
                }
                return;
}
void command_line_init()
{
     gotoxy(2,23);
     return;
}
void command_line(char temp[])
{
     
     cout<< temp;
     return;
}
void display_lowright_init()
{
     gotoxy(50,2);
     return;
}
void display_lowright(char temp[],int y)
{
     gotoxy(50,2+y);
     int w=wherey();
     if(w==25)
     {
        display_lowright_init();      
     }
     cout<<temp;
     return;
}
char * concat(char *str1,char *str2)
{
     char *str3="";
     str3= (char *)malloc((strlen(str1) + strlen(str2) + 1)*sizeof(char));
     strcpy(str3, str1);
     strcat(str3, str2);
     return str3;
}
 
 void tag_disp()// used when veryfing the concept
 {
               entry *temp;
               temp=end->prev;
               
           //     cout<<"title:"<<temp->title<<"\n"<<endl;
        
            //   cout<<"artist:"<<end->prev->artist<<"\n"<<endl;
                                                              
            //   cout<<"album:"<<end->prev->album<<"\n"<<endl;
        
           //    cout<<"year:"<<end->prev->year<<"\n"<<endl;
        
           //    cout<<"comment:"<<end->prev->comment<<"\n"<<endl;
                       
           //    cout<<"genre:"<<genere_det(end->prev->genre)<<"\n"<<endl;
            //   getch();
               return;
}


void open_directory() //the function which is used  for browsing through the directories to extract mp3 files
{
     
    console = GetConsoleWindow();
    GetWindowRect(console, &r);
 
       int count=0;
        char re;
       char *tem_path;
       
       tem_path= (char *)malloc( 1024* sizeof(char));
    
        head->pdir=opendir(head->path);
        _chdir(head->path); 
 
        errno=0;
        MoveWindow(console, r.left, r.top, 800, 500, TRUE);

        
      
        while (1) // while is used to reduce complexities when the funtion is iteratively called ( which may lead to segment fault)
        {
              if((head->pdiren=readdir(head->pdir)))
              {
              _getcwd(tem_path,1204);
           //   cout<<tem_path;
             // getch();
               strcat(tem_path,"\\");
               strcat(tem_path,head->pdiren->d_name);
            //   cout<<"---------"<<head->pdiren->d_name;
             // getch();
           //    cout<<"********"<<tem_path;
              // getch();
                populate_library(tem_path);
      
                }
                else 
                {
                     command_line_init();
                    break;
                    }   
            }
             if(*(head->path)=='#') // to prevent the function from executing the extra number of times during the control return process
         {
                                return;
          
          }
         closedir(head->pdir);
             head=_pop(head);
             gotoxy(56,10);
        
            while(1)
            {
          
          if(*(head->path)=='#')   //to detect the head i.e end of the file stack 
          {
                                //cout<<"***************";
                                return;
          break;
          }
          do
          {
             tem_path= (char *)malloc( 1024* sizeof(char));
             _chdir(head->path);

           errno=0;
           MoveWindow(console, r.left, r.top, 800, 500, TRUE);

           
    
         while (1)
         {
              if((head->pdiren=readdir(head->pdir)))
              {
              _getcwd(tem_path,1204);
          //    cout<<tem_path;
             // getch();
              if(*(tem_path+strlen(tem_path)-1)!='\\')
              {
               strcat(tem_path,"\\");
               }
               strcat(tem_path,head->pdiren->d_name);
        
               populate_library(tem_path);
             
                }
                else 
                {
                     command_line_init();
                    break;
                }    
         }
         if(*(head->path)=='#')
         {
                                return;
          
          }
         // if(*(head->path)=='#')
        //  return;
         closedir(head->pdir);
          head=_pop(head);
          gotoxy(56,10);
         // cout<<head->path;
      // getch();
         
         } while(*(head->path)!='#');
        
       }
        return;
         //else return ;
       //  getch();
        // return true;
 
         
}
void reopen_directory() // not used only for reference of the programmer
{
     int count=0;
        char re;
       char *tem_path;
       tem_path= (char *)malloc( 1024* sizeof(char));
       _chdir(head->path);

        errno=0;
        MoveWindow(console, r.left, r.top, 800, 1200, TRUE);

        
    
        while (1)
        {
              if((head->pdiren=readdir(head->pdir)))
              {
              _getcwd(tem_path,1204);
              //cout<<tem_path;
              getch();
               strcat(tem_path,"\\");
               strcat(tem_path,head->pdiren->d_name);
              // cout<<"---------"<<head->pdiren->d_name;
            //   getch();
              // cout<<"********"<<tem_path;
             //  getch();
             //  display_lowright(pent->d_name,count);
              // cout<<pent->d_name<<"\n";
               
               
             /*   count++;
               
                if(count>=15)
                {   
                    command_line_init();
                    command_line("N:If u want to go to next page.");
                    cin>>re;
                    if(re =='n')
                    {
                      count=0;
                      clrscr();
                      
                 
                    }
                    else if(re!='n')
                    {
                         break;
                     }
                      
                 }*/
                }
                else 
                {
                     command_line_init();
                    break;
                    }    
         }
         closedir(head->pdir);
          head=_pop(head);
         if(head->path!='\0')
         {
            
             
             return reopen_directory();
//             return true;
         }
         else
        {
           // getch();
            
       //    system("PAUSE");
           return ;
        }
      
}


void reopen_dir() // not used 
{
     int count=0;
        char re;
       char *tem_path;
       tem_path= (char *)malloc( 1024* sizeof(char));
       _chdir(head->path);

        errno=0;
        MoveWindow(console, r.left, r.top, 800, 1200, TRUE);

        
    
        while (1)
        {
              if((head->pdiren=readdir(head->pdir)))
              {
              _getcwd(tem_path,1204);
               strcat(tem_path,"\\");
               strcat(tem_path,head->pdiren->d_name);
              // display_library(tem_path,count);
               populate_library(tem_path);
             
                }
                else 
                {
                     command_line_init();
                    break;
                    }    
         }
         closedir(head->pdir);
          head=_pop(head);
         if(head->path!='\0')
         {
            
             
             return reopen_directory();
//             return true;
         }
         else
        {
           
           return ;
        }
      
}

void tag_disp_all() // to display all entries from the library list 
{
               entry *temp;
               int i=0;
               temp=end->prev;
               do
               {         
            //   cout<<"title:"<<temp->title<<"\n"<<endl;
        
            //   cout<<"artist:"<<temp->artist<<"\n"<<endl;
                                                              
            //   cout<<"album:"<<temp->album<<"\n"<<endl;
        
            //   cout<<"year:"<<temp->year<<"\n"<<endl;
       
           //    cout<<"comment:"<<temp->comment<<"\n"<<endl;
                       
            //   cout<<"genre:"<<genere_det(temp->genre)<<"\n"<<endl;
               temp=temp->prev;
               i++;
               
               } while(temp->prev!=NULL);
             //  getch();
               if(temp->prev==NULL)
               cout<<"finished"<<" "<<i<<endl;
               total=i;
         
}



void sort_title()
{
     
               entry *temp,*point,*pre,*next;
               int i=total;
               point=end->prev;
               temp=point->prev; 
               do
               {
                   do
                 {
                      pre=temp->prev;
                      next=temp->next;
                     if(strcmp(temp->title,point->title)>=0)
                     {
                        temp->prev=point;
                        temp->next=point->next;
                        point->next->prev=temp;
                        point->next=temp;
                        pre->next=next;
                        next->prev=pre;
                        point=temp;                                      
                     }
                     temp=pre;
                 } while(temp->prev!=NULL);
                 point->etr_num=i;
                 i--;
                point=point->prev;
                temp=point->prev;
               } while(temp->prev!=NULL);
               temp->etr_num=i;   
              
               return;
}      
void sort_artist()
{
     
               entry *temp,*point,*pre,*next;
               int i=total;
               point=end->prev;
               temp=point->prev; 
               do
               {
                   do
                 {
                      pre=temp->prev;
                      next=temp->next;
                     if(strcmp(temp->artist,point->artist)>=0)
                     {
                        temp->prev=point;
                        temp->next=point->next;
                        point->next->prev=temp;
                        point->next=temp;
                        pre->next=next;
                        next->prev=pre;
                        point=temp;                                      
                     }
                     temp=pre;
                 } while(temp->prev!=NULL);
                 point->etr_num=i;
                 i--;
                point=point->prev;
                temp=point->prev;
               } while(temp->prev!=NULL);
               temp->etr_num=i;   
              
               return;
}      
void sort_album()
{
     
               entry *temp,*point,*pre,*next;
               int i=total;
               point=end->prev;
               temp=point->prev; 
               do
               {
                   do
                 {
                      pre=temp->prev;
                      next=temp->next;
                     if(strcmp(temp->album,point->album)>=0)
                     {
                        temp->prev=point;
                        temp->next=point->next;
                        point->next->prev=temp;
                        point->next=temp;
                        pre->next=next;
                        next->prev=pre;
                        point=temp;                                      
                     }
                     temp=pre;
                 } while(temp->prev!=NULL);
                 point->etr_num=i;
                 i--;
                point=point->prev;
                temp=point->prev;
               } while(temp->prev!=NULL);
               temp->etr_num=i;   
              
               return;
}      
void sort_comment()
{
     
               entry *temp,*point,*pre,*next;
               int i=total;
               point=end->prev;
               temp=point->prev; 
               do
               {
                   do
                 {
                      pre=temp->prev;
                      next=temp->next;
                     if(strcmp(temp->comment,point->comment)>=0)
                     {
                        temp->prev=point;
                        temp->next=point->next;
                        point->next->prev=temp;
                        point->next=temp;
                        pre->next=next;
                        next->prev=pre;
                        point=temp;                                      
                     }
                     temp=pre;
                 } while(temp->prev!=NULL);
                 point->etr_num=i;
                 i--;
                point=point->prev;
                temp=point->prev;
               } while(temp->prev!=NULL);
               temp->etr_num=i;   
              
               return;
}      
void sort_year()
{
     
               entry *temp,*point,*pre,*next;
               int i=total;
               point=end->prev;
               temp=point->prev; 
               do
               {
                   do
                 {
                      pre=temp->prev;
                      next=temp->next;
                     if(strcmp(temp->year,point->year)>=0)
                     {
                        temp->prev=point;
                        temp->next=point->next;
                        point->next->prev=temp;
                        point->next=temp;
                        pre->next=next;
                        next->prev=pre;
                        point=temp;                                      
                     }
                     temp=pre;
                 } while(temp->prev!=NULL);
                 point->etr_num=i;
                 i--;
                point=point->prev;
                temp=point->prev;
               } while(temp->prev!=NULL);
               temp->etr_num=i;   
              
               return;
}      
void sort_genre()
{
     
               entry *temp,*point,*pre,*next;
               int i=total;
               point=end->prev;
               temp=point->prev; 
               do
               {
                   do
                 {
                      pre=temp->prev;
                      next=temp->next;
                     if(strcmp(genere_det(temp->genre),genere_det(point->genre))>=0)
                     {
                        temp->prev=point;
                        temp->next=point->next;
                        point->next->prev=temp;
                        point->next=temp;
                        pre->next=next;
                        next->prev=pre;
                        point=temp;                                      
                     }
                     temp=pre;
                 } while(temp->prev!=NULL);
                 point->etr_num=i;
                 i--;
                point=point->prev;
                temp=point->prev;
               } while(temp->prev!=NULL);
               temp->etr_num=i;   
              
               return;
}      


