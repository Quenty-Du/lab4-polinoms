#include "../include/List.h"

#include <gtest.h>



// ========== Конструкторы ==========

TEST(List, can_create_empty_list) {
    ASSERT_NO_THROW(List<int> l);
}

TEST(List, created_list_is_empty) {
    List<int> l;
    EXPECT_TRUE(l.empty());
    EXPECT_EQ(l.size(), 0);
}

// ========== push_front / push_back ==========

TEST(List, can_push_front) {
    List<int> l;
    l.push_front(5);
    EXPECT_FALSE(l.empty());
    EXPECT_EQ(l.size(), 1);
    EXPECT_EQ(l.front(), 5);
}

TEST(List, can_push_back) {
    List<int> l;
    l.push_back(5);
    EXPECT_FALSE(l.empty());
    EXPECT_EQ(l.size(), 1);
    EXPECT_EQ(l.back(), 5);
}

TEST(List, push_front_adds_element_to_beginning) {
    List<int> l;
    l.push_front(10);
    l.push_front(20);
    EXPECT_EQ(l.front(), 20);
    EXPECT_EQ(l.back(), 10);
    EXPECT_EQ(l.size(), 2);
}

TEST(List, push_back_adds_element_to_end) {
    List<int> l;
    l.push_back(10);
    l.push_back(20);
    EXPECT_EQ(l.front(), 10);
    EXPECT_EQ(l.back(), 20);
    EXPECT_EQ(l.size(), 2);
}

// ========== pop_front / pop_back ==========

TEST(List, can_pop_front) {
    List<int> l;
    l.push_back(10);
    l.push_back(20);
    l.pop_front();
    EXPECT_EQ(l.front(), 20);
    EXPECT_EQ(l.size(), 1);
}

TEST(List, can_pop_back) {
    List<int> l;
    l.push_back(10);
    l.push_back(20);
    l.pop_back();
    EXPECT_EQ(l.back(), 10);
    EXPECT_EQ(l.size(), 1);
}

TEST(List, pop_front_on_empty_list_does_nothing) {
    List<int> l;
    ASSERT_NO_THROW(l.pop_front());
    EXPECT_TRUE(l.empty());
}

TEST(List, pop_back_on_empty_list_does_nothing) {
    List<int> l;
    ASSERT_NO_THROW(l.pop_back());
    EXPECT_TRUE(l.empty());
}

// ========== front / back ==========

TEST(List, front_returns_first_element) {
    List<int> l;
    l.push_back(1);
    l.push_back(2);
    l.push_back(3);
    EXPECT_EQ(l.front(), 1);
}

TEST(List, back_returns_last_element) {
    List<int> l;
    l.push_back(1);
    l.push_back(2);
    l.push_back(3);
    EXPECT_EQ(l.back(), 3);
}

TEST(List, front_throws_when_list_empty) {
    List<int> l;
    ASSERT_ANY_THROW(l.front());
}

TEST(List, back_throws_when_list_empty) {
    List<int> l;
    ASSERT_ANY_THROW(l.back());
}

TEST(List, const_front_works_on_const_list) {
    List<int> l;
    l.push_back(42);
    const List<int>& cl = l;
    EXPECT_EQ(cl.front(), 42);
}

TEST(List, const_back_works_on_const_list) {
    List<int> l;
    l.push_back(42);
    const List<int>& cl = l;
    EXPECT_EQ(cl.back(), 42);
}

// ========== clear ==========

TEST(List, clear_removes_all_elements) {
    List<int> l;
    l.push_back(1);
    l.push_back(2);
    l.push_back(3);
    l.clear();
    EXPECT_TRUE(l.empty());
    EXPECT_EQ(l.size(), 0);
}

TEST(List, clear_on_empty_list_does_nothing) {
    List<int> l;
    ASSERT_NO_THROW(l.clear());
    EXPECT_TRUE(l.empty());
}

// ========== find ==========

TEST(List, find_returns_iterator_to_element) {
    List<int> l;
    l.push_back(10);
    l.push_back(20);
    l.push_back(30);
    auto it = l.find(20);
    EXPECT_NE(it, l.end());
    EXPECT_EQ(*it, 20);
}

TEST(List, find_returns_end_when_element_not_found) {
    List<int> l;
    l.push_back(10);
    l.push_back(20);
    auto it = l.find(99);
    EXPECT_EQ(it, l.end());
}

TEST(List, find_on_empty_list_returns_end) {
    List<int> l;
    auto it = l.find(5);
    EXPECT_EQ(it, l.end());
}

// ========== insert ==========

TEST(List, insert_at_beginning) {
    List<int> l;
    l.push_back(20);
    l.push_back(30);
    auto it = l.insert(l.begin(), 10);
    EXPECT_EQ(*it, 10);
    EXPECT_EQ(l.front(), 10);
    EXPECT_EQ(l.size(), 3);
}

TEST(List, insert_at_end) {
    List<int> l;
    l.push_back(10);
    l.push_back(20);
    auto it = l.insert(l.end(), 30);
    EXPECT_EQ(*it, 30);
    EXPECT_EQ(l.back(), 30);
    EXPECT_EQ(l.size(), 3);
}

