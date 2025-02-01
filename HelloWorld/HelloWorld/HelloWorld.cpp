#include <iostream>
#include <chrono>
#include <thread>
#include <string>
#include <vector>
#include <functional>

#define CLEAR_TEXT "\33[2K\r";

const short shortDelay = 100;
const short longDelay = 400;

const int messageLength = 12;
const char* message = "Hello World!";

int messageCharIndex = 0;

void LoopCharacterAnimation();
bool ExecuteWordBlinkAnim();
bool ExecuteCharBlinkAnim();

std::vector<std::function<bool(void)>> animStates = {
    &ExecuteCharBlinkAnim,
    &ExecuteCharBlinkAnim,
    &ExecuteWordBlinkAnim,
    &ExecuteWordBlinkAnim,
    &ExecuteWordBlinkAnim
};

int main()
{
    LoopCharacterAnimation();
    return 0;
}

void LoopCharacterAnimation() {
    int animStepCounter = 0;

    while (animStepCounter < animStates.size()) {
        bool animationComplete = animStates[animStepCounter]();

        if (animationComplete) {
            messageCharIndex = 0;
            animStepCounter++;
        }
    }

    std::cout << CLEAR_TEXT;
    std::this_thread::sleep_for(std::chrono::milliseconds(longDelay));
}

bool ExecuteCharBlinkAnim() {
    char character = message[messageCharIndex];
    std::string toPrint = "";

    for (int i = 0; i < messageCharIndex; i++) {
        toPrint += " ";
    }

    toPrint += character;
    std::cout << CLEAR_TEXT;
    std::cout << toPrint << std::flush;
    std::this_thread::sleep_for(std::chrono::milliseconds(shortDelay));

    return ++messageCharIndex == messageLength;
}

bool ExecuteWordBlinkAnim() {
    std::cout << CLEAR_TEXT;
    std::this_thread::sleep_for(std::chrono::milliseconds(longDelay));
    std::cout << message;
    std::this_thread::sleep_for(std::chrono::milliseconds(longDelay));

    return true;
}