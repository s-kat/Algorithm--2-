#include<functional>
#include<vector>
#include<list>
#include <iterator>
#include <stdexcept>
#include<utility>

template<class KeyType, class ValueType, class Hash = std::hash<KeyType>> class HashMap {
private:
    std::list<std::pair<const KeyType, ValueType>> elems;
    std::vector<std::list<typename std::list<std::pair<const KeyType,
        ValueType>>::iterator>> table;
    size_t capacity = 0;
    size_t count = 0;
    Hash hasher;
    const size_t hash(const KeyType& key) const {
        return hasher(key) % capacity;
    }

    void MakeTable(size_t cap) {
        capacity = cap;
        table.resize(capacity);
    }

    void rehash() {
        if (count >= capacity) {
            capacity *= 2;
            table.clear();
            MakeTable(capacity);
            auto buf = elems;
            elems.clear();
            count = 0;
            for (const auto& el : buf) {
                insert(el);
            }
            buf.clear();
        }
    }

public:
    using iterator = typename std::list<std::pair<const KeyType, ValueType>>::iterator;
    using const_iterator = typename std::list < std::pair < const KeyType,
        ValueType>>::const_iterator;
    HashMap(Hash newhasher = Hash()) :hasher(newhasher) {
        MakeTable(128);
    }

    template<typename iter>
    HashMap(iter begin, iter end, Hash newhasher = Hash()) : hasher(newhasher) {
        MakeTable(128);
        for (; begin != end; ++begin) {
            insert(*begin);
        }
    }

    HashMap(const std::initializer_list<std::pair<KeyType, ValueType>>& list,
        Hash newhasher = Hash()) :hasher(newhasher) {
        MakeTable(128);
        for (const auto& el : list) {
            insert(el);
        }
    }
    const size_t size() const {
        return count;
    }

    const bool empty() const {
        return count == 0;
    }

    const Hash hash_function() const {
        return hasher;
    }

    bool FindKey(const KeyType& key, const size_t& index) const {
        for (const auto& el : table[index]) {
            if (el->first == key) {
                return true;
            }
        }
        return false;
    }

    void insert(const std::pair<KeyType, ValueType>& pair) {
        rehash();
        size_t place = hash(pair.first);
        if (!(FindKey(pair.first, place))) {
            ++count;
            elems.push_front(pair);
            table[place].push_front(elems.begin());
        }
    }

    void erase(const KeyType& key) {
        size_t place = hash(key);
        for (auto begin = table[place].begin(); begin != table[place].end(); ++begin) {
            if ((*begin)->first == key) {
                elems.erase(*begin);
                table[place].erase(begin);
                --count;
                break;
            }
        }
    }

    iterator begin() {
        return elems.begin();
    }

    const_iterator begin() const {
        return elems.begin();
    }

    iterator end() {
        return elems.end();
    }

    const_iterator end() const {
        return elems.end();
    }

    void clear() {
        count = 0;
        elems.clear();
        table.clear();
        MakeTable(128);
    }

    iterator find(const KeyType& key) {
        size_t place = hash(key);
        for (auto& el : table[place]) {
            if (el->first == key) {
                return el;
            }
        }
        return end();
    }

    const const_iterator find(KeyType key) const {
        size_t place = hash(key);
        for (auto& el : table[place]) {
            if (el->first == key) {
                return el;
            }
        }
        return end();
    }

    const ValueType& at(KeyType key) const {
        size_t place = hash(key);
        for (const auto& el : table[place]) {
            if (el->first == key) {
                return el->second;
            }
        }
        throw std::out_of_range("Bad index");
    }

    ValueType& operator[] (const KeyType& key) {
        size_t place = hash(key);
        for (const auto& el : table[place]) {
            if (el->first == key) {
                return el->second;
            }
        }
        insert({ key, ValueType() });
        return (*elems.begin()).second;
    }
    HashMap& operator =(const HashMap& second) {
        auto ad = second.elems;
        table.clear();
        elems.clear();
        count = 0;
        MakeTable(second.capacity);
        for (const auto& el : ad) {
            insert(el);
        }
        ad.clear();
        return *this;
    }
};
