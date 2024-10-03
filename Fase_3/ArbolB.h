#ifndef ARBOLB_H
#define ARBOLB_H

#include "Nodos.h"
#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

template <typename T, int ORDER>
class ArbolB {
private:
    NodoB<T, ORDER>* root;

    void splitChild(NodoB<T, ORDER>* x, int i);
    void insertNonFull(NodoB<T, ORDER>* x, T k);
    void traverse(NodoB<T, ORDER>* x);
    NodoB<T, ORDER>* search(NodoB<T, ORDER>* x, T k);
    T getPredecessor(NodoB<T, ORDER>* node, int idx);
    T getSuccessor(NodoB<T, ORDER>* node, int idx);
    void fill(NodoB<T, ORDER>* node, int idx);
    void borrowFromPrev(NodoB<T, ORDER>* node, int idx);
    void borrowFromNext(NodoB<T, ORDER>* node, int idx);
    void merge(NodoB<T, ORDER>* node, int idx);
    void removeFromNonLeaf(NodoB<T, ORDER>* node, int idx);
    void removeFromLeaf(NodoB<T, ORDER>* node, int idx);
    void remove(NodoB<T, ORDER>* node, T k);
    void printRec(NodoB<T, ORDER>* nodo, const string& name, ofstream& file, int& printNodeCount) const;
    void traversal(NodoB<T, ORDER>* myNode, vector<T>& elementos) const;

public:
    ArbolB();
    void insert(T k);
    void traverse();
    NodoB<T, ORDER>* search(T k);
    void remove(T k);
    string renderGraphviz(const string& filename) const;
    vector<T> obtenerElementos() const;
};

// Definiciones de las funciones miembro de la clase ArbolB

template <typename T, int ORDER>
ArbolB<T, ORDER>::ArbolB() {
    root = new NodoB<T, ORDER>(true);
}

template <typename T, int ORDER>
void ArbolB<T, ORDER>::splitChild(NodoB<T, ORDER>* x, int i) {
    NodoB<T, ORDER>* y = x->children[i];
    NodoB<T, ORDER>* z = new NodoB<T, ORDER>(y->leaf);
    z->n = ORDER / 2 - 1;

    for (int j = 0; j < ORDER / 2 - 1; j++)
        z->keys[j] = y->keys[j + ORDER / 2];

    if (!y->leaf) {
        for (int j = 0; j < ORDER / 2; j++)
            z->children[j] = y->children[j + ORDER / 2];
    }

    y->n = ORDER / 2 - 1;

    for (int j = x->n; j >= i + 1; j--)
        x->children[j + 1] = x->children[j];

    x->children[i + 1] = z;

    for (int j = x->n - 1; j >= i; j--)
        x->keys[j + 1] = x->keys[j];

    x->keys[i] = y->keys[ORDER / 2 - 1];
    x->n = x->n + 1;
}

template <typename T, int ORDER>
void ArbolB<T, ORDER>::insertNonFull(NodoB<T, ORDER>* x, T k) {
    int i = x->n - 1;

    if (x->leaf) {
        while (i >= 0 && k < x->keys[i]) {
            x->keys[i + 1] = x->keys[i];
            i--;
        }

        x->keys[i + 1] = k;
        x->n = x->n + 1;
    } else {
        while (i >= 0 && k < x->keys[i])
            i--;

        i++;
        if (x->children[i]->n == ORDER - 1) {
            splitChild(x, i);

            if (k > x->keys[i])
                i++;
        }
        insertNonFull(x->children[i], k);
    }
}

template <typename T, int ORDER>
void ArbolB<T, ORDER>::traverse(NodoB<T, ORDER>* x) {
    int i;
    for (i = 0; i < x->n; i++) {
        if (!x->leaf)
            traverse(x->children[i]);
        cout << " " << x->keys[i];
    }

    if (!x->leaf)
        traverse(x->children[i]);
}

template <typename T, int ORDER>
NodoB<T, ORDER>* ArbolB<T, ORDER>::search(NodoB<T, ORDER>* x, T k) {
    int i = 0;
    while (i < x->n && k > x->keys[i])
        i++;

    if (i < x->n && k == x->keys[i])
        return x;

    if (x->leaf)
        return nullptr;

    return search(x->children[i], k);
}

