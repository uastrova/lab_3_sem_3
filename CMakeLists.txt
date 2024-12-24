cmake_minimum_required(VERSION 3.16)

project(lab3 VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Core)
find_package(Qt6 REQUIRED COMPONENTS Widgets)

qt_standard_project_setup()

qt_add_executable(lab3
        main.cpp
        HashTable.h
        AlphabetIndex.h
        ArrayIterator.h
        ArraySequence.h
        Sequence.h
        Book.h
        iterator.h
        vector.h
        Dictionary.h
        Generator.h
        KnapSackProblem.h
        RBTree.h
        Rows.h
        MostFrequent.h
        Pages.h
        tests.h
        MainWindow.h
        MainWindow.h
        MainWindow.cpp
        SubsequenceWindow.cpp
        SubsequenceWindow.h
        InputSequenceWindow.cpp
        InputSequenceWindow.h
        GenerateSequenceWindow.cpp
        GenerateSequenceWindow.h
        KnapsackParametersWindow.cpp
        KnapsackParametersWindow.h
        KnapsackItemsWindow.cpp
        KnapsackItemsWindow.h
        GeneratedSequenceWindow.cpp
        GeneratedSequenceWindow.h
)

target_link_libraries(lab3 PRIVATE Qt6::Core Qt6::Widgets)
