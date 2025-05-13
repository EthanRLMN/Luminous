#include "Editor.hpp"
/*
#include <iostream>
#include <rfl.hpp>
#include <rfl/json.hpp>
#include <string>
#include <vector>*/

/*
struct Person
{
    rfl::Rename<"firstName", std::string> first_name;
    rfl::Rename<"lastName", std::string> last_name;
    std::vector<Person> children;
};*/


int main()
{
    
    Editor* l_editor = new Editor();
    l_editor->Init();

    l_editor->Update();

    l_editor->Destroy();
    delete l_editor;
    l_editor = nullptr;

    return 0;


    /*
    const std::string json_str = R"({
        "firstName": "John",
        "lastName": "Doe",
        "birthday": "1980-01-01",
        "children": [
            {
                "firstName": "Jane",
                "lastName": "Doe",
                "children": []
            }
        ]
    })";


    const rfl::Result<Person> result = rfl::json::read<Person>(json_str);

    if (result)
    {
        const Person& person = result.value();
        std::cout << "First Name: " << person.first_name.value() << std::endl;
        std::cout << "Last Name: " << person.last_name.value() << std::endl;
    } else
    {
        std::cerr << "Erreur de parsing JSON." << std::endl;
    }

    
    Person person;
    person.first_name = "Alice";
    person.last_name = "Smith";



    const std::string json_string = rfl::json::write(person, rfl::json::pretty);
    std::cout << json_string << std::endl;


    return 0;*/
}