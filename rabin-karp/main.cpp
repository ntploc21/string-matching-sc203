#include "rabin_karp.hpp"

int main() {
    std::vector<int> occur;
    occur = rabin_karp::rabin_karp("SCI", "UNIVERSITYOFSCIENCE");
    
    std::cout << "\nMatch: " << occur.size() << '\n';
    std::cout << "Position: ";
    for (int i = 0; i < occur.size(); ++i) {
        std::cout << occur[i] << ' ';
    }

    return 0;
}
