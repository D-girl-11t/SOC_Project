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
string lengthvec(vector<string>  a , int b)
{
    size_t length = a.size() +b;
            stringstream sscg;
            sscg << length;
            string lengthStrcg = sscg.str();
            return lengthStrcg;
}
class integrated_clock_gating   // This Parse object will parse throgh the netlist and collect all the dflip flops , multiplexers and and gates in lists.
{
    public:
    int obsize;
    vector<string>  dff;
    vector<string>  mux;
    vector<string>  andGate;
    vector<string> inverter;
    vector<string> norGate;
    vector<string> neg_latches;
    vector<string> pos_latches;
    vector<int> dff_indices;
    vector<int> mux_indices;
    vector<int> and_indices;
    vector<int> inv_indices;
    vector<int> nor_indices;
    vector<int> neglatch_indices;
    vector<int> poslatch_indices;
    vector<string> objects;
    vector<string> cg_wires;
    vector<int> gated_mux;
    int flag;
    struct myvalues {
    std::pair<int, int> og;
    int ii;
    int cc;
    };
    std::map<int, myvalues> validation_output;
    // std::map<int, std::pair<int, int>, int, int> validation_output;
    int casenumber = -500;
    int clockedge = -500;
    int inv_index = -500;
    double ratio; 
    //some necessary info
    std::vector<std::vector<std::vector<string>>> necessary_info;    //for every dff

   void  parse(const std::string lines[], int size)
    {
        int i;
        i=0;
        while(i<size)
        {
           
            int founddff =lines[i].find("_dfxtp");
           
            int foundmux =lines[i].find("_mux2");
            int foundand =lines[i].find("_and2");
            int foundinverter = lines[i].find("_inv");
            int foundneglatch = lines[i].find("_dlxtn");
            int foundposlatch = lines[i].find("_dlxtp");
            int foundnor = lines[i].find("_nor2");
            int foundobb = lines[i].find("sky130hd");
            if(foundobb != string::npos)
             {
              objects.push_back(lines[i]);
             }

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
             else if (foundnor != string::npos)
             {
                nor_indices.push_back(i);
                string nor=lines[i];
                int j;
                for (j=1;j<=4;j++)
                nor=nor +"\n" + lines[i+j];
                
                norGate.push_back(nor);
                i=i+j;
             }
              else if (foundneglatch != string::npos)
             {
                neglatch_indices.push_back(i);
                string negl=lines[i];
                int j;
                for (j=1;j<=4;j++)
                negl=negl +"\n" + lines[i+j];
                
                neg_latches.push_back(negl);
                i=i+j;
             }
              else if (foundposlatch != string::npos)
             {
                poslatch_indices.push_back(i);
                string posl=lines[i];
                int j;
                for (j=1;j<=4;j++)
                posl=posl +"\n" + lines[i+j];
                
                pos_latches.push_back(posl);
                i=i+j;
             }
             
             else
             i++;

        }
obsize=objects.size() + 4;
    }

