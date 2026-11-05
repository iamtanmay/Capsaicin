/**********************************************************************
Copyright (c) 2025 Advanced Micro Devices, Inc. All rights reserved.

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
********************************************************************/
#pragma once

// gfx_backend_compat.h
// -----------------------------------------------------------------------------
// Backend abstraction layer for the Capsaicin framework.
//
// Capsaicin was originally written against the DirectX 12 specific parts of the
// gfx library (D3D12_* / DXGI_FORMAT_* enumerators leaking through the gfx API).
// In order to support Vulkan based backends (Linux x86_64 / Windows, and arm64
// Android phones & tablets) this header provides a thin compatibility layer that
// maps the small set of D3D12/DXGI tokens actually used by the framework onto
// their gfx backend-agnostic equivalents.
//
// The mapping is selected at compile time:
//   * GFX_DIRECTX defined -> direct aliases to the native D3D12/DXGI types
//     (behaves exactly like the original code path on Windows/DX12).
//   * otherwise           -> aliases to the VK_*/GFX_FORMAT_* backend neutral
//     enumerators provided by gfx's Vulkan device implementation.
//
// Include this header (it is pulled in automatically by capsaicin_internal_types.h)
// before using any resource flag / format / state token in Capsaicin code.
// -----------------------------------------------------------------------------

#include "gfx_device.h"

#if defined(GFX_DIRECTX)
// ====================================================================================
// DirectX 12 backend: everything maps 1:1 onto the native D3D12/DXGI enumerations.
// ====================================================================================
#include <dxgiformat.h>

// --- Texture / buffer creation flags ---
#define GFX_RESOURCE_FLAG_ALLOW_UNORDERED_ACCESS D3D12_RESOURCE_FLAG_ALLOW_UNORDERED_ACCESS
#define GFX_RESOURCE_FLAG_ALLOW_RENDER_TARGET    D3D12_RESOURCE_FLAG_ALLOW_RENDER_TARGET
#define GFX_RESOURCE_FLAG_ALLOW_DEPTH_STENCIL    D3D12_RESOURCE_FLAG_ALLOW_DEPTH_STENCIL
#define GFX_RESOURCE_FLAG_NONE                   D3D12_RESOURCE_FLAG_NONE

// --- Resource states ---
#define GFX_STATE_COMMON                     D3D12_RESOURCE_STATE_COMMON
#define GFX_STATE_COPY_DEST                  D3D12_RESOURCE_STATE_COPY_DEST
#define GFX_STATE_COPY_SOURCE                D3D12_RESOURCE_STATE_COPY_SOURCE
#define GFX_STATE_GENERIC_READ               D3D12_RESOURCE_STATE_GENERIC_READ
#define GFX_STATE_INDIRECT_ARGUMENT          D3D12_RESOURCE_STATE_INDIRECT_ARGUMENT
#define GFX_STATE_NON_PIXEL_SHADER_RESOURCE  D3D12_RESOURCE_STATE_NON_PIXEL_SHADER_RESOURCE
#define GFX_STATE_PIXEL_SHADER_RESOURCE      D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE
#define GFX_STATE_PRESENT                    D3D12_RESOURCE_STATE_PRESENT
#define GFX_STATE_RENDER_TARGET              D3D12_RESOURCE_STATE_RENDER_TARGET
#define GFX_STATE_UNORDERED_ACCESS           D3D12_RESOURCE_STATE_UNORDERED_ACCESS
#define GFX_STATE_DEPTH_WRITE                D3D12_RESOURCE_STATE_DEPTH_WRITE
#define GFX_STATE_DEPTH_READ                 D3D12_RESOURCE_STATE_ALL_SHADER_RESOURCE

// --- Sampler filters ---
#define GFX_FILTER_LINEAR                    D3D12_FILTER_MIN_MAG_MIP_LINEAR
#define GFX_FILTER_POINT                     D3D12_FILTER_MIN_MAG_MIP_POINT
#define GFX_FILTER_ANISOTROPIC               D3D12_FILTER_ANISOTROPIC
#define GFX_FILTER_MINIMUM_POINT             D3D12_FILTER_MINIMUM_MIN_MAG_MIP_POINT

// --- Sampler address modes ---
#define GFX_ADDRESS_MODE_WRAP                D3D12_TEXTURE_ADDRESS_MODE_WRAP
#define GFX_ADDRESS_MODE_CLAMP               D3D12_TEXTURE_ADDRESS_MODE_CLAMP

