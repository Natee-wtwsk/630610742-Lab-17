#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<cstdlib>

using namespace std;

char score2grade(int score){
    if(score >= 80) return 'A';
    if(score >= 70) return 'B';
    if(score >= 60) return 'C';
    if(score >= 50) return 'D';
    else return 'F';
}

string toUpperStr(string x){
    string y = x;
    for(unsigned i = 0; i < x.size();i++) y[i] = toupper(x[i]);
    return y;
}

void importDataFromFile(string &filename,vector<string> &names,vector<int> &scores,vector<char> &grades){
    ifstream data("name_score.txt");
    string s;
    int i = 0;
    while(getline(data,s))
    {
        char name[100];
        float a,b,c;
        char format[] = "%[^:]: %f %f %f";
        char* char_arr;
        string str_obj(s);
        char_arr = &str_obj[0];
        sscanf(char_arr,format,name,&a,&b,&c);
        names.insert(names.begin()+i,name);
        scores.insert(scores.begin()+i,a+b+c);
        if(scores[i] >= 80) grades.insert(grades.begin()+i,'A');
        else if(scores[i] >= 70) grades.insert(grades.begin()+i,'B');
        else if(scores[i] >= 60) grades.insert(grades.begin()+i,'C');
        else if(scores[i] >= 50) grades.insert(grades.begin()+i,'D');
        else grades.insert(grades.begin()+i,'F');
        i++;
    }
}

void getCommand(string &command,string &key){
    cout << "Please input your command: ";
    string raw_command;
    getline(cin,raw_command);
    char format[] = "%s %[^:]\0";
    char temp_command[100],temp_key[100];
    sscanf(raw_command.c_str(),format,temp_command,temp_key);
    command = temp_command;
    key = temp_key;
}

void searchName(vector<string> names,vector<int> scores,vector<char> grades,string key){
    cout << "---------------------------------" << endl;   
    bool find_it = false;
    
    for (unsigned int i = 0; i < names.size(); i++)
    {
        if (toUpperStr(names[i]) == key)
        {
            cout << names[i] << "'s score = " << scores[i] << endl;
            cout << names[i] << "'s grade = " << grades[i] << endl;
            find_it = true;
        }
        
    }

    if(find_it == false) cout << "Cannot found." << endl;
    cout << "---------------------------------" << endl;
}

void searchGrade(vector<string> names,vector<int> scores,vector<char> grades,string key){
    cout << "---------------------------------" << endl;   
    bool find_it = false;
    char char_key;
    string str_obj(key);
    char_key = str_obj[0];
    for (unsigned int i = 0; i < names.size(); i++)
    {
        if (toupper(grades[i]) == char_key)
        {
            cout << names[i] << " (" << scores[i] << ")" << endl;
            find_it = true;
        }
        
    }

    if(find_it == false) cout << "Cannot found." << endl;
    cout << "---------------------------------" << endl;
}

int main(){
    string filename = "name_score.txt";
    vector<string> names;
    vector<int> scores;
    vector<char> grades; 
    importDataFromFile(filename, names, scores, grades);
    
    do{
        string command, key;
        getCommand(command,key);
        command = toUpperStr(command);
        key = toUpperStr(key);
        if(command == "EXIT") break;
        else if(command == "GRADE") searchGrade(names, scores, grades, key);
        else if(command == "NAME") searchName(names, scores, grades, key);
        else{
            cout << "---------------------------------\n";
            cout << "Invalid command.\n";
            cout << "---------------------------------\n";
        }
    }while(true);
    
    return 0;
}
