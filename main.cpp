#include<iostream>
#include<vector>

using namespace std;

class SDES{

public:

    SDES( ): outputKey_10(10), outputKey_8(8){};
    //vector for storing output key of 10bit after p10 permutation
    vector<int> outputKey_10 = vector<int>(10);
    //vector for storing output key of 8bit after p8 permutation
    vector<int> outputKey_8 = vector<int>(8);


    //--------PERMUTATION FUNCTION-----------

    vector<int> result;
    vector<int> permute( vector<int> inputKey, vector<int> permuteTable){
        result.clear();
        for( int i = 0; i< permuteTable.size(); i++){
            result.push_back(inputKey[permuteTable[i]-1]);
            cout<<result[i]<<" ";
        };
        cout <<endl;
        return result;
    };

    //----------------LEFT SHIFT FUCNTION-------------------
    int temp;
    vector<int> leftShift( vector<int> operand){
        temp = operand[0];
        for(int i = 0; i<4; i++){
            operand[i] = operand[i+1];
        };
        operand[4] = temp;
        return operand;
    };
    

    //----------XOR FUNCTION----------------
    vector<int> xor_result;
    vector<int> xor_vec( vector<int> exp_result, vector<int> key){
        cout<<"\n\n xor result \n";
        show(xor_result);
        cout<<endl;
        xor_result.clear();
        cout<<key.size()<<endl;
        for(int i =0; i<key.size(); i++){
            xor_result.emplace_back(exp_result[i] ^ key[i]);
            cout<<xor_result[i]<<" ";
        };
        cout<<endl;
        return xor_result;
    };

    //---------SBOX----------------
    //Helper function 

    int BitstoDec( int a, int b ){ //Binary to Decimal //I couldnt think of a better name than helper temprory variable lol!
        return  (a*2+ b);
    };

    vector<int> DectoBits( int helperX){ //Decimal to Binary //helper function obv 
        vector<int> tempVAR1;
        tempVAR1.push_back( helperX/2);
        tempVAR1.push_back(helperX%2);
        show(tempVAR1);
        return tempVAR1;
    };

    vector<int> SBOX(vector<int> S_operand, const int arr_S[4][4]){
        vector<int> sbox_res;
        int res;
        res = arr_S[ BitstoDec(S_operand[0], S_operand[3])] [ BitstoDec( S_operand[1], S_operand[2])];
        cout<<"the value in matrix is : "<<res<<endl;;
        sbox_res = DectoBits(res);
        return sbox_res;
    };

    //----------FUNCTION TO PRINT------------------
    void show( vector<int> see){
        for(int i = 0; i< see.size(); i++){
            cout<<see[i]<<" ";
        };
        return;
    };

};

