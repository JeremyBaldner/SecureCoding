// Uncomment the next line to use precompiled headers
#include "pch.h"
// uncomment the next line if you do not use precompiled headers
//#include "gtest/gtest.h"
//
// the global test environment setup and tear down
// you should not need to change anything here
class Environment : public ::testing::Environment
{
public:
    ~Environment() override {}

    // Override this to define how to set up the environment.
    void SetUp() override
    {
        //  initialize random seed
        srand(time(nullptr));
    }

    // Override this to define how to tear down the environment.
    void TearDown() override {}
};

// create our test class to house shared data between tests
// you should not need to change anything here
class CollectionTest : public ::testing::Test
{
protected:
    // create a smart point to hold our collection
    std::unique_ptr<std::vector<int>> collection;

    void SetUp() override
    { // create a new collection to be used in the test
        collection.reset(new std::vector<int>);
    }

    void TearDown() override
    { //  erase all elements in the collection, if any remain
        collection->clear();
        // free the pointer
        collection.reset(nullptr);
    }

    // helper function to add random values from 0 to 99 count times to the collection
    void add_entries(int count)
    {
        assert(count > 0);
        for (auto i = 0; i < count; ++i)
            collection->push_back(rand() % 100);
    }
};

// When should you use the EXPECT_xxx or ASSERT_xxx macros?
// Use ASSERT when failure should terminate processing, such as the reason for the test case.
// Use EXPECT when failure should notify, but processing should continue.

// Prior to calling all TEST_F defined methods, CollectionTest::StartUp is called.
// Following all TEST_F defined methods, CollectionTest::TearDown is called.

// Test that a collection is empty when created.
TEST_F(CollectionTest, CollectionSmartPointerIsNotNull)
{
    // is the collection created
    ASSERT_TRUE(collection);

    // if empty, the size must be 0
    ASSERT_NE(collection.get(), nullptr);
}

// Test that a collection is empty when created.
TEST_F(CollectionTest, IsEmptyOnCreate)
{
    // is the collection empty?
    ASSERT_TRUE(collection->empty());

    // if empty, the size must be 0
    ASSERT_EQ(collection->size(), 0);
}

/* Comment this test out to prevent the test from running
 * Uncomment this test to see a failure in the test explorer */
//TEST_F(CollectionTest, AlwaysFail)
//{
//    FAIL();
//}

// Test to verify adding a single value to an empty collection
TEST_F(CollectionTest, CanAddToEmptyVector)
{
    // is the collection empty?
    ASSERT_TRUE(collection->empty());
    // if empty, the size must be 0
    ASSERT_EQ(collection->size(), 0);

    add_entries(1);

    // is the collection still empty?
    ASSERT_FALSE(collection->empty());
    // if not empty, what must the size be?
    ASSERT_EQ(collection->size(), 1);
}

// Test to verify adding five values to collection
TEST_F(CollectionTest, CanAddFiveValuesToVector)
{
    // is the collection empty?
    ASSERT_TRUE(collection->empty());
    // if empty, the size must be 0
    ASSERT_EQ(collection->size(), 0);

    add_entries(5);

    // is the collection still empty?
    ASSERT_FALSE(collection->empty());
    // if not empty, what must the size be?
    ASSERT_EQ(collection->size(), 5);
}

// Test to verify adding ten values to collection
TEST_F(CollectionTest, CanAddTenValuesToVector)
{
    // is the collection empty?
    ASSERT_TRUE(collection->empty());
    // if empty, the size must be 0
    ASSERT_EQ(collection->size(), 0);

    add_entries(10);

    // is the collection still empty?
    ASSERT_FALSE(collection->empty());
    // if not empty, what must the size be?
    ASSERT_EQ(collection->size(), 10);
}

// Test to verify resizing increases the collection
TEST_F(CollectionTest, CanResizeVectorLarger)
{
    add_entries(10);

    // Does the collection have 10 entries?
    ASSERT_EQ(collection->size(), 10);

    collection->resize(15);

    // is the collection size still 10?
    EXPECT_NE(collection->size(), 10);

    // if not 10, what must the size be?
    ASSERT_EQ(collection->size(), 15);
}

// Test to verify resizing decreases the collection
TEST_F(CollectionTest, CanResizeVectorSmaller)
{
    add_entries(10);

    // Does the collection have 10 entries?
    ASSERT_EQ(collection->size(), 10);

    collection->resize(5);

    // is the collection size still 10?
    ASSERT_NE(collection->size(), 10);

    // if not 10, what must the size be?
    EXPECT_EQ(collection->size(), 5);
}

// Test to verify resizing the collection to 0
TEST_F(CollectionTest, CanResizeVectorZero)
{
    add_entries(10);

    // Does the collection have 10 entries?
    ASSERT_EQ(collection->size(), 10);

    collection->resize(0);

    // is the collection size still 10?
    ASSERT_NE(collection->size(), 10);

    // if not 10, what must the size be?
    ASSERT_TRUE(collection->empty());
}

// Test to verify clearing the collection to 0
TEST_F(CollectionTest, CanClearVector)
{
    add_entries(10);

    // Does the collection have 10 entries?
    ASSERT_EQ(collection->size(), 10);

    collection->clear();

    // is the collection size still 10?
    ASSERT_NE(collection->size(), 10);

    // if not 10, what must the size be?
    ASSERT_TRUE(collection->empty());
}

// Test to verify erase(begin, end) erases the collection
TEST_F(CollectionTest, CanEraseVector)
{
    add_entries(10);

    // Does the collection have 10 entries?
    ASSERT_EQ(collection->size(), 10);

    collection->erase(collection->begin(), collection->end());

    // is the collection size still 10?
    ASSERT_NE(collection->size(), 10);

    // if not 10, what must the size be?
    ASSERT_TRUE(collection->empty());
}

// Test to verify reserve increases the capacity but not the size of the collection
TEST_F(CollectionTest, ReserveIncreasesCapacityNotSize)
{
    // is the collection empty?
    ASSERT_TRUE(collection->empty());

    // if the collection is empty, the size must be 0
    EXPECT_EQ(collection->size(), 0);

    // if the size is 0, the capacity should be 0
    EXPECT_EQ(collection->capacity(), 0);

    collection->reserve(50);

    // is the size still 0?
    EXPECT_EQ(collection->size(), 0);

    // verify the capacity was increased
    ASSERT_EQ(collection->capacity(), 50);
}

// Test to verify the std::out_of_range exception is thrown when calling at() with an index out of bounds
TEST_F(CollectionTest, OutOfRangeErrorExpected)
{
    // is the collection empty?
    ASSERT_TRUE(collection->empty());

    // make sure out of range error is thrown
    ASSERT_THROW(collection->at(1), std::out_of_range);
}

// Test to verify exception is thrown when resizing the vector too large
TEST_F(CollectionTest, VectorTooLargeExpected)
{
    // is the collection empty?
    ASSERT_TRUE(collection->empty());
    
    // make sure bad alloc error is thrown
    ASSERT_THROW(collection->resize(9999999999999999999), std::exception);
}

// Test to verify 
TEST_F(CollectionTest, CanEmplaceToEmptyVector)
{
    // is the collection empty?
    ASSERT_TRUE(collection->empty());
    // if empty, the size must be 0
    ASSERT_EQ(collection->size(), 0);

    collection->emplace(collection->end(), 16);

    // is the collection still empty?
    ASSERT_FALSE(collection->empty());
    // if not empty, what must the size be?
    ASSERT_EQ(collection->size(), 1);
    // what is the value emplaced?
    EXPECT_EQ(collection->at(0), 16);
}