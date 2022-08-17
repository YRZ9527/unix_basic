#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
using namespace std;
 
int main()
{
	ifstream infile;
	infile.open("/Users/zong/Code/unix/DRO/载荷/test.dat", ios_base::binary);          //attention1
	
	ofstream outfile;
	outfile.open("output.txt", ios_base::binary);         
	
	char readByte;
	unsigned char readByte2;
    string strTmp;
	int cnt = 0;
	vector<int> tmp;
    
	// outfile << "unsigned char hex_num[ ] = " << endl;
	outfile << "{ " << endl;
	
	while(!infile.eof())
	{
		if(cnt % 16 == 0)
		{
			// outfile << " " << endl;
			// outfile << "   ";
		}
		infile.get(readByte);                              //attention2
		readByte2 = (unsigned char)readByte;               //attention3
        // strTmp = string(readByte2);
		// cnt++;
		// outfile << "0x" << setfill('0') << setw(2);        //attention4
        // outfile << setfill('0') << setw(2); 
		// outfile << hex << (unsigned int)readByte2;         //attention5
		// outfile << ",";
        tmp.push_back((unsigned int)readByte2); //attention6
        // tmp2.push_back((readByte2));
		
	}
    for(int i = 0; i < 10; i++)	
    {
        cout<<tmp[i]<<endl;
    }
    // for(auto i : tmp)
    // {
    //     cout<<i<<endl;
    // }
	outfile << " \n";
	outfile << "}; \n";
	infile.close();
	outfile.close();
	
	return 0;
}
