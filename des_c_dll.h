// MyCFuncs.h
#ifdef __cplusplus
extern "C" {  // only need to export C interface if
              // used by C++ source code
#endif

//__declspec( dllimport ) void codePlayfair(char CharTable[2]);
//__declspec( dllimport ) long long int permute_key(int* permutation_table, long long int mainKey,int keySize, int matrixSize);
//__declspec( dllimport ) long long int generate_key(long long int start_key, int number,int* initial_key_per_table, int* end_key_per_table);
__declspec( dllimport ) long long int encrypt_message(long long int message, long long int key);
__declspec( dllimport ) long long int decrypt_message(long long int message, long long int key);

#ifdef __cplusplus
}
#endif