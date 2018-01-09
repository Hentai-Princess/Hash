#include <iostream>
#include <string>
#include "HashMap.h"
using namespace std;

// iterator declaration
typedef HashMap<string, int>::Iterator iterDec;

int main()
{

    // declare variables
    HashMap<string, int> hashMap;
    
    // Добавление элементов в таблицу
    hashMap.Insert("BIOL", 585);
    hashMap.Insert("BIOL", 386);
    hashMap.Insert("ART", 101);
    hashMap.Insert("BIOL", 462);
    hashMap.Insert("HIST", 251);
    hashMap.Insert("BIOL", 301);
    hashMap.Insert("MATH", 270);
    hashMap.Insert("PE", 145);
    hashMap.Insert("BIOL", 134);
    hashMap.Insert("GEOL", 201);
    hashMap.Insert("CS", 465);
    hashMap.Insert("BIOL", 240);
    hashMap.Insert("GEOL", 101);
    hashMap.Insert("MATH", 150);
    hashMap.Insert("DANCE", 134);
    hashMap.Insert("BIOL", 131);
    hashMap.Insert("ART", 345);
    hashMap.Insert("CHEM", 185);
    hashMap.Insert("PE", 125);
    hashMap.Insert("BIOL", 120);
    string my="BIOL";
    // Количество my
    cout << "Значение "+my+" появляется в таблице " <<
    hashMap.ContainsKey(my) << " раз(а)" << endl;
    
    // Поиск
    iterDec it = hashMap.begin(hashMap.Hash(my));
    
    // Показывает 1-ое значение
    cout << "1-ый элемент со значением "+my+": "
    << it[0].value << endl;
    cout << "Все элементы со значением "+my+":"<< endl;
    for (int x = 0; x < hashMap.BucketSize(hashMap.Hash(my)); ++x)
    {
        if (it[x].key == my)
        {
            cout << "  Key-> " << it[x].key << "  Value-> " << it[x].value << endl;
        }
    }
    
    // Удаляет первый my
    cout << "Удаляем элемент  с " << it[0].value << " и " << it[0].key << endl;
        hashMap.Remove(my, it[0].value);
    
    if (hashMap.BucketSize(hashMap.Hash(my))!= 0) {
    // Количество my
    cout << "Теперь значение "+my+" повторяется " <<
        hashMap.ContainsKey(my) << " раз(а)"<< endl;
        
    }
    
    // Обновляем итератор до новой позиции
    it = hashMap.begin(hashMap.Hash(my));
    
    // Показывает все элементы в таблице
    cout << "Все элементы входящие в таблицу: "<< endl;
    for (int x = 0; x < hashMap.TableSize(); ++x)
    {
        if (!hashMap.IsEmpty(x))
        {
            for (iterDec iter = hashMap.begin(x); iter != hashMap.end(x); ++iter)
            {
                cout << "  Key-> " << (*iter).key << "  Value-> " << iter->value << endl;
            }
            cout << endl;
        }
    }
    
    // Количество элементов
    cout << "Количество элементов: " <<
    hashMap.TotalElems() << endl;
    getchar();
    return 0;
}
