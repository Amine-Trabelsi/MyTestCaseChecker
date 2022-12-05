#include <iostream>
#include <windows.h>
//#include <time.h>
#include <chrono>
#include <filesystem>
#include <fstream>
#include <stdlib.h>
#include <string.h>
using namespace std;

const int AC_color = 2;//green
const int WA_color = 4; // red
const int reset_color_code = 7; // white
string input_file_name = "input";
string out_file_name = "output";
HANDLE  hConsole; // consol to change color
//clock_t tStart;
double Time_Taken;
void reset_color(){
    SetConsoleTextAttribute(hConsole,reset_color_code);
    FlushConsoleInputBuffer(hConsole);
}
void AC(){
    SetConsoleTextAttribute(hConsole,AC_color); // set to green
    cout<<"Correct"<<endl;
    cout<<"Time Taken: "<<Time_Taken<<" ms"<<endl;
    cout<<endl;
    reset_color();
    exit(0);
}
void WA(int line,int index,string type){// ,char *note = ""){
    SetConsoleTextAttribute(hConsole,WA_color); // set to red
    cout<<"Wrong Answer"<<endl;
    if(type == "different")printf("Error, Line: %d, char %d different",line,index); 
    else if(type == "line_count")printf("Error, number of lines differ");
    else if(type == "char_count")printf("Error, Line: %d, character count is different",line);
    cout<<endl;
    // if(note != "")printf(note);
    cout<<"Time Taken: "<<Time_Taken<<" ms"<<endl;
    cout<<endl;
    reset_color();
    exit(0);
}
bool not_safe(string text){
    // Top level security stuff
    int n = text.size();
    for(int i =0;i<n;i++){
        if(isdigit(text[i]) || isalpha(text[i]) || text[i] != '_')
            continue;
        return true;
    }
    return false;
}
int main(int argc,char **argv){
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    if(argc < 2){
        cout<< "Expected 1 argument, only "<< argc - 1<<" was found";
        cout<<endl;
        exit(0);
    }/*
    if(argc > 2){
        cout<<"Note: extra arguments are ignored (only 1)";
        cout<<endl;
    }*/
    input_file_name = argv[2];
    out_file_name = argv[3];
    string filen = argv[1]; // first Name should be a program file (without the .exe part)
    if(not_safe(filen)){cout<<"Haha";cout<<endl;exit(0);} // safe name

    // check if file exists: 
        string file_name = filen+".exe";
        if(!filesystem::exists(file_name)){ // c++17 only
            cout<<"Executable Not Found !";
            cout<<endl;
            exit(0);
        }
    // exists
    string command = filen;
    command += "<"+input_file_name+"> temp";

    /* Run code here */
        auto start = chrono::steady_clock::now();
        cout.flush();
        system(command.c_str());
        auto end = chrono::steady_clock::now();
        auto diff = end - start;
        Time_Taken = chrono::duration <double, milli> (diff).count();
    /*****************/
    // compare temp && out_file
    int line_count = 1;
    string temp_line, out_line;
    ifstream out_file(out_file_name);
    ifstream temp_file("temp");
    while(getline(out_file,out_line)){
        if(getline(temp_file,temp_line)){
            int n = out_line.size(), x = temp_line.size();
            if(n != x){
                WA(line_count,0,"char_count");
            }
            for(int i=0;i<n;i++){
                if(out_line[i] != temp_line[i]){
                    WA(line_count,i,"different");
                }
            }
        }else{
            WA(0,0,"line_count"); // different count of lines
        }
        line_count++;
    }
    AC();
    //SetConsoleTextAttribute(hConsole,reset_color);
  return 0;

}