TEST(List, insert_in_middle) {
    List<int> l;
    l.push_back(10);
    l.push_back(30);
    auto it = l.begin();
    ++it;
    auto newIt = l.insert(it, 20);
    EXPECT_EQ(*newIt, 20);
    EXPECT_EQ(l.size(), 3);
    
    auto check = l.begin();
    EXPECT_EQ(*check, 10);
    ++check;
    EXPECT_EQ(*check, 20);
    ++check;
    EXPECT_EQ(*check, 30);
}

TEST(List, insert_returns_iterator_to_new_element) {
    List<int> l;
    l.push_back(1);
    l.push_back(3);
    auto it = l.insert(++l.begin(), 2);
    EXPECT_EQ(*it, 2);
}

// ========== erase ==========

TEST(List, erase_at_beginning) {
    List<int> l;
    l.push_back(10);
    l.push_back(20);
    l.push_back(30);
    auto it = l.erase(l.begin());
    EXPECT_EQ(*it, 20);
    EXPECT_EQ(l.front(), 20);
    EXPECT_EQ(l.size(), 2);
}

TEST(List, erase_at_end) {
    List<int> l;
    l.push_back(10);
    l.push_back(20);
    l.push_back(30);
    auto it = l.erase(--l.end());
    EXPECT_EQ(it, l.end());
    EXPECT_EQ(l.back(), 20);
    EXPECT_EQ(l.size(), 2);
}

TEST(List, erase_in_middle) {
    List<int> l;
    l.push_back(10);
    l.push_back(20);
    l.push_back(30);
    auto it = l.begin();
    ++it;
    auto nextIt = l.erase(it);
    EXPECT_EQ(*nextIt, 30);
    EXPECT_EQ(l.size(), 2);
    
    auto check = l.begin();
    EXPECT_EQ(*check, 10);
    ++check;
    EXPECT_EQ(*check, 30);
}

TEST(List, erase_returns_iterator_to_next_element) {
    List<int> l;
    l.push_back(1);
    l.push_back(2);
    l.push_back(3);
    auto it = l.erase(++l.begin());
    EXPECT_EQ(*it, 3);
}

TEST(List, erase_on_empty_list_does_nothing) {
    List<int> l;
    ASSERT_NO_THROW(l.erase(l.end()));
}

// ========== Итераторы ==========

TEST(List, begin_returns_iterator_to_first_element) {
    List<int> l;
    l.push_back(10);
    l.push_back(20);
    auto it = l.begin();
    EXPECT_EQ(*it, 10);
}

TEST(List, end_returns_iterator_past_last_element) {
    List<int> l;
    l.push_back(10);
    auto it = l.end();
    --it;
    EXPECT_EQ(*it, 10);
}

TEST(List, const_iterators_work_on_const_list) {
    List<int> l;
    l.push_back(5);
    l.push_back(10);
    const List<int>& cl = l;
    auto it = cl.begin();
    EXPECT_EQ(*it, 5);
    ++it;
    EXPECT_EQ(*it, 10);
}

TEST(List, iterator_can_modify_value) {
    List<int> l;
    l.push_back(10);
    auto it = l.begin();
    *it = 20;
    EXPECT_EQ(l.front(), 20);
}

TEST(List, iterator_arrow_operator_works) {
    struct TestStruct {
        int value;
    };
    List<TestStruct> l;
    l.push_back({42});
    auto it = l.begin();
    EXPECT_EQ(it->value, 42);
}

// ========== Копирование и присваивание ==========

TEST(List, copy_constructor_creates_deep_copy) {
    List<int> l;
    l.push_back(1);
    l.push_back(2);
    l.push_back(3);
    
    List<int> l2(l);
    EXPECT_EQ(l2.size(), l.size());
    
    auto it1 = l.begin();
    auto it2 = l2.begin();
    while (it1 != l.end() && it2 != l2.end()) {
        EXPECT_EQ(*it1, *it2);
        ++it1;
        ++it2;
    }
    
    l2.push_back(4);
    EXPECT_EQ(l.size(), 3);
    EXPECT_EQ(l2.size(), 4);
}

TEST(List, assignment_operator_creates_deep_copy) {
    List<int> l;
    l.push_back(1);
    l.push_back(2);
    
    List<int> l2;
    l2 = l;
    EXPECT_EQ(l2.size(), l.size());
    
    l2.push_back(3);
    EXPECT_EQ(l.size(), 2);
    EXPECT_EQ(l2.size(), 3);
}

TEST(List, self_assignment_does_nothing) {
    List<int> l;
    l.push_back(1);
    l.push_back(2);
    
    l = l;
    EXPECT_EQ(l.size(), 2);
    EXPECT_EQ(l.front(), 1);
    EXPECT_EQ(l.back(), 2);
}

// ========== Деструктор ==========

TEST(List, destructor_frees_memory) {
    List<int>* l = new List<int>();
    l->push_back(1);
    l->push_back(2);
    l->push_back(3);
    ASSERT_NO_THROW(delete l);
}

// ========== Операции с несколькими элементами ==========

TEST(List, works_with_many_elements) {
    List<int> l;
    for (int i = 0; i < 100; ++i) {
        l.push_back(i);
    }
    EXPECT_EQ(l.size(), 100);
    for (int i = 0; i < 100; ++i) {
        EXPECT_EQ(l.front(), i);
        l.pop_front();
    }
    EXPECT_TRUE(l.empty());
}