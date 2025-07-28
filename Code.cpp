#include <iostream>
#include <string>
using namespace std;

// Structure for inventory item
struct Item {
    int item_id;
    string name;
    int quantity;
    float price;
    Item* next;
};

class Inventory {
private:
    Item* head;
    float totalSales;

public:
    Inventory() {
        head = nullptr;
        totalSales = 0;
    }

    // Add new item
    void addItem(int id, string name, int qty, float price) {
        Item* newItem = new Item;
        newItem->item_id = id;
        newItem->name = name;
        newItem->quantity = qty;
        newItem->price = price;
        newItem->next = head;
        head = newItem;
        cout << "\nItem added successfully.\n";
    }

    // Search item by ID
    Item* searchItemById(int id) {
        Item* current = head;
        while (current != nullptr) {
            if (current->item_id == id) {
                return current;
            }
            current = current->next;
        }
        return nullptr;
    }

    // Update quantity
    void updateQuantity(int id, int newQty) {
        Item* item = searchItemById(id);
        if (item != nullptr) {
            item->quantity = newQty;
            cout << "\nQuantity updated successfully.\n";
        }
        else {
            cout << "\nItem not found.\n";
        }
    }

    // Delete item
    void deleteItem(int id) {
        Item* current = head;
        Item* prev = nullptr;
        while (current != nullptr && current->item_id != id) {
            prev = current;
            current = current->next;
        }
        if (current == nullptr) {
            cout << "\nItem not found.\n";
            return;
        }
        if (prev == nullptr) {
            head = current->next;
        }
        else {
            prev->next = current->next;
        }
        delete current;
        cout << "\nItem deleted successfully.\n";
    }

    // Display inventory 
    void displayInventory() {
        if (head == nullptr) {
            cout << "\nInventory is empty.\n";
            return;
        }

        cout << "\nInventory List:\n";
        cout << "------------------------------------------------------\n";
        cout << "ID\tName\t\tQuantity\tPrice\n";
        cout << "------------------------------------------------------\n";

        Item* current = head;
        while (current != nullptr) {
            cout << current->item_id << "\t";

           
            cout << current->name;
            int spaces = 16 - current->name.length();
            for (int i = 0; i < spaces; i++) cout << " ";

            cout << current->quantity << "\t\t";
            cout << current->price << "\n";

            current = current->next;
        }
        cout << "------------------------------------------------------\n";
    }

    // Count total items
    void countTotalItems() {
        int count = 0;
        Item* current = head;
        while (current != nullptr) {
            count++;
            current = current->next;
        }
        cout << "\nTotal number of items: " << count << "\n";
    }

    // Calculate total inventory value 
    void calculateInventoryValue() {
        float total = 0;
        Item* current = head;
        while (current != nullptr) {
            total += current->quantity * current->price;
            current = current->next;
        }

        int rupees = total;
        float paisa = (total - rupees) * 100;
        cout << "\nTotal inventory value: Rs. " << rupees << ".";
        if ((int)paisa < 10) cout << "0";
        cout << (int)paisa << "\n";
    }

    // Sell item
    void sellItem(int id, int qtyToSell) {
        Item* item = searchItemById(id);
        if (item == nullptr) {
            cout << "\nItem not found.\n";
            return;
        }
        if (item->quantity < qtyToSell) {
            cout << "\nNot enough stock to complete the sale.\n";
            return;
        }

        item->quantity -= qtyToSell;
        float saleAmount = qtyToSell * item->price;
        totalSales += saleAmount;

        int rupees = saleAmount;
        float paisa = (saleAmount - rupees) * 100;

        cout << "\nSale completed. Rs. " << rupees << ".";
        if ((int)paisa < 10) cout << "0";
        cout << (int)paisa << " added to daily sales.\n";
    }

    // Show total sales 
    void showTotalSales() {
        int rupees = totalSales;
        float paisa = (totalSales - rupees) * 100;

        cout << "\nTotal sales for the day: Rs. " << rupees << ".";
        if ((int)paisa < 10) cout << "0";
        cout << (int)paisa << "\n";
    }
};

int main() {
    Inventory inventory;
    int choice;

    do {
        cout << "\n===== Grocery Inventory Management =====\n";
        cout << "1. Add Item\n";
        cout << "2. Delete Item\n";
        cout << "3. Update Quantity\n";
        cout << "4. Search Item by ID\n";
        cout << "5. Display Inventory\n";
        cout << "6. Count Total Items\n";
        cout << "7. Calculate Total Inventory Value\n";
        cout << "8. Sell Item\n";
        cout << "9. Show Total Sales\n";
        cout << "10. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            int id, qty;
            float price;
            string name;
            cout << "\nEnter item ID: ";
            cin >> id;
            cout << "Enter item name: ";
            cin.ignore();
            getline(cin, name);
            cout << "Enter quantity: ";
            cin >> qty;
            cout << "Enter price: ";
            cin >> price;
            inventory.addItem(id, name, qty, price);
            break;
        }
        case 2: {
            int id;
            cout << "\nEnter item ID to delete: ";
            cin >> id;
            inventory.deleteItem(id);
            break;
        }
        case 3: {
            int id, qty;
            cout << "\nEnter item ID to update quantity: ";
            cin >> id;
            cout << "Enter new quantity: ";
            cin >> qty;
            inventory.updateQuantity(id, qty);
            break;
        }
        case 4: {
            int id;
            cout << "\nEnter item ID to search: ";
            cin >> id;
            Item* item = inventory.searchItemById(id);
            if (item != nullptr) {
                cout << "\nItem Found:\n";
                cout << "ID: " << item->item_id << "\n";
                cout << "Name: " << item->name << "\n";
                cout << "Quantity: " << item->quantity << "\n";
                cout << "Price: " << item->price << "\n";
            }
            else {
                cout << "\nItem not found.\n";
            }
            break;
        }
        case 5:
            inventory.displayInventory();
            break;
        case 6:
            inventory.countTotalItems();
            break;
        case 7:
            inventory.calculateInventoryValue();
            break;
        case 8: {
            int id, qty;
            cout << "\nEnter item ID to sell: ";
            cin >> id;
            cout << "Enter quantity to sell: ";
            cin >> qty;
            inventory.sellItem(id, qty);
            break;
        }
        case 9:
            inventory.showTotalSales();
            break;
        case 10:
            cout << "\nExiting program. Thank you.\n";
            break;
        default:
            cout << "\nInvalid choice. Please try again.\n";
        }
    } while (choice != 10);

    return 0;
}