#pragma once
using namespace std;
class Tree
{
private:
	struct Node {
		Node* left;
		Node* right;
		Node* parent;
		int key;
		string data;
		bool color; // 0 - black 1 - red
	};

	Node* Root = NULL;

	Node* getBrother(Node* node) {
		if (node->parent->left == node)
			return node->parent->right;
		else
			return node->parent->left;
	}

	Node* newElem(Node* parent, int key, string data) {
		Node* temp = new Node;
		temp->parent = parent;
		temp->left = NULL;
		temp->right = NULL;
		temp->color = 1;
		temp->key = key;
		temp->data = data;
		return temp;
	}

	Node* add(int key, string data, Node* node) {
		if (key < node->key) {
			if (node->left == NULL) {
				Node* temp = newElem(node, key, data);
				node->left = temp;
				return temp;
			}
			else {
				return add(key, data, node->left);		
			}
		}
		else {
			if (node->right == NULL) {
				Node* temp = newElem(node, key, data);
				node->right = temp;
				return temp;
			}
			else
				return add(key, data, node->right);
		}
	}

	void balanced(Node* node) {
		if (node->parent == NULL)
			return;
		else if (node->parent->parent == NULL)
			return;
		Node* granded = node->parent->parent;
		Node* uncle;
		Node* dad;
		if (node->parent->parent->left != node->parent) { 
			uncle = node->parent->parent->left;
			dad = node->parent;
		}
		else {
			uncle = node->parent->parent->right;
			dad = node->parent;
		}
		if ((uncle == NULL || uncle->color == 0) && dad->color == 1) {
			if (granded->left == dad && dad->right == node) { //когда папа и дед в разных сторонах от корня
				node = smallLeftRotation(node);
				return bigRightRotation(node);
			}
			else if (granded->right == dad && dad->left == node) {
				node = smallRightRotation(node);
				return bigLeftRotation(node);
			}
			else if (granded->left == dad && dad->left == node) {//когда папа и дед на одной стороне
				return bigRightRotation(node);
			}
			else if (granded->right == dad && dad->right == node) {
				return bigLeftRotation(node);
			}
		}
		if (dad->color == 1 && uncle->color == 1) {
			repaint(node);
			balanced(node->parent->parent);
			return;
		}

	}

	void repaint(Node* node) {
		if (node->parent->parent != Root)
			node->parent->parent->color = !node->parent->parent->color;
		if(node->parent->parent->left != NULL)
			node->parent->parent->left->color = !node->parent->parent->left->color;
		if(node->parent->parent->right != NULL)
			node->parent->parent->right->color = !node->parent->parent->right->color;
		return;
	}

	/*
			p						x
		L		x		->		p		R
			  C	  R			  L	  C
	*/
	Node* smallLeftRotation(Node* node) { // node = x
		Node* temp = new Node;//переменная темп будет x в конечном случае
		temp->color = node->color;
		temp->key = node->key;
		temp->data = node->data;
		temp->parent = node->parent->parent; //запоминаем у x указатель на дедушку
		node->parent->parent->left == node->parent ? node->parent->parent->left = temp :
			node->parent->parent->right = temp;//у дедушки ставим указатель на темп
		temp->left = node->parent;//ставим x - p
		temp->left->parent = temp;//запоминаем указатель на родителя p - x
		temp->left->right = node->left;// p - С по правому поддереву
		if(temp->left->right != NULL)
			temp->left->right->parent = temp->left;//меняем у С указатель на родителей С - p
		temp->right = node->right;// x - R
		if(temp->right != NULL)
			temp->right->parent = temp;//R - x
		delete node;
		return temp->left;
	}

	/*
			p						x
		x		R		->		L		p
	  L	  C							 C     R
	*/
	Node* smallRightRotation(Node* node) {// node = x
		Node* temp = new Node;// temp будет x в конечном случае
		temp->color = node->color;
		temp->key = node->key;
		temp->data = node->data;
		temp->parent = node->parent->parent;//ставим указатель на дедушку
		node->parent->parent->left == node->parent ? node->parent->parent->left = temp :
			node->parent->parent->right = temp; //у дедушки ставим указатель на темп
		temp->right = node->parent; // x - p
		temp->right->parent = temp;// p - x
		temp->right->left = node->right; // p - C
		temp->right->left->parent = temp->right; // C - p
		temp->left = node->left;// x - L
		temp->left->parent = temp;// L - x
		delete node;
		return temp->right;
	}

