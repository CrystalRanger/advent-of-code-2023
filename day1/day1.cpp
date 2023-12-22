#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include <map>

using namespace std;

int main() {
    ifstream text;
    map<string, char> word_to_num = {
        {"one",'1'},
        {"two",'2'},
        {"three",'3'},
        {"four",'4'},
        {"five",'5'},
        {"six",'6'},
        {"seven",'7'},
        {"eight",'8'},
        {"nine",'9'}
    };
    regex first("(one|two|three|four|five|six|seven|eight|nine|[0-9])");
    regex last("(eno|owt|eerht|ruof|evif|xis|neves|thgie|enin|[0-9])");
    int sum = 0;
    smatch match;
    text.open("input.txt");
    string line;
    getline(text, line);
    while(text) {
        string number = "";
        if(line != "") {
            cout << line << endl;
            regex_search(line,match,first);
            if(isdigit(match.str(1).at(0))){
                number.append(match.str(1));
            } else {
                number.push_back(word_to_num.at(match.str(1)));
            }
            reverse(line.begin(),line.end());
            regex_search(line,match,last);
            if(isdigit(match.str(1).at(0))){
                number.append(match.str(1));
            } else {
                string num = match.str(1);
                reverse(num.begin(),num.end());
                number.push_back(word_to_num.at(num));
            }
            cout << number << endl;
            cout << stoi(number) << endl;
            sum += stoi(number);
            cout << sum << endl;
        }
        getline(text, line);
    }
    cout << sum << endl;
    return 0;
}