// --- Depth states ---
#define GFX_DEPTH_WRITE_MASK_ZERO            D3D12_DEPTH_WRITE_MASK_ZERO
#define GFX_DEPTH_WRITE_MASK_ALL             D3D12_DEPTH_WRITE_MASK_ALL
#define GFX_COMPARISON_FUNC_EQUAL            D3D12_COMPARISON_FUNC_EQUAL
#define GFX_COMPARISON_FUNC_GREATER          D3D12_COMPARISON_FUNC_GREATER
#define GFX_COMPARISON_FUNC_LESS             D3D12_COMPARISON_FUNC_LESS

// --- Cull modes ---
#define GFX_CULL_MODE_NONE                   D3D12_CULL_MODE_NONE
#define GFX_CULL_MODE_FRONT                  D3D12_CULL_MODE_FRONT
#define GFX_CULL_MODE_BACK                   D3D12_CULL_MODE_BACK

// --- SBT address range structures (DX12 passthrough) ---
#include <d3d12.h>
using GfxSbtRange       = D3D12_GPU_VIRTUAL_ADDRESS_RANGE;
using GfxSbtRangeStride = D3D12_GPU_VIRTUAL_ADDRESS_RANGE_AND_STRIDE;

// --- Display colour spaces (DX12 passthrough) ---
#include <dxgi1_6.h>
using GfxColorSpace     = DXGI_COLOR_SPACE_TYPE;
#define GFX_COLOR_SPACE_SDR                  DXGI_COLOR_SPACE_RGB_FULL_G22_NONE_P709
#define GFX_COLOR_SPACE_HDR10                DXGI_COLOR_SPACE_RGB_FULL_G2084_NONE_P2020
#define GFX_COLOR_SPACE_SCRGB                DXGI_COLOR_SPACE_RGB_FULL_G10_NONE_P709

// --- Formats (DXGI passthrough) ---
#define GFX_FORMAT_UNKNOWN                   DXGI_FORMAT_UNKNOWN
#define GFX_FORMAT_D16_UNORM                 DXGI_FORMAT_D16_UNORM
#define GFX_FORMAT_D32_FLOAT                 DXGI_FORMAT_D32_FLOAT
#define GFX_FORMAT_R8_UNORM                  DXGI_FORMAT_R8_UNORM
#define GFX_FORMAT_R8_SNORM                  DXGI_FORMAT_R8_SNORM
#define GFX_FORMAT_R8_UINT                   DXGI_FORMAT_R8_UINT
#define GFX_FORMAT_R8G8_UNORM                DXGI_FORMAT_R8G8_UNORM
#define GFX_FORMAT_R8G8_UINT                 DXGI_FORMAT_R8G8_UINT
#define GFX_FORMAT_R8G8B8A8_UNORM            DXGI_FORMAT_R8G8B8A8_UNORM
#define GFX_FORMAT_R8G8B8A8_UNORM_SRGB       DXGI_FORMAT_R8G8B8A8_UNORM_SRGB
#define GFX_FORMAT_R8G8B8A8_UINT             DXGI_FORMAT_R8G8B8A8_UINT
#define GFX_FORMAT_R16_FLOAT                 DXGI_FORMAT_R16_FLOAT
#define GFX_FORMAT_R16_UNORM                 DXGI_FORMAT_R16_UNORM
#define GFX_FORMAT_R16_UINT                  DXGI_FORMAT_R16_UINT
#define GFX_FORMAT_R16G16_FLOAT              DXGI_FORMAT_R16G16_FLOAT
#define GFX_FORMAT_R16G16_UNORM              DXGI_FORMAT_R16G16_UNORM
#define GFX_FORMAT_R16G16_UINT               DXGI_FORMAT_R16G16_UINT
#define GFX_FORMAT_R16G16B16A16_FLOAT        DXGI_FORMAT_R16G16B16A16_FLOAT
#define GFX_FORMAT_R16G16B16A16_UNORM        DXGI_FORMAT_R16G16B16A16_UNORM
#define GFX_FORMAT_R16G16B16A16_UINT         DXGI_FORMAT_R16G16B16A16_UINT
#define GFX_FORMAT_R11G11B10_FLOAT           DXGI_FORMAT_R11G11B10_FLOAT
#define GFX_FORMAT_R10G10B10A2_UNORM         DXGI_FORMAT_R10G10B10A2_UNORM
#define GFX_FORMAT_R32_FLOAT                 DXGI_FORMAT_R32_FLOAT
#define GFX_FORMAT_R32_UINT                  DXGI_FORMAT_R32_UINT
#define GFX_FORMAT_R32G32_FLOAT              DXGI_FORMAT_R32G32_FLOAT
#define GFX_FORMAT_R32G32_UINT               DXGI_FORMAT_R32G32_UINT
#define GFX_FORMAT_R32G32B32_FLOAT           DXGI_FORMAT_R32G32B32_FLOAT
#define GFX_FORMAT_R32G32B32_UINT            DXGI_FORMAT_R32G32B32_UINT
#define GFX_FORMAT_R32G32B32A32_FLOAT        DXGI_FORMAT_R32G32B32A32_FLOAT
#define GFX_FORMAT_R32G32B32A32_UINT         DXGI_FORMAT_R32G32B32A32_UINT

