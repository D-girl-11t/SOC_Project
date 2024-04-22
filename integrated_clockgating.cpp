#include <iostream>
#include <vector>
#include <string>
#include<fstream>
#include<map>
#include<sstream>
#include<algorithm>
#include <cctype> 
#include <regex>
using namespace std;\

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
    vector<string> cg_wires;
    map<int, std::pair<int, int> > validation_output;
    int casenumber = -1;
    double ratio; 

   void  parse(const std::string lines[], int size)
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

    void validation ()
        {
            // Regular expressions to extract indices
            std::regex dff_regex(R"(\.D\((.*?)\))");
            std::regex dffout_regex(R"(\.Q\((.*?)\))");
            
            for (int i = 0; i < dff.size(); i++) {
            

            // // convert to single line
            // std::string single_line_dff;
            // for (char c : dff[i]) {
            //     if (c != '\n') {
            //         single_line_dff += c;
            //     }
            // }
            // std::cout<<single_line_dff;
            std::smatch match;
            if (std::regex_search(dff[i], match, dffout_regex)) {
                std::string dff_output = match[1];
                if (std::regex_search(dff[i], match, dff_regex)) {
                    std::string dff_input = match[1];
                // if (!output.empty()) {
                    // output.pop_back();
                    // output.pop_back();// Remove the last character
                    
                    std::cout << "Lineoutput " << i << ": " << dff_output <<std::endl;
                    std::cout << "Lineinput " << i << ": " << dff_input <<std::endl;
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
                        for (size_t k = 0; k < 2; ++k) {
                            if (C_all[k] == dff_output && C_all.back()== dff_input) {
                                casenumber = k;
                                found_q = true;
                                break;
                            }
                        }
                        
                        if (found_q) {
                            std::cout << "Found that unique mux" << std::endl;
                            //update the dff, mux and case
                            validation_output.insert({i, {j, casenumber}});
                        } else {std::cout << "Did not find 'q' in C_all" << std::endl;}
                        
                    
                }
                }
            } else {std::cout << "Line " << i << " dff does not contain '.Q('" << std::endl;}
        }
        ratio = (validation_output.size() / static_cast<double>(dff.size()) )*100;
        std::cout<<"Ratio of DFF clock gated = "<< ratio << "%" << endl;
        }



