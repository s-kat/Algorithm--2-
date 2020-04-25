#include<functional>
#include<vector>
#include<list>
#include <iterator>
#include <stdexcept>
#include<utility>
#include<iostream>

template<class KeyType, class ValueType, class Hash = std::hash<KeyType>> class HashMap {
private:
    std::list<std::pair<const KeyType, ValueType>> elems;
    std::vector<typename std::list<std::pair<const KeyType,
        ValueType>>::iterator> table;
    std::vector<int> cond;
    size_t capacity = 0;
    size_t count = 0;
    Hash hasher;
    const size_t hash(const KeyType& key) const {
        return hasher(key) % capacity;
    }

    void MakeTable(size_t cap) {
        capacity = cap;
        table.resize(capacity);
        cond.resize(capacity);
    }

    void rehash() {
        if (count >= capacity / 2) {
            capacity *= 2;
            table.clear();
            cond.clear();
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
        MakeTable(64);
    }

    template<typename iter>
    HashMap(iter begin, iter end, Hash newhasher = Hash()) : hasher(newhasher) {
        MakeTable(64);
        for (; begin != end; ++begin) {
            insert(*begin);
        }
    }

    HashMap(const std::initializer_list<std::pair<KeyType, ValueType>>& list,
        Hash newhasher = Hash()) :hasher(newhasher) {
        MakeTable(64);
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

    void insert(const std::pair<KeyType, ValueType>& pair) {
        rehash();
        KeyType key = pair.first;
        size_t place = hash(key);
        int loop = 1;
        while (loop == 1) {
            if (cond[place] == 0) {
                ++count;
                elems.push_front(pair);
                table[place] = elems.begin();
                cond[place] = 1;
            } else if (table[place]->first == key && cond[place] == 1) {
                break;
            } else {
                place += 1;
                place = place % capacity;
            }
        }
    }

    void erase(const KeyType& key) {
        size_t place = hash(key);
        int loop = 1;
        while (loop == 1) {
            if (cond[place] == 0) {
                break;
            } else if (table[place]->first == key && cond[place] != -1) {
                cond[place] = -1;
                elems.erase(table[place]);
                --count;
                break;
            } else {
                ++place;
                place = place % capacity;
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
        cond.clear();
        MakeTable(64);
    }

    iterator find(const KeyType& key) {
        size_t place = hash(key);
        int loop = 1;
        while (loop == 1) {
            if (cond[place] == 0) {
                return end();
            } else if (table[place]->first == key && cond[place] != -1) {
                return table[place];
            }
            ++place;
            place = place % capacity;
        }
    }

    const const_iterator find(KeyType key) const {
        size_t place = hash(key);
        int loop = 1;
        while (loop == 1) {
            if (cond[place] == 0) {
                return end();
            } else if (table[place]->first == key && cond[place] != -1) {
                return table[place];
            }
             ++place;
             place = place % capacity;
        }
    }

    const ValueType& at(KeyType key) const {
        size_t place = hash(key);
        int loop = 1;
        while (loop == 1) {
            if (cond[place] == 0) {
                throw std::out_of_range("Bad index");
            } else if (table[place]->first == key && cond[place] != -1) {
                return table[place]->second;
            } else {
                ++place;
                place = place % capacity;
            }
        }
        throw std::out_of_range("Bad index");
    }

    ValueType& operator[] (const KeyType& key) {
        rehash();
        size_t place = hash(key);
        int loop = 1;
        while (loop == 1) {
            if (cond[place] == 0) {
                ++count;
                elems.push_front({ key, ValueType() });
                table[place] = elems.begin();
                cond[place] = 1;
                return (*elems.begin()).second;
            } else if (table[place]->first == key) {
                if (cond[place] != -1) {
                    return table[place]->second;
                }
            }
            ++place;
            place = place % capacity;
        }
    }
    HashMap& operator =(const HashMap& second) {
        auto ad = second.elems;
        table.clear();
        elems.clear();
        cond.clear();
        count = 0;
        MakeTable(second.capacity);
        for (const auto& el : ad) {
            insert(el);
        }
        ad.clear();
        return *this;
    }
};
