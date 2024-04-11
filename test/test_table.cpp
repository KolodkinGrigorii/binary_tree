#pragma once
#include "binary_tree.h"
#include <gtest.h>
using namespace std;
TEST(BinaryTreeTest, InsertAndInorder) {
	BinaryTree<int, int> tree;
	tree.insert(50,50);
	tree.insert(30,30);
	tree.insert(70,70);
	tree.insert(20,20);
	tree.insert(40,40);
    testing::internal::CaptureStdout();

	tree.inorder();

	std::string output = testing::internal::GetCapturedStdout();

	EXPECT_EQ(output, "20 30 40 50 70 ");
}

TEST(BinaryTreeTest, InsertAndRemove) {
	BinaryTree<int, int> tree;
	tree.insert(50,50);
	tree.insert(30,30);
	tree.insert(70,70);
	tree.insert(20,20);
	tree.insert(40,40);

	tree.remove(30,30);

	testing::internal::CaptureStdout();

	tree.inorder();

	std::string output = testing::internal::GetCapturedStdout();

	EXPECT_EQ(output, "20 40 50 70 ");
}
TEST(BinaryTreeTest, Iterator) {
	BinaryTree<int, int> tree;
	tree.insert(0, 0);
	tree.insert(1,1);
	tree.insert(2,2);
	tree.insert(3,3);
	tree.insert(4,4);
	int i = 0;
	for (auto it = tree.find(0); it != tree.find(4); ++it) {
		EXPECT_EQ(i, it->value);
		i++;
	}
	auto it = tree.find(1);
	(*it) = 5;
	EXPECT_EQ(5, tree.find(1)->value);
}
TEST(BinaryTreeTest, BigTree) {
	const int N = 9;
	BinaryTree<int, int> tree;
	for (int i = N; i > 0; i--) {
		tree.insert(i, i);
	}
	for (auto it = tree.begin() ; it != tree.end(); ++it) {
		it->value++;
	}
	for (int i = N; i > 0; i--) {
		EXPECT_EQ(i+1, tree.find(i)->value);
	}
}