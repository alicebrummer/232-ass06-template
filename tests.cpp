#ifndef UNITY_H
#define UNITY_H
#include "unity.h"
#endif

#include "code.hpp"
#include <iostream>

// ============================================================
// PART 2 Tests: DoublyLinkedList
// ============================================================

/// Create a DoublyLinkedList. Verify length() is 0 on a new list.
void test_new_list_is_empty(void)
{
    DoublyLinkedList list;
    TEST_ASSERT_TRUE_MESSAGE(list.length() == 0, "Doesn't equal 0");
}

/// Create a DoublyLinkedList. Call pushFrontValue and pushBackValue.
/// Verify length() is 2.
void test_push_increases_length(void)
{
    DoublyLinkedList list;
    list.pushFrontValue(2);
    list.pushBackValue(2);
    TEST_ASSERT_TRUE_MESSAGE(list.length() == 2, "Is not 2");
}

/// Create an EMPTY DoublyLinkedList.
/// Verify popFrontValue() and popBackValue() both have NO value (has_value() is false).
void test_pop_on_empty_list(void)
{
    DoublyLinkedList list;
    TEST_ASSERT_TRUE_MESSAGE(!list.popFrontValue().has_value(), "TODO: Implement this test");
    TEST_ASSERT_TRUE_MESSAGE(!list.popBackValue().has_value(), "TODO: Implement this test");
}

/// Push 1, 2, 3 with pushBackValue.
/// Verify popBackValue() gives 3, then popFrontValue() gives 1, then length() is 1.
void test_pop_order(void)
{
    DoublyLinkedList list;
    list.pushBackValue(1);
    list.pushBackValue(2);
    list.pushBackValue(3);
    std::optional<NodeValue> a = list.popBackValue();
    TEST_ASSERT_TRUE_MESSAGE(a.has_value(), "Doesn't contain value");

    TEST_ASSERT_TRUE_MESSAGE(std::get<int>(a.value()) == 3, "doesn't equal 3");

    std::optional<NodeValue> b = list.popFrontValue();
    TEST_ASSERT_TRUE_MESSAGE(b.has_value(), "Doesn't contain value");

    TEST_ASSERT_TRUE_MESSAGE(std::get<int>(b.value()) == 1, "doesn't equal 1");
    TEST_ASSERT_TRUE_MESSAGE(list.length() == 1, "length doesn't equal 1");
}

/// Push one value, then call deleteValue with a value that is NOT in the list.
/// Verify it returns false and length() does not change.
void test_delete_value_not_found(void)
{
    DoublyLinkedList list;
    list.pushBackValue(1);

    TEST_ASSERT_TRUE_MESSAGE(list.deleteValue(NodeValue{2}) == false, "Returns True");
    TEST_ASSERT_TRUE_MESSAGE(list.length() == 1, "Length Changed");
}

/// Push 1, 2, 3 with pushBackValue. Call deleteValue(2).
/// Verify popBackValue() gives 3 and the next popBackValue() gives 1.
/// (popBackValue follows prevPtr: this fails if you forgot to repair the backward link.)
void test_delete_middle_keeps_links(void)
{
    DoublyLinkedList list;
    list.pushBackValue(1);
    list.pushBackValue(2);
    list.pushBackValue(3);

    list.deleteValue(NodeValue{2});

    std::optional<NodeValue> a = list.popBackValue();
    TEST_ASSERT_TRUE_MESSAGE(a.has_value(), "Doesn't contain value");

    TEST_ASSERT_TRUE_MESSAGE(std::get<int>(a.value()) == 3, "doesn't equal 3");

    std::optional<NodeValue> b = list.popBackValue();
    TEST_ASSERT_TRUE_MESSAGE(b.has_value(), "Doesn't contain value");

    TEST_ASSERT_TRUE_MESSAGE(std::get<int>(b.value()) == 1, "doesn't equal 1");
}

// ============================================================
// PART 3 Tests: StdDoublyLinkedList
// ============================================================

/// Push 1, 2, 1 with pushBackValue. Call deleteValue(NodeValue{1}).
/// Verify length() is 2 and popFrontValue() gives 2 (only the FIRST 1 was removed).
void test_std_delete_only_first(void)
{
    DoublyLinkedList list;
    list.pushBackValue(1);
    list.pushBackValue(2);
    list.pushBackValue(3);

    list.deleteValue(NodeValue{1});
    TEST_ASSERT_TRUE_MESSAGE(list.length() == 2, "Is not 2");

    std::optional<NodeValue> b = list.popFrontValue();

    TEST_ASSERT_TRUE_MESSAGE(std::get<int>(b.value()) == 2, "doesn't equal 1");
}

/// Create an EMPTY StdDoublyLinkedList.
/// Verify popFrontValue() and popBackValue() have NO value and do not crash.
void test_std_pop_on_empty_list(void)
{
    StdDoublyLinkedList list;
    TEST_ASSERT_TRUE_MESSAGE(!list.popFrontValue().has_value(), "Contains a value");
    TEST_ASSERT_TRUE_MESSAGE(!list.popBackValue().has_value(), "Contains a value");
}
