#include<algorithm>
#include<iostream>
#include<cstdlib>

int
main(void)
{
	unsigned long int maxElf = 0, thisElf = 0;

	while (!std::cin.eof()) {
		std::string s;
		std::getline(std::cin, s);

		if (s != "") {
			thisElf += atoi(s.c_str());
		} else {
			maxElf = std::max(maxElf, thisElf);
			thisElf = 0;
		}

	}
	std::cout << maxElf << std::endl;
	return 0;
}
