#include <iostream>
#include <string>
#include <vector>
using namespace std;
bool compare(string i, string j){
    if(j.find(i)!=string::npos)
        return true;
    else return false;
}
int main(int i, char *c[], char *c2[])
{
    if(i==1){

        for(int i = 0; c2[i]!= nullptr; i++){
            cout << c2[i] << endl;
        }
    }
    if(i==2){
        for(int i = 0; c2[i] != nullptr; i++){

                if(compare(c[1],c2[i])){
                    cout << c2[i]<<endl;
                }
            }
        }
    if(i==3){
        string input = c[1];
        if(input=="-n"){
            for(int i = 0; c2[i]!=nullptr; i++){
                string tmp = c2[i];
                if(compare(c[2],tmp))
                    cout << tmp.substr(0,tmp.find("="))<< endl;
            }
        }

        if(input == "-i"){

            for(int i = 0; c2[i]!=nullptr; i++){
                string input2 = c[2];
                string tmp = c2[i];
                for(int j = 0; j<input2.size();j++)
                    input2.at(j) = toupper(input2.at(j));
                if(compare(input2,tmp))
                    cout << c2[i]<< endl;
            }
        }

    }
    if(i==4){
        for(int i = 0; c2[i]!=nullptr; i++){
            string input2 = c[3];
            string tmp = c2[i];
            for(int j = 0; j<input2.size();j++)
                input2.at(j) = toupper(input2.at(j));
            if(compare(input2,tmp))
                cout << tmp.substr(0,tmp.find("="))<< endl;
        }
    }
    return 0;
}
