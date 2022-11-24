#include <iostream>
#include <csignal>

int main() {
    putenv("PROC_TO_KILL=telegram-desktop,rythmbox");
    pid_t PID=fork();
    if(PID==NULL){
        execl("../../Killer/cmake-build-debug/Killer",
              "/HELP /NAME telegram-desktop /PID 21868 /ENVV /EXIT","/HELP /NAME telegram-desktop /PID 21868 /ENVV /EXIT");
    }
    return 0;
}
