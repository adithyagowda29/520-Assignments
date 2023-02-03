#include "binary_search_tree.h"
#include "gtest/gtest.h"

namespace {

    TEST(Node, CreateAndDestroy) {
        struct Node* a = NULL;
        a = Node_new();
        Node_destroy(a);
    }

    TEST(Node, DeathTests) {
        struct Node* a = NULL;
        // a = Node_new();
        Node_insert(&a, 3);
        Node_insert(&a, 4);
        Node_insert(&a, 5);
        Node_insert(&a, 1);
        Node_insert(&a, 2);
        printf("Printing In Order Traversal: ");
        printInOrder(a);
        printf("\n");
        printf("Printing Pre Order Traversal: ");
        printPreOrder(a);
        printf("\n");
        printf("Printing Post Order Traversal: ");
        printPostOrder(a);
        printf("\n");
        ASSERT_EQ(findMin(a), 1);
        ASSERT_EQ(findMax(a), 5);
        ASSERT_EQ(isBST(a), 1);
        struct Node* b;
        // b = search(a, 6);
        // ASSERT_EQ(*b, NULL);
        b = search(a, 3);
        ASSERT_EQ(b->value, 3);
        Node_destroy(a);
    }    
}