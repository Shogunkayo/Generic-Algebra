/*
 * 	Custom implementation of map from STL
 * 	Version 1.0
 * 	Implemented using Binary Search Tree
 *
 * 	Implemented features:
 * 	- Default empty initialization
 * 	- member insertion through operator[]
 * 	- member modification through operator[]
 * 	- member access through operator[]
 * 	- map::insert()
 * 	- map::size()
 * 	- map::empty()
 * 	- map::clear()
 * 	- map::erase()
 *
 */

#ifndef MYMAP_H
#define MYMAP_H

enum COLOR {RED, BLACK};

template <typename T, typename U>
class Node {
public:
    T key;
    U value;
    Node *left;
    Node *right;
    Node *parent;
    COLOR color;

    Node(T key, U value) {
        this->key = key;
        this->value = value;
        parent = nullptr;
        left = nullptr;
        right = nullptr;
        color = RED;
    }
};

template <typename T, typename U>
class Map {
private:
    Node<T, U> *root;
    int no_elements;
    bool is_found;

    void inorder_traversal(Node<T, U> *root);
    void rebalance_insert(Node<T, U> *node_p);
    void rebalance_delete(Node<T, U> *node_p);
    void remove_node(T key);
    Node<T, U> *search_node(T key);
    void delete_postorder(Node<T, U> *&root);

public:
    Map();
    ~Map();
    Node<T, U> &insert(T key, U value);
    void inorder();
    U &operator[](T key);
    int size();
    int erase(T key);
    void clear();
    bool empty();
};

template <typename T, typename U>
Map<T, U>::Map() {
    root = nullptr;
    no_elements = 0;
}

template <typename T, typename U>
Map<T, U>::~Map() {
	clear();
}

template <typename T, typename U>
void Map<T, U>::inorder_traversal(Node<T, U> *root) {
    if (root == nullptr) {
        return;
    }

    inorder_traversal(root->left);
    inorder_traversal(root->right);
}

template <typename T, typename U>
void Map<T, U>::rebalance_insert(Node<T, U> *node_p) {
	if (node_p == root) {
		node_p->color = BLACK;
	}
	else {
		Node<T, U> *root_p = node_p->parent;
		Node<T, U> *uncle_p = root_p->parent->left == root_p ? root_p->parent->right : root_p->parent->left;
		Node<T, U> *grnd_p = root_p->parent;
		Node<T, U> *temp_p;

		if (uncle_p == nullptr || uncle_p->color == BLACK) {
			if (grnd_p->left == root_p && root_p->left == node_p) {
				// ll case
				temp_p = root_p->right;
				root_p->right = grnd_p;
				grnd_p->left = temp_p;

			}
			else if (grnd_p->right == root_p && root_p->right == node_p) {
				// rr case
				temp_p = root_p->left;
				root_p->left = grnd_p;
				grnd_p->right = temp_p;

			}
			else if (grnd_p->left == root_p && root_p->right == node_p) {
				// lr case
				temp_p = node_p->left;
				node_p->left = root_p;
				root_p->right = temp_p;
				root_p->parent = node_p;
				
				temp_p = node_p;
				node_p = root_p;
				root_p = temp_p;

				temp_p = root_p->right;
				root_p->right = grnd_p;
				grnd_p->left = temp_p;
			}
			else {
				// rl case
				temp_p = node_p->right;
				node_p->right = root_p;
				root_p->left = temp_p;
				root_p->parent = node_p;

				temp_p = node_p;
				node_p = root_p;
				root_p = temp_p;

				temp_p = root_p->left;
				root_p->left = grnd_p;
				grnd_p->right = temp_p;
			}

			grnd_p->color = RED;
			root_p->color = BLACK;

			if (grnd_p == root) {
				root = root_p;
			}
			else {
				root_p->parent = grnd_p->parent;
				grnd_p->parent = root_p;
				if (root_p->parent->left == grnd_p) {
					root_p->parent->left = root_p;
				}
				else {
					root_p->parent->right = root_p;
				}
			}
		}
		else {
			root_p->color = BLACK;
			uncle_p->color = BLACK;
			grnd_p->color = RED;

			if (grnd_p == root || grnd_p->parent->color == RED) {
				rebalance_insert(grnd_p);
			}
		}
	}
}

