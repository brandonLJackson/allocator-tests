// -------------------------------------
// projects/allocator/TestAllocator1.c++
// Copyright (C) 2015
// Brandon Jackson
// -------------------------------------

// --------
// includes
// --------

#include <algorithm> // count
#include <memory>    // allocator

#include "gtest/gtest.h"

#include "Allocator.h"

// --------------
// TestAllocator1
// --------------

template <typename A>
struct TestAllocator1 : testing::Test {
    // --------
    // typedefs
    // --------

    typedef          A             allocator_type;
    typedef typename A::value_type value_type;
    typedef typename A::size_type  size_type;
    typedef typename A::pointer    pointer;};

typedef testing::Types<
            std::allocator<int>,
            std::allocator<double>,
            my_allocator<int,    100>,
            my_allocator<double, 100>>
        my_types_1;

TYPED_TEST_CASE(TestAllocator1, my_types_1);

TYPED_TEST(TestAllocator1, test_1) {
    typedef typename TestFixture::allocator_type allocator_type;
    typedef typename TestFixture::value_type     value_type;
    typedef typename TestFixture::size_type      size_type;
    typedef typename TestFixture::pointer        pointer;

          allocator_type x;
    const size_type      s = 1;
    const value_type     v = 2;
    const pointer        p = x.allocate(s);
    if (p != nullptr) {
        x.construct(p, v);
        ASSERT_EQ(v, *p);
        x.destroy(p);
        x.deallocate(p, s);}}

TYPED_TEST(TestAllocator1, test_10) {
    typedef typename TestFixture::allocator_type allocator_type;
    typedef typename TestFixture::value_type     value_type;
    typedef typename TestFixture::size_type      size_type;
    typedef typename TestFixture::pointer        pointer;

          allocator_type  x;
    const size_type       s = 10;
    const value_type      v = 2;
    const pointer         b = x.allocate(s);
    if (b != nullptr) {
        pointer e = b + s;
        pointer p = b;
        try {
            while (p != e) {
                x.construct(p, v);
                ++p;}}
        catch (...) {
            while (b != p) {
                --p;
                x.destroy(p);}
            x.deallocate(b, s);
            throw;}
        ASSERT_EQ(s, std::count(b, e, v));
        while (b != e) {
            --e;
            x.destroy(e);}
        x.deallocate(b, s);}}

// --------------
// TestAllocator2
// --------------

TEST(TestAllocator2, const_index) {
    const my_allocator<int, 100> x;
    ASSERT_EQ(x[0], 92);}

TEST(TestAllocator2, test_min) {
    const my_allocator<int, 12> x;
    ASSERT_EQ(x[0], 4);}

TEST(TestAllocator2, test_index_end) {
    const my_allocator<int, 100> x;
    ASSERT_EQ(x[96], 92);}

TEST(TestAllocator2, test_max) {
    const my_allocator<int, 12> x;
    ASSERT_EQ(x[8], 4);}

TEST(TestAllocator2, index) {
    my_allocator<int, 100> x;
    ASSERT_EQ(x[0], 92);}

// --------------
// TestAllocator3
// --------------

template <typename A>
struct TestAllocator3 : testing::Test {
    // --------
    // typedefs
    // --------

    typedef          A             allocator_type;
    typedef typename A::value_type value_type;
    typedef typename A::size_type  size_type;
    typedef typename A::pointer    pointer;};

typedef testing::Types<
            my_allocator<int,    100>,
            my_allocator<double, 100>>
        my_types_2;

TYPED_TEST_CASE(TestAllocator3, my_types_2);

TYPED_TEST(TestAllocator3, test_1) {
    typedef typename TestFixture::allocator_type allocator_type;
    typedef typename TestFixture::value_type     value_type;
    typedef typename TestFixture::size_type      size_type;
    typedef typename TestFixture::pointer        pointer;

          allocator_type x;
    const size_type      s = 1;
    const value_type     v = 2;
    const pointer        p = x.allocate(s);
    if (p != nullptr) {
        x.construct(p, v);
        ASSERT_EQ(v, *p);
        x.destroy(p);
        x.deallocate(p, s);}}

TYPED_TEST(TestAllocator3, test_10) {
    typedef typename TestFixture::allocator_type allocator_type;
    typedef typename TestFixture::value_type     value_type;
    typedef typename TestFixture::size_type      size_type;
    typedef typename TestFixture::pointer        pointer;

          allocator_type x;
    const size_type      s = 10;
    const value_type     v = 2;
    const pointer        b = x.allocate(s);
    if (b != nullptr) {
        pointer e = b + s;
        pointer p = b;
        try {
            while (p != e) {
                x.construct(p, v);
                ++p;}}
        catch (...) {
            while (b != p) {
                --p;
                x.destroy(p);}
            x.deallocate(b, s);
            throw;}
        ASSERT_EQ(s, std::count(b, e, v));
        while (b != e) {
            --e;
            x.destroy(e);}
        x.deallocate(b, s);}}

