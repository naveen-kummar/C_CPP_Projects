#ifndef TRAVERSE_COMPOSITE_STRUCTURE_USING_VISITOR
#define TRAVERSE_COMPOSITE_STRUCTURE_USING_VISITOR

#include <iostream>
#include <vector>
using namespace std;

class Visitor
{
public:
    virtual void visit(class Primitive*, class Component*) = 0;
    virtual void visit(class Composite*, Component*) = 0;
};

class Component
{
    int value;
public:
    Component(int val)
    {
        value = val;
    }
    virtual void traverse()
    {
        cout << value << " ";
    }
    // Having add() here sacrifices safety, but it supports transparency
    // virtual void add( Component* ) { }
    virtual void accept(Visitor&, Component*) = 0;
};

class Primitive : public Component
{
public:
    Primitive(int val) : Component(val) {}
    /*virtual*/void accept(Visitor& v, Component* c)
    {
        cout << "accept in - Primitive : does not make sense " << endl;
       // v.visit(this, c);
    }
};

class Composite : public Component
{
    vector < Component* > children;
public:
    Composite(int val) : Component(val) {}
    void add(Component* ele)
    {
        children.push_back(ele);
    }
    /*virtual*/void accept(Visitor& v, Component* c)
    {
        v.visit(this, c);
    }
    /*virtual*/void traverse()
    {
        Component::traverse();
        for (int i = 0; i < children.size(); i++)
            children[i]->traverse();
    }
};

class AddVisitor : public Visitor
{
public:
    /*virtual*/void visit(Primitive*, Component*)
    {
        /* does not make sense */
        cout <<"Visitinting - Primitive : does not make sense " << endl;
    }
    /*virtual*/void visit(Composite* node, Component* c)
    {
        cout << "Adding Composite " << endl;
        node->add(c);
    }

};

#endif
