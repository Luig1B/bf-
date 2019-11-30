#include <iostream>
#include <string>
#include <fstream>
#include <vector>

int main(int argc, char** argv)
{
	std::string source;

	if (argc == 1) {
		std::cout << "Source-\n\t";
		std::cin >> source;
	} else {
		std::ifstream file;
		file.open(argv[1]);

		if (!file.is_open()) {
			std::cout << "No such file directory\n";
			return -1;
		}

		std::string temp;
		while (std::getline(file, temp)) { source += temp; }

		file.close();
	}

	unsigned char mem[256];
	int funcs[256];
	for (int i = 0; i < 256; i++) {
		mem[i] = 0;
		funcs[i] = 0;
	}
	unsigned char ptr = 0;
	std::vector<int> callstack;

	std::cout << "Output-\n\t";
	for (int i = 0; i < source.size(); i++) {
		char c = source[i];

		switch (c) {
			case '+': mem[ptr]++; break;
			case '-': mem[ptr]--; break;
			case '>': ptr++; break;
			case '<': ptr--; break;
			case '.': std::cout << mem[ptr]; break;
			case ',': std::cin >> mem[ptr]; break;
			case '[':
			{
				if (mem[ptr]) break;
				int count = 0;
				while (source[++i] != ']' || count > 0) {
					if (source[i] == '[') count++;
					else if (source[i] == ']') count--;
					else if (source.size() <= i + 1) {
						std::cout << "\nSyntax Error" << std::endl;
						return -1;
					}
				}
			} break;
			case ']':
			{
				if (!mem[ptr]) break;
				int count = 0;
				while (source[--i] != '[' || count > 0) {
					if (source[i] == ']') count++;
					else if (source[i] == '[') count--;
					else if (i - 1 < 0) {
						std::cout << "\nSyntax Error" << std::endl;
						return -1;
					}
				}
			} break;
			case '{':
			{
				if (mem[ptr] == 0) {
					std::cout << "\nTrying to make a null function" << std::endl;
					return -1;
				}
				funcs[mem[ptr]] = i;
				int count = 0;
				while (source[++i] != '}')
					if (i + 1 >= source.size()) {
						std::cout << "\nSyntax Error" << std::endl;
						return -1;
					}
			} break;
			case '}':
			{
				if (callstack.size() == 0) {
					std::cout << "\nSyntax Error" << std::endl;
					return -1;
				}
				i = callstack[callstack.size() - 1];
				callstack.pop_back();
			} break;
			case '#':
			{
				if (mem[ptr] == 0) break;
				int dest = funcs[mem[ptr]];
				if (dest == 0) {
					std::cout << "\nTrying to acess a null function" << std::endl;
					return -1;
				}
				callstack.push_back(i);
				i = dest;
			} break;
		}
	}

	std::cout << "\nEnd of the program." << std::endl;
}
