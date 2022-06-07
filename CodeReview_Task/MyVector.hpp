#pragma once
#include <vector>
#include <string>
#include <memory>
#include <algorithm>
#include <stdexcept>

template <typename T, typename Alloc = std::allocator<T>>
class MyVector {
private:
    using value_type = T;
    using name_type = std::string;
    using allocator_type = Alloc;
    using reference = value_type&;
    using const_reference = const value_type&;
    using name_reference = name_type&;
    using const_name_reference = const name_type&;
    using vector_type = std::pair<value_type, name_type>;
    using iterator = typename std::vector<std::pair<value_type, name_type>>::iterator;
    using const_iterator = typename std::vector<std::pair<value_type, name_type>>::const_iterator;
    using size_type = size_t;

    std::shared_ptr<std::vector<vector_type>> m_vector;

    void copy_names() {
        if (m_vector.unique())
            return;

        m_vector = std::make_shared<std::vector<vector_type>>(*m_vector);
    }
public:
    MyVector() : m_vector{ std::make_shared<std::vector<vector_type>>(std::vector<vector_type>()) } {}
    MyVector(const MyVector& other) = default;
    ~MyVector() = default;

    iterator begin() {
        return m_vector->begin();
    }
    const_iterator cbegin() const {
        return m_vector->cbegin();
    }
    iterator end() {
        return m_vector->end();
    }
    const_iterator cend() const {
        return m_vector->cend();
    }
    bool empty() const {
        m_vector->empty();
    }
    size_type size() const {
        return m_vector->size();
    }
    void reserve(size_type n) {
        m_vector->reserve(n);
    }
    void clear() {
        m_vector->clear();
    }
    void push_back(const_reference obj, const_name_reference name) {
        copy_names();

        m_vector->push_back(std::pair<value_type, name_type>(obj, name));
    }
    std::pair<reference, name_reference> operator[](size_type index) {
        copy_names();
        return const_cast<std::pair<reference, name_reference>>(static_cast<const MyVector<value_type>&>(*this)[index]);
    }
    std::pair<const_reference, const_name_reference> operator[](size_type index) const {
        if (index >= m_vector->size())
        {
            throw std::out_of_range("Index is out of range");
        }

        return std::pair<const_reference, const_name_reference>(*m_vector[index]);
    }
    reference operator[](const_name_reference name) {
        copy_names();
        return const_cast<reference>(static_cast<const MyVector<value_type>&>(*this)[name]);
    }
    const_reference operator[](const_name_reference name) const {
        const_iterator iter = std::find_if(m_vector->begin(), m_vector->end(),
            [&](const vector_type& obj) { return obj.second == name; });

        if (iter == m_vector->end())
        {
            throw std::invalid_argument(name + " is not found in MyVector");
        }

        return (*m_vector)[iter - m_vector->begin()].first;
    }
};