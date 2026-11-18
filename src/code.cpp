// ============================================================
// CSCI 232 Assignment 06 – Doubly Linked List vs. std::list
// Student Implementation
// ============================================================

#include "code.hpp"
#include <algorithm>
#include <iostream>

// Uncomment the author block below and fill in your name:

std::string AUTHOR_NAME       = "Alice Brummer";
std::string AUTHOR_AUTHORSHIP = "I acknowledge that I have worked on this "
"assignment independently, except where explicitly noted and referenced. "
"Any collaboration or use of external resources has been properly cited. "
"I am fully aware of the consequences of academic dishonesty and agree "
"to abide by the university's academic integrity policy.";

// ============================================================
// PART 1: Class DoubleNode
// ============================================================

/// Constructor: initialize ALL THREE fields with a member initializer list.
/// value <- newValue, prevPtr <- nullptr, nextPtr <- nullptr.
DoubleNode::DoubleNode(NodeValue newValue)
{
    value = newValue;
    prevPtr = nullptr;
    nextPtr = nullptr;
    // TODO: move the initialization of all three fields into an initializer list
}

/// Const getter: return the stored value.
NodeValue DoubleNode::getValue() const
{
    return value;
    // TODO: return the value field
    return NodeValue{};
}

/// Const getter: return the previous node (or nullptr).
DoubleNode *DoubleNode::getPrev() const
{
    return prevPtr;
    // TODO: return the prevPtr field
}

/// Const getter: return the next node (or nullptr).
DoubleNode *DoubleNode::getNext() const
{
    return nextPtr;
    // TODO: return the nextPtr field
    return nullptr;
}

/// Setter: store newPrevPtr in prevPtr.
void DoubleNode::setPrev(DoubleNode *newPrevPtr)
{
    prevPtr = newPrevPtr;
    // TODO: assign the field
}

/// Setter: store newNextPtr in nextPtr.
void DoubleNode::setNext(DoubleNode *newNextPtr)
{
    nextPtr = newNextPtr;
    // TODO: assign the field
}

// ============================================================
// PART 2: Class DoublyLinkedList
// ============================================================

/// Empty list: headPtr = nullptr, tailPtr = nullptr, count = 0.
DoublyLinkedList::DoublyLinkedList()
{
    headPtr = nullptr;
    tailPtr = nullptr;
    count = 0;
    // TODO: initialize all three fields (use an initializer list)
}

/// RAII: delete ALL nodes. Save the next pointer BEFORE delete.
DoublyLinkedList::~DoublyLinkedList()
{
    while (headPtr != nullptr) 
    {
        DoubleNode *temp = headPtr;
        headPtr = headPtr->getNext();
        delete temp;
    }
    // TODO: walk through the list and delete every node
}

/// Unlink the first node and RETURN it (do not delete it).
/// Fix headPtr, tailPtr, count. Clear the node's own prevPtr and nextPtr.
/// Return nullptr if the list is empty.
DoubleNode *DoublyLinkedList::detachFirst()
{
    if (headPtr == nullptr) 
    {
        return nullptr;
    }
    
    DoubleNode *temp = headPtr;
    headPtr = headPtr->getNext();
    if (headPtr != nullptr) 
    {
        headPtr->setPrev(nullptr);
    }
    else
    {
        tailPtr = nullptr;
    }
    temp->setNext(nullptr);
    count--;
    return temp;
    
    // TODO: implement
}

/// Unlink the last node and RETURN it (do not delete it).
/// Use the tail's prev link. Return nullptr if the list is empty.
DoubleNode *DoublyLinkedList::detachLast()
{
    if (tailPtr == nullptr)
    {
        return nullptr;
    }
    DoubleNode *temp = tailPtr;
    tailPtr = tailPtr->getPrev();
    temp->setPrev(nullptr);
    if(tailPtr != nullptr)
    {
        tailPtr->setNext(nullptr);
    }
    else
    {
        headPtr = nullptr;
    }
    count--;

    return temp;
    // TODO: implement
}

/// Find the FIRST node equal to value and unlink it (head, tail, only node
/// or middle node). Return nullptr if not found. Reuse detachFirst/detachLast.
DoubleNode *DoublyLinkedList::detachValue(NodeValue value)
{
    DoubleNode *current = headPtr;
    while (current != nullptr)
    {
        if (current->getValue() == value)
        {
            if (current == headPtr)
            {
                return detachFirst();
            }
            else if (current == tailPtr)
            {
                return detachLast();
            }
            else
            {
                DoubleNode *prevNode = current->getPrev();
                DoubleNode *nextNode = current->getNext();
                prevNode->setNext(nextNode);
                nextNode->setPrev(prevNode);
                current->setPrev(nullptr);
                current->setNext(nullptr);
                count--;
                return current;
            }
        }
        current = current->getNext();
    }   
    // TODO: implement
    return nullptr;
}

/// Create a node with new and link it in front. Handle the empty list.
void DoublyLinkedList::pushFrontValue(NodeValue value)
{
    DoubleNode *newNode = new DoubleNode(value);
    if (headPtr == nullptr)
    {
        headPtr = tailPtr = newNode;
    }
    else
    {
        headPtr->setPrev(newNode);
        newNode->setNext(headPtr);
        headPtr = newNode;
    }
    count += 1;
    // TODO: implement
}

