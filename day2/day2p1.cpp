#include <iostream>
#include <fstream>
#include <regex>


using namespace std;

ifstream text;
smatch match;

vector<string> split_by(string s, char c) {
    vector<string> ret;
    int l = 0;
    int r;
    while(s.find(c,l) != string::npos) {
        r = s.find(c,l);
        ret.push_back(s.substr(l,r-l));
        l = r+1;
    }
    ret.push_back(s.substr(l,s.length()-l));
    return ret;
}

int main() {
    string buf;
    string line;
    text.open("./input.txt");
    regex reg ("(\\d*)(?=:)");
    int sum = 0;
    while(getline(text, line)) {
        //get game id
        cout << line << endl;
        int id;
        bool valid = true;
        if(regex_search(line,match,reg)) {
            id = stoi(match.str(1));
        } else {
            cout << "no match" << endl;
        }
        int red_n = 0;
        int green_n = 0;
        int blue_n = 0;
        for(string s: split_by(line.substr(6+match.str(1).length()), ';')) {
            cout << s << endl;
            if(valid) {
                regex red("(\\d*)(?= red)");
                regex green("(\\d*)(?= green)");
                regex blue("(\\d*)(?= blue)");
                
                if(regex_search(s,match,red)) {
                    red_n = stoi(match.str(1));
                    cout << "red: "<< match.str(1) << endl;
                }
                if(regex_search(s,match,green)) {
                    green_n = stoi(match.str(1));
                    cout << "green" << endl;
                }
                if(regex_search(s,match,blue)) {
                    blue_n = stoi(match.str(1));
                    cout << "blue" << endl;
                }
                valid = (red_n <= 12) && (green_n <= 13) && (blue_n <= 14);
            }
        }
        if(valid) {
            sum += id;
            cout << "added, sum is " << sum << endl;
        }
    }
    cout << sum << endl;
}

