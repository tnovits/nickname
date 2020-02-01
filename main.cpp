#include <iostream>
#include "radix_tree.h"

int
main()
{
    auto tree = std::make_unique<RadixTree>();
    std::string nick;

//    tree->append("aleksey");
//    tree->append("sasha");
//    tree->append("aleks");
//    tree->append("alek");
//    tree->append("alesha");
//    tree->append("maksim");

    while( std::getline(std::cin, nick) )
    {
        tree->append(nick);
    }

    tree->printNicks();

    std::cout << std::endl;

    tree->printTree();

    return 0;
}