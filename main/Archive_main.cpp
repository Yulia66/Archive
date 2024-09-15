#pragma once
#include <iostream>
#include "archive.h"
#include "utilities.h"

enum Actions { EXIT, INSERT, FIND, REMOVE, CLEAN };

int main() {
  TArchive<int> archive;
  size_t n, pos;
  int* values = nullptr;
  int user;

  std::exception err;
  bool exit = false;
  bool success;
  InputSystem::InsertMode mode;
  InputSystem::InsertMode_Remove mode_2;
  while (!exit) {
    system("cls");
    OutputSystem::show(archive);
    std::cout << "Menu:\n 1. insert,\n 2. find,\n 3. delete,\n 4. clean,\n 0. exit.\nYour choose: ";
    std::cin >> user;



    switch (user) {
    case Actions::EXIT:
      exit = true;
      break;






    case Actions::INSERT://                    ÂÑÒÀÂÊÀ
      if (values != nullptr) { delete[] values; values = nullptr; }
      values = InputSystem::insert<int>(n, pos, mode);
      success = false;
      if (mode == InputSystem::InsertMode::OneValue) {
        try {
          archive.insert(values[0], pos);
          success = true;
        }
        catch (std::exception err) {
          std::cerr << err.what() << std::endl;
        }

      }

      if (mode == InputSystem::InsertMode::SeveralValues) {
        try {
          archive.insert(values, n, pos);
          success = true;
        }catch (std::exception err) {
          std::cerr << err.what() << std::endl;
        }
      }

      if(mode == InputSystem::InsertMode::Front) {
        try {
          archive.push_front(values[0]);
          success = true;
        }catch (std::exception err) {
          std::cerr << err.what() << std::endl;
        }
      }
      if (mode == InputSystem::InsertMode::Back) {
        try {
          archive.push_back(values[0]);
          success = true;
        }catch (std::exception err) {
          std::cerr << err.what() << std::endl;
        }
      }
      if (success) {
        OutputSystem::insert();
      }
      system("pause");
      break;












    case Actions::FIND://                          ÏÎÈÑÊ
      std::cout << "TBD" << std::endl;
      system("pause");
      break;









    case Actions::REMOVE://                        ÓÄÀËÅÍÈÅ
      if (values != nullptr) { delete[] values; values = nullptr; }
      values = InputSystem::remove<int>(n, pos, mode, mode_2);
      if (mode == InputSystem::InsertMode::Front && mode_2== InputSystem::InsertMode_Remove::Position) {
        try {
          archive.pop_front();
        }
        catch (std::exception err) {
          std::cerr << err.what() << std::endl;
        }
      }

      if (mode == InputSystem::InsertMode::Back && mode_2 == InputSystem::InsertMode_Remove::Position) {
        try {
          archive.pop_back();
        }
        catch (std::exception err) {
          std::cerr << err.what() << std::endl;
        }
      }
      if (mode == InputSystem::InsertMode::OneValue && mode_2 == InputSystem::InsertMode_Remove::Position) {
        try {
          archive.remove_by_index(pos);
        }catch (std::exception err) {
          std::cerr << err.what() << std::endl;
        }
      }
      if (mode == InputSystem::InsertMode::SeveralValues && mode_2 == InputSystem::InsertMode_Remove::Position) {
        try {
          archive.erase(pos, n);
        }
        catch (std::exception err) {
          std::cerr << err.what() << std::endl;
        }
      }
      if (mode == InputSystem::InsertMode::Back && mode_2 == InputSystem::InsertMode_Remove::Value) {
        
          archive.remove_last( values[0]);

      }
      if (mode == InputSystem::InsertMode::Front && mode_2 == InputSystem::InsertMode_Remove::Value) {

        archive.remove_first(values[0]);

      }
      if (mode == InputSystem::InsertMode::All && mode_2 == InputSystem::InsertMode_Remove::Value) {

        archive.remove_all( values[0]);

      }
      system("pause");
      break;





    case Actions::CLEAN:
      std::cout << "TBD" << std::endl;
      break;
    }
  }

  return 0;
}
