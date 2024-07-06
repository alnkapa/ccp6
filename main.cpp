#include <algorithm>
#include <cassert>
#include <iostream>
#include <unordered_map>

template <typename T, int initial_value>
class Matrix {
    friend class Proxy;

   private:
    std::size_t m_size{0};
    std::unordered_map<int, std::unordered_map<int, T>> m_matrix;

   public:
    size_t size() const { return m_size; };
    class Proxy {
       private:
        std::unordered_map<int, T> &m_row;

       public:
        Proxy(std::unordered_map<int, T> &row) : m_row(row){};
        T &operator[](int col) {
            std::cout << "T1"
                      << "\n";
            std::cout << m_row[col] << "\n";
            return m_row[col];
        };
        bool dd() { return true; };
    };
    Proxy operator[](int row) {
        std::cout << "A1"
                  << "\n";
        if (auto it = m_matrix.find(row); it != m_matrix.end()) {
            std::cout << "it1"
                      << "\n";
            return Proxy{it->second};
        } else {
            auto m = Proxy{m_matrix[row]};
            m.dd();
            std::cout << "n:" << m_matrix.size() << std::endl;
            return m;
        }
    };
};
struct Arg {
    int i = 1;
    int &value() &  // non-const lvalue
    {
        std::cout << __PRETTY_FUNCTION__ << "\n";
        return i;
    }

    int &&value() &&  // non-const rvalue
    {
        std::cout << __PRETTY_FUNCTION__ << "\n";
        return std::move(i);  // propagate rvalue-ness
    }

    const int &value() const &  // const lvalue
    {
        std::cout << __PRETTY_FUNCTION__ << "\n";
        return i;
    }

    const int &&value() const &&  // const rvalue
    {
        std::cout << __PRETTY_FUNCTION__ << "\n";
        return std::move(i);  // propagate rvalue-ness
    }
};
template <class T>
void wrapper(T &&arg) {
    foo(forward<decltype(forward<T>(arg).get())>(forward<T>(arg).get()));
}
int main() {
    Arg m;
    auto a = m.value();
    m.value() = a;
    const Arg m1;
    auto b = m1.value();
    // m1.value() = a;
    auto d = Arg().value();  // вызов non-const rvalue

    // Arg().value() = 5;  // вызов non-const rvalue

    auto const d1 = Arg().value();  // вызов const rvalue

    return 0;
}
// Matrix<int, -1> matrix;
// assert(matrix.size() == 0);  // все ячейки свободны
// auto a = matrix[0][0];
// assert(a == -1);
// assert(matrix.size() == 0);
// matrix[100][100] = 314;
// assert(matrix[100][100] == 314);
// assert(matrix.size() == 1);
// return 0;
// }
