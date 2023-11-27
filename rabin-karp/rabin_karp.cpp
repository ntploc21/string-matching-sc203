#include "rabin_karp.hpp"

namespace rabin_karp {

    long long random_prime(long long n);

    std::vector<int> rabin_karp(std::string const& pattern, std::string const& text) {
        const int p = 31;
        int pattern_size = pattern.size(), text_size = text.size();
        const int m = random_prime((long long)pattern_size * text_size * text_size);

        // Calculate (p^i) % m
        std::vector<long long> p_pow(std::max(pattern_size, text_size));
        p_pow[0] = 1;
        for (int i = 1; i < (int)p_pow.size(); i++)
            p_pow[i] = (p_pow[i - 1] * p) % m;

        // Calculate (text[i] * p^i) % m
        std::vector<long long> hash_text(text_size + 1, 0);
        for (int i = 0; i < text_size; i++)
            hash_text[i + 1] = (hash_text[i] + text[i] * p_pow[i]) % m;

        // Calculate the hash of pattern
        long long hash_pattern = 0;
        for (int i = 0; i < pattern_size; i++) hash_pattern = (hash_pattern + pattern[i] * p_pow[i]) % m;

        // Rabin-Karp 
        std::vector<int> occurrences;
        for (int i = 0; i + pattern_size - 1 < text_size; i++) {
            long long cur_hash = (hash_text[i + pattern_size] + m - hash_text[i]) % m;
            if (cur_hash == ((hash_pattern * p_pow[i]) % m)) {
                bool isEqual = true;
                for (int j = 0; j < pattern_size; ++j) {
                    if (pattern[j] != text[i + j]) {
                        isEqual = false;
                    }
                }
                if (isEqual) occurrences.push_back(i);
            }
        }
        return occurrences;
    }

    /*<------------------------Generate prime numbers by Rabin-Miller test---------------------------->*/

    long long random64();
    bool rabin_miller_test(long long n);

    long long random_prime(long long n){
        int rand = random64()%(n-2)+2;
        while(!rabin_miller_test(rand)){
            rand = random64()%(n-2)+2;
        }
        return rand;
    }

    long long random64(){
        long long n = 0;
        int l = rand()%(RAND_MAX-2)+2;
        int r = rand()%(RAND_MAX) + rand()%2;
        n = n | ((long long)r);
        n = n << 32;
        n = n | ((long long)l);
        return n;
    }

    /*
    * Calculate a^k mod n
    */
    long long binary_power(long long a, long long k, long long n) {
        a = a % n;
        long long res = 1;
        while (k) {
            if (k & 1) res = (res * a) % n;
            a = (a * a) % n;
            k /= 2;
        }
        return res;
    }

    /*
    * Rabin-Miller conditions
    */
    bool rabin_miller_conditions(long long a, long long n, long long k, long long m) {
        long long mod = binary_power(a, m, n);
        if (mod == 1 || mod == n - 1) return true;          // (a^m + 1) % n == 1 || (a^m - 1) % n == 1        
        for (int l = 1; l < k; ++l) {
            mod = (mod * mod) % n;
            if (mod == n - 1) return true;                  // (a^m)^(2*l) % n == -1
        }
        return false;
    }

    /*
    * Rabin-Miller test
    */
    bool rabin_miller_test(long long n) {
        if (n == 2 || n == 3 || n == 5 || n == 7) return true;
        if (n < 11) return false;

        // n = 2^k * m
        long long k = 0, m = n - 1;
        while (m % 2 == 0) {
            m /= 2;
            k++;
        }

        // Repeat test with probability of false match: (1/4^x) x 100%
        const static int repeatTime = 4;
        for (int i = 0; i < repeatTime; ++i) {
            long long a = rand() % (n - 3) + 2;
            if (!rabin_miller_conditions(a, n, k, m)) return false;
        }
        return true;
    }

};  // namespace rabin_karp
