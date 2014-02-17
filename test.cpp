#include <iostream>
#include <regex>
#include <string>

using namespace std;

int main(int argc, char **argv) {

	string testSubject("Content-Type:   e e e e e e e  \t");

	regex testRegex;
	smatch testMatches;

	string inLine;

	while (true) {
		cout << ": ";
		getline(cin, inLine);
		if (inLine.compare("exit") == 0) {
			break;
		}
		if (inLine.compare("show") == 0) {
			cout << "[" << testSubject << "]" << endl;
			continue;
		}

		try {
			testRegex = inLine;
		}
		catch (regex_error error) {
			cout << "Invalid regex." << endl;
			continue;
		}


		if (regex_match(testSubject, testMatches, testRegex)) {
			cout << "Matches: ";
			for (int i = 0; i < testMatches.size(); i++) {
				cout << "[" << testMatches[i] << "] ";
			}
		}
		else {
			cout << "No match.";
		}
		cout << endl;
	}

	return 0;
}
