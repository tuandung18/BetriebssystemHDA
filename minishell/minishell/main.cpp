#include <iostream>
#include <stdio.h>
#include<unistd.h>
#include <sys/wait.h>
#include <string.h>
#include<filesystem>
#include <vector>
#include<signal.h>
using namespace std;


time_t startTime=time(NULL);
void sigchld_hdl(int sig) {// to kill zombies
    while (waitpid(-1, NULL, WNOHANG) > 0);
}

void closeShell(int) { // to calculate elapsed time
    int diffTime = difftime(time(NULL), startTime);
    cout << endl << "Time elapsed: " << (diffTime / 3600) % 24 << "h " << (diffTime / 60) % 60 << "m " << diffTime % 60 << "s " << endl;
    exit(0);
}
void extractParameter(string eingabe,vector<string>& parameter){
    parameter.clear();
    for(size_t i=0; i<eingabe.size();i++){
        if(eingabe.find(' ')!= string::npos)
        {
            parameter.push_back(eingabe.substr(0, eingabe.find(' ')));
            eingabe = eingabe.substr(eingabe.find_first_of(' ')+1, eingabe.size());
        }

    }
    parameter.push_back(eingabe);
    if(parameter.at(0)=="cd")
    {
        chdir(parameter.at(1).c_str());
    }
    else if(parameter.at(0)=="exit")
    {
        cout<<"Do you want to quit: y/n? ";
        char input;
        cin >> input;
        if(input=='y')
            exit(0);

    }
    return;
}







int main (){

    signal(SIGINT, closeShell);
    signal(SIGCHLD, sigchld_hdl);
    string eingabe;
    int childPid ;
    int status ;
    string command;
    vector<string> parameter;
    while (1) {
        //  system("clear");
        cout << std::filesystem::current_path()<< "> ";
        getline(cin, eingabe);
        extractParameter(eingabe, parameter);
        int x =0;
        if (( childPid = fork()) == -1) {
            fprintf ( stderr , " can 't fork \n " );
            exit (1);
        }

        else if ( childPid == 0) { /* child */
            if(parameter.back()=="&"){
                parameter.pop_back();
            }
            char* para[parameter.size()+1];

            for(size_t i=0;i<parameter.size();i++){
                para[i]=const_cast<char*>(parameter.at(i).c_str());

            }

            para[parameter.size()]=nullptr;
            if(execvp(para[0],(char* const*) para)==-1)
                cerr<<"Command not found"<<endl;
            exit (0);
        }
        else { /* parent process */

            if(parameter.back()=="&")
            {
                cout << childPid << endl;
            }
            else
                waitpid(childPid , & status , WUNTRACED | WCONTINUED );
        }
    }
}
