#include <iostream>
#include <string>

int
main()
{
  std::string name;
  std::cin >> name; // читаем имя пользователя
  std::cout << "Hello world from @" << name << std::endl; // выводим приветствие
  return 0;
}
