#include <filesystem>
#include <windows.h>
#include <string>
#include <iostream>
#include <algorithm>
#include <thread>
#include <chrono>
using namespace std;
namespace fs = filesystem;

int main(int argc,char **argv){
    string code_name = argv[1];
    for (const auto & entry : fs::directory_iterator(fs::current_path())){
        string curr = entry.path().string();
        int n = curr.size();
        bool yes = 0;
        for(int i=0;i+2<n;i++){
            if(curr.substr(i,3) == ".in"){
                yes = 1;
            }
        }
        if(!yes)continue;
        string name = "";
        for(int i=n-1;i>=0;i--){
            if(curr[i] == '\\')break;
                name+=curr[i];
        }
        reverse(name.begin(),name.end());
        string out = "";
        for(int i=0;i<(int)name.size();i++){
            if(i+2 < n && name.substr(i,3) == ".in"){
                out += ".out";
                i+=2;
            }else out+=name[i];
        }
        string command = "run ";
        command += code_name;
        command +=" ";
        command += name;
        command += " ";
        command += out;
        cout<< command<<endl;
        system(command.c_str());
        Sleep(100); // don't remove please
    }
    return 0;
}