    void validation ()
        {
            // Regular expressions to extract indices
            std::regex dff_regex(R"(\.D\((.*?)\))");
            std::regex dffout_regex(R"(\.Q\((.*?)\))");
            std::regex dffclock_regex(R"(\.CLK\((.*?)\))");
            
            for (int i = 0; i < dff.size(); i++) {
                std::vector<std::vector<string>> info;


                // // convert to single line
                // std::string single_line_dff;
                // for (char c : dff[i]) {
                //     if (c != '\n') {
                //         single_line_dff += c;
                //     }
                // }
                // std::cout<<single_line_dff;
                std::smatch match_in;
                std::smatch match_out;
                std::smatch match_clk;
                vector<string> dff_elements;
                if (std::regex_search(dff[i], match_in, dffout_regex)) {
                std::string dff_output = match_in[1];
                if (std::regex_search(dff[i], match_out, dff_regex)) {
                    std::string dff_input = match_out[1];
                    if(std::regex_search(dff[i], match_clk, dffclock_regex)) {
                        std::string dff_clock = match_clk[1];
                        // std::cout << "Lineclk " << i << ": " << dff_clock <<std::endl;
                    
                    // if (!output.empty()) {
                    // output.pop_back();
                    // output.pop_back();// Remove the last character
                    
                    // std::cout << "Lineoutput " << i << ": " << dff_output <<std::endl;
                    // std::cout << "Lineinput " << i << ": " << dff_input <<std::endl;
                    // } 
                    dff_elements.push_back(dff_input);
                    dff_elements.push_back(dff_output);
                    dff_elements.push_back(dff_clock);
                    //lets find if clock is negedge or not
                    info.push_back(dff_elements);
                    // iterate through all inverters and check if output of inverter is input to dff_clock
                    if(inverter.size()!=0){
                    for(int g=0; g<inverter.size();g++){
                        //lets get inverter output

                        std::regex regex_C(R"(\((.*?)\))");
                        std::smatch match_i;
                        std::vector<std::string> inv_elements;
                        auto B_begin = std::sregex_iterator(inverter[g].begin(), inverter[g].end(), regex_C);
                        auto B_end = std::sregex_iterator();
                        for (std::sregex_iterator it = B_begin; it != B_end; ++it) {
                            std::smatch match_i = *it;
                            if (match_i.size() > 1) {
                                std::string C = match_i[1];
                                inv_elements.push_back(C);
                            }
                        }
                        std::cout<<"invertersassemble";
                        if(inv_elements.back() == dff_clock){
                            clockedge = 1; //negclockedge
                            inv_index = g;
                        }else {std::cout<<"positive"; clockedge=0;}
                        info.push_back(inv_elements);
                    }
                    }else {std::cout<<"positive"; clockedge=0;}

                    }
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
                            info.push_back(C_all);
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
                            validation_output[i]={{j,casenumber}, inv_index, clockedge};
                        } else {std::cout << "Did not find 'q' in C_all" << std::endl;}
                        
                    
                    }
                }
            } else {std::cout << "Line " << i << " dff does not contain '.Q('" << std::endl;}
        necessary_info.push_back(info);
        }
        ratio = (validation_output.size() / static_cast<double>(dff.size()) )*100;
        std::cout<<"Ratio of DFF clock gated = "<< ratio << "%" << endl;
        // std::cout<<necessary_info[0][0].back();
    }


