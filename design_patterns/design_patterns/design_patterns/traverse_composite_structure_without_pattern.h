#ifndef TRAVERSE_COMPOSITE_STRUCTURE_WITHOUT_PATTERN
#define TRAVERSE_COMPOSITE_STRUCTURE_WITHOUT_PATTERN
#include <iostream>
#include <vector>
using namespace std;


class Component_N
{
    int value;
public:
    Component_N(int val)
    {
        value = val;
    }
    virtual void traverse()
    {
        cout << value << " ";
    }

    virtual void add(Component_N*) = 0;
};

class Primitive_N : public Component_N
{
public:
    Primitive_N(int val) : Component_N(val) {}
    /*virtual*/void add(Component_N* c)
    {
        //Dummy Implementation
    }
};

class Composite_N : public Component_N
{
    vector < Component_N* > children;
public:
    Composite_N(int val) : Component_N(val) {}
    void add(Component_N* ele)
    {
        children.push_back(ele);
    }

    /*virtual*/void traverse()
    {
        Component_N::traverse();
        for (int i = 0; i < children.size(); i++)
            children[i]->traverse();
    }
};



#endif
