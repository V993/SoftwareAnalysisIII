
#include <iostream>

using namespace std;

template<typename Object>
class List {
    private:
        struct Node {
            Object data;
            Node *prev;
            Node *next;
            Node(const Object &d = Object{}, Node *p = nullptr,
                Node *n = nullptr)
                : data(d), prev(p), next(n) {}
            
            Node(Object &&d, Node *p = nullptr,
                Node *n = nullptr)
                : data{move(d)}, prev{p}, next{n} {}
        };
    public: 
        class const_iterator {
            public: 
                const_iterator(): current_{nullptr} {}
                const Object &operator*() const { return current_->data; }
                const_iterator operator++() {
                    current_ = current_->next_;
                    return *this;
                }
                const_iterator operator++(int) {
                    const_iterator old = *this;
                    ++(*this);
                    return old;
                }

            protected:
                Node *current_;
                const_iterator(Node *p) : current_(p) {}
                friend class List<Object>;
        } 
        class iterator {
            public:
                iterator() {}
                Object &operator*() { return current_->data_; }
                const Object &operator*() const { return current_->data_; }
                iterator operator++() {
                    current_ = current_->next_;
                    return *this;
                }
                iterator operator++(int) {
                    iterator old = *this;
                    ++(*this);
                    return old;
                }
            protected:
                iterator(Node *p) : const_iterator{p} {}
                friend class List<Object>;
        } // Nested class

        List() {}
        List(const List &lst) {
            init();
            for(auto &x: rhs)
                push_back(x); // Need to provide this function.

        }
        List(List &&lst) {}
        const List &operator=(const List &rhs) {
            List copy = rhs;
            std::swap(*this, copy);
            return *this;
        }
        List &operator=(List &&rhs) {}
        ~List() {
            clear();
            delete head_;
            delete tail_;
        }

        iterator begin() {
            return const_iterator(head_->next_);
        }
        const_iterator begin() {}
        iterator end() {}
        const_iterator end() {
            return const_iterator(tail);
        }

}