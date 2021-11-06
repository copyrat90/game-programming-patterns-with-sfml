// This is a modified version of struct ExampleAppLog from https://github.com/ocornut/imgui/blob/master/imgui_demo.cpp
// Therefore, this source file is licensed by Omar Cornut, under the MIT/Expat License.
// See https://github.com/ocornut/imgui/blob/master/LICENSE.txt for details.

#pragma once

#include <ctime>
#include <imgui.h>

namespace igpp::common
{

// Usage:
//  static ImguiLogger my_log;
//  my_log.AddLog("Hello %d world\n", 123);
//  my_log.Draw("title");
class ImguiLogger
{
private:
    ImGuiTextBuffer Buf;
    ImGuiTextFilter Filter;
    ImVector<int> LineOffsets; // Index to lines offset. We maintain this with AddLog() calls.
    bool AutoScroll;           // Keep scrolling if already at the bottom.

    // Added on 2021-11-06 by copyrat90
    ImVec2 initPos_, initSize_;
    ImGuiWindowFlags flags_;
    static const ImGuiWindowFlags DEFAULT_FLAGS = ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove |
                                                  ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoScrollbar;

public:
    // Added on 2021-11-06 by copyrat90
    enum class CornerPos
    {
        UPPER_LEFT,
        UPPER_RIGHT,
        LOWER_LEFT,
        LOWER_RIGHT
    };

    // Modified on 2021-11-06 by copyrat90
    // Added logger window initial pos & size & flags
    ImguiLogger(ImVec2 initPos, ImVec2 initSize, ImGuiWindowFlags flags = DEFAULT_FLAGS)
        : initPos_(initPos), initSize_(initSize), flags_(flags)
    {
        AutoScroll = true;
        Clear();
    }

    // Added on 2021-11-06 by copyrat90
    ImguiLogger(CornerPos cornerPos, ImVec2 sfmlWindowSize, ImVec2 initSize, ImVec2 margin = ImVec2(10, 10),
                ImGuiWindowFlags flags = DEFAULT_FLAGS)
        : initSize_(initSize), flags_(flags)
    {
        initPos_ = margin;
        switch (cornerPos)
        {
        case CornerPos::UPPER_LEFT:
            initPos_ = margin;
            break;
        case CornerPos::UPPER_RIGHT:
            initPos_.x = sfmlWindowSize.x - margin.x - initSize.x;
            initPos_.y = margin.y;
            break;
        case CornerPos::LOWER_LEFT:
            initPos_.x = margin.x;
            initPos_.y = sfmlWindowSize.y - margin.y - initSize.y;
            break;
        case CornerPos::LOWER_RIGHT:
            initPos_.x = sfmlWindowSize.x - margin.x - initSize.x;
            initPos_.y = sfmlWindowSize.y - margin.y - initSize.y;
            break;
        }
        AutoScroll = true;
        Clear();
    }

    // Added on 2021-11-06 by copyrat90
    ImguiLogger(const ImguiLogger&) = delete;
    ImguiLogger& operator=(const ImguiLogger&) = delete;

    void Clear()
    {
        Buf.clear();
        LineOffsets.clear();
        LineOffsets.push_back(0);
    }

    // Modified on 2021-11-05 by copyrat90
    // This function is modified to automatically add a timestamp to the log.
    void AddLog(const char* fmt, ...) IM_FMTARGS(2)
    {
        int old_size = Buf.size();
        va_list args;
        va_start(args, fmt);
        // Add a timestamp before the log message
        std::time_t t = std::time(0);
        std::tm* time = std::localtime(&t);
        Buf.appendf("[%02d:%02d:%02d] ", time->tm_hour, time->tm_min, time->tm_sec);
        // Edit ends here;
        Buf.appendfv(fmt, args);
        va_end(args);
        for (int new_size = Buf.size(); old_size < new_size; old_size++)
            if (Buf[old_size] == '\n')
                LineOffsets.push_back(old_size + 1);
    }

    // Modified on 2021-11-05 by copyrat90
    void Draw(const char* title, bool* p_open = NULL)
    {
        ImGui::SetNextWindowPos(initPos_, ImGuiCond_Once);
        ImGui::SetNextWindowSize(initSize_, ImGuiCond_Once);
        // Modified to add flags
        if (!ImGui::Begin(title, p_open, flags_))
        {
            ImGui::End();
            return;
        }

        // Options menu
        // if (ImGui::BeginPopup("Options"))
        //{
        //    ImGui::Checkbox("Auto-scroll", &AutoScroll);
        //    ImGui::EndPopup();
        //}

        // Main window
        // if (ImGui::Button("Options"))
        //    ImGui::OpenPopup("Options");
        // ImGui::SameLine();
        // bool clear = ImGui::Button("Clear");
        // ImGui::SameLine();
        // bool copy = ImGui::Button("Copy");
        // ImGui::SameLine();
        // Filter.Draw("Filter", -100.0f);

        // ImGui::Separator();
        ImGui::BeginChild("scrolling", ImVec2(0, 0), false, ImGuiWindowFlags_HorizontalScrollbar);

        // if (clear)
        //    Clear();
        // if (copy)
        //    ImGui::LogToClipboard();

        ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 0));
        const char* buf = Buf.begin();
        const char* buf_end = Buf.end();
        if (Filter.IsActive())
        {
            // In this example we don't use the clipper when Filter is enabled.
            // This is because we don't have a random access on the result on our filter.
            // A real application processing logs with ten of thousands of entries may want to store the result of
            // search/filter.. especially if the filtering function is not trivial (e.g. reg-exp).
            for (int line_no = 0; line_no < LineOffsets.Size; line_no++)
            {
                const char* line_start = buf + LineOffsets[line_no];
                const char* line_end =
                    (line_no + 1 < LineOffsets.Size) ? (buf + LineOffsets[line_no + 1] - 1) : buf_end;
                if (Filter.PassFilter(line_start, line_end))
                    ImGui::TextUnformatted(line_start, line_end);
            }
        }
        else
        {
            // The simplest and easy way to display the entire buffer:
            //   ImGui::TextUnformatted(buf_begin, buf_end);
            // And it'll just work. TextUnformatted() has specialization for large blob of text and will fast-forward
            // to skip non-visible lines. Here we instead demonstrate using the clipper to only process lines that are
            // within the visible area.
            // If you have tens of thousands of items and their processing cost is non-negligible, coarse clipping them
            // on your side is recommended. Using ImGuiListClipper requires
            // - A) random access into your data
            // - B) items all being the  same height,
            // both of which we can handle since we an array pointing to the beginning of each line of text.
            // When using the filter (in the block of code above) we don't have random access into the data to display
            // anymore, which is why we don't use the clipper. Storing or skimming through the search result would make
            // it possible (and would be recommended if you want to search through tens of thousands of entries).
            ImGuiListClipper clipper;
            clipper.Begin(LineOffsets.Size);
            while (clipper.Step())
            {
                for (int line_no = clipper.DisplayStart; line_no < clipper.DisplayEnd; line_no++)
                {
                    const char* line_start = buf + LineOffsets[line_no];
                    const char* line_end =
                        (line_no + 1 < LineOffsets.Size) ? (buf + LineOffsets[line_no + 1] - 1) : buf_end;
                    ImGui::TextUnformatted(line_start, line_end);
                }
            }
            clipper.End();
        }
        ImGui::PopStyleVar();

        if (AutoScroll && ImGui::GetScrollY() >= ImGui::GetScrollMaxY())
            ImGui::SetScrollHereY(1.0f);

        ImGui::EndChild();
        ImGui::End();
    }
};

} // namespace igpp::common
