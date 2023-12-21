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
        vector<int> reds;
        vector<int> greens;
        vector<int> blues;
        for(string s: split_by(line.substr(6+match.str(1).length()), ';')) {
            cout << s << endl;
            if(valid) {
                regex red("(\\d*)(?= red)");
                regex green("(\\d*)(?= green)");
                regex blue("(\\d*)(?= blue)");
                
                if(regex_search(s,match,red)) {
                    reds.push_back(stoi(match.str(1)));
                }
                if(regex_search(s,match,green)) {
                    greens.push_back(stoi(match.str(1)));
                }
                if(regex_search(s,match,blue)) {
                    blues.push_back(stoi(match.str(1)));
                }
            }
        }
        int max_red = *max_element(reds.begin(),reds.end());
        int max_blue = *max_element(blues.begin(),blues.end());
        int max_green = *max_element(greens.begin(),greens.end());
        sum += max_red*max_blue*max_green;
    }
    cout << sum << endl;
}

