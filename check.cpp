#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <map>
#include <sstream>
#include <regex>
using namespace std;
int main() {
    std::string text = "sky130_fd_sc_hd_mux2_4 _1_ ( .A0(q), .A1(d), .S(en), .X(_0_) );";

    // Define the regular expression pattern
    std::regex regex_A(R"(^(.*?)(?=\.S))");

    // Search for the pattern in the text
    std::smatch match_A;
    if (std::regex_search(text, match_A, regex_A)) {
        std::string A = match_A[1];
        std::cout << "Text before .S: " << A << std::endl;
    } else {
        std::cout << "Pattern not found" << std::endl;
    }

    return 0;
}
