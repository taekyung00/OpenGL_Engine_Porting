/**
 * \file
 * \author Taekyung Ho
 * \date 2026 Winter
 */
// -------------------------------------------------------------------------
// Platform Specific Includes & Logic
// -------------------------------------------------------------------------

#if defined(_WIN32)
#	include <windows.h>
#	include <psapi.h>
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

	}
		updateMemoryUsage();

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
	float max_graph_ram = (maxRamUsageBytes / (1024.0f * 1024.0f)) * 2.f;
	PlotRingBuffer("RAM (MB)", ramHistory, historyOffset, max_graph_ram);

	if (!customMetrics.empty())
    {
        ImGui::Separator();
        ImGui::Text("GBA Hardware Limits:");
        
        // 맵에 저장된 모든 항목을 순회하며 출력
        for (const auto& [name, value] : customMetrics)
        {
            // 예: "Sprite Count: 128"
            ImGui::Text("%s: %.0f", name.c_str(), value);

            // [심화] 만약 특정 수치가 위험하면 빨간색으로 경고 (선택 사항)
            // GBA 스프라이트 최대 개수(128)를 넘는지 시각적으로 경고
            if (name.find("Sprite") != std::string::npos && value > 128.0f) 
            {
                ImGui::SameLine();
                ImGui::TextColored(ImVec4(1, 0, 0, 1), "(OVER LIMIT!)");
            }
        }
    }
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
	PROCESS_MEMORY_COUNTERS_EX pmc;
	if (GetProcessMemoryInfo(GetCurrentProcess(), (PROCESS_MEMORY_COUNTERS*)&pmc, sizeof(pmc)))
	{
		ramUsageBytes = pmc.PrivateUsage;
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

	if (ramUsageBytes > maxRamUsageBytes)
	{
		maxRamUsageBytes = ramUsageBytes;
	}
}