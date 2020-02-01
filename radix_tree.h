#pragma once


#include <algorithm>
#include <iostream>
#include <memory>
#include <string>


class RadixTree
{
private:
    struct Node;

    using NodeType = Node;
    using NodePointer = std::unique_ptr<NodeType>;

    struct Node
    {
        std::string m_Label;
        bool m_IsEnd = false;
        std::array<NodePointer, 26> m_Children;
    };

    NodePointer m_Root = std::make_unique<NodeType>();

public:
    RadixTree() = default;
    ~RadixTree() = default;

    void append(const std::string &label)
    {
        append(m_Root, label);
    }

    void printTree()
    {
        printTree(m_Root, 0);
    }

    void printNicks()
    {
        printNicks(m_Root, "");
    }

private:
    void append(NodePointer &node, const std::string &label);
    void addNode(NodePointer &node, const std::string &label);
    void printTree(NodePointer &node, size_t level );
    void printNicks(NodePointer &node, const std::string& firstPart);
};