#include <algorithm>
#include <cassert>
#include <iostream>
#include <map>

template <typename T, int initial_value>
class Matrix {
   private:
    using key_t = std::pair<int, int>;
    using type_t = std::map<key_t, T>;
    type_t m_matrix;
    class Proxy {
       private:
        type_t &m_matrix;
        int m_row;
        int m_col;

       public:
        explicit Proxy(type_t &matrix, int row) : m_matrix(matrix), m_row(row){};
        Proxy &operator[](int col) {
            m_col = col;
            return *this;
        };
        Proxy &operator=(T in) {
            m_matrix[key_t{m_row, m_col}] = in;
            return *this;
        };
        operator T() const {
            if (auto it = m_matrix.find(key_t{m_row, m_col}); it != m_matrix.end()) {
                return it->second;
            } else {
                return initial_value;
            }
        };
    };
    class Iterator {
       private:
        type_t::iterator m_ptr;

       public:
        using iterator_category = std::input_iterator_tag;
        explicit Iterator(const type_t::iterator &ptr) : m_ptr(ptr){};
        Iterator &operator++() {
            m_ptr++;
            return *this;
        };
        std::tuple<int, int, T> operator*() {
            return std::make_tuple((m_ptr->first).first, (m_ptr->first).second, m_ptr->second);
        };
        friend bool operator!=(const Iterator &a, const Iterator &b) { return a.m_ptr != b.m_ptr; };
    };

   public:
    std::size_t size() const { return m_matrix.size(); };
    Proxy operator[](int row) { return Proxy{m_matrix, row}; };

    Iterator begin() { return Iterator{m_matrix.begin()}; };
    Iterator end() { return Iterator{m_matrix.end()}; };
};
int main() {
    Matrix<int, -1> matrix;
    assert(matrix.size() == 0);  // все ячейки свободны
    auto a = matrix[0][0];
    assert(a == -1);
    assert(matrix.size() == 0);
    matrix[100][100] = 314;
    assert(matrix[100][100] == 314);
    assert(matrix.size() == 1);

    // выведется одна строка
    // 100100314
    for (auto c : matrix) {
        int x;
        int y;
        int v;
        std::tie(x, y, v) = c;
        std::cout << x << y << v << std::endl;
    }
    return 0;
}
