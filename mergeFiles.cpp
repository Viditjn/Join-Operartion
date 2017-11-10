#include <bits/stdc++.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

void mergeFiles(){
  ifstream in1;
  in1.open("outp1.txt");
  ifstream in2;
  in2.open("outp2.txt");
  ofstream outFinal;
  outFinal.open("finalOutp.txt");
  long long int offset1=0,offset2=0,tempOffset=0;
  string line1,line2;
  if(in1.is_open()){
    while(getline(in1,line1)){
      offset1 += line1.length() + 1;
      char * si = strdup(line1.c_str());
      const char * delim = " ";
      char * token = strtok(si,delim);
      string x1 = token;
      token = strtok(NULL,delim);
      string y1 = token;
      y1 = y1.substr(0,y1.length()-1);
      // cout << "Printing : "<< y1 << " " << x1 << endl;
      free(si);
      if(in2.is_open()){
        // cout << in2.tellg() << endl;
        // in2.seekg(0,ios::beg);
        // cout << in2.tellg() << endl;
        if(in2.tellg()==-1){
          in2.close();
          in2.open("outp2.txt");
          in2.seekg(offset2);
          // cout << in2.tellg() << endl;
        }
        while(getline(in2,line2)){
          tempOffset = offset2 + line2.length() + 1;
          char * si = strdup(line2.c_str());
          const char * delim = " ";
          char * token = strtok(si,delim);
          string y2 = token;
          // cout << string(y1) << " : " << string(y2) << endl;
          token = strtok(NULL,delim);
          string z1 = token;
          z1 = z1.substr(0,z1.length()-1);
          free(si);
          if(string(y1)==string(y2)){
            // cout << y1 << " " << y2 << endl;
            if(outFinal.is_open()){
              string outS;
              outS = x1 + " " + y1 + " " + z1 + '\n';
              outFinal << outS;
              cout << outS;
            }
          }
          if(y1>y2)
            offset2 = tempOffset;
          if(y1<y2)
            break;
        }
      }
    }
  }
  in1.close();
  in2.close();
  outFinal.close();
  return;
}

int main(){
  mergeFiles();
}