void replace ()
{
     for (const auto& pair : validation_output) {
        // cout << "Key: " << pair.first << ", Value: (" << pair.second.first << ", " << pair.second.second << ")" << endl;
        vector<string>muxcg,dffcg;
        int casecg;
        string line;
        istringstream issdff(dff[pair.first]);
        while (getline(issdff, line, '\n')) {
        size_t firstNonSpace = line.find_first_not_of(" \t\n\r");
        line.erase(0, firstNonSpace);
        dffcg.push_back(line);
    }
    istringstream issmux(mux[pair.second.first]);
        while (getline(issmux, line, '\n')) {
        size_t firstNonSpace = line.find_first_not_of(" \t\n\r");
        line.erase(0, firstNonSpace);
        muxcg.push_back(line);
    }
    casecg = pair.second.second;
    cout<<casecg<<endl;
    if (casecg==0)
    {
    size_t start_pos = muxcg[2].find_first_of('(');
    size_t end_pos = muxcg[2].find_first_of(')', start_pos);
    string dff_in = muxcg[2].substr(start_pos + 1, end_pos - start_pos - 1);
    start_pos = muxcg[4].find_first_of('(');
    end_pos = muxcg[4].find_first_of(')', start_pos);
    string dff_clk = muxcg[4].substr(start_pos + 1, end_pos - start_pos - 1);
    string and_out = muxcg[4].substr(start_pos + 1, end_pos - start_pos - 1);
    string new_dff = dffcg[0] + "\n" + ".CLK(" + dff_clk + ")," + "\n" + ".D(" + dff_in + ")," +"\n" + dffcg[3] + "\n" +  dffcg[4];
    start_pos = dffcg[1].find_first_of('(');
    end_pos =dffcg[1].find_first_of(')', start_pos);
    string and_a =  dffcg[1].substr(start_pos + 1, end_pos - start_pos - 1);
    start_pos = muxcg[3].find_first_of('(');
    end_pos =muxcg[3].find_first_of(')', start_pos);
    string and_b =  muxcg[3].substr(start_pos + 1, end_pos - start_pos - 1);
     size_t length = andGate.size();

    // Convert the length to a string
    stringstream ss;
    ss << length;
    string lengthStr = ss.str();


    string new_and = "sky_130_fd_sc_hd_and21 "+lengthStr+" ("+"\n"+".A(" + and_a + ")," + "\n" + ".B(" + and_b + ")," + "\n" + ".X(" + and_out +")"+"\n" + ");";
    andGate.push_back(new_and);
    dff[pair.first]=new_dff;
     mux.erase(mux.begin()+pair.second.first);
    
    
    }
    else
    {
    size_t start_pos = muxcg[1].find_first_of('(');
    size_t end_pos = muxcg[1].find_first_of(')', start_pos);
    string dff_in = muxcg[1].substr(start_pos + 1, end_pos - start_pos - 1);
    start_pos = muxcg[4].find_first_of('(');
    end_pos = muxcg[4].find_first_of(')', start_pos);
    string dff_clk = muxcg[4].substr(start_pos + 1, end_pos - start_pos - 1);
    string and_out = muxcg[4].substr(start_pos + 1, end_pos - start_pos - 1);
    string new_dff = dffcg[0] + "\n" + ".CLK(" + dff_clk + ")," + "\n" + ".D(" + dff_in + ")," +"\n" + dffcg[3] + "\n" +  dffcg[4];
    start_pos = dffcg[1].find_first_of('(');
    end_pos =dffcg[1].find_first_of(')', start_pos);
    string and_a =  dffcg[1].substr(start_pos + 1, end_pos - start_pos - 1);
    start_pos = muxcg[3].find_first_of('(');
    end_pos =muxcg[3].find_first_of(')', start_pos);
    string inv_a = muxcg[3].substr(start_pos + 1, end_pos - start_pos - 1);
    size_t length = inverter.size();

 
    stringstream ss;
    ss << length;
    string lengthStr = ss.str();
    size_t lengthcg = cg_wires.size();

  
    stringstream sscg;
    sscg << lengthcg;
    string lengthStrcg = sscg.str();
    cg_wires.push_back("cg"+lengthStrcg);
    string new_inverter = "sky130_fd_sc_hd__inv_1 " + lengthStr + " (" + "\n" + ".A(" + inv_a + ")," + "\n" + ".Y(cg" + lengthStrcg + ")," + "\n" + ");";
    
    size_t lengthand = andGate.size();
    stringstream ssand;
    ssand << lengthand;
    string lengthStrand = ssand.str();
     string new_and = "sky_130_fd_sc_hd_and21 "+lengthStrand+" ("+"\n"+".A(" + and_a + ")," + "\n" + ".B(cg" + lengthStrcg + ")," + "\n" + ".X(" + and_out +")"+"\n" + ");";
    andGate.push_back(new_and);
    inverter.push_back(new_inverter);
    dff[pair.first]=new_dff;
    mux.erase(mux.begin()+pair.second.first);

    }
    }
}
string modify_netlist(const std::string lines[], int size)
  {
    vector<int> mux_cfg_indices;
    vector<int> dff_cfg_indices;
    for (const auto& pair : validation_output) {
        // Extract key and pair values
        int key = pair.first;
        int firstValue = pair.second.first;

        // Add key to keysList
       dff_cfg_indices.push_back(key);

        // Add first value to firstValuesList
        mux_cfg_indices.push_back(firstValue);
    }
    string new_lines;
    int i ;
    i=0;
    int j=0;
    while(i<size-1)
    {
        int foundand =lines[i].find("and2");
        int foundinverter = lines[i].find("inv");
        int founddff = lines[i].find("DFF");
        int foundmux = lines[i].find("mux");
        if(foundand != string::npos)
        {
            i=i+5;
            continue;
        }
         if(foundinverter != string::npos)
        {
            i=i+4;
            continue;
        }
        if(founddff != string::npos)
        {
            i=i+5;
            continue;
        }
        if(foundmux != string::npos)
        {
            i=i+6;
            continue;
        }
        int foundmodule =lines[i].find("module");
        if(foundmodule != string::npos)
        {new_lines = new_lines + lines[i] + "\n";
        for (auto k = cg_wires.begin(); k != cg_wires.end(); ++k) {
        new_lines= new_lines + "wire " + *k + ";" + "\n" ;
    }
    i++;
    continue;
        }
        
        // auto it = find(mux_indices.begin(), mux_indices.end(), i);
        // if (it !=mux_indices.end())
        // {
        //     auto index_mux = find(mux_indices.begin(), mux_indices.end(), i);
        //     int mux_index = distance(mux_indices.begin(), index_mux);
        //     auto cgmux = find( mux_cfg_indices.begin(),  mux_cfg_indices.end(), mux_index);
        //     if(cgmux != mux_cfg_indices.end())
        //     {
        //         i=i+6;
        //         continue;
        //     }
             
        // }
        // auto itdf = find(dff_indices.begin(), dff_indices.end(), i);
        // if (itdf !=dff_indices.end())
        // {
        //     auto index_dff = find(dff_indices.begin(), dff_indices.end(), i);
        //     int dff_index = distance(dff_indices.begin(), index_dff);
        //     auto cgdff = find(dff_cfg_indices.begin(), dff_cfg_indices.end(), dff_index);
        //     if(cgdff !=dff_cfg_indices.end())
        //     {
        //        i=i+5;
        //        continue;
        //     }
        // }
        new_lines=new_lines + lines[i] + "\n";
        i++;
        j++;
    }
     for (auto k = inverter.begin(); k != inverter.end(); ++k) {
        string line;
        istringstream issdff(*k);
        while (getline(issdff, line, '\n')) {
        new_lines=new_lines +line + "\n";
    }}
     for (auto k = andGate.begin(); k != andGate.end(); ++k) {
        string line;
        istringstream issdff(*k);
        while (getline(issdff, line, '\n')) {
            
        new_lines=new_lines +line + "\n";
    }}
      for (auto k = mux.begin(); k != mux.end(); ++k) {
        string line;
        istringstream issdff(*k);
        while (getline(issdff, line, '\n')) {
        new_lines=new_lines +line + "\n";
    }}
     for (auto k = dff.begin(); k != dff.end(); ++k) {
        string line;
        istringstream issdff(*k);
        while (getline(issdff, line, '\n')) {
        new_lines=new_lines +line + "\n";
    }}
    
  
    new_lines=new_lines+"endmodule"+'\n';
    cout<<"modified netlist"<<endl;
    cout<<new_lines;
    return new_lines;
   

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
    p1.validation();
    for (const auto& pair : p1.validation_output) {
        std::cout << "Key: " << pair.first << ", Value: (" << pair.second.first << ", " << pair.second.second << ")" << std::endl;
    }
    cout<<"validation completed"<<endl;
//    p1.display();
    p1.replace();

//    p1.display();
    string s1;
    s1=p1.modify_netlist(lines,numLines);
  
    std::ofstream outFile("cg.v"); // Change the output filename if needed
    if (outFile.is_open()) {
        outFile << s1; // Write the string to the file
        outFile.close();}
    return 0;  
}