// --------------
// TestAllocator4
// --------------

template <typename A>
struct TestAllocator4 : testing::Test {
    // --------
    // typedefs
    // --------

    typedef          A             allocator_type;
    typedef typename A::value_type value_type;
    typedef typename A::size_type  size_type;
    typedef typename A::pointer    pointer;};

typedef testing::Types<
            my_allocator<int,    100>,
            my_allocator<double, 100>>
        my_types_2;

TYPED_TEST_CASE(TestAllocator4, my_types_2);

TYPED_TEST(TestAllocator4, test_1) {
    typedef typename TestFixture::allocator_type allocator_type;
    typedef typename TestFixture::value_type     value_type;
    typedef typename TestFixture::size_type      size_type;
    typedef typename TestFixture::pointer        pointer;

          allocator_type x;
    const size_type      s = 1;
    const value_type     v = 2;
    const pointer        p = x.allocate(s);
    const pointer        p2 = x.allocate(s);
    const pointer        p3 = x.allocate(s);
    if (p != nullptr) {
        x.construct(p, v);
        ASSERT_EQ(v, *p);
        x.destroy(p);
        x.deallocate(p, s);
      }
    if (p2 != nullptr) {
        x.construct(p2, v);
        ASSERT_EQ(v, *p2);
        x.destroy(p2);
        x.deallocate(p2, s);
      }
      if (p3 != nullptr) {
        x.construct(p3, v);
        ASSERT_EQ(v, *p3);
        x.destroy(p3);
        x.deallocate(p3, s);
      }
    }

//Test 5
//standard
TEST(TestAllocator5, Allocate1) {
    my_allocator<int, 100> x;
    x.allocate(20);
    const my_allocator<int, 100> y = x;
    ASSERT_EQ(-80,y[0]);
    ASSERT_EQ(-80,y[84]);
    ASSERT_EQ(4, y[88]);
    ASSERT_EQ(4, y[96]);
}
//bad pointer
TEST(TestAllocator5, Allocate2) {
    my_allocator<int, 100> x;
    try {
      x.allocate(0);
    }
    catch(std::bad_alloc &e) {
      ASSERT_EQ(true, true);
    }
}
//multiple
TEST(TestAllocator5, Allocate3) {
    my_allocator<int, 100> x;
    x.allocate(5);
    x.allocate(5);
    const my_allocator<int, 100> y = x;
    ASSERT_EQ(-20, y[0]);
    ASSERT_EQ(-20, y[24]);
    ASSERT_EQ(-20, y[28]);
    ASSERT_EQ(-20, y[52]);
    ASSERT_EQ(36,  y[56]);
    ASSERT_EQ(36,  y[96]);
}

//Test 6
//standard
TEST(TestAllocator6, Allocate1) {
    my_allocator<int, 100> x;
    x.deallocate(x.allocate(3), 0);
    const my_allocator<int, 100> y = x;
    ASSERT_EQ(92, y[0]);
    ASSERT_EQ(92, y[96]);
}
//bad pointer
TEST(TestAllocator6, Allocate2) {
    my_allocator<int, 100> x;
    try {
      x.deallocate(x.allocate(1) - 2 * sizeof(int), 0);
    }
    catch(...) {
      ASSERT_EQ(true, true);
    }
}
//multiple
TEST(TestAllocator6, Allocate3) {
    my_allocator<int, 100> x;
    int* p = x.allocate(5);
    int* p2 = x.allocate(5);
    x.deallocate(p, 0);
    x.deallocate(p2, 0);
    const my_allocator<int, 100> y = x;
    ASSERT_EQ(92, y[0]);
    ASSERT_EQ(92, y[96]);
}
//mixed
//multiple
TEST(TestAllocator6, Allocate4) {
    my_allocator<int, 100> x;
    int* p = x.allocate(5);
    x.deallocate(p, 0);
    int* p2 = x.allocate(5);
    x.deallocate(p2, 0);
    const my_allocator<int, 100> y = x;
    ASSERT_EQ(92, y[0]);
    ASSERT_EQ(92, y[96]);
}
//add, add, delete, add, delete
TEST(TestAllocator6, Allocate5) {
    my_allocator<int, 100> x;
    int* p = x.allocate(5);
    int* p2 = x.allocate(5);
    x.deallocate(p, 0);
    p = x.allocate(5);
    x.deallocate(p2, 0);
    const my_allocator<int, 100> y = x;
    ASSERT_EQ(-20, y[0]);
    ASSERT_EQ(-20, y[24]);
}