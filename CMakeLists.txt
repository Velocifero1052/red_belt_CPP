cmake_minimum_required(VERSION 3.25)
project(red_belt_C__)

set(CMAKE_CXX_STANDARD 17)

add_executable(red_belt_C__ main.cpp headers/Solutions.h headers/Logger.h headers/airline_ticket.h headers/deque.h headers/deque_authors.h profile.h headers/student.h headers/template_outputs.h headers/hotel_manager.h headers/simple_vector.h headers/linked_list.h headers/paginator.h headers/stack_vector.h headers/Translator.h
        headers/airport_counter.h
        headers/TextEditor.h)
