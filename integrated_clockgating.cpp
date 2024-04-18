#include <iostream>
#include <vector>
#include <string>
#include<fstream>
using namespace std;
class parse   // This Parse object will parse throgh the netlist and collect all the dflip flops , multiplexers and and gates in lists.
{
    public:
    vector<string>  dff;
    vector<string>  mux;
    vector<string>  andGate;
    vector<int> dff_indices;
    vector<int> mux_indices;
    parse(const std::string lines[], int size)
    {
        int i;
        i=0;
        while(i<size)
        {
           
            int founddff =lines[i].find("DFFE");
            int foundmux =lines[i].find("mux2");
            int foundand =lines[i].find("and2");
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
                cout<<"blahand";
                string and_gate=lines[i];
                int j;
                for (j=1;j<=4;j++)
                and_gate=and_gate +"\n" + lines[i+j];
                
                andGate.push_back(and_gate);
                i=i+j;
             }
             else
             i++;

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
    parse p1(lines,numLines);
   //After parsing
   cout<<"Parsing Completed"<<endl;
   p1.display();
    return 0;
   
}
