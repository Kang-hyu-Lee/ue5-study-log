#include <iostream>
#include <string>
using namespace std;

struct InventoryItem
{
    string Name;
    int Quantity;
    float Value;
};

struct Node
{
    InventoryItem Item;
    Node* Next;

    Node(const InventoryItem& NewItem, Node* Next) : Item(NewItem), Next(Next) {}
};

class Inventory
{
    private: 
    Node* Head = nullptr;
    Node* Tail = nullptr;

    public:

    ~Inventory()
    {
        Node* Current = Head;
        while(Head != nullptr)
        {  
            Head = Head->Next;
            delete Current;
            Current = Head;
        }
        Tail = nullptr;
        cout << "Inventory destroyed" << endl;
    }
    
    void AddItem(const InventoryItem& NewItem)
    {
        Node* NewNode = new Node(NewItem, nullptr);

        if(Head == nullptr)
        {
            Head = NewNode;
            Tail = NewNode;
            return;
        }

        Tail->Next = NewNode;
        Tail = NewNode;
    }

    void RemoveItem(const std::string& Name)
    {
        if(Head == nullptr)
        {
            cout << "Inventory is Empty" << endl;
            return;
        }
        
        Node* Tracker = Head;

        if(Tracker->Item.Name == Name)
        {
            if(Tracker->Next == nullptr)
            {
                Head = nullptr;
                Tail = nullptr;
                delete Tracker;
                cout << "Inventory is now empty" << endl;
                return;
            }

            Node*Temp = Tracker;
            Tracker = Tracker->Next;
            Head = Tracker;
            delete Temp;
            return;
        }
        
        Node* Prev = Head;
        Tracker = Head->Next;

        while(Tracker != nullptr)
        {
            if(Tracker->Item.Name == Name) 
            {
                if(Tracker->Next == nullptr)
                {
                    Tail = Prev;
                    Prev->Next = nullptr;
                    delete Tracker;
                    return;
                }
                Prev->Next = Tracker->Next;
                delete Tracker;
                return;
            }
            Tracker = Tracker->Next;
            Prev = Prev->Next;
        }
        cout << "Item not found" << endl;
        return;
    }

    const InventoryItem* FindItem(const std::string& Name) const
    {
        if(Head == nullptr)
        {
            cout << "Inventory is Empty" << endl;
            return nullptr;
        }

        Node* Finder = Head;
        while(Finder != nullptr)
        {
            if(Finder->Item.Name == Name)
            {
                cout << "Item found!: " << Finder->Item.Name << endl;
                return &Finder->Item;
            }
            Finder = Finder->Next;
        }
        cout << "Item not found" << endl;
        return nullptr;
    }

    void PrintInventory() const
    {
        if(Head == nullptr)
        {
            cout << "Inventory is Empty" << endl;
            return;
        }
        Node* Tracker = Head;
        while(Tracker != nullptr)
        {
            cout << "Name: " << Tracker->Item.Name << " Quantity: " << Tracker->Item.Quantity << " Value: " << Tracker->Item.Value << endl;
            Tracker = Tracker->Next;
        }
    }

    float TotalValue() const
    {
        if(Head == nullptr)
        {
            cout << "Inventory is Empty" << endl;
            return 0;
        }
        Node* Tracker = Head;
        float TotalCount = 0;
        while(Tracker != nullptr)
        {
            TotalCount += Tracker->Item.Value;
            Tracker = Tracker->Next;
        }
        return TotalCount;
    }
};

int main()
{
    InventoryItem Sword = {"Sword", 1, 10.0f};
    InventoryItem Bow = {"Bow", 1, 15.0f};
    InventoryItem Arrow = {"Arrow", 20, 5.0f};

    Inventory MyInventory;
    MyInventory.AddItem(Sword);
    MyInventory.AddItem(Bow);
    MyInventory.AddItem(Arrow);

    MyInventory.PrintInventory();

    cout << "Inventory total value is: " << MyInventory.TotalValue() << endl;

    MyInventory.FindItem("Bow");

    MyInventory.RemoveItem("Sword");
    MyInventory.PrintInventory();

    cout << "Inventory total value is: " << MyInventory.TotalValue() << endl;

    return 0;
}