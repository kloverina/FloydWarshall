#pragma once
#include <iostream>
#include <stdexcept>
using namespace std;

template<class T>
class List
{
private:
	struct Node
	{
		T value;
		Node* next;
		Node* prev;
		Node () { }
		Node(T value, Node* next_element, Node* prev_element)
		{
			this->value = value;
			this->next = next_element;
			this->prev = prev_element;
		}

		~Node()
		{
			next = nullptr;
			prev = nullptr;
		}
	};

	Node* Top;
	Node* Back;
	size_t size; 

public:
	//constructor of the list, creates an empty list
	List()
	{
		Top = nullptr;
		Back = nullptr;
		size = 0;
	}

	//creates list with size ' size' filled with 'value'
	List(size_t size, T value)
	{
		Top = nullptr;
		Back = nullptr;
		size = 0;
		for (size_t i = 0; i < size; ++i)
			push_back(value);
	}

	//copy constructor
	List(const List& lst)
	{
		this->size = lst.size;
		if (size > 0)
		{
			Top = new Node(lst.Top->value, nullptr, nullptr);

			if (size > 1)
			{
				Node* there = lst.Top->next;
				Node* here = Top;
				for (size_t i = 0; i < size - 2; ++i)
				{
					auto temp = new Node(there->value, nullptr, here);
					here->next = temp;
					there = there->next;
					here = temp;
				}

				Back = new Node(lst.Back->value, nullptr, here);
				here->next = Back;
			}
			else
				Back = Top;
		}
	}

	//move constructor
	List(List&& lst) noexcept
	{
		this->size = lst.size;
		if (size > 0)
		{
			Top = new Node(lst.Top->value, nullptr, nullptr);

			if (size > 1)
			{
				Node* there = lst.Top->next;
				Node* here = Top;
				for (size_t i = 0; i < size - 2; ++i)
				{
					Node* temp = new Node(there->value, nullptr, here);
					here->next = temp;
					there = there->next;
					here = temp;
				}

				Back = new Node(lst.Back->value, nullptr, here);
				here->next = Back;
			}
			else
				Back = Top;

			lst.clear();
		}
	}

	//copy assignment constructor
	List& operator=(const List& lst)
	{
		if (this != &lst)
		{
			clear();
			size = lst.size;

			if (size > 0)
			{
				Top = new Node(lst.Top->value, nullptr, nullptr);

				if (size > 1)
				{
					Node* there = lst.Top->next;
					Node* here = Top;
					for (size_t i = 0; i < size - 2; ++i)
					{
						Node* temp = new Node(there->value, nullptr, here);
						here->next = temp;
						there = there->next;
						here = temp;
					}

					Back = new Node(lst.Back->value, nullptr, here);
					here->next = Back;
				}
				else
					Back = Top;
			}
		}

		return *this;
	}

	//move assignment constructor
	List& operator=(List&& lst) noexcept
	{
		if (this != &lst)
		{
			clear();
			size = lst.size;

			if (size > 0)
			{
				Top = new Node(lst.Top->value, nullptr, nullptr);

				if (size > 1)
				{
					Node* there = lst.Top->next;
					Node* here = Top;
					for (size_t i = 0; i < size - 2; ++i)
					{
						auto temp = new Node(there->value, nullptr, here);
						here->next = temp;
						there = there->next;
						here = temp;
					}

					Back = new Node(lst.Back->value, nullptr, here);
					here->next = Back;
				}
				else
					Back = Top;

				lst.clear();
			}

		}

		return *this;
	}

	~List()
	{
		clear();
	}

	//deletes all values in the list
	void clear()
	{
		//does nothing if the list is empty
		if (!isEmpty())
		{
			Node* current = Top;
			do
			{
				current = current->next;
				delete Top;
				Top = current;
				size--;
			} while (current != nullptr);

		}
	}
	//checks if the list has elements
	bool isEmpty() const
	{
		if (size == 0)
			return true;

		return false;
	}

	//inserts value at the back of the list
	void push_back(T value)
	{
		if (!isEmpty())
		{
			auto current = new Node(value, nullptr, Back);
			Back->next = current;
			Back = current;
		}
		else
		{
			Top = new Node(value, nullptr, nullptr);
			Back = Top;
		}
		size++;
	}

	//inserts value at the top of the list
	void push_front(T value)
	{
		if (!isEmpty())
		{
			auto current = new Node(value, Top, nullptr);
			Top->prev = current;
			Top = current;
		}
		else
		{
			Top = new Node(value, nullptr, nullptr);
			Back = Top;
		}
		size++;
	}

	//inserts a list to the beginning
	void push_front(List& list)
	{
		if (!isEmpty() && !list.isEmpty())
		{
			for (size_t i = 0; i < list.getSize(); ++i)
				insert(list.at(i), i);
		}
		else
			throw std::out_of_range("Error: Can not push into empty list!");
	}