int main(){


    //---------------------------------------------------------------------------------------
    //permutation table 

    //p10 (k1, k2, k3, k4, k5, k6, k7, k8, k9, k10) = (k3, k5, k2, k7, k4, k10, k1, k9, k8, k6)
    const vector<int> p10_table = {3, 5, 2, 7, 4, 10, 1, 9, 8, 6};

    //p8 (k1, k2, k3, k4, k5, k6, k7, k8, k9, k10) = (k6, k3, k7, k4, k8, k5, k10, k9)
    const vector<int> p8_table = {6, 3, 7, 4, 8, 5, 10, 9};

    //----------------------------------------------------------------------------------------

    //key

    vector<int> key = {1, 0, 1, 0, 0, 0, 0, 0, 1, 0};
    vector<int> key1(0);
    vector<int> key2(0);
    vector<int> combined(0);

    vector<int> p10_key(10);
    SDES k1;
    p10_key = k1.permute( key, p10_table);
    cout<<"P10 key before.."<<endl;
    k1.show( p10_key);

    vector<int> left1, right1;
    for(int i = 0; i<5; i++){
        left1.emplace_back(p10_key[i]);
        right1.emplace_back(p10_key[i+5]);
    };

    //-----KEY 1----------------------
    cout<<"\n\n---FOR KEY 1-----\n\n";
    cout<<"\nLeft key before : ";
    k1.show(left1);
    cout<<endl;
    cout<<"\nI am doing left shifting...."<<endl;
    left1 = k1.leftShift(left1);
    cout<<"Left key after : ";
    k1.show(left1);
    cout<<endl;

    cout<<"Right key before : ";
    k1.show(right1);
    cout<<endl;
    cout<<"\nI am doing right shifting...."<<endl;
    right1 = k1.leftShift(right1);
    cout<<"Right key After : ";
    k1.show(right1);
    

    combined = left1;
    combined.insert(combined.end(), right1.begin(), right1.end());
    cout<<"combined : "<<endl;
    k1.show(combined);

    cout<<"\npermutating to 8 : ";
    key1 = k1.permute(combined, p8_table);

    //------------KEY 2----------------------
    cout<<"\n\n---FOR KEY 2-----\n\n";
    cout<<"\nLeft key before : ";
    k1.show(left1);
    cout<<endl;
    cout<<"\nI am doing left shifting...."<<endl;
    left1 = k1.leftShift(left1);
    cout<<"Left key after : ";
    k1.show(left1);
    cout<<endl;

    cout<<"Right key before : ";
    k1.show(right1);
    cout<<endl;
    cout<<"\nI am doing right shifting...."<<endl;
    right1 = k1.leftShift(right1);
    cout<<"Right key After : ";
    k1.show(right1);
    cout<<endl;

    combined.clear();
    combined = left1;
    combined.insert(combined.end(), right1.begin(), right1.end());
    cout<<"combined : "<<endl;
    k1.show(combined);

    cout<<"\nKey 2 : ";
    key2 = k1.permute(combined, p8_table);

    //-----ENCRYPTION--------------
    const vector<int> plaintext = {1, 0, 1, 1, 1, 1, 0, 1}; //plain text
    const vector<int> ip_table = {2, 6, 3, 1, 4, 8, 5, 7}; //intial permutation table


    k1.show(plaintext);
    cout<<"\nInitial permutation happening..\n";
    vector<int> ip_result = k1.permute(plaintext, ip_table);

    vector<int> left2(0);
    vector<int> right2(0);

    for(int i=0; i<4; i++){
        left2.emplace_back(ip_result[i]);
        right2.emplace_back(ip_result[i+4]);
    };

    cout<<"\n\nLeft side of IP result : ";
    k1.show(left2);
    cout<<"\nRIght side of IP result : ";
    k1.show(right2);
    cout<<endl;

    cout<<"\nKey 1 : ";
    k1.show(key1);
    const vector<int> exp_table = {4, 1, 2, 3, 2, 3, 4, 1};
    cout<<"\nExpansion Result : ";
    vector<int> exp_result = k1.permute(right2, exp_table);

    cout<<"\n\nXOR result : ";

    vector<int> xor_result = k1.xor_vec(exp_result, key1);

    vector<int> s0;
    vector<int> s1;
    for(int i = 0; i<4; i++){
        s0.emplace_back(xor_result[i]);
        s1.emplace_back(xor_result[i+4]);
    };

    cout<<"\n\nS0 : ";
    k1.show(s0);
    cout<<"\nS1 : ";
    k1.show(s1);
    cout<<endl;

    //-------SBOX PART-----------
    //this is done to provde maximum confusion
    const int arr_S0[4][4] = {
        {1, 0, 3, 2}, {3, 2, 1, 0}, {0, 2, 1, 3}, {3, 1, 3, 2}
    };

    const int arr_S1[4][4] = {
        {0, 1, 2, 3}, {2, 0, 1, 3}, {3, 0, 1, 0}, {2, 1, 0, 3}
    };

    vector<int> s0_compressed = k1.SBOX(s0, arr_S0);
    vector<int> s1_compressed = k1.SBOX(s1, arr_S1);

    vector<int> combined_p1(0);
    combined_p1 = s0_compressed;
    combined_p1.insert(combined_p1.end(), s1_compressed.begin(), s1_compressed.end());

    cout<<endl;
    vector<int> p1_xor;
    p1_xor = k1.xor_vec(combined_p1, left2);

    vector<int> temp_swap;
    temp_swap = p1_xor;
    p1_xor = right2;
    right2 = temp_swap;

    cout<<"\nExpansion Result : ";
    exp_result = k1.permute(right2, exp_table);

    xor_result = k1.xor_vec(exp_result, key2);

    s0.clear();
    s1.clear();
    for(int i = 0; i<4; i++){
        s0.emplace_back(xor_result[i]);
        s1.emplace_back(xor_result[i+4]);
    };

    s0_compressed.clear();
    s0_compressed = k1.SBOX(s0, arr_S0);
    s1_compressed.clear();
    s1_compressed = k1.SBOX(s1, arr_S1);

    combined_p1.clear();
    combined_p1 = s0_compressed;
    combined_p1.insert(combined_p1.end(), s1_compressed.begin(), s1_compressed.end());

    cout<<endl;
    p1_xor.clear();
    p1_xor = k1.xor_vec(combined_p1, temp_swap);

    vector<int> ip_2(0);
    ip_2 = p1_xor;
    ip_2.insert(ip_2.end(), right2.begin(), right2.end());

    ip_result.clear();
    ip_result = k1.permute( ip_2, ip_table);
    cout<<"\n\n\n\n Cipher text is : \n\n\n\n";
    k1.show(ip_result);
    return 0;

}
