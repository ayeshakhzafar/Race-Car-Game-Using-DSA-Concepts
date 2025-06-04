//Ayesha_Khalid_22i2678
#ifndef HEADER_H
#define HEADER_H
#include<iostream>
#include<vector>
#include<string>
using namespace std;

// structure to print board
struct BoardElement
{
    static int instanceCounter;
    
    int elementID;
    int mass;
    int strength;
    char symbol;

    BoardElement(int s, char sym)
    {
        elementID = instanceCounter++;
        strength = s;
        symbol = sym;

        switch (sym) {
            case '#':
            case '|':
            case 'X':
                mass = 100 + (-1 * strength);
                break;
            case '$':
            case '\xE2':
            case '!':
                mass = 100 - strength;
                break;
            case '*':
                mass = 100;
                break;
            default:
                mass = 0;
                break;
        }
    }
};


int BoardElement::instanceCounter = 0;


struct Store
    {
        BoardElement* element;
        Store* next;

        Store(BoardElement* elem)
            : element(elem), next(nullptr)
        {
        }
    };

// Queue
class ElementQueue
{
    

    Store* front;
    Store* rear;

public:
    ElementQueue()
        : front(nullptr), rear(nullptr)
    {
    }

    BoardElement* Front()
    {
        if (IsEmpty())
        {
            return nullptr;
        }
        else
        {
            return front->element;
        }
    }

    bool IsEmpty()
    {
       if (front == NULL)
		{
			return 1;
		}
		return 0;
    }

    void Enqueue(BoardElement* data)
    {
        Store* newNode = new Store(data);
        if (IsEmpty())
        {
            front = rear = newNode;
        }
        rear->next = newNode;
        rear = rear->next;
    }

    void Dequeue()
    {
        if (IsEmpty())
        {
            return;
        }
        Store* toDelete = front;
        front = front->next;
        delete toDelete;
    }

    int Size()
    {
        Store* traverse = front;
        int count = 0;
        while (traverse != nullptr)
        {
            count++;
            traverse = traverse->next;
        }
        return count;
    }
};

// class

struct PowerUpItem
{
        BoardElement* element;
        PowerUpItem* next;

        PowerUpItem(BoardElement* elem)
            : element(elem), next(nullptr)
        {
        }
};
class PowerUpCollection
{  
    PowerUpItem* head;

public:
    PowerUpCollection()
        : head(nullptr)
    {
    }

    void Insert(BoardElement* element)
    {
        PowerUpItem* newItem = new PowerUpItem(element);
        if (head == nullptr)
        {
            head = newItem;
            return;
        }

        PowerUpItem* current = head;
        while (current->next != nullptr)
        {
            current = current->next;
        }

        current->next = newItem;
    }

    void Display()
    {
        PowerUpItem* current = head;
        while (current != nullptr)
        {
            cout << current->element->symbol << " ";
            current = current->next;
        }
    }
};






class CustomLinkedList
{
public:
    struct ListNode
    {
        BoardElement* data;
        ListNode* next;

        ListNode()
            : data(nullptr), next(nullptr)
        {
        }

        ListNode(BoardElement* elem)
            : data(elem), next(nullptr)
        {
        }
    };

private:
    ListNode* head;

public:
    CustomLinkedList()
        : head(nullptr)
    {
    }

    ListNode* GetHead()
    {
        return head;
    }


    void Insert(BoardElement* element)
    {
        if (element == nullptr)
        {
            return;
        }

        ListNode* newNode = new ListNode(element);
        if (head == nullptr)
        {
            head = newNode;
            return;
        }

        ListNode* current = head;
        while (current->next != nullptr)
        {
            current = current->next;
        }
        current->next = newNode;
    }

void Display() {
    ListNode* temp = head;
    cout << "| ";

    while (temp != nullptr) {
        switch (temp->data->symbol) {
            case '#':
            case '|':
            case 'X':
                cout << temp->data->symbol << " ";
                temp = temp->next;
                break;
            case '.':
            case 'T':
                cout << temp->data->symbol << " ";
                temp = temp->next;
                break;
            case '\xE2':
            case '$':
            case '!':
                cout << temp->data->symbol << " ";
                temp = temp->next;
                break;
            case 'C':
            case 'E':
                cout << temp->data->symbol << " ";
                temp = temp->next;
                break;
            default:
                cout << temp->data->symbol << " ";
                temp = temp->next;
                break;
        }
    }

    cout << '|';
}


};


bool TurnRight(CustomLinkedList*& graph, char targetCharacter, int size, PowerUpCollection& powerUps, int& obstacleCount) {
    for (int i = 0; i < size; ++i) {
        CustomLinkedList::ListNode* currentNode = graph[i].GetHead();

        while (currentNode != nullptr) {
            if (currentNode->data->symbol == targetCharacter) {
                CustomLinkedList::ListNode* nextNode = currentNode->next;

                if (nextNode != nullptr) {
                    char nextSymbol = nextNode->data->symbol;

                    if (nextSymbol == '#' || nextSymbol == '|' || nextSymbol == 'X') {
                        obstacleCount++;
                    } else if (nextSymbol == '\xE2' || nextSymbol == '$' || nextSymbol == '!') {
                        BoardElement* temp = new BoardElement(nextNode->data->strength, nextSymbol);
                        powerUps.Insert(temp);
                        nextNode->data->symbol = '*';
                    } else if (nextSymbol == 'E') {
                        return true;
                    }

                    nextNode->data->symbol = currentNode->data->symbol;
                    currentNode->data->symbol = nextSymbol;

                    currentNode = nextNode;
                }
            }

            currentNode = currentNode->next;
        }
    }

    return false;
}


