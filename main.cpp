#include <iostream>
#include <vector>
#include <map>

using namespace std;

string prefix(int size, string word) {
    string ans = "";
    for(int i = 0; i < size; i++) {
        ans += word[i];
    }
    return ans;
}

bool contains(string container, string item) {
    for(int i = 0; i < item.size(); i++) {
        if(container[container.size() - 1 - i] != item[item.size() - 1 - i]) {
            return false;
        }
    }
    return true;
}

int main() {
    // Declare
    int size;
    string pattern;
    string text;
    vector<char> alphabet;
    for(char letter = 'a'; letter <= 'z'; letter++) {
        alphabet.push_back(letter);
    }
    alphabet.push_back('.');
    alphabet.push_back(',');
    alphabet.push_back(' ');

    // Get
    cin >> size;
    cin.ignore();
    getline(cin, text);
    getline(cin, pattern);

    // Process
    map<int, map<char, int>> transition;
    int k;
    for(int i = 0; i <= pattern.size(); i++) {
        for(char letter : alphabet) {
            k = min((int)pattern.size() + 1, i + 2);
            do {
                k--;
            } while(k != 0 && !contains(
                    pattern.substr(0, i) + letter,
                    pattern.substr(0, k)));

            transition[i][letter] = k;
        }
    }

    vector<int> occurrences;
    int state = 0;
    for(int i = 0; i < text.size(); i++) {
        state = transition[state][text[i]];
        if(state == pattern.size()) {
            occurrences.push_back( i + 1 - pattern.size() + 1 );
        }
    }

    // Show
    char command;
    while(cin >> command, command != 'e') {
        if(command == 's') {
            for(int i : occurrences) {
                cout << i << endl;
            }
        } else {
            cout << "Tabela Delta" << endl;
            for(int i = 0; i <= pattern.size(); i++) {
                for(char letter : alphabet) {
                    if(transition[i][letter] != 0) {
                        cout << "[" << i << ", " << letter << "]: " << transition[i][letter] << endl;
                    }
                }
            }
        }
    }

}