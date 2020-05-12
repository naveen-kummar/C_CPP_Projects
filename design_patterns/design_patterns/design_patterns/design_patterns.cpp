// design_patterns.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "design_patterns.h"
#include "traverse_composite_structure_using_visitor.h"
#include "traverse_composite_structure_without_pattern.h"

int main()
{
    std::cout << "Hello World!\n";
    VisitorTraverseNodes();
   // NonVisitorTraverseNodes();

}


void NonVisitorTraverseNodes()
{
    Component_N* nodes[3];
    // The type of Composite* is "lost" when the object is assigned to a
    // Component*
    nodes[0] = new Composite_N(1);
    nodes[1] = new Composite_N(2);
    nodes[2] = new Composite_N(3);

    // If add() were in class Component, this would work
    //    nodes[0]->add( nodes[1] );
    // If it is NOT in Component, and only in Composite,  you get the error -
    //    no member function `Component::add(Component *)' defined

    // Instead of sacrificing safety, we use a Visitor to support add()

    nodes[0]->add(nodes[1]);
    nodes[0]->add(nodes[2]);
    nodes[0]->add( new Primitive_N(4));
    nodes[1]->add(new Primitive_N(5));
    nodes[1]->add( new Primitive_N(6));
    nodes[2]->add( new Primitive_N(7));

    for (int i = 0; i < 3; i++)
    {
        nodes[i]->traverse();
        cout << endl;
    }
  
    cout << endl;
}

void VisitorTraverseNodes()
{
    Component* nodes[3];
    // The type of Composite* is "lost" when the object is assigned to a
    // Component*
    nodes[0] = new Composite(1);
    nodes[1] = new Composite(2);
    nodes[2] = new Composite(3);

    // If add() were in class Component, this would work
    //    nodes[0]->add( nodes[1] );
    // If it is NOT in Component, and only in Composite,  you get the error -
    //    no member function `Component::add(Component *)' defined

    // Instead of sacrificing safety, we use a Visitor to support add()
    AddVisitor addVisitor;
    nodes[0]->accept(addVisitor, nodes[1]);
    nodes[0]->accept(addVisitor, nodes[2]);
    nodes[0]->accept(addVisitor, new Primitive(4));
    nodes[1]->accept(addVisitor, new Primitive(5));
    nodes[1]->accept(addVisitor, new Primitive(6));
    nodes[2]->accept(addVisitor, new Primitive(7));

    for (int i = 0; i < 3; i++)
    {
        nodes[i]->traverse();
        cout << endl;
    }
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
