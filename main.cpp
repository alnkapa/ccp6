#include <algorithm>
#include <iostream>
#include <vector>

namespace model {
    class Shape {
       public:
        Shape(std::initializer_list<float> in) : m_vertices(in){};
        const std::vector<float> &data() const { return m_vertices; };
        friend bool operator==(const Shape &a, const Shape &b) { return &a == &b; };
        std::vector<unsigned char> dump() const {
            std::vector<unsigned char> rez{};
            // TODO
            return rez;
        };
        void import(const std::vector<unsigned char> &in) {
            // TODO
        };

       private:
        std::vector<float> m_vertices;
    };

    class Document {
       public:
        void clear() { m_doc.clear(); };
        void add_shape(Shape &&shape) { m_doc.emplace_back(shape); };
        void add_shape(Shape &shape) { m_doc.emplace_back(shape); };
        void del_shape(const Shape &shape) {
            auto it = std::find(m_doc.begin(), m_doc.end(), shape);
            if (it != m_doc.end()) {
                m_doc.erase(it);
            }
        };
        const std::vector<Shape> &data() const { return m_doc; };
        std::vector<unsigned char> dump() const {
            std::vector<unsigned char> rez{};
            // TODO
            for (const auto &v : m_doc) {
                [[maybe_unused]] auto part = v.dump();
                // TODO
            }
            // TODO
            return rez;
        };
        void import(const std::vector<unsigned char> &in) {
            // TODO
            for (auto &v : m_doc) {
                v.import(in);
                // TODO
            }
            // TODO
        };

       private:
        std::vector<Shape> m_doc;
    };

}  // namespace model

namespace view {
    class Shape {
       public:
        static void render(const std::vector<float> &shape) {
            std::cout << "Shape: ";
            for (const auto &v : shape) {
                std::cout << v << " ; ";
            }
        };
    };
    class Document {
       public:
        static void render(const std::vector<model::Shape> &document) {
            for (const auto &v : document) {
                std::cout << "Document: ";
                Shape::render(v.data());
                std::cout << std::endl;
            }
        };
    };
}  // namespace view

class Controller {
   public:
    void clear_document() {  // создание нового документа
        m_model.clear();
        view::Document::render(m_model.data());
    };
    void create_shape(model::Shape &&shape) {  // создание графического примитива
        m_model.add_shape(std::move(shape));
        view::Document::render(m_model.data());
    };
    void create_shape(model::Shape &shape) {  // создание графического примитива
        m_model.add_shape(shape);
        view::Document::render(m_model.data());
    };

    void delete_shape(const model::Shape &shape) {  // удаление графического примитива
        m_model.del_shape(shape);
        view::Document::render(m_model.data());
    };

    void import_document(const std::vector<unsigned char> &file) {  // импорт документа из файла
        m_model.import(file);
        view::Document::render(m_model.data());
    };
    std::vector<unsigned char> export_document() {  // экспорт документа в файл
        return m_model.dump();
    };

   private:
    model::Document m_model{};
};

int main() {
    auto c{Controller{}};
    c.clear_document();
    auto s1{model::Shape{{10, 20, 30, 40}}};
    c.create_shape(s1);
    for (int i = 0; i < 2; i++) {
        c.create_shape(std::move(model::Shape{{11, 12}}));
    };
    c.delete_shape(s1);
    const auto data = c.export_document();
    for (int i = 0; i < 3; i++) {
        c.create_shape(std::move(model::Shape{{15, 3}}));
    };
    c.import_document(data);
    // TODO
    return 0;
}
/*
строки ведут себя как вектор ?

а есть что то для итераторов для из инвалидации
автоматический

*/