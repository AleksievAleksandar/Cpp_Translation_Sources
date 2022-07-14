﻿#include <iostream>
#include <string>

typedef std::string data;
typedef int keyType;

struct tree
{
    keyType key;
    data info;

    tree* left;
    tree* right;
};

/* Търсене в двоично дърво */
tree* search(keyType key, tree* T)
{
    if (nullptr == T)
    {
        return nullptr;
    }
    else if (key < T->key)
    {
        return search(key, T->left);
    }
    else if (key > T->key)
    {
        return search(key, T->right);
    }
    else
    {
        return T;
    }
}

/* Включване в двоично дърво */
void insertKey(keyType key, data x, tree*& T)
{
    if (nullptr == T)
    {
        T = new tree();
        T->key = key;
        T->info = x;
        T->left = nullptr;
        T->right = nullptr;
    }
    else if (key < T->key)
    {
        insertKey(key, x, T->left);
    }
    else if (key > T->key)
    {
        insertKey(key, x, T->right);
    }
    else
    {
        std::cerr << "Елементът е вече в дървото!" << std::endl;
    }
}

/* Изключване от двоично дърво Ј */

/* Намиране на минималния елемент в дърво */
tree* findMin(tree* T)
{
    while (nullptr != T->left)
    {
        T = T->left;
    }
    return T;
}

void deleteKey(keyType key, struct tree*& T)
{
    if (nullptr == T)
    {
        std::cout << "върхът, който трябва да се изключи, липсва!" << std::endl;
    }
    else
    {
        if (key < T->key)
        {
            deleteKey(key, T->left);
        }
        else if (key > T->key)
        {
            deleteKey(key, T->right);
        }
        else  /* елемента за изключване е намерен */
        {
            if (T->left && T->right) {       /* елементът има и ляво и дясно поддърво */
              /* намира се върхът за размяна */
                tree* replace = findMin(T->right);
                T->key = replace->key;
                T->info = replace->info;
                deleteKey(T->key, T->right);    /* върхът се изключва */
            }
            else /* елементът има нула или едно поддървета */
            {
                tree* temp = T;
                if (T->left)
                {
                    T = T->left;
                }
                else
                {
                    T = T->right;
                }
                delete temp;
            }
        }
    }
}

void printTree(tree* T)
{
    if (nullptr == T)
    {
        return;
    }

    std::cout << T->key << " ";

    printTree(T->left);
    printTree(T->right);
}

int main()
{
    tree* T = nullptr;
    tree* result = nullptr;

    /* включва 10 върха с произволни ключове */
    for (size_t i = 0; i < 10; i++)
    {
        int ikey = (rand() % 20) + 1;
        std::cout << "Вмъква се елемент с ключ " << ikey << std::endl;
        insertKey(ikey, "someinfo", T);
    }

    std::cout << "Дърво: ";
    printTree(T);
    std::cout << std::endl;

    /* претърсва за елемента с ключ 5 */
    result = search(5, T);
    std::cout << "намерен е: " << result->info << std::endl;

    /* изтрива произволни 10 върха от дървото */
    for (size_t i = 0; i < 10; i++)
    {
        int ikey = (rand() % 20) + 1;
        std::cout << "Изтрива се елемент с ключ " << ikey << std::endl;
        deleteKey(ikey, T);
    }

    std::cout << "Дърво: ";
    printTree(T);
    std::cout << std::endl;

    return 0;
}