// TestBed.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "Engine.h"

class TestBed : public Developing::Core::Application {
public:
    TestBed();
};

TestBed::TestBed() {
    CLIENT_INFO("Testbed Application initialzed. yeah");
}

Developing::Core::Application* Developing::Core::CreateApp() {
    return new TestBed();
}

