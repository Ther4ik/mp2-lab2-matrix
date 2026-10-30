#include "tmatrix.h"
#include <gtest.h>
#include <sstream>


static TDynamicMatrix<int> makeSequential(size_t n) // матрица n x n, заполненная последовательно 1,2,3,...
{
    TDynamicMatrix<int> m(n);
    int k = 1;
    for (size_t i = 0; i < n; i++)
        for (size_t j = 0; j < n; j++)
            m[i][j] = k++;

    return m;
}

TEST(TDynamicMatrix, can_create_matrix_with_positive_length)
{
  ASSERT_NO_THROW(TDynamicMatrix<int> m(5));
}

TEST(TDynamicMatrix, cant_create_too_large_matrix)
{
  ASSERT_ANY_THROW(TDynamicMatrix<int> m(MAX_MATRIX_SIZE + 1));
}

TEST(TDynamicMatrix, throws_when_create_matrix_with_negative_length)
{
  ASSERT_ANY_THROW(TDynamicMatrix<int> m(-5));
}

TEST(TDynamicMatrix, can_create_copied_matrix)
{
  TDynamicMatrix<int> m(5);

  ASSERT_NO_THROW(TDynamicMatrix<int> m1(m));
}

TEST(TDynamicMatrix, copied_matrix_is_equal_to_source_one)
{
    TDynamicMatrix<int> m = makeSequential(3);
    TDynamicMatrix<int> m1(m);
    EXPECT_EQ(m, m1);
}

TEST(TDynamicMatrix, copied_matrix_has_its_own_memory)
{
    TDynamicMatrix<int> m = makeSequential(3);
    TDynamicMatrix<int> m1(m);
    m1[0][2] = 100;

    EXPECT_EQ(3, m[0][2]);
    EXPECT_EQ(100, m1[0][2]); 
}

TEST(TDynamicMatrix, can_get_size)
{
    TDynamicMatrix<int> m(3);

    EXPECT_EQ(3u, m.size());
}

TEST(TDynamicMatrix, can_set_and_get_element)
{
    TDynamicMatrix<int> m(3);
    m[1][2] = 7;
    EXPECT_EQ(7, m[1][2]);
}

TEST(TDynamicMatrix, throws_when_set_element_with_negative_index)
{
    TDynamicMatrix<int> m(3);
    EXPECT_THROW(m.at(-1), std::out_of_range);
}

TEST(TDynamicMatrix, throws_when_set_element_with_too_large_index)
{
    TDynamicMatrix<int> m(3);

    EXPECT_THROW(m.at(3), std::out_of_range);
}

TEST(TDynamicMatrix, throws_when_column_index_is_too_large)
{
    TDynamicMatrix<int> m(3);

    EXPECT_THROW(m.at(0).at(3), std::out_of_range);
}

TEST(TDynamicMatrix, can_assign_matrix_to_itself)
{
    TDynamicMatrix<int> m = makeSequential(3);

    ASSERT_NO_THROW(m = m);
    EXPECT_EQ(5, m[1][1]);
}

TEST(TDynamicMatrix, can_assign_matrices_of_equal_size)
{
    TDynamicMatrix<int> m = makeSequential(3), m1(3);
    m1 = m;

    EXPECT_EQ(m, m1);
}

TEST(TDynamicMatrix, assign_operator_change_matrix_size)
{
    TDynamicMatrix<int> m = makeSequential(4), m1(2);
    m1 = m;

    EXPECT_EQ(4u, m1.size());
    EXPECT_EQ(m, m1);
}

TEST(TDynamicMatrix, can_assign_matrices_of_different_size)
{
    TDynamicMatrix<int> m = makeSequential(4), m1(2);

    EXPECT_EQ(2u, m1.size());

    m1 = m;

    EXPECT_EQ(4u, m1.size());
    EXPECT_EQ(m, m1);

}

TEST(TDynamicMatrix, compare_equal_matrices_return_true)
{
    TDynamicMatrix<int> m = makeSequential(3), m1 = makeSequential(3);

    EXPECT_TRUE(m == m1);
    EXPECT_FALSE(m != m1);
}

TEST(TDynamicMatrix, compare_matrix_with_itself_return_true)
{
    TDynamicMatrix<int> m = makeSequential(3);

    EXPECT_TRUE(m == m);
}

TEST(TDynamicMatrix, matrices_with_different_size_are_not_equal)
{
    TDynamicMatrix<int> m(3), m1(4);

    EXPECT_TRUE(m != m1);
    EXPECT_FALSE(m == m1);
}

TEST(TDynamicMatrix, can_add_matrices_with_equal_size)
{
    TDynamicMatrix<int> m = makeSequential(2), m1 = makeSequential(2);
    TDynamicMatrix<int> r = m + m1;

    EXPECT_EQ(2, r[0][0]);
    EXPECT_EQ(4, r[0][1]);
    EXPECT_EQ(6, r[1][0]);
    EXPECT_EQ(8, r[1][1]);
}

TEST(TDynamicMatrix, cant_add_matrices_with_not_equal_size)
{
    TDynamicMatrix<int> m(3), m1(4);

    EXPECT_THROW(m + m1, std::invalid_argument);
}

TEST(TDynamicMatrix, can_subtract_matrices_with_equal_size)
{
    TDynamicMatrix<int> m = makeSequential(2);
    TDynamicMatrix<int> m1 = makeSequential(2) * 3;
    TDynamicMatrix<int> r = m1 - m;

    EXPECT_EQ(2, r[0][0]);
    EXPECT_EQ(4, r[0][1]);
    EXPECT_EQ(6, r[1][0]);
    EXPECT_EQ(8, r[1][1]);
}

TEST(TDynamicMatrix, cant_subtract_matrixes_with_not_equal_size)
{
    TDynamicMatrix<int> m(3), m1(4);

    EXPECT_THROW(m - m1, std::invalid_argument);
}

TEST(TDynamicMatrix, can_multiply_matrices)
{
    TDynamicMatrix<int> a(2), b(2);
    a[0][0] = 1; a[0][1] = 2; a[1][0] = 3; a[1][1] = 4;
    b[0][0] = 5; b[0][1] = 6; b[1][0] = 7; b[1][1] = 8;

    TDynamicMatrix<int> r = a * b;
    EXPECT_EQ(19, r[0][0]);
    EXPECT_EQ(22, r[0][1]);
    EXPECT_EQ(43, r[1][0]);
    EXPECT_EQ(50, r[1][1]);
}

TEST(TDynamicMatrix, can_read_matrix)
{
    std::istringstream in("1 2 3 4");
    TDynamicMatrix<int> m(2);
    in >> m;

    EXPECT_EQ(1, m[0][0]);
    EXPECT_EQ(2, m[0][1]);
    EXPECT_EQ(3, m[1][0]);
    EXPECT_EQ(4, m[1][1]);
}

TEST(TDynamicMatrix, can_write_matrix)
{
    TDynamicMatrix<int> m = makeSequential(2);

    std::stringstream sstr;
    sstr << m;

    EXPECT_EQ("1 2 \n3 4 \n", sstr.str());
}