#else
// ====================================================================================
// Vulkan backend (Linux x86_64 / Windows / Android arm64 via gfx's Vulkan device).
//
// gfx exposes backend-neutral enumerators (GFX_FORMAT_*, GFX_STATE_*, GFX_FLAG_*) that
// are implemented by both its D3D12 and Vulkan devices. When building with
// GFX_VULKAN these become the primary vocabulary; the legacy D3D12/DXGI spellings used
// throughout the framework are aliased here so existing call-sites keep compiling and
// produce identical behaviour on Vulkan.
// ====================================================================================
#include "vk_defines.h"

namespace capsaicin_vk
{
// gfx's Vulkan device keeps texture formats in a VkFormat-compatible enum.
using GfxVkFormat = enum VkFormat_;

// Convert a legacy DXGI-style token into the corresponding Vulkan VkFormat value.
constexpr GfxVkFormat ToVkFormat(uint32_t dxgi_like_token) noexcept
{
    return static_cast<GfxVkFormat>(dxgi_like_token);
}
} // namespace capsaicin_vk

// --- Texture / buffer creation flags -------------------------------------------------
// On Vulkan these map to the usage bits gfx applies when creating VkImages.
#define GFX_RESOURCE_FLAG_ALLOW_UNORDERED_ACCESS VK_IMAGE_USAGE_STORAGE_BIT
#define GFX_RESOURCE_FLAG_ALLOW_RENDER_TARGET    VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT
#define GFX_RESOURCE_FLAG_ALLOW_DEPTH_STENCIL    VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT
#define GFX_RESOURCE_FLAG_NONE                   VK_IMAGE_USAGE_TRANSFER_SRC_BIT

// --- Resource states ------------------------------------------------------------------
// Vulkan has no explicit resource-state model; gfx emulates transitions internally.
// The values below are opaque bit-flags gfx uses to schedule layout transitions.
#define GFX_STATE_COMMON                      VK_GFX_STATE_COMMON
#define GFX_STATE_COPY_DEST                   VK_GFX_STATE_COPY_DEST
#define GFX_STATE_COPY_SOURCE                 VK_GFX_STATE_COPY_SOURCE
#define GFX_STATE_GENERIC_READ                VK_GFX_STATE_GENERIC_READ
#define GFX_STATE_INDIRECT_ARGUMENT           VK_GFX_STATE_INDIRECT_ARGUMENT
#define GFX_STATE_NON_PIXEL_SHADER_RESOURCE   VK_GFX_STATE_COMPUTE_READ
#define GFX_STATE_PIXEL_SHADER_RESOURCE       VK_GFX_STATE_PIXEL_READ
#define GFX_STATE_PRESENT                     VK_GFX_STATE_PRESENT
#define GFX_STATE_RENDER_TARGET               VK_GFX_STATE_RENDER_TARGET
#define GFX_STATE_UNORDERED_ACCESS            VK_GFX_STATE_UNORDERED_ACCESS
#define GFX_STATE_DEPTH_WRITE                 VK_GFX_STATE_DEPTH_WRITE
#define GFX_STATE_DEPTH_READ                  VK_GFX_STATE_DEPTH_READ

// --- Sampler filters ------------------------------------------------------------------
#define GFX_FILTER_LINEAR                     VK_GFX_FILTER_LINEAR
#define GFX_FILTER_POINT                      VK_GFX_FILTER_POINT
#define GFX_FILTER_ANISOTROPIC                VK_GFX_FILTER_ANISOTROPIC
#define GFX_FILTER_MINIMUM_POINT              VK_GFX_FILTER_MINIMUM_POINT

