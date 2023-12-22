#include <iostream>
#include <fstream>
#include <regex>

using namespace std;

ifstream text;

struct coords {
	int x;
	int y;
	int width;
	string text;
};

vector<coords> find_regex(string s, regex reg, int y) {
	vector<coords> finds;
	string search = s;
	smatch match;
	int x = 0;
	while(regex_search(search, match, reg)) {
		coords find;
		cout << "text: " << match.str(1) << endl;
		find.x = x + match.position();
		find.y = y;
		x += match.prefix().length() + match.str(1).length();
		find.width = match.length();
		find.text = match.str(1);
		finds.push_back(find);
		search = match.suffix();
	}
	return finds;
}

int main() {
	text.open("input.txt");

	string line;
	string last;

	smatch match;

	regex get_symbols("(\\*)");
	regex get_nums("(\\d+)");
	
	int y = 0;

	vector<coords> symbols;
	vector<coords> numbers;

	while(getline(text, line)) {
		cout << y << " " << line << endl;
		for(coords c: find_regex(line, get_symbols, y)) {
			symbols.push_back(c);
			cout << c.x << " " << c.y << " " << endl;
		}	
		for(coords c: find_regex(line, get_nums, y)) {
			numbers.push_back(c);
			cout << c.x << " " << c.y << " " << endl;
		}
		y++;
	}
	

	int sum;

	for(coords s: symbols) {
		cout << "symbol: " << s.text << endl;
		int matches = 0;
		vector<coords> parts;
		for(coords n: numbers) {
			if(abs(n.x - s.x) <= 1 || abs((n.x+n.width-1)-s.x) <= 1) {
				if(abs(n.y-s.y)<= 1) {
					cout << "match" << n.x << " " << n.y << " " << endl;
					matches += 1;
					parts.push_back(n);
				}
			}
		}
		if(matches == 2) {
			sum += stoi(parts[0].text) * stoi(parts[1].text);
		}
	}
	cout << sum << endl;
	return 0;
}
