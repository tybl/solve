#include <fstream>
#include <iostream>
#include <iterator>

void run(std::string input) {
	std::cout << "Input: $" << input << "$ end of input\n";
}

void run_file(std::string path) {
	std::ifstream file(path);
	std::string input(std::istreambuf_iterator<char>{file}, {});
	run(input);
}

void run_prompt() {
	std::string input;
	while (true) {
		std::cout << "> ";
		std::getline(std::cin, input);
		if (input.empty()) break;
		run(input);
	}
}

int main(int argc, char* argv[]) {
	if (2 < argc) {
		return -1;
	} else if (2 == argc) {
		run_file(argv[1]);
	} else if (1 == argc) {
		run_prompt();
	}
	return 0;
}
