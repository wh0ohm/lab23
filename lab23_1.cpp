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

void importDataFromFile(string filename, vector<string>&names,vector<int>& scores,vector<char> &grades){
    ifstream file(filename);
    string s;
    char name[100];
    int score1=0,score2=0,score3=0;
    char format[] = "%[^:]:%d%d%d";
    
    while (getline(file,s)){
    sscanf(s.c_str(),format,name,&score1,&score2,&score3);
    names.push_back(name);
    scores.push_back(score1+score2+score3);
    grades.push_back(score2grade(score1+score2+score3));
    }
}

void getCommand(string &command, string &key){
    string com;
    cout <<"Please input your command:"<<endl;
    getline(cin,com);
    int start =0;
    int end  = com.find_first_of(" ");
    command = com.substr(start,end-start);
    start = end +1;
    key = com.substr(start,com.size()-start);

}

void searchName(vector<string> &names, vector<int> &scores,vector<char> &grades, string &key){ 
    bool notfound = true;
    key = toUpperStr(key);
    cout << "---------------------------------\n";
    for (size_t i = 0; i < names.size(); i++) {
        if (key == toUpperStr(names[i])) {  
            notfound = false;
            cout << names[i] << "'s score = " << scores[i] << endl;
            cout << names[i] << "'s grade = " << grades[i] << endl;
        }
    }
    
    if (notfound) {
        cout << "Cannot be found." << endl;
    }
    cout << "---------------------------------\n";
}

void searchGrade(vector<string> &names, vector<int> &scores, vector<char> &grades, string key){
    bool notfound=true;
       cout<<"---------------------------------\n";
       for (unsigned int i = 0; i < grades.size(); i++){
           if (key[0] ==   grades[i] ){
               notfound= false;
               cout<< names[i] << " ("<<  scores[i]<<")" <<endl;
                
           }
       }
       if (notfound){
           cout<<"Cannot found."<<endl;
       }
       cout<<"---------------------------------\n";
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