bool MoveBackward(CustomLinkedList*& graph, char targetCharacter, int size, PowerUpCollection& powerUps, int& obstacleCount) {
    for (int i = size - 1; i > 0; --i) {
        CustomLinkedList::ListNode* currentNode = graph[i].GetHead();
        CustomLinkedList::ListNode* upperNode = graph[i - 1].GetHead();
        bool foundTarget = false;

        while (currentNode != nullptr && upperNode != nullptr) {
            if (currentNode->data->symbol == targetCharacter) {
                foundTarget = true;

                if (upperNode->data->symbol == '#' || upperNode->data->symbol == '|' || upperNode->data->symbol == 'X') {
                    obstacleCount++;
                } else if (upperNode->data->symbol == '\xE2' || upperNode->data->symbol == '$' || upperNode->data->symbol == '!') {
                    BoardElement* temp = new BoardElement(upperNode->data->strength, upperNode->data->symbol);
                    powerUps.Insert(temp);
                    upperNode->data->symbol = '*';
                } else if (upperNode->data->symbol == 'E') {
                    return true;
                }

                char store = upperNode->data->symbol;
                upperNode->data->symbol = currentNode->data->symbol;
                currentNode->data->symbol = store;
            }

            currentNode = currentNode->next;
            upperNode = upperNode->next;
        }

        if (foundTarget) {
            break;
        }
    }

    return false;
}

bool MoveUp(CustomLinkedList*& graph, char targetCharacter, int size, PowerUpCollection& powerUps, int& obstacleCount) {
    for (int i = 0; i < size; ++i) {
        CustomLinkedList::ListNode* currentNode = graph[i].GetHead();
        CustomLinkedList::ListNode* upperNode = nullptr;

        if (i > 0) {
            upperNode = graph[i - 1].GetHead();
        }

        while (currentNode != nullptr && upperNode != nullptr) {
            if (currentNode->data->symbol == targetCharacter) {
                if (upperNode->data->symbol == '#' || upperNode->data->symbol == '|' || upperNode->data->symbol == 'X') {
                    obstacleCount++;
                } else if (upperNode->data->symbol == '\xE2' || upperNode->data->symbol == '$' || upperNode->data->symbol == '!') {
                    BoardElement* temp = new BoardElement(upperNode->data->strength, upperNode->data->symbol);
                    powerUps.Insert(temp);
                    upperNode->data->symbol = '*';
                } else if (upperNode->data->symbol == 'E') {
                    return true;
                }

                char store = upperNode->data->symbol;
                upperNode->data->symbol = currentNode->data->symbol;
                currentNode->data->symbol = store;
            }

            currentNode = currentNode->next;
            if (upperNode != nullptr) {
                upperNode = upperNode->next;
            }
        }
    }

    return false;
}

bool TurnLeft(CustomLinkedList*& graph, char targetCharacter, int size, PowerUpCollection& powerUps, int& obstacleCount) {
    for (int i = 0; i < size; ++i) {
        CustomLinkedList::ListNode* currentNode = graph[i].GetHead();

        while (currentNode != nullptr && currentNode->next != nullptr) {
            if (currentNode->next->data->symbol == targetCharacter) {
                if (currentNode->data->symbol == '#' || currentNode->data->symbol == '|' || currentNode->data->symbol == 'X') {
                    obstacleCount++;
                } else if (currentNode->data->symbol == '\xE2' || currentNode->data->symbol == '$' || currentNode->data->symbol == '!') {
                    BoardElement* temp = new BoardElement(currentNode->data->strength, currentNode->data->symbol);
                    powerUps.Insert(temp);
                    currentNode->data->symbol = '*';
                } else if (currentNode->data->symbol == 'E' && currentNode->next->data->symbol == 'C') {
                    return true;
                }

                char store = currentNode->next->data->symbol;
                currentNode->next->data->symbol = currentNode->data->symbol;
                currentNode->data->symbol = store;
            }

            currentNode = currentNode->next;
        }
    }

    return false;
}


// function to display graph
void DisplayGraph(CustomLinkedList* graphArray, int size)
{
    cout << endl;

    for (int i = 0; i < size; i++)
    {
        graphArray[i].Display();
        cout << endl;
    }

    cout << endl;
}




// Graph class
class CustomGraph
{
    int numVertices;
    CustomLinkedList* adjacencyList;

public:
    CustomGraph(int vertices)
        : numVertices(vertices), adjacencyList(new CustomLinkedList[vertices])
    {
    }

    void AddEdge(int vertex, BoardElement* element)
    {
        adjacencyList[vertex].Insert(element);
    }


    void Display()
    {
        for (int i = 0; i < numVertices; ++i)
        {
            CustomLinkedList::ListNode* traverse = adjacencyList[i].GetHead();

            while (traverse != nullptr)
            {
                traverse = traverse->next;
            }

            cout << endl;
        }
    }
};


#endif
