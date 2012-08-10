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
public:
	/* Type definitions */
	typedef unsigned int size_type;
	typedef bool color_type;

	/* Make an empty (head-less) Feap */
	Feap() {
		m_top = NULL;
		m_size = 0;
	}

	/* Copy Feap using equals operator */
	Feap(const Feap<T> & f) {
		*this = f;
	}

	/* Destroy Feap */
	virtual ~Feap() {
		delete m_top;
		m_size = 0;
	}

	/* Copy circular structure of TreeNodes */
	Feap<T> & operator=(const Feap<T> & f) {
		if (this != &f) {
			m_top = grow_forest(f.m_top);
			m_size = f.m_size;
		}
		return *this;
	}

	/* The minimum is the current top's head's value */
	const T & top() const {
		assert(m_top);
		return m_top->value;
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

	void insert(const T & t) {
		m_top = plant(m_top, new TreeNode(t));
	}

	/* O(log(n)* time */
	void pop() {
		if (m_size > 1) {
			/* Promote all nodes in the child to the top level */
			plant(m_top, m_top->child);
			/* Splice out the top, and "forget" about its child(ren) */
			m_top->right->left = m_top->left;
			m_top->left->right = m_top->right;
			m_top->child = NULL;
		}
		/* Cleanup top, if necessary */
		germinate(m_top);
	}

	void decrease_key(const T & key, const T & t) {
		// TODO decrease key in O(1)*?
		/* Operation decrease key will take the node,
		 * decrease the key and if the heap property becomes violated
		 * (the new key is smaller than the key of the parent),
		 * the node is cut from its parent.
		 * If the parent is not a root, it is marked.
		 * If it has been marked already, it is cut as well and its parent is marked.
		 * We continue upwards until we reach either the root or an unmarked node.
		 * In the process we create some number, say k, of new trees.
		 * Each of these new trees except possibly the first one was marked originally
		 * but as a root it will become unmarked. One node can become marked.
		 * Therefore the potential decreases by at least k − 2.
		 * The actual time to perform the cutting was O(k),
		 * therefore the amortized running time is constant.
		 */

	}

	void erase(const T & t) {
		// TODO in O(log(n))*
		/* How to decrease key in general? */
	}

	/* TODO update, in O(1) */
	Feap<T> & merge(Feap<T> & f) {
		/* Don't merge with yourself */
		if (this != &f) {
			/* Otherwise, plant f's root next-door and add */
			m_top = plant(m_top, f.m_top);
			m_size += f.m_size;
			/* Merge empties the other Feap */
			f.m_top = NULL;
			f.m_size = 0;
		}
		return *this;
	}

private:
	/* TreeNode structure for organizing Feap as circularly linked forest */
	struct TreeNode {
		/* TreeNode representation */
		size_type degree; color_type mark; T value;
		/* A TreeNode has left and right siblings, which are circularly linked */
		TreeNode * left, * right, * child;

		/* Constructors (default implicit and copy) and Destructor */
		TreeNode(const T & t = T(), size_type d = 1, color_type c = GREY) :
			degree(d), mark(c), value(t) {
			left = right = this;
			child = NULL;
		}
		TreeNode(const TreeNode & t) :
			TreeNode(t.value, t.degree, t.mark) {
			child = grow_forest(t.child);
		}
		~TreeNode() {
			burn_forest(child);
		}

		/* Utility methods */
		TreeNode * grow_forest(const TreeNode * old_top) const {
			/* Build a copy of the old_top and return it */
			if (old_top) {
				/* Represent a new top, and iterators for the old and new tops */
				TreeNode * new_top, * t, * n;
				/* Invoke construction that explicitly copies the old top */
				t = new_top = new TreeNode(*old_top);
				/* For every other node known to the old top */
				for (n = old_top->right; n != old_top; n = n->right) {
					t->right = new TreeNode(*n);
					t->right->left = t;
					t = t->right;
				}
				t->right = new_top;
				new_top->left = t;
				return new_top;
			}
			/* No top, no copy */
			return NULL;
		}
		void burn_forest(TreeNode * & t) {
			if (t) {
				// Detach this node from the chain
				// Isolate the tree on its flank
				t->left->right = NULL;
				// Recur around the structure
				// Start burning to the right
				burn_forest(t->right);
				t->right = NULL;
				// Free memory on post-order
				// Burn this tree, and bury it
				delete t; t = NULL;
			}
		}
	};

	/* Does the same thing as this, in general:
	inline TreeNode * germinate_left(TreeNode * old_tree, TreeNode * new_tree) {
		assert(old_tree && new_tree);
		new_tree->left = old_tree->left;
		new_tree->right = old_tree;
		old_tree->left->right = new_tree;
		old_tree->left = new_tree;
		return min(old_tree, new_tree);
	}*/
	inline TreeNode * plant(TreeNode * a, TreeNode * b) {
		/* Regular Order:
		 * First, tell a's right about its new left, b's left
		 * Next, tell b's left about its new right, a's right
		 * Lastly, make a's right b and b's left a
		 */
		if (a && b) {
			a->right->left = b->left;
			b->left->right = a->right;
			(a->right = b)->left = a;
			return (a->value < b->value) ? a : b;
		}
		return (a) ? a : b;
	}

	/* Consolidates degrees of all trees not t in t's cycle */
	inline void germinate(TreeNode * & t) {
		/* t references a dying tree that needs to be replaced */
		if (t) {
			/* TODO Max degree: m_size - 1, make all NULL? */
			TreeNode * node_of_degree[--m_size], * n, * m;
			for (size_type i = 0; i < m_size; ++i) {
				node_of_degree[i] = NULL;
			}
			/* Start searching for work right of t */
			for (m = n = t->right; n != t; n = n->right) {
				size_type degree = n->degree;
				if (node_of_degree[degree]) {
					/* TODO FIX DEGREE */
					for (size_type d = degree; d < m_size; ++d) {
						if (node_of_degree[d]) {
							// merge(n, node_of_degree[d]);
						}
					}
				} else {
					node_of_degree[degree] = n;
				}
			}
			delete t;
			t = m;
		}
	}

	/* Feap representation */
	TreeNode * m_top;
	size_type m_size;
};

#endif /* FEAP_H_ */
