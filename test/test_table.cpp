#pragma once
#include "binary_tree.h"
#include <gtest.h>
#include <algorithm>
#include <random>
#include <vector>
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

	tree.remove(30);

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
	for (auto it = tree.begin(); it != tree.find(4); ++it) {
		EXPECT_EQ(i, *it);
		i++;
	}
}
TEST(BinaryTreeTest, BigTree) {
	const int N = 1000;
	BinaryTree<int, int> tree;
	for (int i = 0; i < N; i++) {
		tree.insert(i,i);
	}
	for (auto it = tree.begin(); it != tree.end(); ++it) {
		it->value++;
	}
	for (int i = 0; i < N; i++) {
		EXPECT_EQ(i + 1, tree.find(i)->value);
	}
}
TEST(BinaryTreeTest, BigTreeOperator) {
	const int N = 1000;
	BinaryTree<int, int> tree;
	for (int i = 0; i < N; i++) {
		tree.insert(i, i);
	}
	for (int i = 0; i < N; i++) {
		tree[i]++;
	}
	for (int i = 0; i < N; i++) {
		EXPECT_EQ(i + 1, tree[i]);
	}
}
TEST(BinaryTreeTest, BigRandomInsert) {
	const int N = 500000;
	vector<int> ar;
	BinaryTree<int, int> tree;
	for (int i = 0; i < N; i++) {
		ar.push_back(i);
	}
	random_device rd;
	mt19937 g(rd());
	shuffle(ar.begin(), ar.end(), g);
	for (int i = 0; i < N; i++) {
		tree.insert(ar[i], ar[i]);
	}
}

TEST(BinaryTreeTest, BigRandomRemove) {
	const int N = 500000;
	vector<int> ar;
	BinaryTree<int, int> tree;
	for (int i = 0; i < N; i++) {
		ar.push_back(i);
	}
	random_device rd;
	mt19937 g(rd());
	shuffle(ar.begin(), ar.end(), g);
	for (int i = 0; i < N; i++) {
		tree.insert(ar[i], ar[i]);
	}
	shuffle(ar.begin(), ar.end(), g);
	for (int i = 0; i < N; i++) {
		tree.remove(ar[i]);
	}
}
/*TEST(BinaryTreeTest, BigRandomInsertAndRemove) {
	const int N = 1000;
	BinaryTree<int, int> tree;
	vector<int> ar;
	for (int i = 0; i < N; i++) {
		ar.push_back(i);
	}
	random_device rd;
	mt19937 g(rd());
	shuffle(ar.begin(), ar.end(), g);
	for (int i = 0; i < N; i++) {
		tree.insert(ar[i], ar[i]);
	}
	int height = tree.getheight();
	vector<int> ar2;
	for (int i = 1000; i < 1100; i++) {
		ar2.push_back(i);
	}
	int j = 0;
	while (tree.getheight() < height + 11) {
		shuffle(ar2.begin(), ar2.end(), g);
		for (int i = 0; i < 100; i++) {
			tree.insert(ar2[i], ar2[i]);
		}
		shuffle(ar2.begin(), ar2.end(), g);
		for (int i = 0; i < 100; i++) {
			tree.remove(ar2[i]);
		}
		j++;
	}
	cout << height << " " << j;
}*/