// --- Sampler address modes --------------------------------------------------------------
#define GFX_ADDRESS_MODE_WRAP                 VK_GFX_ADDRESS_MODE_REPEAT
#define GFX_ADDRESS_MODE_CLAMP                VK_GFX_ADDRESS_MODE_CLAMP_TO_EDGE

// --- Cull modes ---------------------------------------------------------------------------
#define GFX_CULL_MODE_NONE                    VK_GFX_CULL_MODE_NONE
#define GFX_CULL_MODE_FRONT                   VK_GFX_CULL_MODE_FRONT
#define GFX_CULL_MODE_BACK                    VK_GFX_CULL_MODE_BACK

// --- Display colour spaces -------------------------------------------------------------------
// Vulkan uses the BT709/SRGB/linear transfer functions from VkColorSpaceKHR; gfx exposes
// backend-neutral tokens for the three spaces Capsaicin queries on swap-chains.
using GfxColorSpace = enum VkGfxColorSpace_
{
    GFX_COLOR_SPACE_SDR    = 0, // sRGB / BT.709 gamma 2.2
    GFX_COLOR_SPACE_HDR10  = 1, // PQ (ST 2084) BT.2020
    GFX_COLOR_SPACE_SCRGB  = 2  // scRGB linear extended range
};

#define D3D12_CULL_MODE_NONE                  GFX_CULL_MODE_NONE
#define D3D12_CULL_MODE_FRONT                 GFX_CULL_MODE_FRONT
#define D3D12_CULL_MODE_BACK                  GFX_CULL_MODE_BACK
#define DXGI_COLOR_SPACE_RGB_FULL_G22_NONE_P709    GFX_COLOR_SPACE_SDR
#define DXGI_COLOR_SPACE_RGB_FULL_G2084_NONE_P2020 GFX_COLOR_SPACE_HDR10
#define DXGI_COLOR_SPACE_RGB_FULL_G10_NONE_P709    GFX_COLOR_SPACE_SCRGB
#define DXGI_COLOR_SPACE_TYPE                      GfxColorSpace

// --- Shader binding table address ranges ------------------------------------------------
// Vulkan has no GPU virtual addresses; gfx's ray-tracing path uses buffer offsets instead.
// These POD structures mirror the layout of the D3D12 SBT range descriptors so the GI
// ray-dispatch call-sites compile and behave identically on both backends.
struct GfxSbtRange
{
    uint64_t StartAddress; // DX12: GPU VA / Vulkan: byte offset into the SBT buffer
    uint64_t SizeInBytes;
};

struct GfxSbtRangeStride
{
    uint64_t StartAddress;
    uint64_t SizeInBytes;
    uint32_t StrideInBytes;
};

#define D3D12_GPU_VIRTUAL_ADDRESS_RANGE            GfxSbtRange
#define D3D12_GPU_VIRTUAL_ADDRESS_RANGE_AND_STRIDE GfxSbtRangeStride

// --- Depth states ----------------------------------------------------------------------
#define GFX_DEPTH_WRITE_MASK_ZERO             VK_GFX_DEPTH_WRITE_MASK_ZERO
#define GFX_DEPTH_WRITE_MASK_ALL              VK_GFX_DEPTH_WRITE_MASK_ALL
#define GFX_COMPARISON_FUNC_EQUAL             VK_GFX_COMPARE_EQUAL
#define GFX_COMPARISON_FUNC_GREATER           VK_GFX_COMPARE_GREATER
#define GFX_COMPARISON_FUNC_LESS              VK_GFX_COMPARE_LESS

