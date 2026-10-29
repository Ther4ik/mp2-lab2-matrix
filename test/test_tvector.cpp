#include "tmatrix.h"

#include <gtest.h>

TEST(TDynamicVector, can_create_vector_with_positive_length)
{
    ASSERT_NO_THROW(TDynamicVector<int> v(5));
}

TEST(TDynamicVector, default_constructor_creates_vector_of_size_one)
{
    TDynamicVector<int> v;

    EXPECT_EQ(1u, v.size());
}

TEST(TDynamicVector, cant_create_vector_with_zero_length)
{
    ASSERT_ANY_THROW(TDynamicVector<int> v(0));
}

TEST(TDynamicVector, cant_create_too_large_vector)
{
    ASSERT_ANY_THROW(TDynamicVector<int> v(MAX_VECTOR_SIZE + 1));
}

TEST(TDynamicVector, throws_when_create_vector_with_negative_length)
{
    ASSERT_ANY_THROW(TDynamicVector<int> v(-5));
}

TEST(TDynamicVector, can_create_copied_vector)
{
    TDynamicVector<int> v(10);

    ASSERT_NO_THROW(TDynamicVector<int> v1(v));
}

TEST(TDynamicVector, copied_vector_is_equal_to_source_one)
{
    int arr[] = { 1, 2, 3 };
    TDynamicVector<int> v(arr, 3);
    TDynamicVector<int> v1(v);

    EXPECT_EQ(v, v1);
}

TEST(TDynamicVector, copied_vector_has_its_own_memory) 
{   
    int arr[] = { 1, 2, 3 };
    TDynamicVector<int> v(arr, 3);
    TDynamicVector<int> v1(v);
    v1[2] = 100;

    EXPECT_EQ(3, v[2]); 
    EXPECT_EQ(100, v1[2]); // разные значения на одних индексах = вектор имеет другую область памяти
}

TEST(TDynamicVector, can_get_size)
{
    TDynamicVector<int> v(4);

    EXPECT_EQ(4u, v.size());
}

TEST(TDynamicVector, throws_when_set_element_with_negative_index)
{
    TDynamicVector<int> v(4);

    ASSERT_THROW(v.at(-1), std::out_of_range); 
}

TEST(TDynamicVector, throws_when_set_element_with_too_large_index)
{
    TDynamicVector<int> v(4);

    ASSERT_THROW(v.at(4), std::out_of_range);
}

TEST(TDynamicVector, can_assign_vector_to_itself)
{
    int arr[] = { 1, 2, 3 };
    TDynamicVector<int> v(arr, 3);

    ASSERT_NO_THROW(v = v);
    EXPECT_EQ(3u, v.size());
    EXPECT_EQ(2, v[1]);
}

TEST(TDynamicVector, can_assign_vectors_of_equal_size)
{
    int arr[] = { 1, 2, 3 };
    TDynamicVector<int> v(arr, 3), v1(3);
    v1 = v;

    EXPECT_EQ(v, v1);
}

TEST(TDynamicVector, assign_operator_change_vector_size)
{
    int arr[] = { 1, 2, 3, 4, 5 };
    TDynamicVector<int> v(arr, 5), v1(2);
    v1 = v;

    EXPECT_EQ(5u, v1.size());
}

TEST(TDynamicVector, can_assign_vectors_of_different_size)
{
    int arr[] = { 1, 2, 3, 4, 5 };
    TDynamicVector<int> v(arr, 5), v1(2);

    ASSERT_NO_THROW(v1 = v);
    EXPECT_EQ(v, v1);
}

TEST(TDynamicVector, compare_equal_vectors_return_true)
{
    int arr[] = { 1, 2, 3 };
    TDynamicVector<int> v(arr, 3), v1(arr, 3);

    EXPECT_TRUE(v == v1);
    EXPECT_FALSE(v != v1);
}

TEST(TDynamicVector, compare_vector_with_itself_return_true)
{
    TDynamicVector<int> v(3);

    EXPECT_TRUE(v == v);
}

