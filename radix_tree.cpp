#include "radix_tree.h"


void RadixTree::append(NodePointer &node, const std::string &label)
{
    auto index = std::mismatch( node->m_Label.begin(), node->m_Label.end(), label.begin(), label.end() );

    if( index.first != node->m_Label.end())
    {
        std::string newStr;

        std::for_each( index.first, node->m_Label.end(), [&newStr]( auto element){ newStr.push_back(element); });

        node->m_Label.erase( index.first, node->m_Label.end() );

        auto& childrenNode = node->m_Children[newStr[0] - 'a'];

        if( childrenNode == nullptr )
        {
            auto tmpChildren = std::move(node->m_Children);

            addNode(childrenNode, newStr);

            childrenNode->m_Children = std::move(tmpChildren);

            node->m_IsEnd = false;
        }
        else
        {
            append(childrenNode, newStr);
        }
    }

    if( index.second != label.end() )
    {
        auto& childrenNode = node->m_Children[*index.second  - 'a'];

        std::string newStr;

        std::for_each( index.second, label.end(), [&newStr]( auto element){ newStr.push_back(element); });

        if( childrenNode == nullptr )
        {
            addNode(childrenNode, newStr);
        }
        else
        {
            append(childrenNode, newStr);
        }
    }
}

void RadixTree::addNode(NodePointer &node, const std::string &label)
{
    node = std::make_unique<Node>();

    node->m_Label = label;
    node->m_IsEnd = true;
}

void RadixTree::printTree(NodePointer &node, size_t level )
{
    for(size_t i = 0; i < level; ++i)
    {
        std::cout << "  ";
    }

    std::cout << node->m_Label;

    if( node->m_IsEnd )
    {
        std::cout << "$";
    }

    std::cout << std::endl;

    auto result = std::find_if(node->m_Children.begin(), node->m_Children.end(), [](const auto& element){return element != nullptr;});

    while( result != node->m_Children.end())
    {
        printTree(*result, level + 1);
        result = std::find_if(++result, node->m_Children.end(), [](const auto& element){return element != nullptr;});
    }
}

void RadixTree::printNicks(NodePointer &node, const std::string& firstPart)
{
    if( node->m_IsEnd )
    {
        std::cout << firstPart << node->m_Label << "    " << firstPart + node->m_Label[0] << std::endl;
    }

    auto result = std::find_if(node->m_Children.begin(), node->m_Children.end(), [](const auto& element){return element != nullptr;});

    while( result != node->m_Children.end())
    {
        printNicks(*result, firstPart + node->m_Label);
        result = std::find_if(++result, node->m_Children.end(), [](const auto& element){return element != nullptr;});
    }
}