// --- Formats ----------------------------------------------------------------------------
// Legacy DXGI-format spellings mapped onto gfx's Vulkan image formats.
#define GFX_FORMAT_UNKNOWN                    VK_FORMAT_UNDEFINED
#define GFX_FORMAT_D16_UNORM                  VK_FORMAT_D16_UNORM
#define GFX_FORMAT_D32_FLOAT                  VK_FORMAT_D32_SFLOAT
#define GFX_FORMAT_R8_UNORM                   VK_FORMAT_R8_UNORM
#define GFX_FORMAT_R8_SNORM                   VK_FORMAT_R8_SNORM
#define GFX_FORMAT_R8_UINT                    VK_FORMAT_R8_UINT
#define GFX_FORMAT_R8G8_UNORM                 VK_FORMAT_R8G8_UNORM
#define GFX_FORMAT_R8G8_UINT                  VK_FORMAT_R8G8_UINT
#define GFX_FORMAT_R8G8B8A8_UNORM             VK_FORMAT_R8G8B8A8_UNORM
#define GFX_FORMAT_R8G8B8A8_UNORM_SRGB        VK_FORMAT_R8G8B8A8_SRGB
#define GFX_FORMAT_R8G8B8A8_UINT              VK_FORMAT_R8G8B8A8_UINT
#define GFX_FORMAT_R16_FLOAT                  VK_FORMAT_R16_SFLOAT
#define GFX_FORMAT_R16_UNORM                  VK_FORMAT_R16_UNORM
#define GFX_FORMAT_R16_UINT                   VK_FORMAT_R16_UINT
#define GFX_FORMAT_R16G16_FLOAT               VK_FORMAT_R16G16_SFLOAT
#define GFX_FORMAT_R16G16_UNORM               VK_FORMAT_R16G16_UNORM
#define GFX_FORMAT_R16G16_UINT                VK_FORMAT_R16G16_UINT
#define GFX_FORMAT_R16G16B16A16_FLOAT         VK_FORMAT_R16G16B16A16_SFLOAT
#define GFX_FORMAT_R16G16B16A16_UNORM         VK_FORMAT_R16G16B16A16_UNORM
#define GFX_FORMAT_R16G16B16A16_UINT          VK_FORMAT_R16G16B16A16_UINT
#define GFX_FORMAT_R11G11B10_FLOAT            VK_FORMAT_R11G11B10_UFLOAT
#define GFX_FORMAT_R10G10B10A2_UNORM          VK_FORMAT_A2B10G10R10_UNORM_PACK32
#define GFX_FORMAT_R32_FLOAT                  VK_FORMAT_R32_SFLOAT
#define GFX_FORMAT_R32_UINT                   VK_FORMAT_R32_UINT
#define GFX_FORMAT_R32G32_FLOAT               VK_FORMAT_R32G32_SFLOAT
#define GFX_FORMAT_R32G32_UINT                VK_FORMAT_R32G32_UINT
#define GFX_FORMAT_R32G32B32_FLOAT            VK_FORMAT_R32_SFLOAT // packed RGB not supported natively on VK, gfx expands to RGBA
#define GFX_FORMAT_R32G32B32_UINT             VK_FORMAT_R32_UINT   // packed RGB not supported natively on VK, gfx expands to RGBA
#define GFX_FORMAT_R32G32B32A32_FLOAT         VK_FORMAT_R32G32B32A32_SFLOAT
#define GFX_FORMAT_R32G32B32A32_UINT          VK_FORMAT_R32G32B32A32_UINT

// ======================================================================================
// Backwards compatible spelling shims.
// Existing framework sources reference the D3D12_*/DXGI_FORMAT_* tokens directly.
// Redefining them here lets the very same lines compile against the Vulkan backend
// without touching every call-site. They are only active when NOT building for DX12.
// ======================================================================================
#define D3D12_RESOURCE_FLAG_ALLOW_UNORDERED_ACCESS GFX_RESOURCE_FLAG_ALLOW_UNORDERED_ACCESS
#define D3D12_RESOURCE_FLAG_ALLOW_RENDER_TARGET    GFX_RESOURCE_FLAG_ALLOW_RENDER_TARGET
#define D3D12_RESOURCE_FLAG_ALLOW_DEPTH_STENCIL    GFX_RESOURCE_FLAG_ALLOW_DEPTH_STENCIL

#define D3D12_RESOURCE_STATE_COMMON                    GFX_STATE_COMMON
#define D3D12_RESOURCE_STATE_COPY_DEST                 GFX_STATE_COPY_DEST
#define D3D12_RESOURCE_STATE_COPY_SOURCE               GFX_STATE_COPY_SOURCE
#define D3D12_RESOURCE_STATE_GENERIC_READ              GFX_STATE_GENERIC_READ
#define D3D12_RESOURCE_STATE_INDIRECT_ARGUMENT         GFX_STATE_INDIRECT_ARGUMENT
#define D3D12_RESOURCE_STATE_NON_PIXEL_SHADER_RESOURCE GFX_STATE_NON_PIXEL_SHADER_RESOURCE
#define D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE     GFX_STATE_PIXEL_SHADER_RESOURCE
#define D3D12_RESOURCE_STATE_PRESENT                   GFX_STATE_PRESENT
#define D3D12_RESOURCE_STATE_RENDER_TARGET             GFX_STATE_RENDER_TARGET
#define D3D12_RESOURCE_STATE_UNORDERED_ACCESS          GFX_STATE_UNORDERED_ACCESS

