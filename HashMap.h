
#define TEMPLATE_HASH_MAP
#include <iostream>
#include <string>
#include <sstream>
#include <cstdlib>

using namespace std;

// размер hash map
const int HASH_SIZE = 350;

template <class Key, class Value>
class HashMap
{
public:
    /*  Конструктор инициализирует hash map */
    HashMap(int hashSze = HASH_SIZE);
    /*   Проверка на пустоту  */
    bool IsEmpty(int keyIndex);
    /*   Проверка на полноту  */
    bool  IsFull();
    /*   Генерирует и возвращает код элемента  */
    int Hash(Key m_key);
    /*   Добавление элемента m_value в таблицу  */
    void Insert(Key m_key, Value m_value);
    /*   Удаление элемента deleteItem в таблицу  */
    bool Remove(Key m_key, Value deleteItem);
    /*   Возвращает размер hash map     */
    int TableSize();
    /*   Возвращает общее количество элементов в hash map  */
    int TotalElems();
    /*   Возвращает количество элементов контейнера hash map  */
    int BucketSize(int keyIndex);
    /*   Возвращает количество раз searchItem появляется в Hash map      */
    int Count(Key m_key, Value searchItem);
    /*   Возвращает количество раз сколько повторяется ключ в Hash map  */
    int ContainsKey(Key m_key);
    /*   Проверяет Hash map на пустоту  */
    void MakeEmpty();
    /*   Удаляет Hash map  */
    ~HashMap();
    
    //  -- ITERATOR CLASS --
    class Iterator;
    /* Function: Class declaration to the iterator */
    
    Iterator begin(int keyIndex) { return(!IsEmpty(keyIndex)) ? head[keyIndex] : NULL; }
    /* Returns the beginning of the current hashmap key index */
    
    Iterator end(int keyIndex = 0) { return NULL; }
    /* Returns the end of the current hashmap key index */
    
private:
    struct KeyValue
    {
        Key key;
        Value value;
    };
    struct node
    {
        KeyValue currentItem;
        node* next;
    };
    node** head; // array of linked list
    int hashSize; // Размер хеш-таблицы
    int totElems; //  Количество элементов
    int* bucketSize; //  Количество элементов объединенных общим признаком
};

//=========================  Implementation  ================================//
/*Инициализация таблицы*/
template <class Key, class Value>
HashMap<Key, Value>::HashMap(int hashSze)
{
    hashSize = hashSze;
    head = new node*[hashSize];
    bucketSize = new int[hashSize];
    for (int x = 0; x < hashSize; ++x)
    {
        head[x] = NULL;
        bucketSize[x] = 0;
    }
    totElems = 0;
}

template <class Key, class Value>
bool HashMap<Key, Value>::IsEmpty(int keyIndex)
{
    if (keyIndex >= 0 && keyIndex < hashSize)
    {
        return head[keyIndex] == NULL;
    }
    return true;
}

template <class Key, class Value>
bool HashMap<Key, Value>::IsFull()
{
    try
    {
        node* location = new node;
        delete location;
        return false;
    }
    catch (bad_alloc&)
    {
        return true;
    }
}

template <class Key, class Value>
int HashMap<Key, Value>::Hash(Key m_key)
{
    long h = 19937;
    stringstream convert;
    
    // конвертруем параметр в строку используя "stringstream"
    // удобно использовать так как он подходит для любых типов данных
    convert << m_key;
    string temp = convert.str();
    
    for (unsigned x = 0; x < temp.length(); ++x)
    {
        h = (h << 6) ^ (h >> 26) ^ temp[x];
    }
    return abs(h % hashSize);
}

template <class Key, class Value>
void HashMap<Key, Value>::Insert(Key m_key, Value m_value)
{
    if (IsFull())
    {
        //cout<<"INSERT ERROR - HASH MAP FULL";
    }
    else
    {
        int keyIndex = Hash(m_key);
        node* newNode = new node;   // добавляем новый node
        newNode->currentItem.key = m_key;
        newNode->currentItem.value = m_value;
        newNode->next = NULL;
        
        if (IsEmpty(keyIndex))
        {
            head[keyIndex] = newNode;
        }
        else
        {
            node* temp = head[keyIndex];
            while (temp->next != NULL)
            {
                temp = temp->next;
            }
            temp->next = newNode;
        }
        ++bucketSize[keyIndex];
        ++totElems;
    }
}

template <class Key, class Value>
bool HashMap<Key, Value>::Remove(Key m_key, Value deleteItem)
{
    bool isFound = false;
    node* temp;
    int keyIndex = Hash(m_key);
    
    if (IsEmpty(keyIndex))
    {
        //cout<<"REMOVE ERROR - HASH MAP EMPTY";
    }
    else if (head[keyIndex]->currentItem.key == m_key
             && head[keyIndex]->currentItem.value == deleteItem)
    {
        temp = head[keyIndex];
        head[keyIndex] = head[keyIndex]->next;
        delete temp;
        --totElems;
        --bucketSize[keyIndex];
        isFound = true;
    }
    else
    {
        for (temp = head[keyIndex]; temp->next != NULL; temp = temp->next)
        {
            if (temp->next->currentItem.key == m_key
                && temp->next->currentItem.value == deleteItem)
            {
                node* deleteNode = temp->next;
                temp->next = temp->next->next;
                delete deleteNode;
                isFound = true;
                --totElems;
                --bucketSize[keyIndex];
                break;
            }
        }
    }
    return isFound;
}

