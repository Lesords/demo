#include <iostream>
#include <map>
#include <string>

std::map<std::string, int> mapValues{{"name", 123}, {"value", 321}};

void debug(const std::map<std::string, int> &value) {
    printf("map value - size: %ld\n", value.size());
    for (auto v: value) {
        printf("%s = %d\n", v.first.c_str(), v.second);
    }
    printf("\n");
}

int main() {
    printf("name: %d, value: %d\n", mapValues["name"], mapValues["value"]);
    if (mapValues.find("status") == mapValues.end()) {
        printf("status not exists\n");
    }
    debug(mapValues);

    mapValues["status"] = 1;
    debug(mapValues);
	return 0;
}
