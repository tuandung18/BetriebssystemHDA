#include <iostream>
#include <stdio.h>
#include<unistd.h>
#include <sys/wait.h>
#include <string.h>
#include<filesystem>
#include <vector>
#include<signal.h>
using namespace std;

#define log(x) cout << x << endl;
time_t startTime=time(NULL);
vector<string> tmp;
int childPid;
void sigchld_hdl(int sig) {
    pid_t pid;
//    int status;
    while ((pid = waitpid(-1, NULL, WNOHANG)) > 0) {
        log(pid << " ended");
    }

}

void closeShell(int) {
    int diffTime = difftime(time(NULL), startTime); // diffTime is second
    cout << endl << "Time elapsed: " << (diffTime / 3600) % 24 << "h " << (diffTime / 60) % 60 << "m " << diffTime % 60 << "s " << endl;
    exit(0);
}
void extractParameter(string input, vector<string>& parameter){
    parameter.clear();
    for(size_t i=0; i < input.size(); i++){
        if(input.find(' ') != string::npos)
        {
            parameter.push_back(input.substr(0, input.find(' ')));
            input = input.substr(input.find_first_of(' ') + 1, input.size());
        }

    }
    parameter.push_back(input);
    if(parameter.at(0)=="cd")
    {
        if(parameter.size() <= 1) {
            cerr << "There is no such directory!" << endl;
            return;
        }
        chdir(parameter.at(1).c_str());
    }
    else if(parameter.at(0) == "exit") {
        cout << "Do you want to exit? (y/n): ";
        char input;
        cin >> input;
        switch (input) {
            case 'y': {
                exit(0);
            }
            case 'n':
                return;
            default: break;
        }
    }
    return;
}


int main (){
    vector<string> parameter;
    signal(SIGINT, closeShell);
    signal(SIGCHLD, sigchld_hdl);  //SIGCHLD: when a child stop or terminated
    string eingabe;
    int status ;
    string command;
    while (1) {
        //system("clear");
        cout << std::filesystem::current_path()<< "> ";
        getline(cin, eingabe);
        extractParameter(eingabe, parameter);
        int x =0;
        if (( childPid = fork()) == -1) {       //fork wird ausgeführt
            fprintf ( stderr , " can 't fork \n " );
            exit (1);
        }

        else if ( childPid == 0) {      /* child */
            if(parameter.back()=="&"){
                parameter.pop_back();
            }
            char* para[parameter.size()+1];

            for(size_t i=0;i<parameter.size();i++){
                para[i]= const_cast<char*>(parameter.at(i).c_str());

            }
            para[parameter.size()]=nullptr; //nullptr at the end of the vector, prevent unwanted output
            //execvp(para[0],(char* const*) para);
            if(execvp(para[0],(char* const*) para) == -1 ) {
                std::cout << endl;
                std::cerr << "command not found" << endl;
            }
            exit (0);
        }
        else { /* parent process */

            if(parameter.back()=="&")
            {
                tmp = parameter;
                cout<< childPid << endl;

            }
            else
                waitpid(childPid , & status , WUNTRACED | WCONTINUED );

        }
    }
}