#ifndef SIMPLEMAP_H
#define SIMPLEMAP_H

#include <string>
#include "ListaSE.h"
#include "Nodos.h"

using namespace std;

template <typename K, typename V>
class SimpleMap {
private:
    MapNode<K, V>* head;

public:
    SimpleMap();
    ~SimpleMap();
    void insert(K key, V value);
    V* get(K key);
    bool contains(K key);
};

// Implementación de SimpleMap
template <typename K, typename V>
SimpleMap<K, V>::SimpleMap() : head(nullptr) {}

template <typename K, typename V>
SimpleMap<K, V>::~SimpleMap() {
    MapNode<K, V>* temp = head;
    while (temp != nullptr) {
        MapNode<K, V>* next = temp->next;
        delete temp;
        temp = next;
    }
}

template <typename K, typename V>
void SimpleMap<K, V>::insert(K key, V value) {
    MapNode<K, V>* newNode = new MapNode<K, V>(key, value);
    newNode->next = head;
    head = newNode;
}

template <typename K, typename V>
V* SimpleMap<K, V>::get(K key) {
    MapNode<K, V>* temp = head;
    while (temp != nullptr) {
        if (temp->key == key) {
            return &temp->value;
        }
        temp = temp->next;
    }
    return nullptr;
}

template <typename K, typename V>
bool SimpleMap<K, V>::contains(K key) {
    return get(key) != nullptr;
}

// Necesario para evitar errores de enlace con templates
template class SimpleMap<string, ListaSE<string>>;

#endif // SIMPLEMAP_H