	/*
					g									p
			p				u					x				g
		x		C		D		E	->		A		B		C		u
	  A   B														  D	  E
	  перекраска p и g
	*/
	void bigRightRotation(Node* node) {//node = x 
		Node* temp = new Node;//temp = p в конечном случае
		temp->color = !node->parent->color;//перекрашиваем p
		temp->key = node->parent->key;
		temp->data = node->parent->data;
		temp->parent = node->parent->parent->parent; // указатель p - предку
		if(node->parent->parent->parent != NULL)
			if (node->parent->parent->parent->left == node->parent->parent) // предка к p
				node->parent->parent->parent->left = temp;
			else
				node->parent->parent->parent->right = temp;
		if (node->parent->parent == Root)
			Root = temp;
		temp->right = node->parent->parent;// p - g
		temp->right->parent = temp;//g - p
		temp->right->color = !temp->right->color; //перекаршиваем g
		temp->right->left = node->parent->right;// g - c
		if(temp->right->left != NULL)
			temp->right->left->parent = temp->right;// c - g
		temp->left = node; // p - x 
		delete node->parent;
		temp->left->parent = temp;// x - p
	}
	/*
					g										p
			u				p			->			g				x	
		A		B		C		x				u		C		D		E
							  D	  E			  A   B
	 перекраска p и g
	*/
	void bigLeftRotation(Node* node) {
		Node* temp = new Node;//temp = p в конечном случае
		temp->key = node->parent->key;
		temp->data = node->parent->data;
		temp->color = !node->parent->color;//перекрашиваем p
		temp->parent = node->parent->parent->parent; // p к предкам
		if (node->parent->parent->parent != NULL)
			if(node->parent->parent->parent->left == node->parent->parent) // предка к p
				node->parent->parent->parent->left = temp;
			else
				node->parent->parent->parent->right = temp;
		if (node->parent->parent == Root)
			Root = temp;
		temp->left = node->parent->parent; //p - g
		temp->left->parent = temp;//g - p
		temp->left->color = !temp->left->color;//Перекаршиваем g
		temp->left->right = node->parent->left;//g - C
		if(temp->left->right != NULL)
			temp->left->right->parent = temp->left;//C - g
		temp->right = node;//p - x 
		delete node->parent;
		temp->right->parent = temp;//x - p
	}

	Node* searching(int key, Node* node) {
		if (node == NULL)
			return NULL;
		if (key == node->key)
			return node;
		if (key < node->key)
			return searching(key, node->left);
		else
			return searching(key, node->right);
	}

	void delete_case1(Node* node) {// проверка на корень
		if (node->parent != NULL) {
			delete_case2(node);
		}
	}

	void delete_case2(Node* node) {
		Node* brother = node->parent->left == node ? brother = node->parent->right : brother = node->parent->left;
		if (brother->color == 1) {//если красный брат
			if (node->parent->left == node) { //надо сделать большой левый поворот
				if (brother->right == NULL) {
					smallRightRotation(brother->left);
					bigLeftRotation(brother->right);
				}
				else
					bigLeftRotation(brother->right);
			}
			else {//а тут правый
				if (brother->left == NULL) {
					smallLeftRotation(brother->right);
					bigRightRotation(brother->left);
				}
				else
					bigRightRotation(brother->left);
			}
		}
		delete_case3(node);
	}

	void delete_case3(Node* node) {
		Node* brother = node->parent->left == node ? brother = node->parent->right : brother = node->parent->left;
		if (node->parent->color == 0 && brother->color == 0)
			if ((brother->left == NULL || brother->left->color == 0) && (brother->right == NULL || brother->right->color == 0)) {
				brother->color = 1;
				delete_case1(node->parent);
				return;
			}
		delete_case4(node);
	}

	void delete_case4(Node* node) {
		Node* brother = getBrother(node);
		if (brother->color == 0 && brother->parent->color == 1) {
			if ((brother->left == NULL || brother->left == 0) && (brother->right == NULL || brother->right == 0)) {
				brother->color = !brother->color;
				brother->parent->color = !brother->parent->color;
				return;
			}
		}
		delete_case5(node);
	}

