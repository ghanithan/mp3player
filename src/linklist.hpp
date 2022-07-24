#include <fstream>


#include <iostream>


#include<conio.h>

#include<string.h>
#include<stdio.h>
#include <dirent.h>
#include<direct.h>//getcwd
#include<dos.h>
#include<dir.h>
#include <cstdlib>
#include<malloc.h>
using namespace std;


int counter=0,ply_tot=0;
int length=1024;
bool flag=false;


int TAG_SZ=3;
int TITLE_SZ=30;
//int ARTIST_SZ=30;
//int ALBUM_SZ 30;
int YEAR_SZ=4;
//int COMMENT_SZ 30;
int GENERE_SZ=1;




class TAGdata // the tag class
{
      public:
      /* int tags_z;
        int titles_z;
        int artists_z;
        int albums_z;
        int years_z;
        int comments_z;
        int genres_z;*/
        char tag[4];
        char title[31];
        char artist[31];
        char album[31];
        char year[5];
        char comment[31];
        char *fileName;
        int etr_num;
        int genre;
        string gen_nm;
        
        
};

class TAGdata tag_cls;


typedef struct dirent diren;
 ofstream outfile ;
 ofstream outfile_2 ;
  ofstream outfile_ply;
 ifstream  infile_2;
 ifstream  infile;
struct file_stack
{
       DIR *pdir;
        diren *pdiren;
        char *path;
       struct file_stack *next;
};

typedef struct file_stack folder; 

folder *head;

struct file_list // the structure used in library 
{
       char *tag;
        char *title;
        char *artist;
        char *album;
        char *year;
        char *comment;
        char *fileName;
        int genre;
        int etr_num;
        struct file_list *prev;
       struct file_list *next;
};

struct play_list
{
        char *fileName;
        int etr_num;
        struct play_list *prev;
       struct play_list *next;
};

typedef struct play_list plylst;

typedef struct file_list entry; 

plylst *opn;
plylst *cls;

entry *start;
entry *end;
entry *temp_1;
int stlen=1024;
int i=0;
char *str;
bool _free(folder *list);
folder * _pop(folder *list);
folder * _push(folder *list);
bool load_lib();
void tag_disp();
 void str_cpy( char* des,char* src,int n,int pos);
char *genere_det(int a );
 
 void str_cpy( char* des,char* src,int n,int pos)
{
     int i;
     for(i=0;i<n;i++)
     {
             *(des+i)=*(src+pos+i);    
     }     
     *(des+i)='\0';     
     return;
}

void initialize() // to initialise the linked list used for library and the playlist
{
     int net=3;
      
      head=(folder *)malloc(sizeof(folder));
     head->pdir= (DIR *)malloc(sizeof(DIR));
       head->pdiren= (diren *)malloc(sizeof(diren));
    //   head->path=(char *)malloc(1024*sizeof(char));
        head->pdir=NULL;
        head->pdiren=NULL;
         head->path=(char *)malloc(2*sizeof(char));
      //  str_cpy(head->path,"ytujye",6,0);
      *(head->path)='#';
      *(head->path+1)='\0';
         //cout<<head->path;
     //   *(head->path+1)='\0';
    
      // head=_push(head);
     start=(entry *)malloc(sizeof(entry ));
     start->prev=(entry *)malloc(sizeof(entry ));
       start->prev=NULL;
       start->tag=NULL;
        start->title=NULL;
        start->artist=NULL;
        start->album=NULL;
        start->year=NULL;
        start->comment=NULL;
        start->fileName=NULL;
        start->etr_num=-1;
        start->genre=-1;
        
        end=(entry *)malloc(sizeof(entry ));
        end->next=(entry *)malloc(sizeof(entry ));
        end->next=NULL;
        end->tag=NULL;
        end->title=NULL;
        end->artist=NULL;
        end->album=NULL;
        end->year=NULL;
        end->comment=NULL;
        end->fileName=NULL;
        end->etr_num=-1;
        end->genre=-1;
        start->next=end;
        end->prev=start;
        counter=0;
        
        opn=(plylst *)malloc(sizeof(plylst));
        opn->fileName=NULL;
        opn->etr_num=-1;
        opn->prev=(plylst *)malloc(sizeof(plylst));
        opn->prev=NULL;
        cls=(plylst *)malloc(sizeof(plylst ));
        cls->fileName=NULL;
        cls->etr_num=-1;
        cls->next=(plylst *)malloc(sizeof(plylst));
        cls->next=NULL;
        opn->next=cls;
        cls->prev=opn;
        
        ply_tot=0;
        
          outfile .open("LIBRARY.mlib",ofstream::trunc);
          outfile_2 .open("LIBRARY_2.mlib",ofstream::trunc);
       //   outfile_ply.open("ply.txt");
          infile_2 .open("new_2.mlib",ifstream::in);
          str=(char *)malloc(1024*sizeof(char));
          tag_cls.fileName=(char *)malloc(1024*sizeof(char));
            errno=0;
}

