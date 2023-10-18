#include <iostream>
#include <vector> // from the STL. Used to create a dynamic array of Task ovjects
#include <string>
#include <iomanip>
using namespace std;

// base class
class Task
{
protected: // data members made private. inaccessible to other classes that are not friends
  string task_name, task_description, due_date;

public:
  // Default constructor
  Task() {}

  // initializer list
  Task(string name, string desc, string date) : task_name(name), task_description(desc), due_date(date) {}

  // Parameterized constructor
  // Task(string name, string desc, string date)
  // {
  //   // initialize private variables
  //   task_name = name;
  //   task_description = desc;
  //   due_date = date;
  // }

  // copy constructor
  // Task(const Task &obj)
  // { // const is used because a rvalue (a temporary object without any location in memory) cannot be assigned to a non-const reference
  //   // so Task &obj has to be made const
  //   task_name = obj.task_name;
  //   task_description = obj.task_description;
  //   due_date = obj.due_date;
  // }

  // Function to display task details
  // it is marked as const because we tell the compiler that this
  // function doesn't modify the state of the object on which it is called
  // virtual keyword indicates that this function can be overridden by derived classes
  virtual void display() const
  {
    cout << left << setw(27) << task_name << left << setw(20) << task_description << setw(14) << right << due_date << endl;
  }

  friend class List; // friend class List declared. grants access to protected members of a class to another function/class
};

// inherited from Task
class List : public Task
{
private:
  vector<Task> tasks; // Vector of Task objects

public:
  // defining this function outside using "inline keyword"
  void add_task();

  // default constructor
  List(){};

  // create own copy constructor to ensure a deep copy of the vector "tasks"
  // List(const List &o)
  // {
  //   tasks = o.tasks; // performs a deep copy, as a shallow copy will not duplicate the contents into the vector
  // }

  // Update a task in the list
  void update_task(int index)
  {
    // if the index lies between 0 till the length of the vector
    if (index >= 0 && index < tasks.size())
    {
      string title, description, sub_date;

      cout << "Enter updated title: ";
      // cin.ignore(); // used to clear any newline characters left in the input buffer before using getline().
      // otherwise cin and int clash
      getline(cin, title);
      // tasks.insert(tasks.begin() + index, Task(title, description, sub_date));
      tasks[index].task_name = title; // insert the title at that particular index
      cout << endl;
      char sub_ans = 'n', sub_ans_2 = 'n';

      cout << "Do you also want to update the task description? (y/n): ";
      cin >> sub_ans;
      cout << endl;
      if (sub_ans == 'y' || sub_ans == 'Y')
      {
        cin.ignore();
        cout << "Enter updated task description: ";
        getline(cin, description);
        tasks[index].task_description = description;
        cout << endl;
      }

      cout << "Do you also want to update the date? (y/n): ";
      cin >> sub_ans_2;
      cout << endl;
      if (sub_ans_2 == 'y' || sub_ans_2 == 'Y')
      {
        cin.ignore();
        cout << "Enter updated task due date: ";
        getline(cin, sub_date);
        tasks[index].due_date = sub_date;
        cout << endl;
      }
      // tasks[index] = Task(title, description, sub_date); // push the data into that particular index
      cout << "Task updated successfully!" << endl
           << endl;
    }
    else
    {
      cout << "Invalid Task Number" << endl
           << endl;
    }
  }

  // Delete a task from the list
  vector<Task>::iterator i; // declare iterator

  void del_task(int index)
  {
    if (index >= 0 && index < tasks.size())
    {
      tasks.erase(tasks.begin() + index); // since index starts from 0
      cout << endl;
      cout << "Task deleted" << endl;
      cout << endl;
    }
    else
    {
      cout << endl;
      cout << "Invalid Task Number" << endl;
      cout << endl;
    }
  }

  // operator overloading
  // first parameter is the output stream, 2nd parameter is a constant reference to a List object
  friend ostream &operator<<(ostream &out, const List &L)
  {
    out << endl;
    out << "Task Title             "
        << "Task Description           "
        << "Task Due Date           " << endl;
    out << "----------------------------------------------------------------" << endl;

    // this for loop iterates over each Task in the tasks vector of the List object L.
    // for each task, it calls the display function
    for (const Task &task : L.tasks)
    {
      task.display(); // calling the display() function. uses polymorphism
    }
    return out; // return the output stream
  }

  // Display all tasks in the list
  // another example of polymorphism
  void display()
  {
    cout << endl;
    cout << "Task Title             "
         << "Task Description           "
         << "Task Due Date           " << endl;
    cout << "----------------------------------------------------------------" << endl;
    for (int i = 0; i < tasks.size(); i++)
    {
      cout << i + 1 << ". ";
      tasks[i].display(); // calling the display() function
    }
  }
};

// adding task to a list
// this is an inline function definition
inline void List::add_task()
{
  cout << "Enter task name: ";
  cin.ignore();
  getline(cin, task_name);
  cout << endl;
  cout << "Enter task description: ";
  getline(cin, task_description);
  cout << endl;
  cout << "Enter task due date: ";
  getline(cin, due_date);
  cout << endl;

  tasks.push_back(Task(task_name, task_description, due_date));
  cout << "Task added successfully!" << endl
       << endl;
}

int main()
{
  List taskList;             // taskList is an temporary object.
  List taskList2 = taskList; // copy contents of 1st obj to 2nd obj. a shallow copy is created
  int choice, task_no;
  char ans;
  string task;
  ans = 'y';

  while (ans == 'y' || ans == 'Y')
  {
    cout << endl;
    cout << "------------------------ "
         << "MENU"
         << " ------------------------" << endl;
    cout << endl;
    cout << "(1) ADD  (2) UPDATE  (3) DELETE  (4) DISPLAY  (5) EXIT" << endl;
    cout << endl;
    cout << "Enter option: ";

    cin >> choice;

    if (choice >= 1 || choice <= 5)
    {

      switch (choice)
      {
      case 1:
        cout << endl;
        taskList.add_task(); // using copy constructor. the copy is handled by taskList2
        cout << endl;
        break;

      case 2:
        cin.clear();
        cout << endl;
        cout << "Enter Task number to update: ";

        cin >> task;
        try
        {
          task_no = stoi(task);
          cin.ignore(); // clear the newline character from the buffer
          cout << endl;
          taskList.update_task(task_no - 1);
          cout << endl;
        }
        catch (const std::invalid_argument &e)
        {
          cout << endl;
          cout << "Error! Enter only numbers" << endl;
          cout << endl;
        }

        break;

      case 3:
        cout << endl;
        cout << "Enter Task Number to delete: ";
        cin >> task_no;
        taskList.del_task(task_no - 1); // to align user's task number with the index of the vector, there is a need to subtract 1.
        cout << endl;
        break;

      case 4:
        cout << endl;
        taskList.display();
        cout << endl;
        break;

      case 5:
        exit(1);

      default:
        cout << endl;
        cout << "Invalid input. Try again." << endl;
        cout << endl;
      }

      cout << "Do you want to continue? (y/n): ";
      cin >> ans;
      cout << endl;
    }

    else
    {
      cout << "Invalid choice. Try again.";
      exit(1);
    }
  }

  return 0;
}