/**
 * \file
 * \author Taekyung Ho
 * \date 2026 Winter
 */
#include "PerformanceMonitor.h"
#include <algorithm>
#include <imgui.h>
#include <vector>

// -------------------------------------------------------------------------
// Platform Specific Includes & Logic
// -------------------------------------------------------------------------

#if defined(_WIN32)
#	include <psapi.h>
#	include <windows.h>
#	pragma comment(lib, "psapi.lib")
#elif defined(__EMSCRIPTEN__)
#	include <emscripten/emscripten.h>
#elif defined(__linux__)
#	include <fstream>
#	include <sys/param.h>
#	include <sys/types.h>
#	include <unistd.h>
#endif

PerformanceMonitor::PerformanceMonitor()
{
	frameTimeHistory.resize(HISTORY_SIZE, 0.0f);
	ramHistory.resize(HISTORY_SIZE, 0.0f);
}

void PerformanceMonitor::Update(double dt)
{
    // 1. Calculate FPS & Frame Time
    frameTime = dt * 1000.0; // in milliseconds
    timeAccumulator += dt;
    frameCount++;

    // Update stats every 0.5 sec to reduce overhead
    if (timeAccumulator >= 0.5)
    {
        fps = static_cast<double>(frameCount) / timeAccumulator;
        timeAccumulator -= 0.5;
        frameCount = 0;

        updateMemoryUsage();
    }

    // 2. Record History for Graphs (Every frame)
    frameTimeHistory[historyOffset] = static_cast<float>(frameTime);
    ramHistory[historyOffset] = static_cast<float>(ramUsageBytes) / (1024.0f * 1024.0f); // in MB
    historyOffset = (historyOffset + 1) % HISTORY_SIZE;
}

