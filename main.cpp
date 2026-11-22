#include <ctime>
#include <ctype.h>
#include <fstream>
#include <iostream>
#include <vector>
#include <stdbool.h>
#include <string>

std::vector<std::string> todo;
const std::string APP_VERSION = "1.0.0";
const std::string TODO_PATH = "./todo.txt";

// Prototypes
void addTask(std::string task);
char confirmUser(std::string prompt);
void deleteTask(void);
std::string getCurrentTime(void);
void initTodo(void);
char promptUser(std::string prompt);
void printTodo(bool withIndex);
void saveTodo(void);
void updateTodo(void);
void validateInput(int argc, char* argv[]);

int main(int argc, char* argv[])
{
    initTodo();
    updateTodo();
    validateInput(argc, argv);
    return 0;
}

void addTask(std::string task)
{
    updateTodo();
    std::string finalString = getCurrentTime() + " | " + task ;
    todo.push_back(finalString);
    saveTodo();
}

char confirmUser(std::string prompt)
{
    char answer;
    do
    {
        std::cout << prompt << " (y/n): ";
        std::cin >> answer;
        answer = tolower(answer);
    }
    while(answer != 'y' && answer != 'n');
    return answer;
}

void deleteTask()
{
    updateTodo();
    printTodo(/*withIndex=*/true);
    char indexAnswer = promptUser("Which item to delete? (index)");
    // std::cout << "DEBUG: got char '" << indexAnswer << "' (int=" << (int)indexAnswer << ")\n";   
    int index = (indexAnswer - '0') - 1;

    if (!(index >= 0 && index < (int) todo.size())) 
    {
        std::cout << "Index " << indexAnswer << " does not have a todo entry." << std::endl;
        return;
    }
    char confirmAnswer = confirmUser("This action will delete the todo entry \"" + todo.at(index) + "\" proceed?");
    if(confirmAnswer != 'y')
    {
        std::cout << "Aborted." << std::endl;
        return;
    }
    todo.erase(todo.begin() + index);
    saveTodo();
    return;
}

std::string getCurrentTime()
{
    char buf[64];
    std::time_t now = std::time(nullptr);
    std::strftime(buf, sizeof(buf), "%d/%m/%Y %I:%M:%S %p", std::localtime(&now));
    return buf;
}

void initTodo()
{
    std::ifstream in(TODO_PATH);
    if (in.is_open())
    {
        return;
    }

    std::ofstream out(TODO_PATH);
    out.close();
}

void printTodo(bool withIndex = false)
{
    updateTodo();
    int length = todo.size();
    for(int i = 0; i < length; i++)
    {
        if(withIndex)
        {
            std::cout << i + 1 << " | ";
        }
        std::cout << todo[i] << std::endl;
    }
}

char promptUser(std::string prompt)
{
    char answer;
    std::cout << prompt << ": ";
    std::cin >> answer;
    return answer;
}

void saveTodo(void)
{
    std::ofstream out(TODO_PATH, std::ofstream::trunc);
    for (const auto& task : todo)
    {
        out << task << "\n";
    }
}

void updateTodo(void)
{
    std::ifstream in(TODO_PATH);
    if (!in.is_open())
    {
        return;
    }

    todo.clear();
    std::string line;
    while (std::getline(in, line))
    {
        todo.push_back(line);
    }
}

void validateInput(int argc, char* argv[])
{
    const std::string USAGE_TEXT = "Usage: task-cli <add|delete|view> \n run --help for more info.";

    if (argc < 2)
    {
        std::cout << USAGE_TEXT << std::endl;
        return;
    }

    std::string command = argv[1];

    if (command == "add")
    {
        if (argc < 3)
        {
            std::cout << "Usage: task-cli add <\"task\">" << std::endl;
            return;
        }
        addTask(argv[2]);
    }
    else if (command == "delete")
    {
        deleteTask();
    }
    else if (command == "view")
    {
        printTodo();
    }
    else if(command == "--help" || command == "-?")
    {
        std::cout << USAGE_TEXT << std::endl;
        std::cout << "TaskCLI Version: " << APP_VERSION << std::endl;
        std::cout << "COMMANDS:\n view\n\tgives a list of all tasks within todo.txt file.\n add \"task\"\n\tadds the task specified within the double-quotes to the todo.txt file.\n delete\n\tgives a list of tasks and prompts the user for an index of that task to delete.\n --help or -? \n\tprnts this message and exits.\n--version or -v\n\tprints the version number and exits." << std::endl;
    }
    else if (command == "--version" || command == "-v")
    {
        std::cout << "TaskCLI Version: " << APP_VERSION << std::endl;
    }
    else
    {
        std::cout << "Unknown command: " << command << std::endl;
        std::cout << USAGE_TEXT << std::endl;
    }
}
