/**
 * \file
 * \author Taekyung Ho
 * \date 2026 Winter
 */

#pragma once
#include <cstddef> // size_t
#include <map>
#include <string>
#include <vector>

class PerformanceMonitor
{
public:
	PerformanceMonitor();

	// should be called every frame
	void Update(double dt);

	// renders the ImGui window
	void DrawImGui();

	// helper to track game-specific metrics (e.g. "Sprite Count")
	void SetCustomMetric(const std::string& name, float value);

private:
	// internal helpers to fetch RAM usage based on OS
	void updateMemoryUsage();

private:
    // timing
    double frameTime = 0.0;
    double fps = 0.0;
    double timeAccumulator = 0.0;
    size_t frameCount = 0;

    // memory(in Bytes)
    size_t ramUsageBytes = 0;
    size_t maxRamUsageBytes = 0;

    // history data for Graphs (ring buffers)
    static constexpr size_t HISTORY_SIZE = 90;
    std::vector<float> frameTimeHistory;
    std::vector<float> ramHistory;
    int historyOffset = 0;

    // custom metrics map
    std::map<std::string, float> customMetrics;
};
