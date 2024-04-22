#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <map>
#include <sstream>
#include <regex>
using namespace std;


class integrated_clock_gating   // This Parse object will parse throgh the netlist and collect all the dflip flops , multiplexers and and gates in lists.
{
    public:
    vector<string>  dff;
    vector<string>  mux;
    vector<string>  andGate;
    vector<string> inverter;
    vector<int> dff_indices;
    vector<int> mux_indices;
    vector<int> and_indices;
    vector<int> inv_indices;
    map<int, std::pair<int, int>> validation_output;
    int casenumber = -1;

   void parse(const std::string lines[], int size)
    {
        int i;
        i=0;
        while(i<size)
        {
           
            int founddff =lines[i].find("DFFE");
            int foundmux =lines[i].find("mux2");
            int foundand =lines[i].find("and2");
            int foundinverter = lines[i].find("inv");
             if(founddff != string::npos)
             {
                dff_indices.push_back(i);
                string flip_flop=lines[i];
                int j;
                for (j=1;j<=4;j++)
                flip_flop=flip_flop +"\n" + lines[i+j];
                dff.push_back(flip_flop);
                i=i+j;

             }
             else if(foundmux != string::npos)
             {
                mux_indices.push_back(i);
                string mulitplexer=lines[i];
                int j;
                for (j=1;j<=5;j++)
                mulitplexer=mulitplexer +"\n" + lines[i+j];
                mux.push_back(mulitplexer);
                i=i+j;
             }
             else if (foundand != string::npos)
             {
                and_indices.push_back(i);
                string and_gate=lines[i];
                int j;
                for (j=1;j<=4;j++)
                and_gate=and_gate +"\n" + lines[i+j];
                
                andGate.push_back(and_gate);
                i=i+j;
             }
             else if (foundinverter != string::npos)
             {
                inv_indices.push_back(i);
                string inv=lines[i];
                int j;
                for (j=1;j<=3;j++)
                inv=inv +"\n" + lines[i+j];
                
                inverter.push_back(inv);
                i=i+j;
             }
             
             else
             i++;

        }
    }
//     void replace(const map<int, int>& myMap)
//     {
//         for (const auto& pair : myMap) {
//         vector<string> muxcg ,dffcg ;
//         string line;
//         while (getline(mux[pair.second], line, '\n')) {
//         muxcg.push_back(line);
//     }
//    while (getline(dff[pair.first], line, '\n')) {
//         dffcg.push_back(line);
//     }
//     }

//     }
// 
// 
    void validation ()
    {
        // Regular expressions to extract indices
        std::regex dff_regex(R"(\.D\((.*?)\))");
        std::regex dffout_regex(R"(\.Q\((.*?)\))");

        for (int i = 0; i < dff.size(); i++) {
        std::smatch match;
        // std::cout<<"dff";
        if (regex_search(dff[i], match, dff_regex)) {
            std::string dff_output = match[1];
            if (std::regex_search(dff[i], match, dff_regex)) {
                std::string dff_input = match[1];
            // if (!output.empty()) {
                // output.pop_back();
                // output.pop_back();// Remove the last character
                // std::cout << "Lineoutput " << i << ": " << dff_output <<std::endl;
                // std::cout << "Lineinput " << i << ": " << dff_input <<std::endl;
                // } 
                // Iterate through MUXes
                for (int j = 0; j < mux.size(); j++) {

                    // convert to single line
                    std::string single_line_text;
                    for (char c : mux[j]) {
                        if (c != '\n') {
                            single_line_text += c;
                        }
                    }
                    std::vector<std::string> C_all;
                    std::smatch mux_match;
                    // extracting inputs irrespective of anything
                                          
                    
                    
                // B = Remove everything before the first dot (.)
                    std::regex regex_B(R"(\.(.*))");
                    std::smatch match_B;
                    if(std::regex_search(single_line_text, match_B, regex_B)){
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
                        // if (!C_all.empty()) {
                        //     // std::cout << "elements of mux ";
                        //     for (const auto& c : C_all) {
                        //         std::cout << c << " ";
                        //     }
                        //     std::cout << std::endl;
                        // } //else {std::cout << "no elements ? recheck" << std::endl;}
                    }
                
                
                    bool found_q = false;
                    for (size_t k = 0; k < C_all.size(); ++k) {
                        if (C_all[k] == dff_output && C_all.back()== dff_input) {
                            casenumber = k;
                            found_q = true;
                            break;
                        }
                    }
                    
                    if (found_q) {
                        // std::cout << "Found that unique mux" << std::endl;
                        //update the dff, mux and case
                        validation_output.insert({i, {j, casenumber}});
                    } //else {std::cout << "Did not find 'q' in C_all" << std::endl;}
                    
                // else {std::cout << "No selectors found ? Recheck" << std::endl;}
            }
            }
        } //else {std::cout << "Line " << i << " dff does not contain '.Q('" << std::endl;}
    }

    }


    void display()
    {
        cout<<"D flip flop list"<<endl;
        for (const string& str : dff) {
        cout << str << endl;
        }
        cout<<"Mux list"<<endl;
        for (const string& str : mux) {
            cout << str << endl;
        }
        cout<<"And gate list"<<endl;
        for (const string& str : andGate) {
            cout << str << endl;
        }
        cout<<"D flip flop indices"<<endl;
            for (const int& str : dff_indices) {
            cout << str << endl;
        }
        cout<<"Mux indices"<<endl;
            for (const int& str : mux_indices) {
            cout << str << endl;
        }
        
    }
};

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " <filename>" << std::endl;
        return 1; // return error code 1
    }

    ifstream file(argv[1]);
    if (!file.is_open()) {
        cerr << "Error: Unable to open file " << argv[1] << endl;
        return 1; // return error code 1
    }

    int numLines = 0;
    string line;
    while (getline(file, line)) {
        ++numLines;
    }

    file.close();
    file.open(argv[1]);
    string lines[numLines];

    int index = 0;
    while (getline(file, line)) {
        lines[index++] = line;
    }
    file.close();
    //intial netlist 
    cout<<"Intiial Netlist"<<endl;
    cout << "Lines read from file " << argv[1] << ":" << endl;
    for (int i = 0; i < numLines; ++i) {
        cout << lines[i] <<endl;
    }
    integrated_clock_gating p1;
    p1.parse(lines,numLines);
   //After parsing
    cout<<"Parsing Completed"<<endl;
    // p1.display();
    p1.validation();
    for (const auto& pair : p1.validation_output) {
        std::cout << "Key: " << pair.first << ", Value: (" << pair.second.first << ", " << pair.second.second << ")" << std::endl;
    }
    cout<<"validation completed"<<endl;
    


    return 0;

   
}