template <class Key, class Value>
int HashMap<Key, Value>::TableSize()
{
    return hashSize;
}

template <class Key, class Value>
int HashMap<Key, Value>::TotalElems()
{
    return totElems;
}

template <class Key, class Value>
int HashMap<Key, Value>::BucketSize(int keyIndex)
{
    return(!IsEmpty(keyIndex)) ? bucketSize[keyIndex] : 0;
}

template <class Key, class Value>
int HashMap<Key, Value>::Count(Key m_key, Value searchItem)
{
    int keyIndex = Hash(m_key);
    int search = 0;
    
    if (IsEmpty(keyIndex))
    {
        //cout<<"COUNT ERROR - HASH MAP EMPTY";
    }
    else
    {
        for (node* temp = head[keyIndex]; temp != NULL; temp = temp->next)
        {
            if (temp->currentItem.key == m_key
                && temp->currentItem.value == searchItem)
            {
                ++search;
            }
        }
    }
    return search;
}

template <class Key, class Value>
int HashMap<Key, Value>::ContainsKey(Key m_key)
{
    int keyIndex = Hash(m_key);
    int search = 0;
    
    if (IsEmpty(keyIndex))
    {
        //cout<<"CONTAINS KEY ERROR - HASH MAP EMPTY";
    }
    else
    {
        for (node* temp = head[keyIndex]; temp != NULL; temp = temp->next)
        {
            if (temp->currentItem.key == m_key)
            {
                ++search;
            }
        }
    }
    return search;
}

template <class Key, class Value>
void HashMap<Key, Value>::MakeEmpty()
{
    totElems = 0;
    for (int x = 0; x < hashSize; ++x)
    {
        if (!IsEmpty(x))
        {
            while (!IsEmpty(x))
            {
                node* temp = head[x];
                head[x] = head[x]->next;
                delete temp;
            }
        }
        bucketSize[x] = 0;
    }
}

template <class Key, class Value>
HashMap<Key, Value>::~HashMap()
{
    MakeEmpty();
    delete[] head;
    delete[] bucketSize;
}

//   END OF THE HASH MAP CLASS
// -----------------------------------------------------------
//   HASH MAP ITERATOR CLASS

template <class Key, class Value>
class HashMap<Key, Value>::Iterator :
public iterator<forward_iterator_tag, Value>,
public HashMap<Key, Value>
{
public:
    // Iterator constructor
    Iterator(node* otherIter = NULL)
    {
        itHead = otherIter;
    }
    ~Iterator() {}
    Iterator& operator=(const Iterator& other)
    {
        itHead = other.itHead;
        return(*this);
    }
    bool operator==(const Iterator& other)const
    {
        return itHead == other.itHead;
    }
    bool operator!=(const Iterator& other)const
    {
        return itHead != other.itHead;
    }
    bool operator<(const Iterator& other)const
    {
        return itHead < other.itHead;
    }
    bool operator>(const Iterator& other)const
    {
        return other.itHead < itHead;
    }
    bool operator<=(const Iterator& other)const
    {
        return (!(other.itHead < itHead));
    }
    bool operator>=(const Iterator& other)const
    {
        return (!(itHead < other.itHead));
    }
    // Обновляем положение чтобы ссылаться на следующий элемент в HashMap.
    Iterator operator+(int incr)
    {
        node* temp = itHead;
        for (int x = 0; x < incr && temp != NULL; ++x)
        {
            temp = temp->next;
        }
        return temp;
    }
    Iterator operator+=(int incr)
    {
        for (int x = 0; x < incr && itHead != NULL; ++x)
        {
            itHead = itHead->next;
        }
        return itHead;
    }
    Iterator& operator++() // pre increment
    {
        if (itHead != NULL)
        {
            itHead = itHead->next;
        }
        return(*this);
    }
    Iterator operator++(int) // post increment
    {
        node* temp = itHead;
        this->operator++();
        return temp;
    }
    KeyValue& operator[](int incr)
    {
        // предостеречь программу от вылета
        if (itHead == NULL || (*this + incr) == NULL)
        {
            return junk;
        }
        return(*(*this + incr));
    }
    
    KeyValue& operator*()
    {
        // предостеречь программу от вылета
        if (itHead == NULL)
        {
            return junk;
        }
        return itHead->currentItem;
    }
    KeyValue* operator->()
    {
        return(&**this);
    }
private:
    node* itHead;
    KeyValue junk;
};

