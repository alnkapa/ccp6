#include <algorithm>
#include <cassert>
#include <iostream>
#include <unordered_map>

template <typename T, int initial_value>
class SparseMatrix {
   private:
    std::size_t m_size{0};
    std::unordered_map<int, std::unordered_map<int, T>> m_matrix;

   public:
    size_t size() const { return m_size; };
    class Proxy {
       private:
        std::unordered_map<int, T> m_row;

       public:
        Proxy(std::unordered_map<int, T> &row) : m_row(row){};
        T &operator[](int col) {
            std::cout << "T1"
                      << "\n";
            std::cout << m_row[col] << "\n";
            return m_row[col];
        };
    };
    Proxy operator[](int row) {
        std::cout << "A1"
                  << "\n";
        if (auto it = m_matrix.find(row); it != m_matrix.end()) {
            std::cout << "it1"
                      << "\n";
            return Proxy{it->second};
        } else {
            return Proxy{m_matrix[row]};
        }
    };
};

int main() {
    SparseMatrix<int, -1> matrix;
    assert(matrix.size() == 0);  // все ячейки свободны
    auto a = matrix[0][0];
    // assert(a == -1);    
    assert(matrix.size() == 0);
    matrix[100][100] = 314;
    assert(matrix[100][100] == 314);
    return 0;
}