/// Create a node with new and link it at the end. Handle the empty list.
void DoublyLinkedList::pushBackValue(NodeValue value)
{
    DoubleNode *newNode = new DoubleNode(value);
    if (tailPtr == nullptr)
    {
        headPtr = tailPtr = newNode;
    }
    else
    {
        tailPtr->setNext(newNode);
        newNode->setPrev(tailPtr);
        tailPtr = newNode;
    }
    count += 1;
    // TODO: implement
}

/// Detach the first node, read its value, delete the node, return the value.
/// Empty list -> std::nullopt.
std::optional<NodeValue> DoublyLinkedList::popFrontValue()
{
    DoubleNode *node = detachFirst();
    if (node != nullptr)
    {
        NodeValue value = node->getValue();
        delete node;
        return std::optional<NodeValue>(value);
    }
    // TODO: implement
    return std::nullopt;
}

/// Detach the last node, read its value, delete the node, return the value.
/// Empty list -> std::nullopt.
std::optional<NodeValue> DoublyLinkedList::popBackValue()
{
    if (tailPtr == NULL)
    {
       return std::nullopt;
    };

    DoubleNode *node = detachLast();
    if (node != nullptr)
    {   
        NodeValue value = node->getValue();
        delete node;
        return std::optional<NodeValue>(value);
    }
    // TODO: implement
    return std::nullopt;
}

/// Remove the FIRST node equal to value and free it.
/// Return true if something was removed.
bool DoublyLinkedList::deleteValue(NodeValue value)
{
    DoubleNode *node = detachValue(value);
    if (node != nullptr)
    {
        delete node;
        return true;
    }
    // TODO: implement
    return false;
}

/// Return true if any node holds value.
bool DoublyLinkedList::containsValue(NodeValue value) const
{
    // TODO: implement
    DoubleNode *current = headPtr;
    while (current != nullptr)
    {
        if (current->getValue() == value)
        {
            return true;
        }
        current = current->getNext();
    }
    return false;
}

/// Print values head -> tail with std::visit (each followed by a space,
/// then a newline). Return the number of printed values.
int DoublyLinkedList::printForward() const
{
    DoubleNode *current = headPtr;
    int count = 0;
    while (current != nullptr)
    {
        std::visit([](const auto& val) { std::cout << val << " "; }, current->getValue());
        count++;
        current = current->getNext();
    }
    std::cout << std::endl;
    // TODO: implement
    return count;
}

/// Print values tail -> head using prevPtr. Return the number of printed values.
int DoublyLinkedList::printBackward() const
{
    DoubleNode *current = tailPtr;
    int count = 0;
    while (current != nullptr)
    {
        std::visit([](const auto& val) { std::cout << val << " "; }, current->getValue());
        count++;
        current = current->getPrev();
    }
    std::cout << std::endl;
    // TODO: implement
    return count;
}

/// Return count.
int DoublyLinkedList::length() const
{
    // TODO: implement
    return count;
}

// ===== BEGIN PART 3 (do not remove this marker) =====
// ============================================================
// PART 3: Class StdDoublyLinkedList
// ============================================================
// Only std::list methods, <algorithm>, iterators and std::visit.
// A loop is allowed ONLY for printing.

/// Which std::list method inserts at the front?
void StdDoublyLinkedList::pushFrontValue(NodeValue value)
{
    data.push_front(value);

    // TODO: implement
}

/// Which std::list method inserts at the back?
void StdDoublyLinkedList::pushBackValue(NodeValue value)
{
    data.push_back(value);
    // TODO: implement
}

/// Read the front element, remove it, return it. Empty -> std::nullopt.
std::optional<NodeValue> StdDoublyLinkedList::popFrontValue()
{
    if(data.empty())
    {
        return std::nullopt;
    }
    NodeValue value = data.front();
    data.pop_front();
    return value;
    // TODO: implement
}

/// Read the back element, remove it, return it. Empty -> std::nullopt.
std::optional<NodeValue> StdDoublyLinkedList::popBackValue()
{
    if(data.empty())
    {
        return std::nullopt;
    }
    NodeValue value = data.back();
    data.pop_back();
    return value;
    // TODO: implement
    return std::nullopt;
}

/// Remove only the FIRST element equal to value. Return true if removed.
bool StdDoublyLinkedList::deleteValue(NodeValue value)
{
    if (containsValue(value))
    {
        data.remove(value);
        return true;
    }
    return false;
    // TODO: implement
}

/// Search without writing your own loop.
bool StdDoublyLinkedList::containsValue(NodeValue value) const
{
    return std::find(data.begin(), data.end(), value) != data.end();
    // TODO: implement
}

/// Print head -> tail (same format as Part 2). Return the number of values.
int StdDoublyLinkedList::printForward() const
{
    int count = 0;
    for (auto i = data.begin(); i != data.end(); i++)
    {
        std::visit([](const auto& val) { std::cout << val << " "; }, *i);
        count++;
    }
    // TODO: implement
    return count;
}

/// Print tail -> head (same format as Part 2). Return the number of values.
int StdDoublyLinkedList::printBackward() const
{
    int count = 0;
    for (auto i = data.rbegin(); i != data.rend(); ++i)
    {
        std::visit([](const auto& val) { std::cout << val << " "; }, *i);
        count++;
    }
    
    // TODO: implement
    return count;
        // TODO: implement
}

/// size() returns size_t, length() returns int.
int StdDoublyLinkedList::length() const
{
    return data.size();
}
// ===== END PART 3 (do not remove this marker) =====