	//deletes last value
	void pop_back()
	{
		Node* current;
		if (size > 1)
		{
			current = Back->prev;
			delete Back;
			current->next = nullptr;
			Back = current;

			size--;
		}
		else if (size == 1)
		{
			delete Back;
			Top = nullptr;
			Back = nullptr;
			current = nullptr;
			size = 0;
		}
	}

	//deletes first value
	void pop_front()
	{
		Node* current;
		if (size > 1)
		{
			current = Top->next;
			delete Top;
			current->prev = nullptr;
			Top = current;

			size--;
		}
		else if (size == 1)
		{
			delete Back;
			Top = nullptr;
			Back = nullptr;
			current = nullptr;
			size = 0;
		}
	}

	//inserts value 'value' at position 'index'
	void insert(T value, const size_t index)
	{
		if (index <= size && index >= 0)
		{
			if (index == 0) 
				push_front(value);
			else if (index == size) 
				push_back(value);
			else
			{
				Node* current;
				if (index <= (size - 1) / 2)
				{
					current = Top;
					for (size_t i = 0; i < index; ++i)
						current = current->next;

					Node* temp = new Node(value, current, current->prev);
					current->prev->next = temp;
					current->prev = temp;
					current = temp;
				}
				else if (index > (size - 1) / 2)
				{
					current = Back;
					for (auto i = size - 1; i > index; --i)
						current = current->prev;

					Node* temp = new Node(value, current, current->prev);

					current->prev->next = temp;
					current->prev = temp;
					current = temp;
				}

				size++;
			}
		}
		else
			throw std::out_of_range("Error: invalid index!");
	}

	//gets the value at position 'index'
	T at(const size_t index) const
	{
		if (index < size && index >= 0)
		{
			if (index == 0) 
				return Top->value;

			if (index == size - 1) 
				return Back->value;

			Node* current;

			if (index <= (size - 1) / 2)
			{
				current = Top;
				for (size_t i = 0; i < index; ++i)
					current = current->next;

				return current->value;
			}

			if (index > (size - 1) / 2)
			{
				current = Back;
				for (auto i = size - 1; i > index; --i)
					current = current->prev;

				return current->value;
			}

		}
		else
			throw std::out_of_range("Error: invalid index!");
	}

	//deletes value at position 'index'
	void remove(const size_t index)
	{
		//checks index, throws an exception if index is wrong
		if (index < size && index >= 0)
		{
			if (index == 0) 
				pop_front();
			else if (index == size - 1)
				pop_back(); 
			else
			{
				
				Node* current;
				if (index <= (size - 1) / 2)
				{
					current = Top;

					for (size_t i = 0; i < index; ++i)
						current = current->next;

					Node* temp = current->next;
					current->prev->next = temp;
					temp->prev = current->prev;

					delete current;
				}
				else if (index > (size - 1) / 2)
				{
					current = Back;

					for (auto i = size - 1; i > index; --i)
						current = current->prev;

					Node* temp = current->prev;
					current->next->prev = temp;
					temp->next = current->next;

					delete current;
				}
				size--;
			}
		}
		else
			throw std::out_of_range("Error: invalid index!");
	}

	//returns size of the list
	size_t get_size() const
	{
		return size;
	}

	//prints all values to the console
	void print_to_console() const
	{
		Node* current = Top;

		for (size_t i = 0; i < size; ++i)
		{
			cout << current->value << endl;
			current = current->next;
		}
	}

	//finds index of the element, if elements isn't at the list returns -1
	int find(T element) const
	{
		Node* current = Top;

		for (size_t index = 0; index < size; index++)
		{
			if (current->value == element)
				return index;

			current = current->next;
		}

		return -1;
	}

	//checks if the element is in the list
	bool contains(T element) const
	{
		Node* current = Top;

		while (current != nullptr)
		{
			if (current->value == element)
				return true;

			current = current->next;
		}

		return false;
	}

	

	//sets value 'value' for the element at position 'index'
	void set(const size_t index, T value)
	{
		if (index < size && index >= 0)
		{
			if (index == 0) 
				Top->value = value;
			else if (index == size - 1) 
				Back->value = value;
			else
			{
				Node* current;
				if (index <= (size - 1) / 2)
				{
					current = Top;
					for (size_t i = 0; i < index; ++i)
						current = current->next;

					current->value = value;
				}
				else if (index > (size - 1) / 2)
				{
					current = Back;
					for (auto i = size - 1; i > index; --i)
						current = current->prev;

					current->value = value;
				}
			}
		}
		else
			throw std::out_of_range("Error: invalid index!");
	}

};
