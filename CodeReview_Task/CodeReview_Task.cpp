#pragma once
#include "MyVector.hpp"
#include <iostream>

/*
 * MyVector stores a collection of objects with their names.
 *
 * For each object T, MyVector stores T`s name as std::string.
 * Several objects can have similar name.
 * operator[](const std::string& name) should return the first object
 * with the given name.
 *
 * You can change MyVector interface completely, but there are several rules:
 * 1) you should correctly and fully implement copy-on-write idiom.
 * 2) std::pair<const T&, const std::string&> operator[](int index) const must take constant time at worst.
 * 3) const T& operator[](const std::string& name) const should be present.
 * 4) both operator[] should have non-const version.
 * 5) your implementation should provide all the member types of std::vector.
 * 6) your implementation should provide the following functions:
 *    1) begin(), cbegin(), end(), cend()
 *    2) empty(), size()
 *    3) reserve(), clear()
 */

int main() {
    MyVector<std::string> cities;
    cities.push_back("Lviv", "West");
    cities.push_back("Kyiv", "North");
    cities.push_back("Lutsk", "West");
    std::cout << "Cities[West]: " << cities["West"] << std::endl;
    std::cout << std::endl;

    MyVector<std::string> cities2 = cities;
    cities2.push_back("Luhansk", "East");
    std::cout << "Cities2[East]: " << cities2["East"] << std::endl;
    try {
        std::cout << "Cities[East]: " << cities["East"] << std::endl;
    }
    catch (const std::invalid_argument ex) {
        std::cout << "Cities[East]: " << ex.what() << std::endl;
    }
    std::cout << std::endl;

    std::cout << "Cities size = " << cities.size() << std::endl;
    std::cout << "Cities2 size = " << cities2.size() << std::endl;

    return 0;
}
