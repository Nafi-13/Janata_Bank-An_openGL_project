#include <iostream>
using namespace std;
#include <Windows.h>
#include <MMSystem.h>

int main()
{
    PlaySound(TEXT("woo.wav"),NULL, SND_SYNC);
}