template <typename T, int ORDER>
T ArbolB<T, ORDER>::getPredecessor(NodoB<T, ORDER>* node, int idx) {
    NodoB<T, ORDER>* current = node->children[idx];
    while (!current->leaf)
        current = current->children[current->n];
    return current->keys[current->n - 1];
}

template <typename T, int ORDER>
T ArbolB<T, ORDER>::getSuccessor(NodoB<T, ORDER>* node, int idx) {
    NodoB<T, ORDER>* current = node->children[idx + 1];
    while (!current->leaf)
        current = current->children[0];
    return current->keys[0];
}

template <typename T, int ORDER>
void ArbolB<T, ORDER>::fill(NodoB<T, ORDER>* node, int idx) {
    if (idx != 0 && node->children[idx - 1]->n >= ORDER / 2)
        borrowFromPrev(node, idx);
    else if (idx != node->n && node->children[idx + 1]->n >= ORDER / 2)
        borrowFromNext(node, idx);
    else {
        if (idx != node->n)
            merge(node, idx);
        else
            merge(node, idx - 1);
    }
}

template <typename T, int ORDER>
void ArbolB<T, ORDER>::borrowFromPrev(NodoB<T, ORDER>* node, int idx) {
    NodoB<T, ORDER>* child = node->children[idx];
    NodoB<T, ORDER>* sibling = node->children[idx - 1];

    for (int i = child->n - 1; i >= 0; --i)
        child->keys[i + 1] = child->keys[i];

    if (!child->leaf) {
        for (int i = child->n; i >= 0; --i)
            child->children[i + 1] = child->children[i];
    }

    child->keys[0] = node->keys[idx - 1];

    if (!child->leaf)
        child->children[0] = sibling->children[sibling->n];

    node->keys[idx - 1] = sibling->keys[sibling->n - 1];

    child->n += 1;
    sibling->n -= 1;
}

template <typename T, int ORDER>
void ArbolB<T, ORDER>::borrowFromNext(NodoB<T, ORDER>* node, int idx) {
    NodoB<T, ORDER>* child = node->children[idx];
    NodoB<T, ORDER>* sibling = node->children[idx + 1];

    child->keys[child->n] = node->keys[idx];

    if (!child->leaf)
        child->children[child->n + 1] = sibling->children[0];

    node->keys[idx] = sibling->keys[0];

    for (int i = 1; i < sibling->n; ++i)
        sibling->keys[i - 1] = sibling->keys[i];

    if (!sibling->leaf) {
        for (int i = 1; i <= sibling->n; ++i)
            sibling->children[i - 1] = sibling->children[i];
    }

    child->n += 1;
    sibling->n -= 1;
}

template <typename T, int ORDER>
void ArbolB<T, ORDER>::merge(NodoB<T, ORDER>* node, int idx) {
    NodoB<T, ORDER>* child = node->children[idx];
    NodoB<T, ORDER>* sibling = node->children[idx + 1];

    child->keys[ORDER / 2 - 1] = node->keys[idx];

    for (int i = 0; i < sibling->n; ++i)
        child->keys[i + ORDER / 2] = sibling->keys[i];

    if (!child->leaf) {
        for (int i = 0; i <= sibling->n; ++i)
            child->children[i + ORDER / 2] = sibling->children[i];
    }

    for (int i = idx + 1; i < node->n; ++i)
        node->keys[i - 1] = node->keys[i];

    for (int i = idx + 2; i <= node->n; ++i)
        node->children[i - 1] = node->children[i];

    child->n += sibling->n + 1;
    node->n--;

    delete sibling;
}

template <typename T, int ORDER>
void ArbolB<T, ORDER>::removeFromNonLeaf(NodoB<T, ORDER>* node, int idx) {
    T k = node->keys[idx];

    if (node->children[idx]->n >= ORDER / 2) {
        T pred = getPredecessor(node, idx);
        node->keys[idx] = pred;
        remove(node->children[idx], pred);
    } else if (node->children[idx + 1]->n >= ORDER / 2) {
        T succ = getSuccessor(node, idx);
        node->keys[idx] = succ;
        remove(node->children[idx + 1], succ);
    } else {
        merge(node, idx);
        remove(node->children[idx], k);
    }
}

