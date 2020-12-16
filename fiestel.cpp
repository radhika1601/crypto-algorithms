#include <iostream>
#include <string>

using namespace std;
#define num_of_rounds 16 

string decToBinary(int n) 
{ 
    // array to store binary number 
    int binaryNum[8]={0}; 
  
    // counter for binary array 
    int i = 0; 
    while (n > 0) { 
  
        // storing remainder in binary array 
        binaryNum[7-i] = n % 2; 
        n = n / 2; 
        i++; 
    } 
  
    string dec="";
    
    for (int j = 0; j<8; j++) {
        // string conversion and adding to string
        dec+=to_string(binaryNum[j]); 
    }
    
    return dec;
} 
  
string rand_key(int x){
    string key="";
    srand(time(0));
    for(int i=0;i<x;i++){
        // getting random binary number 
        int y=rand()%2;
        key += to_string(y);
    }
    return key;
}

string sxor(string s1, string s2){
    string result="";

    for(int i=0;i<s1.length();i++){
        // if same bits return 0 else 1
        if(s1[i]==s2[i]){
            result+="0";
        }
        else{
            result+="1";
        }
    }

    return result;
}

string encrypt(string pt_bin, string keys[], int n){
    
    string ciphertext="";
    
    string L1, R1;
    // extracting lef and right part
    L1 = pt_bin.substr(0,n);
    R1 = pt_bin.substr(n,n);

    string R2, L2, f1;
    for(int i=0;i<num_of_rounds;i++){
        // calculating right part during encryption 
        f1=sxor(keys[i],R1);;
        R2=sxor(L1,f1);
        
        // calculating left part
        L2=R1;
        
        // adjusting values to repeat loop
        R1=R2;
        L1=L2;
    }

    ciphertext=L1+R1;
    
    return ciphertext;
}

string decrypt(string pt_bin, string keys[], int n){
    
    string plaintext="";
    
    string L1, R1;
    // extracting lef and right part
    L1 = pt_bin.substr(0,n);
    R1 = pt_bin.substr(n,n);

    string R2, L2, f1;
    for(int i=0;i<num_of_rounds;i++){
        // calculating left part during decryption 
        f1=sxor(keys[num_of_rounds-i-1],L1);;
        L2=sxor(R1,f1);

        // calculating right part
        R2=L1;

        // adjusting values to repeat loop
        R1=R2;
        L1=L2;
    }

    plaintext=L1+R1;
    
    return plaintext;
}

string binAscii(string bin){
    string ascii="";

    for(int i=0;i<bin.length();i+=8){
        // getting the 8 bits
        string byte=bin.substr(i,8);
        
        // converting the ascii value to charachter
        char ctr = char(stoi(byte,0,2));
        ascii+=ctr;
    }
    return ascii;
}

int main(){

    string plaintext;
    cout << "Enter the text to be encrypted:  ";
    getline(cin, plaintext);

    cout << "Plaintext is "<< plaintext <<endl; 
    string pt_bin = "";

    // converting ascii to binary
    for(int i=0;i<plaintext.length();i++){
        int x=(int )plaintext[i];
        pt_bin+=decToBinary(x);
    }

    // length of each part
    int n = (pt_bin.length())/2;
    
    string keys[num_of_rounds];
    
    for(int i=0;i<num_of_rounds;i++){
        keys[i]=rand_key(n);
    }
    
    // encode plaintext 
    string ct_bin = encrypt(pt_bin, keys, n);
    string ciphertext = binAscii(ct_bin);
    cout << "Ciphertext is: "<< ciphertext << endl;

    // decode ciphertext
    string ot_bin = decrypt(ct_bin, keys, n);
    string orginaltext = binAscii(ot_bin);
    cout << "Original Text is: "<< orginaltext << endl;

    return 0;

}
