# BTP305 Final Project

The purpose of this term project is to put my C++ Object Oriented skills to practice by developing a simulated Assembly Line.

Below is a check list of the modules that are to be implemented to the project:
- [x] Utilities
    - Used to parse strings and help populate data for other modules.
- [x] Item
    - Manages a single item on the assembly line.
- [x] CustomerOrder
    - Used to encapsulate and manage all the details related to a customer's order on the assembly line.
- [x] Task
    - Inherits from the Item module, and will contain additional information:
        - a double ended queue with CustomerOrders, coming in one side and exited out the other once it is filled.
        - a pointer to the next task on the assembly line.
- [x] LineManager
    - Manages the entire assembly line

Here you can find a documentation of the classes that are currently implemented:

### Utilities
`void setFieldWidth(size_t)`  
   - Sets the field width of the current object.


`size_t getFieldWidth() const`  
   - Returns the field width of the current object.


`const std::string extractToken(const std::string& str, size_t& next_pos, bool& more)`  
   - Extracts tokens from `str`.  
   - This extracts the token start at position `next_pos`.  
   - If the extraction is successful it sets `more` to true or false depending if there are more tokens to extract.  
   - This function returns a string of the token found.  
   - This function will throw an exception if:  
        - There are no more tokens to be extract; OR 
        - `next_pos` is out of bounds of `str`


`static void setDelimiter(const char&)`  
   - Sets the delimiter character. The delimiter character is a shared value accross all instances of Utilities.


`const char getDelimiter() const`  
   - Returns the delimiter character.

### Item
`Item(const std::string&)`
   - A custom constructor that recieves a string containing information to populate variables.
   - The construct assumes the string contains the information in the following order seperated by a delimiter:
      - name of item
      - starting serial number
      - quantity in stock
      - description

`const std::string& getName() const`
   - Returns the name of the item.

`const unsigned int getSerialNumber()`
   - Returns the current serial number of the item.

`const unsigned int getQuantity()`
   - Returns the quantity remaining in stock.

`void updateQuantity()`
   - Subtracts one from the quantity, and increments the serial number.

`void display(std::ostream&, bool) const`
   - Display information about the item

### CustomerOrder
`CustomerOrder()`
   - The default constructor, this simply sets variables to null.

`CustomerOrder(const std::string&)`
   - A custom constructor that recieves a string containing information to populate variables.
   - The constructor assumes the string contains the information in the following order seperated by a delimiter:
      - customer name
      - order name
      - a list of items ordered (requires at least one item)

`CustomerOrder(CustomerOrder&)`
   - Copying this class is not allowed, this will throw an exception.

`CustomerOrder& operator=(CustomerOrder&)`
   - Copy assignment operator has been deleted.

`CustomerOrder(CustomerOrder&&) noexcept`
`CustomerOrder& operator=(CustomerOrder&&);`
   - Move operations are still allowed.

`bool getItemFillState(std::string) const`
   - Returns if the item specified in the parameter has been fulfilled in the order.
   - If there are multiple of the item specified in the parameter in the order, if any of them are unfulfilled, this function will return false.
   - If the item does not exist in the order, this function will return true.

`bool getOrderFillState() const`
   - Returns if all items in the order are fulfilled.

`void fillItem(Item& item, std::ostream&)`
   - This function will attempt to fulfill the order with the item specified in the parameter.
   - This function does nothing if the item specified in the parameter does not exist in the order.
   - If the item is found in the order, it will update the order with the item's serial number that was used to fulfill the order.
   - If the there is not stock remaining it will print a message stating that the order could not be fulfilled.

`void display(std::ostream&) const`
   - Displays the current state of the order, which items are fulfilled along with serial number for the item if it has been fulfilled.

### Task
`Task(const std::string&)`
   - Since this class is inherited from the Item class, it uses the string in the parameter to populate the variables from Item.
   - See "Item" for more details.

`Task& operator+=(CustomerOrder&&)`
   - This overloaded operator moves the CustomerOrder into the queue for the current task.

`void runProcess(std::ostream&)`
   - It will verify the CustomerOrder at the front of the queue if it requires the current item, and will attempt to fulfill it. 
   - This function will throw an exception if there is no available inventory remaining to fulfill the current order. 

`bool moveTask()`
   - Moves the CustomerOrder at the front of the queue to the next task if the CustomerOrder's fill state true for the current Item.

`void setNextTask(Task&)`
   - Points to the Task provided as the next task in the assembly line. 

`bool getCompleted(CustomerOrder&)`
   - If all items of the CustomerOrder at the front of the queue are fulfilled, it will move the CustomerOrder to the parameter provided.

`void validate(std::ostream&)`
   - Displays the Item that the Task is responsible for, as well as the next task in the assembly line.
   - If the current object does not point to a next task, it is assumed that this current Task is the end of the assembly line.

### LineManager
`LineManager(const std::string&, std::vector<Task*>&, std::vector<CustomerOrder>&)`
   - The string parameter is the filename of the file containing the order of tasks on the assembly line.
   - The Task* vector is the list of tasks to be in the assembly line.
   - The CustomerOrder vector is a list of orders to be fulfilled. Upon instatiation of this object, all CustomerOrders in this vector will be moved to the LineManager's own data members. 

`bool run(std::ostream&)`
   - If there are any CustomerOrders to are still to be filled, it will insert one order into the assembly line.
   - Completes a single run through the entire assembly line vector to try and fulfill CustomerOrders currently in the assembly line.
   - Moves CustomerOrders to the next Task if they have been fulfilled at the current Task.
   - Removes any completed CustomerOrders currently in the assembly line.
   - Returns if all CustomerOrders are completely fulfilled.

`void displayCompleted(std::ostream&) const`
   - Displays a list of currently completed CustomerOrders.

`void validateTasks() const`
   - Displays a list of all Tasks in the assembly line, as well as the next Task for each Task, or if a Task is the end of the assembly line.