folder * _push(folder *list)
{
       folder *p;
       p=(folder *)malloc(sizeof(folder));  
       p->pdir= (DIR *)malloc(sizeof(DIR));
       p->pdiren= (diren *)malloc(sizeof(diren));
       p->path=(char *)malloc(1024*sizeof(char));
       p->next=list;
       return p;    
}

bool _free(folder *lis)
{
     free(lis->pdir);
     free(lis->pdiren);
     free(lis->path);
     free(lis->next);
     return true;
         
}
void free_ent(entry *list)
{
          free(list->tag);
           free(list->title);   
           free(list->album);
           free(list->artist);
           free(list->year);
           free(list->comment);
           free(list->fileName);
           /*free(list->genre);
        free(list->etr_num);*/
          //free(list);
       return;                                         
}
void free_all()
{
     entry *temp;
     temp=start->next;
     do
     {
             free_ent(temp);         
             free(temp->prev);
        temp=temp->next;                                                
     }while(temp->next!=NULL);
     return;
        
}


folder * _pop(folder *list)
{
       
        return list->next; 
      
}



// the function is used to fill the linkedlist entries of the library
bool fill(entry *temp)
{
        
        char *guard;
        
        guard=(char *)malloc(3);
        
         temp->title=(char *)malloc(31*sizeof(char));
         
          temp->artist=(char *)malloc(31*sizeof(char));
          
       temp->album=(char *)malloc(31*sizeof(char));
       
       
      temp->year=(char *)malloc(5*sizeof(char));
      
                
       temp->comment=(char *)malloc(31*sizeof(char));
   
                
       temp->fileName=(char *)malloc(1024*sizeof(char));
         
        temp->genre=(int )malloc(sizeof(int));
        temp->etr_num=(int )malloc(sizeof(int));
        
   

        str_cpy( temp->title,"                              ",TITLE_SZ,0);
        str_cpy(temp->artist,"                              ",TITLE_SZ,0);
        str_cpy(temp->album ,"                              ",TITLE_SZ,0);
        str_cpy( temp->comment,"                              ",TITLE_SZ,0);
        str_cpy( temp->year,"     ",YEAR_SZ,0);
        
        str_cpy(temp->title,tag_cls.title,strlen(tag_cls.title),0);
        str_cpy(temp->artist,tag_cls.artist,strlen(tag_cls.artist),0);
        str_cpy(temp->album,tag_cls.album,strlen(tag_cls.album),0);
        str_cpy(temp->year,tag_cls.year,strlen(tag_cls.year),0);
      
        str_cpy(temp->comment,tag_cls.comment,strlen(tag_cls.comment),0);
        str_cpy(temp->fileName,tag_cls.fileName,strlen(tag_cls.fileName),0);
             
        temp->genre=tag_cls.genre;
        if(flag==false)
        temp->etr_num=++counter;    
        else
        temp->etr_num=tag_cls.etr_num;
        if(temp->genre==-1)
        {
             temp->genre=80;
        }
        end->prev->next=temp; 
        temp->prev=end->prev;  
        temp->next=end;
        end->prev=temp;
       
          return true;   
}

bool append()// toappend entries in the library
{
      
      entry *temp;
      temp=(entry *)malloc(sizeof(entry ));
      
      if(fill(temp)==true)  
      return true;  
      else
      {
        
      return false; 
      }
      
                     
}

            
void write_to_file() // to save the library
{
     entry *temp;
     char *gen,*len;
     int i=0;
     temp=start->next;
        do
               {         
              // cout<<"title:"<<temp->title<<"\n"<<endl;
               gen=(char *)malloc(2*sizeof(char));
               gen = itoa(temp->genre,gen,10);//integer to string 
               len=(char *)malloc(10*sizeof(char));
               str_cpy(len,"         ",strlen("         "),0);
               len = itoa(temp->etr_num,len,10);
     
   //  sprintf(gen, "%d\0", temp->genre); 
     
                    outfile.write (temp->title,31);
                    outfile<<"#";
                    outfile.write (temp->artist,31);
                    outfile<<"#";
                    outfile.write (temp->album,31);
                    outfile<<"#";
                    outfile.write (temp->year,5);
                    outfile<<"#";
                    outfile.write (temp->comment,31);
                    outfile<<"#";
                    outfile.write (gen,2);
                    outfile<<"#";
                    outfile.write (temp->fileName,strlen(temp->fileName));
                    outfile<<"#";
                    outfile.write (len,10);
                    outfile<<"#";
                    outfile<<"\n";
                    outfile<<"#";
   
                    outfile_2.write (temp->fileName,strlen(temp->fileName));
                    outfile_2<<"#";
                    outfile_2.write (len,10);
                    outfile_2<<"#";
        
    // outfile.write (temp->genre,1);
                     outfile_2<<"\n";
                     outfile_2<<"#";
                     i++;
                     temp=temp->next;
     //free_ent(temp);
                    } while(temp->next!=NULL);
              // getch();
               if(temp->next==NULL)
               {
                outfile.close();
                outfile_2<<"endlist#";
               outfile_2.close();
               cout<<"finished"<<" "<<i<<endl;
               }
   
      
             
    
}

