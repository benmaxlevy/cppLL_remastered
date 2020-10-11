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
	static Node* createNode(const int value = 0, Node* next = nullptr) {
		return new Node(value, next);
	}

	//create a new node
	int add(const int value) {

		//if the pointer to the head node is null, create it!
		if (head == nullptr) {
			head = createNode(value);

			return 0;
		}
		//if it's not, wait until we find the end of the ll, and then create the pointer to the next node.
		else {
			//make a reference point
			auto* current_node = head;

			while (current_node->next != nullptr) {
				current_node = current_node->next;
			}
			current_node->next = createNode();
			current_node->next->value = value;
			current_node->next->next = nullptr;

			return 0;
		}
	}

	//find node, and return a pointer to that node
	Node* find(const int index) {
		auto* current_node = head;

		for (auto i = 0; i < index; i++)
		{
			if (current_node->next == nullptr)
			{
				//check if the pointer to the next node is nullptr
				return nullptr;
			}
			else
			{
				current_node = current_node->next;
			}
		}

		//return the node at the specified index
		return current_node;

	}
	
	//find value of node at specified index
	int findValue(const int index) {
		const auto* found_node = this->find(index);

		//check if the found node is null or not
		if(found_node == nullptr)
		{
			return 1; //error
		} else
		{
			return found_node->value;	
		}
		
	}

	//add node after index
	int addAfter(const int value, const int index)
	{
		//store the head node for context
		auto* current_node = head;

		for(int i = 0; i < index; i++)
		{
			if(current_node->next == nullptr)
			{
				return 1; //return error
			}
			else
			{
				current_node = current_node->next;
			}
		}

		//check if the next node (of the node that we want to add after) is a nullptr
		if(current_node->next == nullptr) 
		{
			current_node->next = createNode(value);
			return 0;
		} else //if the next node exists
		{
			//save the pointer to the next node, so that we can insert a node before, and "make it seamless"
			auto* to_save = current_node->next;
			
			current_node->next = createNode(value, to_save);

			return 0; //success! 
		}
	}

	int remove(const int index)
	{
		//store the head of this ll, so that we can get the node before the passed index 
		auto* before_to_remove = head;

		for(int i = 0; i < index-1; i++)
		{
			if(before_to_remove->next == nullptr)
			{
				return 1; //error! (unable to reach the node at the index-1)
			}
			else
			{
				before_to_remove = before_to_remove->next;
			}
		}

		//make sure that the node that we want to remove actually exists!
		if(before_to_remove->next == nullptr)
		{
			return 1; //the node that we want to remove is a nullptr!
		} else
		{
			if(before_to_remove->next->next == nullptr) //if there's nothing after what we want to remove
			{
				delete before_to_remove->next; //get rid of the node we want to remove!
				before_to_remove->next = nullptr;

				return 0;
			} else
			{
				auto* const to_remove = before_to_remove->next; //store the node we want to remove
				before_to_remove->next = before_to_remove->next->next; //set the pointer to the next node to the node after the one we want to remove.
				
				//delete to_remove;

				return 0;
			}
		}
	}
};


int main() {
	auto* ll = new LinkedList;
	ll->add(5);
	ll->add(6);
	ll->add(50);

	ll->remove(1);
	cout << ll->findValue(1) << endl;
}
