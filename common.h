#pragma once
#include <windows.h>

#include <d3d9.h>
#include <d3dx9.h>
#include <chrono>

using namespace std::chrono_literals;

#include "../../dependencies/imgui/imgui.h"
#include "../../dependencies/imgui/imgui_freetype.h"
#include "../../dependencies/imgui/imgui_internal.h"
#include "../../dependencies/imgui/dx9/imgui_impl_dx9.h"
#include "../../dependencies/imgui/win32/imgui_impl_win32.h"

#include "utilities/logging.h"
#include "utilities/memory/memory.h"
#include "core/sdk/datatypes/color.h"
#include "utilities/encryption/xorstr.h"
#include "utilities/input/key_handler.h"
#include "dependencies/lazy_importer/lazy_importer.h"  