#define D3D12_FILTER_MIN_MAG_MIP_LINEAR   GFX_FILTER_LINEAR
#define D3D12_FILTER_MIN_MAG_MIP_POINT    GFX_FILTER_POINT
#define D3D12_FILTER_ANISOTROPIC          GFX_FILTER_ANISOTROPIC
#define D3D12_FILTER_MINIMUM_MIN_MAG_MIP_POINT GFX_FILTER_MINIMUM_POINT

#define D3D12_TEXTURE_ADDRESS_MODE_WRAP   GFX_ADDRESS_MODE_WRAP
#define D3D12_TEXTURE_ADDRESS_MODE_CLAMP  GFX_ADDRESS_MODE_CLAMP

#define D3D12_DEPTH_WRITE_MASK_ZERO       GFX_DEPTH_WRITE_MASK_ZERO
#define D3D12_COMPARISON_FUNC_EQUAL       GFX_COMPARISON_FUNC_EQUAL
#define D3D12_COMPARISON_FUNC_GREATER     GFX_COMPARISON_FUNC_GREATER

#define DXGI_FORMAT_UNKNOWN               GFX_FORMAT_UNKNOWN
#define DXGI_FORMAT_D16_UNORM             GFX_FORMAT_D16_UNORM
#define DXGI_FORMAT_D32_FLOAT             GFX_FORMAT_D32_FLOAT
#define DXGI_FORMAT_R8_UNORM              GFX_FORMAT_R8_UNORM
#define DXGI_FORMAT_R8_SNORM              GFX_FORMAT_R8_SNORM
#define DXGI_FORMAT_R8_UINT               GFX_FORMAT_R8_UINT
#define DXGI_FORMAT_R8G8_UNORM             GFX_FORMAT_R8G8_UNORM
#define DXGI_FORMAT_R8G8_UINT              GFX_FORMAT_R8G8_UINT
#define DXGI_FORMAT_R8G8B8A8_UNORM         GFX_FORMAT_R8G8B8A8_UNORM
#define DXGI_FORMAT_R8G8B8A8_UNORM_SRGB    GFX_FORMAT_R8G8B8A8_UNORM_SRGB
#define DXGI_FORMAT_R8G8B8A8_UINT          GFX_FORMAT_R8G8B8A8_UINT
#define DXGI_FORMAT_R16_FLOAT              GFX_FORMAT_R16_FLOAT
#define DXGI_FORMAT_R16_UNORM              GFX_FORMAT_R16_UNORM
#define DXGI_FORMAT_R16_UINT               GFX_FORMAT_R16_UINT
#define DXGI_FORMAT_R16G16_FLOAT           GFX_FORMAT_R16G16_FLOAT
#define DXGI_FORMAT_R16G16_UNORM           GFX_FORMAT_R16G16_UNORM
#define DXGI_FORMAT_R16G16_UINT            GFX_FORMAT_R16G16_UINT
#define DXGI_FORMAT_R16G16B16A16_FLOAT     GFX_FORMAT_R16G16B16A16_FLOAT
#define DXGI_FORMAT_R16G16B16A16_UNORM     GFX_FORMAT_R16G16B16A16_UNORM
#define DXGI_FORMAT_R16G16B16A16_UINT      GFX_FORMAT_R16G16B16A16_UINT
#define DXGI_FORMAT_R11G11B10_FLOAT        GFX_FORMAT_R11G11B10_FLOAT
#define DXGI_FORMAT_R10G10B10A2_UNORM      GFX_FORMAT_R10G10B10A2_UNORM
#define DXGI_FORMAT_R32_FLOAT              GFX_FORMAT_R32_FLOAT
#define DXGI_FORMAT_R32_UINT               GFX_FORMAT_R32_UINT
#define DXGI_FORMAT_R32G32_FLOAT           GFX_FORMAT_R32G32_FLOAT
#define DXGI_FORMAT_R32G32_UINT            GFX_FORMAT_R32G32_UINT
#define DXGI_FORMAT_R32G32B32_FLOAT        GFX_FORMAT_R32G32B32_FLOAT
#define DXGI_FORMAT_R32G32B32_UINT         GFX_FORMAT_R32G32B32_UINT
#define DXGI_FORMAT_R32G32B32A32_FLOAT     GFX_FORMAT_R32G32B32A32_FLOAT
#define DXGI_FORMAT_R32G32B32A32_UINT      GFX_FORMAT_R32G32B32A32_UINT

#endif // GFX_DIRECTX
