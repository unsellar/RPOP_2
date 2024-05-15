#include <iostream>
#include <fstream>
#include <regex>
#include <cctype>
#include <string>
using namespace std;

//string        int : string        4:spam                          ^\d+:[a-zA-Z]*$
//int           i int e             i1024e          i(0|[1-9][0-9]*)e

//list          l item item e       l i101e l 4:spam i1024e e e  [101, ['spam', 1024]]                                              l([a-z0-9:]+)e

//dict          d key value e       d 1:a 0: 1:p l 1:b 2:cd e e     d(([^:]+)([^e]+))+e

void print(string str){
    ofstream output;
    output.open("/Users/vsevolod/Documents/RPOP_2/RPOP_2/output.txt", ios_base::app);
    output << str;
    output.close();
}

bool checkstring(string line){
    regex str("\\d+:[a-zA-Z]*");
    return regex_match(line, str);
}

bool checkint(string line){
    regex str("i(0|[1-9][0-9]*)e");
    return regex_match(line, str);}

bool checklist(string line){
    regex str("l([a-z0-9:]+)e");
    return regex_match(line, str);}

bool checkdict(string line){
    regex str("d(([^:]+)([^e]+))+e");
    return regex_match(line, str);
}

string decodestring(string line){
    string result = "";
    string stringlength;
    if(line[0] == '0'){
        line.erase(0, 2);
        cout << "empty string is detecteed" << endl;
        print("''");
        return line;
    }
    for(int i = 0; isdigit(line[0]); i++){
        stringlength += line[0];
        line.erase(0, 1);
    }
    cout << "string length is   " << stoi(stringlength) << endl;
    int length = stoi(stringlength);
    line.erase(0, 1);
    for(int i = 0; i < length; i++){
        result += line[0];
        line.erase(0, 1);
    }
    cout << "decoded string is   " << result << endl;
    print("'" + result + "'");
    return line;
}

string decodeint(string line){
    string result;
    line.erase(0, 1);
    for(int i = 0; line[0] != 'e'; i++){
        result += line[0];
        line.erase(0, 1);
    }
    line.erase(0, 1);
    cout << "decoded int is   " << result << endl;
    print("'" + result + "'");
    return line;
}

string decodelist(string line){
    // l item item e       l i101e l 4:spam i1024e e e  [101, ['spam', 1024]]
    print("[");
    line.erase(0,1);
    cout << "line to list checking  " << line << endl;
    while(line[0] != 'e'){
        if(isdigit(line[0])){//string
            cout << "checker detected string" << endl;
            line = decodestring(line);
        }else if (line[0] == 'i'){
            cout << "checker detected int" << endl;
            line = decodeint(line);
        }else if (line[0] == 'l'){
            cout << "checker detected list" << endl;
            line = decodelist(line);
        }else if (line[0] == 'd'){
            cout << "checker detected dict" << endl;
            return "dict";//2222222222222222222222222222222222222222222222222222222222222222222222
        }
        if(line[0] != 'e') print(", ");
    }
    print("]");
    return line;
}

string decodedict(string line){
    //d key value e       d 1:a 0: 1:p l 1:b 2:cd e e     d(([^:]+)([^e]+))+e
    print("[");
    line.erase(0,1);
    cout << "line to dict checking  " << line << endl;
    while(line[0] != 'e'){
        //key find sequence
        if(isdigit(line[0])){//string
            cout << "checker detected string" << endl;
            line = decodestring(line);
        }else if (line[0] == 'i'){
            cout << "checker detected int" << endl;
            line = decodeint(line);
        }else if (line[0] == 'l'){
            cout << "checker detected list" << endl;
            line = decodelist(line);
        }else if (line[0] == 'd'){
            cout << "checker detected dict" << endl;
            line = decodedict(line);//2222222222222222222222222222222222222222222222222222222222222222222222
        }
        //value find sequence
        print("=>");
        if(isdigit(line[0])){//string
            cout << "checker detected string" << endl;
            line = decodestring(line);
        }else if (line[0] == 'i'){
            cout << "checker detected int" << endl;
            line = decodeint(line);
        }else if (line[0] == 'l'){
            cout << "checker detected list" << endl;
            line = decodelist(line);
        }else if (line[0] == 'd'){
            cout << "checker detected dict" << endl;
            line = decodedict(line);//2222222222222222222222222222222222222222222222222222222222222222222222
        }
        if(line[0] != 'e') print(" ");
    }
    print("]");
    return line;
}

string task2(){
    ifstream input2 ("/Users/vsevolod/Documents/RPOP_2/RPOP_2/input2.txt");
//    ofstream output;
//    output.open("/Users/vsevolod/Documents/RPOP_2/RPOP_2/output.txt");
    string ccode;
    input2 >> ccode; //getline
    cout << "checked line is:   " << ccode << endl;
    if(isdigit(ccode[0])){
        cout << "checker detected string" << endl;
        return decodestring(ccode);
    }else if (ccode[0] == 'i'){
        cout << "checker detected int" << endl;
        return decodeint(ccode);
    }else if (ccode[0] == 'l'){
        cout << "checker detected list" << endl;
        return decodelist(ccode);
    }else if (ccode[0] == 'd'){
        cout << "checker detected dict" << endl;
        return decodedict(ccode);
    }
    print("Error pos 0");
    return "bad ending(";
}


int main(){
    ofstream output1;
    output1.open("/Users/vsevolod/Documents/RPOP_2/RPOP_2/output.txt");
    output1.close();
    int num;
    string test = "test";
    test.erase(test.length() - 1);
    cout << test << endl;
//    cout << "Task num: ";
//    cin >> num;
    num = 2;
    
    if (num == 2){
        task2();
//        cout << "final result is   " << res << endl;
//        output << res;
    }
    return 0;
}
