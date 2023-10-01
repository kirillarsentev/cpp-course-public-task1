#include "list.h"


List::List()
{
    first = nullptr;
    last = nullptr;
}


bool
List::is_empty()
{
    if (first == nullptr && last == nullptr) {
        return true;
    }
    else {
        return false;
    }
}


void
List::clear()
{
    if (is_empty()) return;
    else {
        while (first)
            remove_front();
        first = nullptr;
        last = nullptr;
    }
}


void
List::push_front(int _val)
{
    if (is_empty()) {
        Node* p = new Node(_val);
        first = p;
        last = p;
    }
    else {
        Node* p = new Node(_val);
        p->next = first;
        first = p;
    }
}


void
List::push_back(int _val)
{
    if (is_empty()) {
        Node* p = new Node(_val);
        first = p;
        last = p;
    }
    else {
        Node* p = new Node(_val);
        last->next = p;
        last = p;
    }
}


Node*
List::find(int _val)
{
    if (is_empty()) return nullptr;
    else {
        Node* p = first;
        while (p) {
            if (p->val == _val) return p;
            p = p->next;
        }
        return nullptr;
    }
}


void
List::remove_front()
{
    if (is_empty()) return;
    first = first->next;
}


void
List::remove_back()
{
    if (is_empty()) return;
    else {
        Node* p = first;
        while (p) {
            if (p->next == last) {
                p->next = nullptr;
                last = p;
            }
            p = p->next;
        }
    }
}


bool
List::remove(const Node* _node)
{
    if (is_empty()) return false;
    else if (_node == first) {
        remove_front();
        return true;
    }
    else {
        Node* p = first;
        while (p) {
            if (p->next == _node) {
                p->next = _node->next;
                return true;
            }

            p = p->next;
        }
        return false;
    }
}