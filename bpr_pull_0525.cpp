#include <stdlib.h>
#include <iostream>
#include <string>
#include <string.h>
#include <fstream>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <sstream>
#include <algorithm>
#include <functional>
#include <iomanip>
#include <vector>

using namespace std;
using std::vector;

int main(){
ifstream file1;
ifstream file2;
ofstream file3;
ofstream file4;
ofstream file5;

file1.open("sam.txt");
file3.open("bpr_output.txt");

int FLAG=256;
int MAPQ=10;
int WIN=500;

string input;
int line;

for(int i=0;!file1.eof();i++){
	getline(file1,input);
	line=i;
}
cout<<line<<endl;

string **info;
info=new string*[line];
for(int i=0;i!=line;i++) info[i]=new string[3];

int ** flag;
flag=new int*[line];
for(int i=0;i!=line;i++) flag[i]=new int[5];

file1.close();
file1.clear();
file1.open("sam.txt");

for(int i=0;i!=line;i++){
	file1>>info[i][0];//tag
	file1>>flag[i][0];//FLAG
	file1>>info[i][1];//chr
	file1>>flag[i][1];//POS
	file1>>flag[i][2];//MAPQ
	file1>>info[i][2];//CIGAR
	if(flag[i][0]<FLAG&&flag[i][2]>=MAPQ){
		flag[i][3]=flag[i][1]+WIN;
	}
	else flag[i][3]=-1;
	flag[i][4]=1;//reads_num
}

cout<<info[line-1][0]<<endl;


//no FLAG filter
//no MAPQ filter
//no chr filter
for(int i=0;i!=line;i++){
	cout<<i<<endl;
	if(flag[i][3]!=-1){
		for(int j=0;j!=line;j++){
			if(flag[j][3]!=-1&&i!=j){
				if(info[i][1]==info[j][1]){
					if(!((flag[i][1]>flag[j][3])||(flag[i][3]<flag[j][1]))){
						int end, start;
						start=flag[i][1];
						end=flag[i][3];
						if(flag[j][1]<flag[i][1]) start=flag[j][1];
						if(flag[j][3]>flag[i][3]) end=flag[j][3];
						flag[j][3]=-1;
						flag[i][1]=start;
                                                flag[i][3]=end;
						flag[i][4]=flag[i][4]+flag[j][4];
					}
				}
			}
		}
	}
}

for(int i=0;i!=line;i++){
	if(flag[i][3]!=-1){
		file3<<info[i][1]<<'\t'<<flag[i][1]<<'\t'<<flag[i][3]<<'\t'<<flag[i][4]<<endl;
	}
}

file1.close();
file2.close();
file3.close();
}
