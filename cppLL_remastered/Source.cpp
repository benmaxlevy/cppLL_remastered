#include <cstdlib>
#include <iostream>

using namespace std;

typedef struct Node{
	//set value of the node to 0
	int value = 0;

	//initialize value of the pointer to the next node to nullptr
	Node* next = nullptr;

	//NOTE: all of these contructors will be overloaded by the ":"

	//original contstructor - calls the next constructor
	Node () : Node(0) {
			
	}

	//constructor that takes in the value (an int), and calls the next contructor
	Node(int value) : Node(value, nullptr)  {

	}
	
	//final constructor
	Node(int value, Node* next) {
		//set the value of this node to the value passed
		this->value = value;
		//set the value of the pointer to the next node to the pointer passed
		this->next = next;
	}

	//destructor
	~Node() {
		//delete the pointer to the next node
		if (next != nullptr) {
			delete this->next;
		}
	}
} Node;

class LinkedList {
private:
	Node* head;
	
public:

	//constructor
	LinkedList() {
		this->head = nullptr;
	}

	//destructor
	~LinkedList() {
		delete head;
	}

	//make a node (returns pointer to a node)
	static Node* createNode() {
		return new Node;
	}

	//create a new node
	int add(int value) {

		//if the pointer to the head node is null, create it!
		if (this->head == nullptr) {
			this->head = createNode();
			this->head->value = value;
			this->head->next = nullptr;

			return 0;
		}
		//if it's not, wait until we find the end of the ll, and then create the pointer to the next node.
		else {
			//make a reference point
			Node* currentNode = this->head;

			while (currentNode->next != nullptr) {
				currentNode = currentNode->next;
			}
			currentNode->next = createNode();
			currentNode->next->value = value;
			currentNode->next->next = nullptr;

			return 0;
		}
	}

	//find value of node at specified index
	int find(int index) {
		
		//make a reference point
		Node* currentNode = this->head;

		for (int i = 0; i < index; i++) {
			//check if the pointer to the next node is nullptr
			if (currentNode->next == nullptr) {
				//invalid! (cannot reach the index specified).
				return 1;
			}
			else {
				currentNode = currentNode->next;
			}
		}

		return currentNode->value;
	}

	//add node after index
	int addAfter(int index, int value) {

	}
};


int main() {
	auto ll = new LinkedList;
	ll->add(5);
	ll->add(6);
	ll->add(50);

}