TEST(TDynamicVector, vectors_with_different_size_are_not_equal)
{
    TDynamicVector<int> v(3), v1(4);

    EXPECT_TRUE(v != v1);
    EXPECT_FALSE(v == v1);
}

TEST(TDynamicVector, can_add_scalar_to_vector) // странный тест, мы же не писали такой функционал. Как мы можем прибавить скаляр к вектору?
{
    TDynamicVector<int> v(3), v1(1);

    ASSERT_ANY_THROW(v += v1); //вектор длинной 1 - это число 
}

TEST(TDynamicVector, can_subtract_scalar_from_vector)
{
    TDynamicVector<int> v(3), v1(1);

    ASSERT_ANY_THROW(v -= v1); //вектор длинной 1 - это число
}

TEST(TDynamicVector, can_multiply_scalar_by_vector)
{
    int arr[] = { 1, 2, 3, 4 }, r[] = { 5, 10, 15, 20 };
    TDynamicVector<int> v(arr, 4), expected(r, 4);

    EXPECT_EQ(expected, v * 5);
}

TEST(TDynamicVector, can_add_vectors_with_equal_size)
{
    int a[] = { 1, 2, 3 };
    int b[] = { 10, 20, 30 };
    int r[] = { 11, 22, 33 };
    TDynamicVector<int> v(a, 3), v1(b, 3), expected(r, 3);
    EXPECT_EQ(expected, v + v1);
}

TEST(TDynamicVector, cant_add_vectors_with_not_equal_size)
{
    int a[] = { 1, 2, 3 };
    int b[] = { 10, 20, 30, 40};
    TDynamicVector<int> v(a, 3), v1(b, 4);
    
    ASSERT_ANY_THROW(v += v1);
    ASSERT_ANY_THROW(v + v1);
}

TEST(TDynamicVector, can_subtract_vectors_with_equal_size)
{
    int a[] = { 10, 20, 30 };
    int b[] = { 1, 2, 3 };
    int r[] = { 9, 18, 27 };
    TDynamicVector<int> v(a, 3), v1(b, 3), expected(r, 3);
    EXPECT_EQ(expected, v - v1);
}


TEST(TDynamicVector, cant_subtract_vectors_with_not_equal_size)
{
    int a[] = { 1, 2, 3 };
    int b[] = { 10, 20, 30, 40 };
    TDynamicVector<int> v(a, 3), v1(b, 4);

    ASSERT_ANY_THROW(v -= v1); 
    ASSERT_ANY_THROW(v - v1);
}

TEST(TDynamicVector, can_multiply_vectors_with_equal_size)
{
    int a[] = { 1, 2, 3, 5, 5 };
    int b[] = { 1, 2, 3, 4, 6 };
    TDynamicVector<int> v(a, 5), v1(b, 5);

    EXPECT_EQ(64, v * v1); 

}

TEST(TDynamicVector, cant_multiply_vectors_with_not_equal_size)
{
    int a[] = { 1, 2, 3, 5 };
    int b[] = { 1, 2, 3, 4, 6 };
    TDynamicVector<int> v(a, 4), v1(b, 5);

    ASSERT_ANY_THROW(v * v1);
}

TEST(TDynamicVector, works_with_double)
{
    double a[] = { 0.5, 1.5 };
    TDynamicVector<double> v(a, 2);

    EXPECT_DOUBLE_EQ(2.5, v * v); // 0.25 + 2.25
}

TEST(TDynamicVector, can_read_vector_from_stream)
{
    std::istringstream in("1 2 3");
    TDynamicVector<int> v(3);
    in >> v;

    EXPECT_EQ(1, v[0]);
    EXPECT_EQ(2, v[1]);
    EXPECT_EQ(3, v[2]);
}

TEST(TDynamicVector, can_write_vector_to_stream)
{
    int a[] = { 1, 2, 3 };
    TDynamicVector<int> v(a, 3);
    std::ostringstream out;
    out << v;

    EXPECT_EQ("1 2 3 ", out.str());
}

