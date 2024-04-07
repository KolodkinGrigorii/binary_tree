#pragma once
#include "binary_tree.h"
#include <gtest.h>
using namespace std;
TEST(BinaryTreeTest, InsertAndInorder) {
	BinaryTree tree;
	tree.insert(50);
	tree.insert(30);
	tree.insert(70);
	tree.insert(20);
	tree.insert(40);
    testing::internal::CaptureStdout();

	tree.inorder();

	std::string output = testing::internal::GetCapturedStdout();

	EXPECT_EQ(output, "20 30 40 50 70 ");
}

TEST(BinaryTreeTest, InsertAndRemove) {
	BinaryTree tree;
	tree.insert(50);
	tree.insert(30);
	tree.insert(70);
	tree.insert(20);
	tree.insert(40);

	tree.remove(30);

	testing::internal::CaptureStdout();

	tree.inorder();

	std::string output = testing::internal::GetCapturedStdout();

	EXPECT_EQ(output, "20 40 50 70 ");
}
TEST(BinaryTreeTest, Iterator) {
	BinaryTree tree;
	tree.insert(0);
	tree.insert(1);
	tree.insert(2);
	tree.insert(3);
	int i = 0;
	for (auto it = tree.find(0); it != tree.find(3); ++it) {
		EXPECT_EQ(i, it->value);
		i++;
	}
	auto it = tree.find(1);
	Node node=*it;
	EXPECT_EQ(1, node.value);
}

