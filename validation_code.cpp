#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <regex>

int main() {
    // Sample array of DFFs and MUXes
    std::vector<std::string> dffs = {
    "sky130_fd_sc_hd__dfxtp_1 \q$_DFFE_PP_  ("
    ".CLK(clk),"
    ".D(_0_),"
    ".Q(q));",
        "sky130_fd_sc_hd__dfxtp_1 \q$_DFFE_PP_  ("
    ".CLK(clk),"
    ".D(_0_),"
    ".Q(q1));",
    };

    std::vector<std::string> muxes = {
        "",
        "",
        "sky130_fd_sc_hd_mux2_4 _1 ( .A0(q1), .A1(d), .S(en), .X(0) );",
        "sky130_fd_sc_hd_mux2_4 _1 ( .A0(q), .A1(d), .S(en), .X(0) );",
        // Add more MUXes here
    };

    // Dictionary to store the mapping
    std::map<int, std::pair<int, int>> validation_output;

    // Regular expressions to extract indices
    std::regex dff_regex(R"(\.Q\((.*?)\))");
    std::regex mux_regex(R"(^(.*)(?=\.S))");
    
    int casenumber = -1;

    // Iterate through DFFs
    for (int i = 0; i < dffs.size(); i++) {
        std::smatch match;
        std::cout<<"dff";
        if (std::regex_search(dffs[i], match, dff_regex)) {
            std::string dff_output = match[1];
            // if (!output.empty()) {
                // output.pop_back();
                // output.pop_back();// Remove the last character
            std::cout << "Line " << i << ": " << dff_output <<std::endl;
            // } 
            // Iterate through MUXes
            for (int j = 0; j < muxes.size(); j++) {
                std::vector<std::string> C_all;
                std::smatch mux_match;
                // extracting inputs irrespective of anything
                    // A = Extract text before .S
                std::regex regex_A(R"(^(.*?)(?=\.S))");
                std::smatch match_A;
                if (std::regex_search(muxes[j], match_A, regex_A)) {
                    std::string A = match_A[1];
                    // std::cout << "A = " << A << std::endl;
                
                // B = Remove everything before the first dot (.)
                    std::regex regex_B(R"(\.(.*))");
                    std::smatch match_B;
                    if(std::regex_search(A, match_B, regex_B)){
                        std::string B = match_B[1];
                        // std::cout << "B = " << B << std::endl;
            
                // C = Extract text within parenthesis
                //dont touch this code, its working
                        std::regex regex_C(R"(\((.*?)\))");
                        std::smatch match_C;
                        auto B_begin = std::sregex_iterator(B.begin(), B.end(), regex_C);
                        auto B_end = std::sregex_iterator();
                        for (std::sregex_iterator it = B_begin; it != B_end; ++it) {
                            std::smatch match = *it;
                            if (match.size() > 1) {
                                std::string C = match[1];
                                C_all.push_back(C);
                            }
                        }
                        if (!C_all.empty()) {
                            std::cout << "inputs of mux ";
                            for (const auto& c : C_all) {
                                std::cout << c << " ";
                            }
                            std::cout << std::endl;
                        } else {std::cout << "inputs empty ? recheck" << std::endl;}
                    }
                
                
                    bool found_q = false;
                    for (size_t k = 0; k < C_all.size(); ++k) {
                        if (C_all[k] == dff_output) {
                            casenumber = k;
                            found_q = true;
                            break;
                        }
                    }
                    
                    if (found_q) {
                        std::cout << "Found 'q' in mux" << std::endl;
                        //update the dff, mux and case
                        validation_output.insert({i, {j, casenumber}});
                    } else {std::cout << "Did not find 'q' in C_all" << std::endl;}
                    
                } else {std::cout << "No selectors found ? Recheck" << std::endl;}
            }
        } else {std::cout << "Line " << i << " does not contain '.Q('" << std::endl;}
    }

    // Print the mapping
    for (const auto& pair : validation_output) {
        std::cout << "Key: " << pair.first << ", Value: (" << pair.second.first << ", " << pair.second.second << ")" << std::endl;
    }

    return 0;
}