	void delete_case5(Node* node) {
		Node* brother = getBrother(node);
		if (brother->color == 0) {
			if (brother->left != NULL) {
				if (node->parent->left == node && brother->left->color == 1 && (brother->right == NULL || brother->right->color == 0)) {
					brother->color = !brother->color;
					brother->left->color = !brother->left->color;
					smallRightRotation(brother->left);
				}
			}
			else if(brother->right != NULL)
				if (node->parent->right == node && brother->right->color == 1 && ( brother->left == NULL || brother->left->color == 0)) {
					brother->color = !brother->color;
					brother->right->color = !brother->right->color;
					smallLeftRotation(brother->right);
				}
		}
		delete_case6(node);
	}

	void delete_case6(Node* node) {
		Node* brother = getBrother(node);

		if (node->parent->left == node) {
			if (brother->right == NULL) {
				smallRightRotation(brother->left);
				bigLeftRotation(brother->right);
				Root->color = 0;
			}
			else {
				//brother->right->color = 0;
				bigLeftRotation(brother->right);
				Root->color = 0;
			}
		}
		else {//а тут правый
			if (brother->left == NULL) {
				smallLeftRotation(brother->right);
				bigRightRotation(brother->left);
				Root->color = 0;
			}
			else {
				//brother->left->color = 0;
				bigRightRotation(brother->left);
				Root->color = 0;
			}
		}
	}

	Node* min(Node* node) {
		if (node->left)
			return min(node->left);
		else
			return node;
	}

	void NLR(Node* node) {
		if (node != NULL) {
			cout << node->key << " " << node->data << " ";
			NLR(node->left);
			NLR(node->right);
		}
	}

	void LNR(Node* node) {
		if (node != NULL) {
			LNR(node->left);
			cout << node->key << " " << node->data << " ";
			LNR(node->right);
		}
	}

	void LRN(Node* node) {
		if (node != NULL) {
			LRN(node->left);
			LRN(node->right);
			cout << node->key << " " << node->data << " ";
		}
	}

	void addRoot(int key, string data) {
		Root = new Node;
		Root->parent = NULL;
		Root->left = NULL;
		Root->right = NULL;
		Root->color = 0;
		Root->key = key;
		Root->data = data;

	}

public:
	Tree() {
	}

	void NLR() {
		if (Root != NULL) {
			cout << Root->key << " " << Root->data << " ";
			NLR(Root->left);
			NLR(Root->right);
		}
	}

	void LNR() {
		if (Root != NULL) {
			LNR(Root->left);
			cout << Root->key << " " << Root->data << " ";
			LNR(Root->right);
		}
	}

	void LRN() {
		if (Root != NULL) {
			LRN(Root->left);
			LRN(Root->right);
			cout << Root->key <<" " << Root->data << " ";
		}
	}



	void Insert(int key, string data) {
		if (Root == NULL) {
			addRoot(key, data);
		}
		else {
			Node* node = add(key, data, Root);
			balanced(node);
		}
		
	}

	string Search(int key) {
		Node* node = searching(key, Root);
		return node != NULL ? node->data : "Not Found";
	}

	void Delete(int key) {
		Node* node = searching(key, Root);
		Node* child = node->left == NULL ? child = node->right : child = node->left;
		if(!node)
			return;
		if (node->left && node->right) {//Если есть 2 ребёнка
			Node* temp = min(node->right);
			node->key = temp->key;
			node->data = temp->data;
			node = temp;
		}
		if (node == Root) {
			Root = child;
			if (Root == NULL)
				return;
			child->parent = NULL;
			if (Root->color == 1)
				Root->color = !Root->color;
			return;
		}
		if (!node->left && !node->right) {
			if(node->color == 0)
				delete_case1(node);
			node->parent->left == node ? node->parent->left = NULL : node->parent->right = NULL;
			delete node;
			return;
		}
		if (node->parent->left == node) {
			node->parent->left = child;
			child->parent = node->parent;
		}
		else {
			node->parent->right = child;
			child->parent = node->parent;
		}
		if (node->color == 0) {
			if (child->color == 1)
				child->color = 0;
			else
				delete_case1(child);
		}
		delete node;
	}
};

