#include <cassert>
#include <iostream>
#include <map>
#include <tuple>

template <typename T, int initial_value>
class SparseMatrix {
   public:
    using result_t = SparseMatrix<T, initial_value>;
    using key_t = std::pair<int, int>;
    size_t size() const { return m_matrix.size(); };
    class Proxy {
       public:
        Proxy(result_t &parent, int row) : m_parent(parent), m_row(row){};
        T &operator[](int col) {
            std::cout << "T1"
                      << "\n";
            return m_parent.m_matrix[{m_row, col}];
        };
        const T operator[](int col) const {
            std::cout << "T2"
                      << "\n";
            try {
                return m_parent.m_matrix.at({m_row, col});
            } catch (std::out_of_range) {
                return initial_value;
            }
        };

       private:
        int m_row;
        result_t &m_parent;
    };
    const Proxy operator[](int row) const {
        std::cout << "A1"
                  << "\n";
        return Proxy{*this, row};
    };
    Proxy operator[](int row) {
        std::cout << "A1"
                  << "\n";
        return Proxy{*this, row};
    };
    // const Proxy &operator[](int row) const {
    //     std::cout << "A2"
    //               << "\n";
    //     const auto p = Proxy{this, row};
    //     return p;
    // };

   private:
    std::map<key_t, T> m_matrix;
};

int main() {
    SparseMatrix<int, -1> matrix;
    assert(matrix.size() == 0);  // все ячейки свободны
    auto const a = matrix[0][0];
    // // assert(a == -1);
    // // assert(matrix.size() == 0);
    matrix[100][100] = 314;
    assert(matrix[100][100] == 314);
    return 0;
}