bool tag(char *path) // function to extract the tag fields from the mp3file and store it in the object cls.
{
        
        
        ifstream mp3File;
        int mp3TagSize=128;
        char buffer[mp3TagSize];
      
       tag_cls.fileName=path;
       
        mp3File.open(tag_cls.fileName);
        buffer[mp3TagSize] = '\0';  //just a precaution
       

        mp3File.seekg(-(mp3TagSize),ios::end);
     
        mp3File.read(buffer,mp3TagSize);
        //cout<<buffer;
       //getch();
         if(errno!=0)
         {
                  //   cout<<"failed";
                  //   system("pause");
                   return false;
         }
        
        str_cpy(tag_cls.tag,buffer,TAG_SZ,0);
        
        
         str_cpy(tag_cls.title,buffer,TITLE_SZ,(TAG_SZ));
         //cout<<"title:"<<tag_cls.title;
      
         str_cpy(tag_cls.artist,buffer,TITLE_SZ,(TITLE_SZ+TAG_SZ));
         str_cpy(tag_cls.album,buffer,TITLE_SZ,(2*TITLE_SZ+TAG_SZ));
         str_cpy(tag_cls.year,buffer , YEAR_SZ, (3*TITLE_SZ+TAG_SZ));
         str_cpy(tag_cls.comment , buffer , TITLE_SZ , (YEAR_SZ+3*TITLE_SZ+TAG_SZ));
         tag_cls.genre=buffer[127];
       // genere_det(tag_cls.genre,tag_cls.gen_nm );
        tag_cls.gen_nm=genere_det(tag_cls.genre);
       gotoxy(2,25);
    
      mp3File.close();
      if(errno!=0)
         {
                    //cout<<"failed";
                    // system("pause");
                     return false;
         }
      return true;
}



bool load_lib()
{    
           
           char *ted;
             int ge;
             flag=true;
          while(1)
           {               
             
                             
                                      
                 infile_2.getline(str,length,'#'); 
                                 
                   ted=(char*)malloc(strlen(str)*sizeof(char));
                 str_cpy(ted,str,strlen(str),0);
                    cout<<ted;
                               
                           if(strcmp(ted,"endlist")==0)
                           break;
                            //  getch();                              
                              infile_2.getline(str,length,'#'); 
                              
                                 tag_cls.etr_num=atoi (str);//convert from char * to int  
                                  infile_2.getline(str,length,'#');
                               if(tag(ted)==true)
                               {
                               append();
                               clrscr();
                               tag_disp();
                               getch();
                               }
               //getch();
            //  getch();
            //   tag_disp_all();
              // getch();
                
          }
          getch();
          flag=false;
         return true;
                  
 }
 

         

 void concat_2(char *des,char *src,int n)
{
       int de;
       de=strlen(des);
       int sr=strlen(src);
     int i;
     for(i=0;i<n;i++)
     {
             *(des+de+i)=*(src+i);    
     }   
      if(sr<n)
     {
           for(i=sr;i<n;i++)
     {
                      //cout<<*(src+i);
             *(des+de+i)=' ';    
             //getch();
     }       
     }   
     *(des+de+n)='\0';     
     return ;
}
 
 void concat_3(char *des,char *src,int n) //customised concatination function used in our program to concate the string to the empty string
{
       
     int i;
     int sr=strlen(src);
     for(i=0;i<n;i++)
     {
                      //cout<<*(src+i);
             *(des+i)=*(src+i);    
             //getch();
     } 
     if(sr<n)
     {
           for(i=sr;i<n;i++)
     {
                      //cout<<*(src+i);
             *(des+i)=' ';    
             //getch();
     }       
     }
         
     *(des+n)='\0';     
     return ;
}

bool write_ply(char *name) // to save the playlist in the user specified name
{
    
     char *c;
     c=(char *)malloc(40);
  
     concat_3(c,name,strlen(name));
     concat_2(c,".mply",5);
   //  cout<<c;
     //getch();
     outfile_ply.open(c,ofstream::trunc);
     plylst *temp;
     char *len;
     int i=0;
     temp=opn->next;
        do
               {  
               len=(char *)malloc(10*sizeof(char));
               str_cpy(len,"         ",strlen("         "),0);
               len = itoa(temp->etr_num,len,10);
               outfile_ply.write(temp->fileName,strlen(temp->fileName));
                    outfile_ply<<"#";
                    outfile_ply.write (len,10);
                    outfile_ply<<"#";
                     outfile_ply<<"\n";
                     outfile_ply<<"#";
                     i++;
                     temp=temp->next;
               } while(temp->next!=NULL);
                outfile_ply<<"endlist#";
             //   getch();
              outfile_ply.close();
               gotoxy(54,12);
              cout<<"saved";
              getch();
              return true;
              
              // cout<<"finished"<<" "<<i<<endl;
    }


