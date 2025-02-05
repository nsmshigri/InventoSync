InventoSync
Introduction
InventoSync is an Inventory Management System designed to streamline inventory operations for businesses of all sizes. It provides features like inventory tracking, role-based access control, purchase management, and authentication. Built using C++ and OOP principles, InventoSync ensures security and flexibility through a command-line interface (CLI).

Description
InventoSync allows users to manage stock, items, user roles, and purchases via a text-based CLI. The system offers role management and authentication to ensure secure and efficient inventory management.

Classes and Design
Identified Classes:
Admin
Customer
Employee
Item
Stock
Purchase
User
Identified Relationships:
Aggregation:
Customers can make purchases.
Purchases consist of multiple items.
Composition:
Admins, Employees, and Customers interact with Stock for operations.
Inheritance:
Admin and Employee inherit from User.
Structure
User: Login functionality for Admin, Employee, and Customer.
Item: Manages inventory items with name, code, quantity, and price.
Stock: Handles the collection of items.
Purchase: Manages customer orders.
How to Run the Project
Clone the repository:
git clone https://github.com/yourusername/InventoSync.git
Navigate to the project directory: cd InventoSync
Compile the project: g++ main.cpp -o inventosync
Run the program: ./inventosync
