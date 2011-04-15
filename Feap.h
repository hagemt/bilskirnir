/*
 * Feap.h
 *
 *  Created on: Oct 25, 2010
 *      Author: Tor E Hagemann <hagemt@rpi.edu>
 */

#ifndef FEAP_H_
#define FEAP_H_
#ifndef NULL
#define NULL 0
#endif
#define BLACK true
#define GREY false
#include <cassert>

template<class T> class Feap {
	/* Type definitions */
	typedef unsigned int size_type;
	typedef bool color_type;
	/* TreeNode structure for organizing Feap as circularly linked forest */
	struct TreeNode {
		struct BinaryTree {
			/*  */
			size_type degree; color_type mark; T value;
			BinaryTree * left, *right;
			BinaryTree(const T & t = T(), size_type d = 0, color_type c = GREY) :
				degree(d), mark(c), value(t) {
				left = right = NULL;
			}
			BinaryTree * copy_tree(const BinaryTree * t) const {
				if (t) {
					BinaryTree * new_tree =
							new BinaryTree(t->value, t->degree, t->mark);
					new_tree->left = copy_tree(t->left);
					new_tree->right = copy_tree(t->right);
					return new_tree;
				}
				return NULL;
			}
			~BinaryTree() {
				if (left) {
					delete left;
					left = NULL;
				}
				if (right) {
					delete right;
					right = NULL;
				}
			}
		};
		/* TreeNode representation */
		BinaryTree * head;
		TreeNode * left, *right;
		TreeNode(BinaryTree * t = NULL) :
			head(t) {
			left = right = this;
		}
		~TreeNode() {
			delete head;
		}
	};
	/* Feap representation */
	TreeNode * m_top;
	size_type m_size;
	/* Utility methods */
	TreeNode * copy_forest(const TreeNode * old_top) const {
		if (old_top) {
			TreeNode * new_top, *t, *n;
			t = new_top = new TreeNode(copy_tree(old_top->head));
			for (n = old_top->right; n != old_top; n = n->right) {
				t->right = new TreeNode(copy_tree(n));
				t->right->left = t;
				t = t->right;
			}
			t->right = new_top;
			new_top->left = t;
			return new_top;
		}
		return NULL;
	}
	void burn_forest(TreeNode * & t) {
		if (t) {
			// Detach this node from the chain
			t->left->right = NULL;
			// Recur around the structure
			// Start burning to the right
			burn_forest(t->right);
			// Free memory on post-order
			// Burn this tree, and bury it
			delete t;
			t = NULL;
		}
	}
public:
	/* Make an empty (head-less) Feap */
	Feap() {
		m_top = NULL;
		m_size = 0;
	}

	/* Copy Feap using equals operator */
	Feap(const Feap & f) {
		*this = f;
	}

	/* Destroy Feap */
	virtual ~Feap() {
		burn_forest(m_top);
		m_size = 0;
	}

	/* Copy circular structure of TreeNodes */
	Feap & operator=(const Feap & f) {
		if (this != &f) {
			m_top = copy_forest(f.m_top);
			m_size = f.m_size;
		}
		return *this;
	}

	/* The minimum is the current top's head's value */
	const T & find_min() const {
		assert(m_top && m_top->head);
		return m_top->head->value;
	}

	/* Is our size zero? */
	bool empty() const {
		return m_size == 0;
	}

	/* Get rid of everything */
	void clear() {
		burn_forest(m_top);
		m_size = 0;
	}

	/* What is our size? */
	size_type size() const {
		return m_size;
	}

	void insert(const T& t) {
		// TODO insert in O(1)?
	}

	/* O(log(n)* time */
	void delete_min() {
		assert(m_top && m_top->head);
	}

	void decrease_key(const T& t) {
		// TODO decrease key in O(1)*?
	}

	void erase(const T& t) {
		// TODO in O(log(n))*
	}

	/* TODO update, in O(1) */
	Feap& merge(const Feap& f) {
		// Merges with an empty Feap are work-less
		if (!f.empty()) {
			// When we are empty, merge merely consists of a copy
			if (m_top->root) {
				TreeNode* old_right = m_top->right;
				TreeNode* new_right = m_top->right = copy_forest(f.m_top);
				new_right->left->left = old_right;
				new_right->left = m_top;
				// TODO works on one-feaps?
				if (m_top->right->root->value < m_top->root->value) {
					m_top = m_top->right;
				}
			} else {
				m_top = copy_forest(f.m_top);
			}
		}
		m_size += f.m_size;
		return *this;
	}
};

#endif /* FEAP_H_ */
