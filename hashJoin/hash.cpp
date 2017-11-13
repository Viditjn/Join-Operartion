#include <bits/stdc++.h>
using namespace std;

vector < pair <string,string> > readData(ifstream& in,long long int M, int index){
  long long int i = 0;
  string line;
  const char* delim = " ";
  vector < pair<string,string> > ans;
  while(i<M && getline(in,line)){
    char * dup = strdup(line.c_str());
    char * token = strtok(dup, delim);
    vector <string> v;
    int i = 0;
    while(token != NULL){
      v.push_back(string(token));
      token = strtok(NULL, delim);
    }
    string key = v[index];
    string finalStr = v[(index==0?1:0)];
    ans.push_back(make_pair(key,finalStr));
    free(dup);
    i++;
  }
  return ans;
}

const int M = 1000003;
vector <vector <pair<string,string> > >  hashTable(M);

long long int power(int base,int x){
  long long int ans = 1;
  for(int i=1;i<x;i++)
    ans = ((ans%M)*(base))%M;
  return ans;
}

long long int hashValue(string data){
  long long int ans = 0;
  for(int i=0;i<data.size();i++)
    ans = (ans+(int(data[i])*power(257,i))%M)%M;
  return ans;
}

// long long int searchKey(int index,long long int data){
//   for(int i=0;i<hashTable[index].size();i++)
//     if(hashTable[index][i]==data)
//       return data;
//   return -1;
// }

void insert(int index,pair<string,string> data){
  hashTable[index].push_back(data);
}

void printFormat(long long int data){
  string s = to_string(data);
  int l = s.size();
  int t = ceil(s.size()*1.0/3);
  int l1 = l-((t-1)*3);
  cout << atoi(s.substr(0,l1).c_str()) << " ";
  for(int i=0;i<t-1;i++)
    cout << atoi(s.substr(l1+(3*i),3).c_str()) << " ";
  cout << endl;
}

int main(int argc, char** argv){
  if(argc<3){
    cout << "Check Input Format" << endl;
    return 0;
  }
  vector<pair<string,string> > ans;
  ifstream infile;
  infile.open(argv[1]);
  if(!infile.is_open()){
    cout << "Error : Check Filename " << endl;
    return 0;
  }
  long long int MemSize = 1024*1024*atoi(argv[3]);
  ans = readData(infile,MemSize,1);
  while(ans.size()!=0){
    for(long long int i=0;i<ans.size();i++){
      int hash = hashValue(ans[i].first.c_str());
      // long long int data = atoll(ans[i].c_str());
      insert(hash,ans[i]);
    }
    ans.clear();
    ans = readData(infile,MemSize,1);
  }
  ans.clear();
  infile.close();
  infile.open(argv[2]);
  ans = readData(infile,MemSize,0);
  ofstream outPointer("outHash.txt");
  while(ans.size()!=0){
    for(long long int i=0;i<ans.size();i++){
      int hash = hashValue(ans[i].first.c_str());
      for(int j=0;j<hashTable[hash].size();j++){
        if(hashTable[hash][j].first==ans[i].first){
          string s = hashTable[hash][j].second + " " + hashTable[hash][j].first + " " + ans[i].second + '\n';
          outPointer << s;
        }
      }
    }
    ans.clear();
    ans = readData(infile,MemSize,1);
  }
  // for(int i=0;i<M;i++)
  //   if(hashTable[i].size())
  //     for(int j=0;j<hashTable[i].size();j++)
  //       cout << i << " : " << hashTable[i][j].first << " : " << hashTable[i][j].second << endl;


  return 0;
}
