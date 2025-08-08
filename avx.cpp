#pragma GCC target("avx2")
#include <iostream>
#include <immintrin.h>

signed main() {
    __m256i a = _mm256_setzero_si256();
    __m256i b = _mm256_set1_epi32(64);
    int array0[] = {1,2,3,4,5,6,7,8}, array1[] = {1,2,3,4,5,6,7,8};
    __m256i c = _mm256_lddqu_si256(reinterpret_cast<__m256i*>(array0)), d = _mm256_lddqu_si256(reinterpret_cast<__m256i*>(array1));
    __m256i e = _mm256_add_epi32(c, d);
    int res[8];
    _mm256_storeu_si256(reinterpret_cast<__m256i*>(res), e);
    for (int elem : res) std::cout << elem << ' ';
}