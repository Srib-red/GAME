#pragma once
#include <raylib.h>
#include <raymath.h>
#include <deque>

extern Color green;
extern Color darkgreen;

extern double lastUpdateTime;

bool ElementInDeque(Vector2 element, std::deque<Vector2> deque1);
bool EventTriggered(double interval);

extern int cellSize;
extern int cellCount;
extern int offset;
