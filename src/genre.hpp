#include<cstdlib>
#include <iostream>
#include <fstream>
#include <string>
using namespace std;
  void str_cpy2( char* des,char* src)
{
     int i;
     int n=strlen(src);
     for(i=0;i<n;i++)
     {
             *(des+i)=*(src+i);    
     }     
     *(des+i)='\0';     
     return;
}
 
char * genere_det(int a )
{
       char *gen;
       gen=(char *)malloc(15);
     switch(a)
     {
             case 0:
                   str_cpy2(gen,"Blues");
                  break;
             case 1:
                    str_cpy2(gen,"Classic Rock");
                  break;
             case 2:
                    str_cpy2(gen,"Country");
                  break;
             case 3:
                    str_cpy2(gen,"Dance");
                  break;
             case 4:
                    str_cpy2(gen,"Disco");
                  break;
             case 5:
                    str_cpy2(gen,"Funk");
                  break;
             case 6:
                    str_cpy2(gen,"Grunge");
                  break;
             case 7:
                    str_cpy2(gen,"Hip-Hop");
                  break;
             case 8:
                    str_cpy2(gen,"Jazz");
                  break;
             case 9:
                    str_cpy2(gen,"Metal");
                  break;
             case 10:
                    str_cpy2(gen,"New Age");
                  break;
             case 11:
                    str_cpy2(gen,"Oldies");
                  break;
             case 12:
                    str_cpy2(gen,"Other");
                  break;
             case 13:
                    str_cpy2(gen,"Pop");
                  break;
             case 14:
                    str_cpy2(gen,"R&B");
                  break;
             case 15:
                    str_cpy2(gen,"Rap");
                  break;
             case 16:
                    str_cpy2(gen,"Reggae");
                  break;
             case 17:
                    str_cpy2(gen,"Rock");
                  break;
             case 18:
                    str_cpy2(gen,"Techno");
                  break;
             case 19:
                    str_cpy2(gen,"Industrial");
                  break;
             case 20:
                    str_cpy2(gen,"Alternative");
                  break;
             case 21:
                    str_cpy2(gen,"Ska");
                  break;
             case 22:
                    str_cpy2(gen,"Death Metal");
                  break;
             case 23:
                    str_cpy2(gen,"Pranks");
                  break;
             case 24:
                    str_cpy2(gen,"Soundtrack");
                  break;
             case 25:
                    str_cpy2(gen,"Euro-Techno");
                  break;
             case 26:
                    str_cpy2(gen,"Ambient");
                  break;
             case 27:
                    str_cpy2(gen,"Trip-Hop");
                  break;
             case 28:
                    str_cpy2(gen,"Vocal");
                  break;
             case 29:
                    str_cpy2(gen,"Jazz+Funk");
                  break;
             case 30:
                    str_cpy2(gen,"Fusion");
                  break;
             case 31:
                    str_cpy2(gen,"Trance");
                  break;
             case 32:
                    str_cpy2(gen,"Classical");
                  break;
             case 33:
                    str_cpy2(gen,"Instrumental");
                  break;
             case 34:
                    str_cpy2(gen,"Acid");
                  break;
             case 35:
                    str_cpy2(gen,"House");
                  break;
             case 36:
                    str_cpy2(gen,"Game");
                  break;
             case 37:
                    str_cpy2(gen,"Sound Clip");
                  break;
             case 38:
                    str_cpy2(gen,"Gospel");
                  break;
             case 39:
                    str_cpy2(gen,"Noise");
                  break;
             case 40:
                    str_cpy2(gen,"AlternRock");
                  break;
             case 41:
                    str_cpy2(gen,"Bass");
                  break;
             case 42:
                    str_cpy2(gen,"Soul");
                  break;
             case 43:
                    str_cpy2(gen,"Punk");
                  break;
             case 44:
                    str_cpy2(gen,"Space");
                  break;
             case 45:
                    str_cpy2(gen,"Meditative");
                  break;
             case 46:
                    str_cpy2(gen,"Instrumental Pop");
                  break;
             case 47:
                    str_cpy2(gen,"Instrumental Rock");
                  break;
             case 48:
                    str_cpy2(gen,"Ethnic");
                  break;
             case 49:
                    str_cpy2(gen,"Gothic");
                  break;
             case 50:
                    str_cpy2(gen,"Darkwave");
                  break;
             case 51:
                    str_cpy2(gen,"Techno-Industrial");
                  break;
             case 52:
                    str_cpy2(gen,"Electronic");
                  break;
             case 53:
                    str_cpy2(gen,"Pop-Folk");
                  break;
             case 54:
                    str_cpy2(gen,"Eurodance");
                  break;
             case 55:
                    str_cpy2(gen,"Dream");
                  break;
             case 56:
                    str_cpy2(gen,"Southern Rock");
                  break;
             case 57:
                    str_cpy2(gen,"Comedy");
                  break;
             case 58:
                    str_cpy2(gen,"Cult");
                  break;
             case 59:
                    str_cpy2(gen,"Gangsta");
                  break;
             case 60:
                    str_cpy2(gen,"Top 40");
                  break;
             case 61:
                    str_cpy2(gen,"Christian Rap");
                  break;
             case 62:
                    str_cpy2(gen,"Pop/Funk");
                  break;
             case 63:
                    str_cpy2(gen,"Jungle");
                  break;
             case 64:
                    str_cpy2(gen,"Native American");
                  break;
             case 65:
                    str_cpy2(gen,"Cabaret");
                  break;
             case 66:
                    str_cpy2(gen,"New Wave");
                  break;
             case 67:
                    str_cpy2(gen,"Psychadelic");
                  break;
             case 68:
                    str_cpy2(gen,"Rave");
                  break;
             case 69:
                    str_cpy2(gen,"Showtunes");
                  break;
             case 70:
                    str_cpy2(gen,"Trailer");
                  break;
             case 71:
                    str_cpy2(gen,"Lo-Fi");
                  break;
             case 72:
                    str_cpy2(gen,"Tribal");
                  break;
             case 73:
                    str_cpy2(gen,"Acid Punk");
                  break;
             case 74:
                    str_cpy2(gen,"Acid Jazz");
                  break;
             case 75:
                    str_cpy2(gen,"Polka");
                  break;
             case 76:
                    str_cpy2(gen,"Retro");
                  break;
             case 77:
                    str_cpy2(gen,"Musical");
                  break;
             case 78:
                    str_cpy2(gen,"Rock & Roll");
                  break;
             case 79:
                    str_cpy2(gen,"Hard Rock");
                  break;
             default:
                    str_cpy2(gen,"no   genere");
             break;
     }
     return  gen ;
}


