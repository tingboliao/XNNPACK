// Auto-generated file. Do not edit!
//   Template: src/f32-vbinary/vopc-scalar.c.in
//   Generator: tools/xngen
//
// Copyright 2019 Google LLC
//
// This source code is licensed under the BSD-style license found in the
// LICENSE file in the root directory of this source tree.

#include <assert.h>

#include <xnnpack/common.h>
#include <xnnpack/math.h>
#include <xnnpack/vbinary.h>


void xnn_f32_vminc_ukernel__wasm_x1(
    size_t n,
    const float* a,
    const float* b,
    float* y,
    const union xnn_f32_default_params params[restrict static 1])
{
  assert(n != 0);
  assert(n % sizeof(float) == 0);


  const float vb = *b;
  for (; n >= sizeof(float); n -= sizeof(float)) {
    const float va = *a++;
    float vy = __builtin_wasm_min_f32(va, vb);
    *y++ = vy;
  }
}
