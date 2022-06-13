#include <iostream>
#include <string>
#include <fstream>
using namespace std;
int main()
{
 ofstream foutput; 
 ifstream finput;
 finput.open ("liczby.txt");
 foutput.open ("liczby.txt",ios::app); 
 
 if(finput.is_open()){
    for(int i = 1; i <=500000; i++){
        
        foutput<< i << "\n"; 
    }
 }

 
 finput.close();
 foutput.close(); 
 
 return 0;
}