template <typename T, int ORDER>
void ArbolB<T, ORDER>::removeFromLeaf(NodoB<T, ORDER>* node, int idx) {
    for (int i = idx + 1; i < node->n; ++i)
        node->keys[i - 1] = node->keys[i];

    node->n--;
}

template <typename T, int ORDER>
void ArbolB<T, ORDER>::remove(NodoB<T, ORDER>* node, T k) {
    int idx = 0;
    while (idx < node->n && node->keys[idx] < k)
        ++idx;

    if (idx < node->n && node->keys[idx] == k) {
        if (node->leaf)
            removeFromLeaf(node, idx);
        else
            removeFromNonLeaf(node, idx);
    } else {
        if (node->leaf) {
            cout << "The key " << k << " is not present in the tree\n";
            return;
        }

        bool flag = ((idx == node->n) ? true : false);

        if (node->children[idx]->n < ORDER / 2)
            fill(node, idx);

        if (flag && idx > node->n)
            remove(node->children[idx - 1], k);
        else
            remove(node->children[idx], k);
    }
}

template <typename T, int ORDER>
void ArbolB<T, ORDER>::insert(T k) {
    if (root->n == ORDER - 1) {
        NodoB<T, ORDER>* s = new NodoB<T, ORDER>(false);
        s->children[0] = root;
        root = s;
        splitChild(s, 0);
        insertNonFull(s, k);
    } else
        insertNonFull(root, k);
}

template <typename T, int ORDER>
void ArbolB<T, ORDER>::traverse() {
    if (root != nullptr)
        traverse(root);
}

template <typename T, int ORDER>
NodoB<T, ORDER>* ArbolB<T, ORDER>::search(T k) {
    return (root == nullptr) ? nullptr : search(root, k);
}

template <typename T, int ORDER>
void ArbolB<T, ORDER>::remove(T k) {
    if (!root) {
        cout << "The tree is empty\n";
        return;
    }

    remove(root, k);

    if (root->n == 0) {
        NodoB<T, ORDER>* tmp = root;
        if (root->leaf)
            root = nullptr;
        else
            root = root->children[0];

        delete tmp;
    }
}

template <typename T, int ORDER>
void ArbolB<T, ORDER>::printRec(NodoB<T, ORDER>* nodo, const string& name, ofstream& file, int& printNodeCount) const {
    if (nodo) {
        // Create a label for the node with all its values
        string label = "";
        for (int i = 0; i < nodo->n; ++i) {
            label += nodo->keys[i].toString();
            if (i < nodo->n - 1) {
                label += "|";
            }
        }
        file << '"' << name << '"' << "[label=\"" << label << "\", shape=record];\n";

        // Recursively print all children
        for (int i = 0; i <= nodo->n; ++i) {
            if (nodo->children[i]) {
                string childName = "Nodo" + to_string(++printNodeCount);
                file << '"' << name << "\"->\"" << childName << "\";\n";
                printRec(nodo->children[i], childName, file, printNodeCount);
            }
        }
    }
}

template <typename T, int ORDER>
string ArbolB<T, ORDER>::renderGraphviz(const string& filename) const {
    string dotFilename = filename + ".dot";
    string pngFilename = filename + ".png";
    string dotCommand = "dot -Tpng " + dotFilename + " -o " + pngFilename;

    ofstream file(dotFilename);
    file << "digraph G {\n";
    file << "node [shape=record];\n"; // Use record shape for nodes
    if (root) {
        int printNodeCount = 0;
        printRec(root, "Nodo" + to_string(++printNodeCount), file, printNodeCount);
    }
    file << "}\n";
    file.close();

    int result = system(dotCommand.c_str());
    if (result != 0) {
        cerr << "Error generating image\n";
    } else {
        cout << "Image generated successfully\n";
    }
    return pngFilename;
}

template <typename T, int ORDER>
void ArbolB<T, ORDER>::traversal(NodoB<T, ORDER>* myNode, vector<T>& elementos) const {
    int i;
    if (myNode) {
        for (i = 0; i < myNode->n; i++) {
            traversal(myNode->children[i], elementos);
            elementos.push_back(myNode->keys[i]);
        }
        traversal(myNode->children[i], elementos);
    }
}

template <typename T, int ORDER>
vector<T> ArbolB<T, ORDER>::obtenerElementos() const {
    vector<T> elementos;
    traversal(root, elementos);
    return elementos;
}

#endif // ARBOLB_H
