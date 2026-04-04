#pragma once
#include <iostream>
#include <string>

template <typename Key, typename Value>
class Map {
private:
    struct Node {
        Key key;
        Value value;
        Node* next;

        Node(const Key& k, const Value& v) : key(k), value(v), next(nullptr) {}
    };

    Node* head;

    void clear() {
        Node* current = head;
        while (current != nullptr) {
            Node* toDelete = current;
            current = current->next;
            delete toDelete;
        }
        head = nullptr;
    }

    void copyFrom(const Map& other) {
        if (other.head == nullptr) {
            return;
        }

        head = new Node(other.head->key, other.head->value);
        Node* current = head;
        Node* otherCurrent = other.head->next;

        while (otherCurrent != nullptr) {
            current->next = new Node(otherCurrent->key, otherCurrent->value);
            current = current->next;
            otherCurrent = otherCurrent->next;
        }
    }

public:
    Map() : head(nullptr) {}

    ~Map() {
        clear();
    }

    Map(const Map& other) : head(nullptr) {
        copyFrom(other);
    }

    Map& operator=(const Map& other) {
        if (this == &other) {
            return *this;
        }

        clear();
        copyFrom(other);
        
        return *this;
    }

    void add(const Key& key, const Value& value) {
        if (head == nullptr) {
            head = new Node(key, value);
            return;
        }

        Node* current = head;
        while (current != nullptr) {
            if (current->key == key) {
                current->value = value; 
                return;
            }
            if (current->next == nullptr) {
                break;
            }
            
            current = current->next;
        }
        current->next = new Node(key, value);
    }

    Value* find(const Key& key) {
        Node* current = head;
        while (current != nullptr) {
            if (current->key == key) {
                return &current->value;
            }
            current = current->next;
        }
        return nullptr;
    }

    const Value* find(const Key& key) const {
        Node* current = head;
        while (current != nullptr) {
            if (current->key == key) {
                return &current->value;
            }
            current = current->next;
        }
        return nullptr;
    }

    template <typename K, typename V>
    friend std::ostream& operator<<(std::ostream& os, const Map<K, V>& map);
};

template <typename K, typename V>
std::ostream& operator<<(std::ostream& os, const Map<K, V>& map) {
    typename Map<K, V>::Node* current = map.head;
    while (current != nullptr) {
        os << current->key << ":\n" << current->value << "\n";
        current = current->next;
    }
    return os;
}