template <typename T, typename U>
void Map<T, U>::rebalance_delete(Node<T, U>* node_p) {
	if (node_p->left == nullptr && node_p->right == nullptr && node_p->color == BLACK) {
		Node<T, U>* sibling_p = node_p->parent->right == node_p ? node_p->parent->left : node_p->parent->right;

		if (sibling_p->color == BLACK) {
			if (sibling_p->left != nullptr && sibling_p->left->color == RED) {
				sibling_p->parent = sibling_p->parent->parent;
				sibling_p->parent->left = sibling_p->right;
				sibling_p->right = node_p->parent;

				sibling_p->left->color = BLACK;
				sibling_p->color = sibling_p->right->color;
				sibling_p->right->color = BLACK;

				node_p->parent->right = nullptr;
			}
			else if (sibling_p->right != nullptr && sibling_p->right->color == RED) {
				sibling_p->parent = sibling_p->right;
				sibling_p->right = sibling_p->right->left;
				node_p->parent->left = sibling_p->parent->right;
				sibling_p->parent->right = node_p->parent;
				node_p->parent->parent = sibling_p->parent;

				sibling_p->parent->color = node_p->parent->color;
				node_p->parent->color = BLACK;
				
				node_p->parent->right = nullptr;
			}
			else {
				sibling_p->color = RED;
				if (node_p->parent->color == RED) {
					node_p->parent->color = BLACK;
				}
				else if (node_p->parent != root) {
					rebalance_delete(node_p->parent);
				}
			}
		}
		else {
			sibling_p->parent->left = sibling_p->right;
			sibling_p->parent = sibling_p->parent->parent;
			sibling_p->right = node_p->parent;
			
			sibling_p->color = BLACK;
			sibling_p->right->color = RED;
			rebalance_delete(node_p);
		}
	}

	else {
		Node<T, U>* child_p = node_p->left != nullptr ? node_p->left : node_p->right;

		if (node_p->parent->right == node_p) {
			node_p->parent->right = child_p;
		}
		else {
			node_p->parent->left = child_p;
		}

		child_p->parent = node_p->parent;
		child_p->color = node_p->color == BLACK ? BLACK : child_p->color;
	}
}

template <typename T, typename U>
void Map<T, U>::remove_node(T key) {
	Node<T, U>* node_p = search_node(key);
	if (node_p == nullptr) {
		return;
	}
	
	if (node_p->left != nullptr && node_p->right != nullptr) {
		Node<T, U>* successor_p = node_p->right;
		while (successor_p != nullptr) {
			successor_p = successor_p->left;
		}

		node_p->key = successor_p->key;

		rebalance_delete(successor_p);
		
		delete successor_p;
		return;
	}
	
	rebalance_delete(node_p);
	delete node_p;
}

template<typename T, typename U>
Node<T, U>* Map<T,U>::search_node(T key) {
	Node<T, U> *root_p = root;

	while (root_p != nullptr) {
		if (root_p->key > key) {
			root_p = root_p->left;
		}
		else if (root_p->key < key) {
			root_p = root_p->right;
		}
		else {
			return root_p;
		}
	}

	return nullptr;
}

template<typename T, typename U>
void Map<T, U>::delete_postorder(Node<T, U>*& root) {
	if(root!=nullptr) {
		delete_postorder(root->left);
		delete_postorder(root->right);
		delete root;
		root = nullptr;
	}
}

template <typename T, typename U>
Node<T, U>& Map<T, U>::insert(T key, U value) {
    Node<T, U> *node_p = new Node<T, U>(key, value);
    Node<T, U> *root_p = root;
    no_elements++;

    if (root == nullptr) {
        root = node_p;
        root->color = BLACK;
        return *root;
    }

    while (1) {
        if (root_p->key < node_p->key) {
            if (root_p->right == nullptr) {
                node_p->parent = root_p;
                root_p->right = node_p;
                break;
            } else {
                root_p = root_p->right;
            }
        } else {
            if (root_p->left == nullptr) {
                node_p->parent = root_p;
                root_p->left = node_p;
                break;
            } else {
                root_p = root_p->left;
            }
        }
    }

    if (root_p->color == RED) {
        rebalance_insert(node_p);
    }

    return *node_p;
}

template <typename T, typename U>
void Map<T, U>::inorder() {
    inorder_traversal(root);
}

template <typename T, typename U>
U& Map<T, U>::operator[](T key) {
    Node<T, U>* node = search_node(key);

    if (node == nullptr) {
        return insert(key, U()).value;
    }

    return node->value;
}

template <typename T, typename U>
int Map<T, U>::size() {
    return no_elements;
}

template <typename T, typename U>
int Map<T, U>::erase(T key) {
    is_found = true;
    remove_node(key);

    if (!is_found) {
        return 0;
    }

    no_elements--;
    return 1;
}

template <typename T, typename U>
void Map<T, U>::clear() {
    delete_postorder(root);
}

template <typename T, typename U>
bool Map<T, U>::empty() {
    return (root == nullptr);
}

#endif
