#include <iostream>
#include <string>
#include <vector>
using namespace std;
bool compare(string i, string j){
    if(j.find(i)!=string::npos)
        return true;
    else return false;
}
int main(int argc, char *argv[], char *envG[])
{
    if(argc == 1){

        for(int i = 0; envG[i] != nullptr; i++){
            cout << envG[i] << endl;
        }
    }
    if(argc == 2){
        for(int i = 0; envG[i] != nullptr; i++){

                if(compare(argv[1], envG[i])){
                    cout << envG[i] << endl;
                }
            }
        }
    if(argc == 3){
        string input = argv[1];
        if(input=="-n"){
            for(int i = 0; envG[i] != nullptr; i++){
                string tmp = envG[i];
                if(compare(argv[2], tmp))
                    cout << tmp.substr(0,tmp.find("="))<< endl;
            }
        }

        if(input == "-i"){

            for(int i = 0; envG[i] != nullptr; i++){
                string input2 = argv[2];
                string tmp = envG[i];
                for(int j = 0; j<input2.size();j++)
                    input2.at(j) = toupper(input2.at(j));
                if(compare(input2,tmp))
                    cout << envG[i] << endl;
            }
        }

    }
    if(argc == 4){
        for(int i = 0; envG[i] != nullptr; i++){
            string input2 = argv[3];
            string tmp = envG[i];
            for(int j = 0; j<input2.size();j++)
                input2.at(j) = toupper(input2.at(j));
            if(compare(input2,tmp))
                cout << tmp.substr(0,tmp.find("="))<< endl;
        }
    }
    return 0;
}
