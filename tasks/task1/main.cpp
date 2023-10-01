#include "list.h"

#include "iostream"

int main()
{
    List l;
    std::cout << l.is_empty() << std::endl;
    l.push_back(4);
    l.push_back(123);
    l.push_front(89);
    l.print();
    std::cout << l.is_empty() << std::endl;
    const Node* to_del = l.find(123);
    l.remove(to_del);
    l.print();
    l.clear();
    l.push_back(1234);
    //l.remove_front();
    l.print();
    std::cout << l[0]->val << std::endl;
    l.remove_back();
    return 0;
}