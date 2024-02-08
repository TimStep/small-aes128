#include <iostream>
#include <algorithm>
#include <iterator>

int x02(int n) {

    int res;
    if (n < 0x80) {
        res = (n << 1);
    }
    else {
        res = (n << 1)^0x1b;
    }

    return (res % 0x100);
}

int x03(int n) {return (x02(n)^n); }

int main() {
    //Initial permutation
    int n[16] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
    int state[4][4];
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            state[j][i] = n[4*i + j];
            //std::cout << state[j][i];
        }
    }

    /* //check
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            std::cout << state[i][j];
        }
    }
    */

    int sbox_s[5][16] = {
    {10, 14, 13, 5, 9, 7, 0, 6, 15, 4, 11, 8, 2, 12, 1, 3},
    {0, 2, 11, 6, 8, 10, 5, 13, 15, 9, 12, 7, 1, 3, 14, 4},
    {9, 3, 13, 5, 7, 11, 8, 6, 2, 4, 14, 15, 12, 0, 1, 10},
    {7, 8, 5, 15, 11, 3, 9, 6, 2, 12, 1, 4, 14, 0, 10, 13},
    {13, 12, 5, 15, 4, 0, 10, 9, 7, 8, 3, 2, 11, 6, 1, 14}
    };

    //SubBytes
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            state[j][i] = sbox_s[0][4*i + j];
        }
    }

    /* //check
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            std::cout << state[i][j] << std::endl;
        }
    }
    */

    //ShiftRows
    for (int i = 1; i < 4; i++) {
        int temp[4]; 
        for (int j = 0; j < 4; j++) {
            temp[j] = state[i][(j+i)%4];
        }
        std::copy(std::begin(temp), std::end(temp), std::begin(state[i]));
    }

    /*//check
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            std::cout << state[i][j] << std::endl;
        }
    }
    */

    //MixColumns
    for (int i = 0; i < 4; i++) {
        int s0 = x02(state[0][i])^x03(state[1][i])^state[2][i]^state[3][i];
        int s1 = state[0][i]^x02(state[1][i])^x03(state[2][i])^state[3][i];
        int s2 = state[0][i]^state[1][i]^x02(state[2][i])^x03(state[3][i]);
        int s3 = x03(state[0][i])^state[1][i]^state[2][i]^x02(state[3][i]);

        state[0][i] = s0;
        state[1][i] = s1;
        state[2][i] = s2;
        state[3][i] = s3;
    }

    /*//check
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            std::cout << state[i][j] << std::endl;
        }
    }
    */

    //AddRoundKey
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            state[i][j] ^= sbox_s[0][4*i + j];
        }
    }

    //check
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            std::cout << state[i][j] << std::endl;
        }
    }
    
    return 0;
}