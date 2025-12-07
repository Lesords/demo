#include <iostream>
#include <string>
#include <regex>

int main() {
	char cVal[10] = "123456";
    std::string sVal(cVal);
	std::regex e("\\d{6}");

    /*
     * regex_match: full match
     * regex_search: partial search
     */

    // const char *
	std::cmatch cm;
	std::regex_match(cVal, cm, e);

	std::cout << "cm size: " << cm.size() <<"\n";
    std::cout << "value: " << cm[0] << "\n";

    // string
	std::smatch sm;
	std::regex_match(sVal, sm, e);

	std::cout << "sm size: " << sm.size() << "\n";
    std::cout << "value: " << sm[0] << "\n";

    e.assign("\\d{2}");
	while(std::regex_search(sVal, sm, e)) {
        printf("size: %ld, value: %s\n", sm.size(), sm.str().c_str());
		sVal = sm.suffix().str(); 
	}

	return 0;
}