// void test()
// {
//   for (const auto& entry : validation_output) {
//         std::cout << "Key: " << entry.first
//                   << ", og: (" << entry.second.og.first << ", " << entry.second.og.second << ")"
//                   << ", ii: " << entry.second.ii
//                   << ", cc: " << entry.second.cc
//                   << std::endl;
//                   cout<<mux[pair.second.og.first]<<endl;
//     }
//     flag=0;
// }
void replace ()
{
    
     for (const auto& pair : validation_output) {
      
        // cout << "Key: " << pair.first << ", Value: (" << pair.second.first << ", " << pair.second.second << ")" << endl;
        // cout<<"Key" << pair.first << "value"
        vector<string>muxcg,dffcg,invcg;
        int casecg,trigcg;
        string line;
        istringstream issdff(dff[pair.first]);
        while (getline(issdff, line, '\n')) {
        size_t firstNonSpace = line.find_first_not_of(" \t\n\r");
        line.erase(0, firstNonSpace);
        dffcg.push_back(line);
    }
    cout<<pair.second.og.first<<endl;
    cout<<mux[pair.second.og.first]<<endl;
    istringstream issmux(mux[pair.second.og.first]);
        while (getline(issmux, line, '\n')) {
        size_t firstNonSpace = line.find_first_not_of(" \t\n\r");
        line.erase(0, firstNonSpace);
        muxcg.push_back(line);
    }
    //   istringstream issinv(inverter[pair.second.ii]);
    //     while (getline(issinv, line, '\n')) {
    //     size_t firstNonSpace = line.find_first_not_of(" \t\n\r");
    //     line.erase(0, firstNonSpace);
    //     cout<<line<<endl;
    //     invcg.push_back(line);
    // }
    
    casecg = pair.second.og.second;
    trigcg=pair.second.cc;
    cout<<"case"<<casecg<<endl;
    cout<<"pos/neg"<<trigcg<<endl;
    size_t start_pos = muxcg[1].find_first_of('(');
    size_t end_pos = muxcg[1].find_first_of(')', start_pos);
    string muxip1= muxcg[1].substr(start_pos + 1, end_pos - start_pos - 1);
    start_pos = muxcg[2].find_first_of('(');
    end_pos = muxcg[2].find_first_of(')', start_pos);
    string muxip2= muxcg[2].substr(start_pos + 1, end_pos - start_pos - 1);
    start_pos = muxcg[3].find_first_of('(');
    end_pos = muxcg[3].find_first_of(')', start_pos);
    string muxenable= muxcg[3].substr(start_pos + 1, end_pos - start_pos - 1);
    start_pos = muxcg[4].find_first_of('(');
    end_pos = muxcg[4].find_first_of(')', start_pos);
    string muxoutput= muxcg[4].substr(start_pos + 1, end_pos - start_pos - 1);
    start_pos = dffcg[1].find_first_of('(');
    end_pos = dffcg[1].find_first_of(')', start_pos);
    string dffclk= dffcg[1].substr(start_pos + 1, end_pos - start_pos - 1);
   
    
   
    
    //     istringstream issinv(inverter[pair.second.ii]);
    //     while (getline(issinv, line, '\n')) {
    //     size_t firstNonSpace = line.find_first_not_of(" \t\n\r");
    //     line.erase(0, firstNonSpace);
    //     cout<<line<<endl;
    //     invcg.push_back(line);
    
    // start_pos = invcg[1].find_first_of('(');
    // end_pos = invcg[1].find_first_of(')', start_pos);
    // invclk= invcg[1].substr(start_pos + 1, end_pos - start_pos - 1);
    // start_pos = invcg[2].find_first_of('(');
    // end_pos = invcg[2].find_first_of(')', start_pos);
    // invout= invcg[2].substr(start_pos + 1, end_pos - start_pos - 1);
    
    cout<<trigcg;
    if (trigcg==0)
    {
      cout<<"openroad";
        if(casecg==0)
        {
          cout<<mux.size()<<"test"<<endl;
           string lengthStrcg =lengthvec(objects,100000);
           objects.push_back(lengthStrcg);
            string new_inv = "sky130_fd_sc_hd__inv_1 _" +lengthStrcg+ "_ "  +" (\n" + ".A(" + dffclk + "),\n" +".Y(";
            lengthStrcg = lengthvec(cg_wires,0);
            cg_wires.push_back("cg"+lengthStrcg);
            new_inv= new_inv + "cg"+lengthStrcg +")\n" + ");\n";
            
            lengthStrcg = lengthvec(objects,100000);
            objects.push_back(lengthStrcg);
            string new_neg_latch = "sky130_fd_sc_hd__dlxtn_1 _"+lengthStrcg+"_ (\n" + ".D(" +  muxenable +"),\n." + "GATE_N(" + cg_wires.back() + "),\n" ;
           
            lengthStrcg = lengthvec(cg_wires,0);
            cg_wires.push_back("cg"+lengthStrcg);
            new_neg_latch= new_neg_latch + ".Q(cg"+lengthStrcg +")\n" + ");\n";
            lengthStrcg = lengthvec(objects,100000);
            string new_and= "sky130_fd_sc_hd__and2_1 _" + lengthStrcg +"_ " +"(\n" + ".A(" + cg_wires.back() + "),\n" + ".B(" + dffclk + "),\n"+".X("+muxoutput +")\n" +");\n";
            string new_dff=dffcg[0]+ "\n" + ".CLK(" + muxoutput + "),\n" + ".D(" + muxip2 + "),\n" + dffcg[3] +"\n" + dffcg[4]+"\n";
            dff[pair.first]=new_dff;
            andGate.push_back(new_and);
            inverter.push_back(new_inv);
            neg_latches.push_back(new_neg_latch);
            // mux.erase(mux.begin()+pair.second.og.first);
            gated_mux.push_back(pair.second.og.first);
        }
        if(casecg==1)
        {
        string lengthStrcg = lengthvec(objects,obsize);
        objects.push_back(lengthStrcg);
        string new_inv = "sky130_fd_sc_hd_inv_1_ _" + lengthStrcg +"_ " + "(\n" + ".A(" + muxenable + "),\n";
        lengthStrcg = lengthvec(cg_wires,0);
        cg_wires.push_back("cg" +lengthStrcg);
        new_inv= new_inv + ".B("+ cg_wires.back()+")\n" + ");\n";
        inverter.push_back(new_inv);
        lengthStrcg = lengthvec(objects,obsize);
        objects.push_back(lengthStrcg);
        string new_inv1 = "sky130_fd_sc_hd_inv_1_ _" + lengthStrcg +"_ "+ "(\n" + ".A(" + dffclk + "),\n";
        lengthStrcg =lengthvec(cg_wires,0);
        cg_wires.push_back("cg" +lengthStrcg);
        new_inv1 = new_inv1 + ".B(" + cg_wires.back() + ")\n" +");\n";
        lengthStrcg = lengthvec(objects,obsize);
        objects.push_back(lengthStrcg);
        string new_neg_latch= "sky130_fd_sc_hd__dlxtn_1\\\q"+lengthStrcg+"\\\sky130_fd_sc_hd__dlxtn_1 (\n" + ".D(" +cg_wires[cg_wires.size()-2] + "),\n" + ".GATEN(" + cg_wires.back() +"),\n";
        lengthStrcg = lengthvec(cg_wires,0);
        cg_wires.push_back("cg" +lengthStrcg);
        new_neg_latch = new_neg_latch + ".Q(" + cg_wires.back() + ")\n" + ");\n";
        lengthStrcg = lengthvec(objects,obsize);
        objects.push_back(lengthStrcg);
        string new_and = "sky_130_fd_sc_hd_and21_ _" + lengthStrcg +"_ "+  "(\n" + ".A(" + cg_wires.back() + "),\n" + ".B(" + dffclk + "),\n" + ".X(" + muxoutput + ")\n" + ");\n";
        string new_dff= dffcg[0] + "\n" + ".CLK("  + muxoutput + "),\n" + ".D(" + muxip1 + "),\n" + dffcg[3] + "\n" + dffcg[4] + "\n";
        dff[pair.first]=new_dff;
        andGate.push_back(new_and);
        inverter.push_back(new_inv1);
        neg_latches.push_back(new_neg_latch);
        // mux.erase(mux.begin()+pair.second.og.first);
        gated_mux.push_back(pair.second.og.first);
        }
     }
    else if (trigcg==1)
    {
    istringstream issinv(inverter[pair.second.ii]);
    while (getline(issinv, line, '\n')) {
    size_t firstNonSpace = line.find_first_not_of(" \t\n\r");
    line.erase(0, firstNonSpace);
    cout<<line<<endl;
    invcg.push_back(line);}
    string invclk,invout;
    start_pos = invcg[1].find_first_of('(');
    end_pos = invcg[1].find_first_of(')', start_pos);
    invclk= invcg[1].substr(start_pos + 1, end_pos - start_pos - 1);
    start_pos = invcg[2].find_first_of('(');
    end_pos = invcg[2].find_first_of(')', start_pos);
    invout= invcg[2].substr(start_pos + 1, end_pos - start_pos - 1);
    if(casecg==0)
    {string lengthStrcg = lengthvec(objects,obsize);
    objects.push_back(lengthStrcg);
            string new_pos_latch = "sky130_fd_sc_hd__dlxtp_1 \\\q" + lengthStrcg + "\\\sky130_fd_sc_hd__dlxtp_1 (\n" + ".D(" + muxenable +"),\n" + ".GATE(" + invclk +"),\n" ;
            
            lengthStrcg = lengthvec(cg_wires,0);
            cg_wires.push_back("cg"+lengthStrcg);
            new_pos_latch=new_pos_latch + ".Q(" + cg_wires.back() + ")\n" + ");\n";
            string new_inv = invcg[0] + "\n" + ".A(" + cg_wires.back() + "),\n" + invcg[2] + "\n" + invcg[3] +"\n";
            
            lengthStrcg = lengthvec(objects,obsize);
            objects.push_back(lengthStrcg);
            string new_nor = "sky130_fd_sc_hd__nor2_1 _" + lengthStrcg+"_ " + "(\n" + ".A(" + invclk + "),\n" + ".B(" + dffclk  + "),\n" + ".Y(" + muxoutput + ")\n" + ");\n";
            string new_dff = dffcg[0] + "\n" + ".CLK(" + muxoutput + "),\n" + ".D(" + muxip2 + "),\n" + dffcg[3] + "\n" + dffcg[4] +"\n";
            dff[pair.first]=new_dff;
            norGate.push_back(new_nor);
            inverter[pair.second.ii]=(new_inv);
            pos_latches.push_back(new_pos_latch);
            // mux.erase(mux.begin()+pair.second.og.first);
            gated_mux.push_back(pair.second.og.first);
       }
    if(casecg==1)
    {
    string lengthStrcg = lengthvec(objects,obsize);
    objects.push_back(lengthStrcg);

        string new_inv = invcg[0] + "\n" + ".A(" + muxenable + "),\n" + invcg[2] + "\n" + invcg[3] +"\n";
        inverter[pair.second.ii]=(new_inv);
         lengthStrcg = lengthvec(objects,obsize);
         objects.push_back(lengthStrcg);
        string new_pos_latch = "sky130_fd_sc_hd__dlxtp_1 \\\q" + lengthStrcg + "\\\sky130_fd_sc_hd__dlxtp_1 (\n" + ".D(" +invout + "),\n" + ".GATE(" + invclk + "),\n";
        lengthStrcg = lengthvec(cg_wires,0);
        cg_wires.push_back("cg" +lengthStrcg);
        new_pos_latch = new_pos_latch + ".Q(" + cg_wires.back() + ")\n" + ");\n";
        lengthStrcg = lengthvec(objects,obsize);
        objects.push_back(lengthStrcg);
        string new_inv1= "sky130_fd_sc_hd__inv_1 _" + lengthStrcg +"_ " + "(\n" + ".A(" + cg_wires.back() + "),\n"; 
        lengthStrcg = lengthvec(cg_wires,0);
        cg_wires.push_back("cg" +lengthStrcg);
        new_inv1 = new_inv1 + ".Y(" + cg_wires.back() + ")\n" + ");\n";
        lengthStrcg = lengthvec(objects,obsize);
        objects.push_back(lengthStrcg);
       string new_nor= "sky130_fd_sc_hd__nor2_1 _" + lengthStrcg+"_ " + "(\n" + ".A(" + cg_wires.back() + "),\n" + ".B(" + invclk + "),\n" + ".Y(" + muxoutput + ")\n" + ");\n";
       string new_dff = dffcg[0] +"\n" + ".CLK(" + muxoutput + "),\n" + ".D(" + muxip1 + "),\n" + dffcg[3] + "\n" +dffcg[4]+"\n";
       dff[pair.first]=new_dff;
        norGate.push_back(new_nor);
        inverter.push_back(new_inv1);
        pos_latches.push_back(new_pos_latch);
        // mux.erase(mux.begin()+pair.second.og.first);
        gated_mux.push_back(pair.second.og.first);
 
    }
    }
   
    }
     cout<<mux.size()<<"replacebl"<<endl;
}
string modify_netlist(const std::string lines[], int size)
  {
    vector<int> mux_cfg_indices;
    vector<int> dff_cfg_indices;
    for (const auto& pair : validation_output) {
        // Extract key and pair values
        int key = pair.first;
        int firstValue = pair.second.og.first;

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
        int foundand =lines[i].find("_and2");
        int foundinverter = lines[i].find("_inv");
        int founddff = lines[i].find("_dfxtp");
        int foundmux = lines[i].find("_mux2");
        int foundneglatch = lines[i].find("_dlxtn");
        int foundposlatch = lines[i].find("_dlxtp");
        int foundnor = lines[i].find("_nor2");
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
         if(foundnor != string::npos)
        {
            i=i+5;
            continue;
        }
         if(foundneglatch != string::npos)
        {
            i=i+5;
            continue;
        }
        if(foundposlatch != string::npos)
        {
            i=i+5;
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
       for (auto k = pos_latches.begin(); k != pos_latches.end(); ++k) {
        string line;
        istringstream issdff(*k);
        while (getline(issdff, line, '\n')) {
        new_lines=new_lines +line + "\n";
    }}
       for (auto k = neg_latches.begin(); k != neg_latches.end(); ++k) {
        string line;
        istringstream issdff(*k);
        while (getline(issdff, line, '\n')) {
        new_lines=new_lines +line + "\n";
    }}
       for (auto k = norGate.begin(); k != norGate.end(); ++k) {
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
    //   for (auto k = mux.begin(); k != mux.end(); ++k) {
    //     string line;
    //     istringstream issdff(*k);
    //     while (getline(issdff, line, '\n')) {
    //     new_lines=new_lines +line + "\n";
    // }}
     
      for (size_t i = 0; i < mux.size(); ++i) {
        
        // Check if the index is in the 'indices_to_exclude' vector
        if (std::find(gated_mux.begin(), gated_mux.end(), i) == gated_mux.end()) {
            // If the index is not in 'indices_to_exclude', print the word
           
            string line;
            istringstream issdff(mux[i]);
            while (getline(issdff, line, '\n')) {
              
        new_lines=new_lines +line + "\n";
    }
        }
    }
     for (auto k = dff.begin(); k != dff.end(); ++k) {
        string line;
        istringstream issdff(*k);
        while (getline(issdff, line, '\n')) {
        new_lines=new_lines +line + "\n";
    }}
    
  
    new_lines=new_lines+"endmodule"+'\n';
    // cout<<"modified netlist"<<endl;
    // cout<<new_lines;
    cout<<"Ratio of DFF clock gated = "<< ratio << "%" << endl;
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
    // cout<<"Intiial Netlist"<<endl;
    // cout << "Lines read from file " << argv[1] << ":" << endl;
    // for (int i = 0; i < numLines; ++i) {
    //     cout << lines[i] <<endl;
    // }
    integrated_clock_gating p1;
    p1.parse(lines,numLines);
   //After parsing
    cout<<"Parsing Completed"<<endl;
    p1.validation();
    std::cout << "Key: " << "dff" << ", Value: ((" << "mux" << ", " << "casenumber" << "), " << "inverter index" <<"," << "pos/neg edge" << ")" << std::endl;
    for (const auto& pair : p1.validation_output) {
        std::cout << "Key: " << pair.first << ", Value: ((" << pair.second.og.first << ", " << pair.second.og.second << "), " << pair.second.ii <<"," << pair.second.cc << ")" << std::endl;
    }
    cout<<"validation completed"<<endl;
 

    p1.replace();

//    p1.display();
    string s1;
    s1=p1.modify_netlist(lines,numLines);
    cout<<argv[1];
     string s2;
     s2=argv[1];
    // s2.pop_back();
    // s2.pop_back();
    // s2=s2+"_cg.v";

    std::ofstream outFile(s2); // Change the output filename if needed
    if (outFile.is_open()) {
       outFile << s1; // Write the string to the file
        outFile.close();}
    //   std::ofstream outFile2("1_1_yosys.v"); // Change the output filename if needed
    // if (outFile2.is_open()) {
    //     outFile2 << s1; // Write the string to the file
    //     outFile2.close();}
    return 0;  
}
