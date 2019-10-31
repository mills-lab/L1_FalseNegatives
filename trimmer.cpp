#include <stdlib.h>
#include <iostream>
#include <string>
#include <string.h>
#include <fstream>
#include <vector>
#include <cmath>

#include <sstream>
#include <algorithm>
#include <functional>

using namespace std;

int main(){
    ifstream file1;
    ifstream file2;
    ofstream file3;
    ofstream file4;
    ofstream file5;
    ofstream file6;
    ofstream file7;
    ofstream file8;
    
    file1.open("300_R2.fastq");
    file2.open("300_R2.fastq");
    file3.open("300_R2_trimmed_Liseq.fastq");
    file4.open("300_R2_trimmed_polyA.fastq");
    file5.open("300_R2_trimmed_gDNA.fastq");
    file6.open("300_R2_Liseq.txt");
    file7.open("300_R2_polyA.txt");
    file8.open("300_R2_gDNA.txt");
    
    string input;
    string seq;
    string quan;
    string title;
    string title2;
    
    int N_L1=21;
    
    for(int i=0;!file1.eof();i++){
        file1>>title;
        file2>>title;
        file1>>title2;
        file2>>title2;
        
        
        int seq_l=0;
        int quan_l=0;
        
        file1>>seq;
        seq_l=seq.length();
        char *seq_char;
        seq_char=   new char[seq_l];
        
        for(int j=0;j!=seq_l;j++){
            file2>>seq_char[j];
        }
        
        file1>>input;
        file2>>input;
        
        
        file1>>quan;
        quan_l=quan.length();
        char *quan_char;
        quan_char=  new char[quan_l];
        
        for(int j=0;j!=quan_l;j++){
            file2>>quan_char[j];
        }
        
        if(quan_l!=seq_l){
            cout<<"f**king wrong"<<endl;
            break;
        }



        
        file3<<title<<'\t'<<title2<<endl;
        file4<<title<<'\t'<<title2<<endl;
        file5<<title<<'\t'<<title2<<endl;
       


        for(int j=0;j!=N_L1;j++){
            file3<<seq_char[j];
            file6<<seq_char[j];
            
        }
        
        file3<<endl;
        file6<<endl;
        
        
        int polyA_site=N_L1;
        int end=0;
        for(int j=N_L1;j!=seq_l-5;j++){
            int flag=0;
            if(seq_char[j]!='A') flag=flag+1;
            if(seq_char[j+1]!='A') flag=flag+1;
            if(seq_char[j+2]!='A') flag=flag+1;
            if(seq_char[j+3]!='A') flag=flag+1;
            if(seq_char[j+4]!='A') flag=flag+1;
            if (flag>=4){
                if(seq_char[j]!='A'){
                    polyA_site=j;
                }
                else {
                    polyA_site=j+1;
                }
		end=1;
                break;
            }
        }
        
	if(end==0){
		polyA_site=seq_l;
	}
        
        for(int j=N_L1;j!=polyA_site;j++){
            file4<<seq_char[j];
            file7<<seq_char[j];
        }
        file4<<endl;
        file7<<endl;
        
        for(int j=polyA_site;j!=seq_l;j++){
            file5<<seq_char[j];
            file8<<seq_char[j];
        }
        file5<<endl;
        file8<<endl;
        
        
        file3<<input<<endl;
        file4<<input<<endl;
        file5<<input<<endl;
        
        for(int j=0;j!=N_L1;j++){
            file3<<quan_char[j];
            
        }
        file3<<endl;
        
        for(int j=N_L1;j!=polyA_site;j++){
            file4<<quan_char[j];
        }
        file4<<endl;
        
        for(int j=polyA_site;j!=seq_l;j++){
            file5<<quan_char[j];
        }
        file5<<endl;
        





}
    file1.close();
    file2.close();
    file3.close();
    
}
