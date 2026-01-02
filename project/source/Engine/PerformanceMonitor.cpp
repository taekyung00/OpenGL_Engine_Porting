/**
 * \file
 * \author Taekyung Ho
 * \date 2026 Winter
 */
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
#include "PerformanceMonitor.h"
#include <algorithm>
#include <imgui.h>
#include <vector>


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
	ramHistory[historyOffset]		= static_cast<float>(ramUsageBytes) / (1024.0f * 1024.0f); // in MB
	historyOffset					= (historyOffset + 1) % HISTORY_SIZE;
}

void PerformanceMonitor::DrawImGui()
{
	ImGui::Begin("System Monitor");
	// --- Summary Text ---
	ImGui::Text("FPS: %.1f", fps);
	ImGui::Text("Frame Time: %.3f ms", frameTime);

	if (ramUsageBytes > 0)
	{
		ImGui::Text("RAM Usage: %.2f MB", ramUsageBytes / (1024.0f * 1024.0f));
		ImGui::Text("Peak RAM:  %.2f MB", maxRamUsageBytes / (1024.0f * 1024.0f));
	}
	else
	{
		ImGui::Text("RAM Usage: N/A (Unsupported Platform)");
	}
	ImGui::Separator();

	// --- Graphs ---
	auto PlotRingBuffer = [](const char* label, const std::vector<float>& data, int offset, float max_val)
	{
		ImGui::PlotLines(label, data.data(), static_cast<int>(data.size()), offset, nullptr, 0.0f, max_val, ImVec2(0, 60));
	};

	// Graph 1: Frame Time
	PlotRingBuffer("Frame Time (ms)", frameTimeHistory, historyOffset, 40.0f);
	// Graph 2: RAM Usage (Dynamic Scale)
	float max_graph_ram = (maxRamUsageBytes / (1024.0f * 1024.0f)) * 1.2f;
	PlotRingBuffer("RAM (MB)", ramHistory, historyOffset, max_graph_ram);
	ImGui::End();
}

void PerformanceMonitor::SetCustomMetric(const std::string& name, float value)
{
    customMetrics[name] = value;
}

void PerformanceMonitor::updateMemoryUsage()
{
#if defined(_WIN32)
	// [Windows] Use PSAPI to get Working Set Size
	PROCESS_MEMORY_COUNTERS pmc;
	if (GetProcessMemoryInfo(GetCurrentProcess(), (PROCESS_MEMORY_COUNTERS*)&pmc, sizeof(pmc)))
	{
		ramUsageBytes = static_cast<size_t>(pmc.WorkingSetSize);
	}
#elif defined(__EMSCRIPTEN__)
	ramUsageBytes = (size_t)EM_ASM_INT({
		if (window.performance && window.performance.memory)
		{
			return window.performance.memory.usedJSHeapSize;
		}
		return 0;
	});

#elif defined(__linux__)
	long rss = 0;
	{
		std::ifstream statm("/proc/self/statm");
		if (statm.is_open())
		{
			long ignore;
			statm >> ignore >> rss; // skip first value, read RSS
		}
	}
	ramUsageBytes = static_cast<size_t>(rss) * static_cast<size_t>(sysconf(_SC_PAGESIZE));
#endif
}