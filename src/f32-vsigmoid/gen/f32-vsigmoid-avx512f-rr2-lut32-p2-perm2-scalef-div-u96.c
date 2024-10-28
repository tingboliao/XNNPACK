// Auto-generated file. Do not edit!
//   Template: src/f32-vsigmoid/avx512f-rr2-lut32-p2-perm2-scalef.c.in
//   Generator: tools/xngen
//
// Copyright 2020 Google LLC
//
// This source code is licensed under the BSD-style license found in the
// LICENSE file in the root directory of this source tree.

#include <assert.h>

#include <immintrin.h>

#include "xnnpack/common.h"
#include "xnnpack/intrinsics-polyfill.h"
#include "xnnpack/vunary.h"


void xnn_f32_vsigmoid_ukernel__avx512f_rr2_lut32_p2_perm2_scalef_div_u96(
    size_t batch,
    const float* input,
    float* output,
    const struct xnn_f32_default_params params[restrict XNN_MIN_ELEMENTS(1)])
{
  assert(batch != 0);
  assert(batch % sizeof(float) == 0);
  assert(input != NULL);
  assert(output != NULL);

  XNN_ALIGN(64) static const float table[32] = {
    0x1.000000p+0f, 0x1.059B0Ep+0f, 0x1.0B5586p+0f, 0x1.11301Ep+0f,
    0x1.172B84p+0f, 0x1.1D4874p+0f, 0x1.2387A6p+0f, 0x1.29E9E0p+0f,
    0x1.306FE0p+0f, 0x1.371A74p+0f, 0x1.3DEA64p+0f, 0x1.44E086p+0f,
    0x1.4BFDAEp+0f, 0x1.5342B6p+0f, 0x1.5AB07Ep+0f, 0x1.6247ECp+0f,
    0x1.6A09E6p+0f, 0x1.71F75Ep+0f, 0x1.7A1148p+0f, 0x1.82589Ap+0f,
    0x1.8ACE54p+0f, 0x1.93737Cp+0f, 0x1.9C4918p+0f, 0x1.A5503Cp+0f,
    0x1.AE89FAp+0f, 0x1.B7F770p+0f, 0x1.C199BEp+0f, 0x1.CB720Ep+0f,
    0x1.D5818Ep+0f, 0x1.DFC974p+0f, 0x1.EA4AFAp+0f, 0x1.F50766p+0f,
  };
  const __m512 vtable_lo = _mm512_load_ps(&table[0]);
  const __m512 vtable_hi = _mm512_load_ps(&table[16]);

  const __m512i vsign_mask = _mm512_set1_epi32(UINT32_C(0x80000000));
  const __m512 vmagic_bias = _mm512_set1_ps(0x1.800000p18f);
  const __m512 vlog2e = _mm512_set1_ps(0x1.715476p0f);
  const __m512 vminus_ln2_hi = _mm512_set1_ps(-0x1.62E430p-1f);
  const __m512 vminus_ln2_lo = _mm512_set1_ps(0x1.05C61p-29f);
  const __m512 vc2 = _mm512_set1_ps(0x1.000000p-1f);
  const __m512 vc1 = _mm512_set1_ps(0x1.0000F6p-0f);
  const __m512 vone = _mm512_set1_ps(1.0f);

  XNN_FORCE_REALIZATION(vsign_mask);
  XNN_FORCE_REALIZATION(vmagic_bias);
  XNN_FORCE_REALIZATION(vlog2e);
  XNN_FORCE_REALIZATION(vminus_ln2_hi);
  XNN_FORCE_REALIZATION(vminus_ln2_lo);
  XNN_FORCE_REALIZATION(vc2);
  XNN_FORCE_REALIZATION(vc1);
  XNN_FORCE_REALIZATION(vone);

  for (; batch >= 96 * sizeof(float); batch -= 96 * sizeof(float)) {
    const __m512 vx0 = _mm512_loadu_ps(input);
    const __m512 vx1 = _mm512_loadu_ps(input + 16);
    const __m512 vx2 = _mm512_loadu_ps(input + 32);
    const __m512 vx3 = _mm512_loadu_ps(input + 48);
    const __m512 vx4 = _mm512_loadu_ps(input + 64);
    const __m512 vx5 = _mm512_loadu_ps(input + 80);
    input += 96;

    const __m512 vz0 = _mm512_castsi512_ps(_mm512_or_epi32(_mm512_castps_si512(vx0), vsign_mask));
    const __m512 vz1 = _mm512_castsi512_ps(_mm512_or_epi32(_mm512_castps_si512(vx1), vsign_mask));
    const __m512 vz2 = _mm512_castsi512_ps(_mm512_or_epi32(_mm512_castps_si512(vx2), vsign_mask));
    const __m512 vz3 = _mm512_castsi512_ps(_mm512_or_epi32(_mm512_castps_si512(vx3), vsign_mask));
    const __m512 vz4 = _mm512_castsi512_ps(_mm512_or_epi32(_mm512_castps_si512(vx4), vsign_mask));
    const __m512 vz5 = _mm512_castsi512_ps(_mm512_or_epi32(_mm512_castps_si512(vx5), vsign_mask));

    __m512 vn0 = _mm512_fmadd_ps(vz0, vlog2e, vmagic_bias);
    __m512 vn1 = _mm512_fmadd_ps(vz1, vlog2e, vmagic_bias);
    __m512 vn2 = _mm512_fmadd_ps(vz2, vlog2e, vmagic_bias);
    __m512 vn3 = _mm512_fmadd_ps(vz3, vlog2e, vmagic_bias);
    __m512 vn4 = _mm512_fmadd_ps(vz4, vlog2e, vmagic_bias);
    __m512 vn5 = _mm512_fmadd_ps(vz5, vlog2e, vmagic_bias);

    const __m512 vl0 = _mm512_permutex2var_ps(vtable_lo, _mm512_castps_si512(vn0), vtable_hi);
    const __m512 vl1 = _mm512_permutex2var_ps(vtable_lo, _mm512_castps_si512(vn1), vtable_hi);
    const __m512 vl2 = _mm512_permutex2var_ps(vtable_lo, _mm512_castps_si512(vn2), vtable_hi);
    const __m512 vl3 = _mm512_permutex2var_ps(vtable_lo, _mm512_castps_si512(vn3), vtable_hi);
    const __m512 vl4 = _mm512_permutex2var_ps(vtable_lo, _mm512_castps_si512(vn4), vtable_hi);
    const __m512 vl5 = _mm512_permutex2var_ps(vtable_lo, _mm512_castps_si512(vn5), vtable_hi);

    vn0 = _mm512_sub_ps(vn0, vmagic_bias);
    vn1 = _mm512_sub_ps(vn1, vmagic_bias);
    vn2 = _mm512_sub_ps(vn2, vmagic_bias);
    vn3 = _mm512_sub_ps(vn3, vmagic_bias);
    vn4 = _mm512_sub_ps(vn4, vmagic_bias);
    vn5 = _mm512_sub_ps(vn5, vmagic_bias);

    __m512 vt0 = _mm512_fmadd_ps(vn0, vminus_ln2_hi, vz0);
    __m512 vt1 = _mm512_fmadd_ps(vn1, vminus_ln2_hi, vz1);
    __m512 vt2 = _mm512_fmadd_ps(vn2, vminus_ln2_hi, vz2);
    __m512 vt3 = _mm512_fmadd_ps(vn3, vminus_ln2_hi, vz3);
    __m512 vt4 = _mm512_fmadd_ps(vn4, vminus_ln2_hi, vz4);
    __m512 vt5 = _mm512_fmadd_ps(vn5, vminus_ln2_hi, vz5);

    vt0 = _mm512_fmadd_ps(vn0, vminus_ln2_lo, vt0);
    vt1 = _mm512_fmadd_ps(vn1, vminus_ln2_lo, vt1);
    vt2 = _mm512_fmadd_ps(vn2, vminus_ln2_lo, vt2);
    vt3 = _mm512_fmadd_ps(vn3, vminus_ln2_lo, vt3);
    vt4 = _mm512_fmadd_ps(vn4, vminus_ln2_lo, vt4);
    vt5 = _mm512_fmadd_ps(vn5, vminus_ln2_lo, vt5);

    __m512 vp0 = _mm512_fmadd_ps(vt0, vc2, vc1);
    __m512 vp1 = _mm512_fmadd_ps(vt1, vc2, vc1);
    __m512 vp2 = _mm512_fmadd_ps(vt2, vc2, vc1);
    __m512 vp3 = _mm512_fmadd_ps(vt3, vc2, vc1);
    __m512 vp4 = _mm512_fmadd_ps(vt4, vc2, vc1);
    __m512 vp5 = _mm512_fmadd_ps(vt5, vc2, vc1);

    vt0 = _mm512_mul_ps(vt0, vl0);
    vt1 = _mm512_mul_ps(vt1, vl1);
    vt2 = _mm512_mul_ps(vt2, vl2);
    vt3 = _mm512_mul_ps(vt3, vl3);
    vt4 = _mm512_mul_ps(vt4, vl4);
    vt5 = _mm512_mul_ps(vt5, vl5);

    vp0 = _mm512_fmadd_ps(vt0, vp0, vl0);
    vp1 = _mm512_fmadd_ps(vt1, vp1, vl1);
    vp2 = _mm512_fmadd_ps(vt2, vp2, vl2);
    vp3 = _mm512_fmadd_ps(vt3, vp3, vl3);
    vp4 = _mm512_fmadd_ps(vt4, vp4, vl4);
    vp5 = _mm512_fmadd_ps(vt5, vp5, vl5);

    const __m512 ve0 = _mm512_scalef_ps(vp0, vn0);
    const __m512 ve1 = _mm512_scalef_ps(vp1, vn1);
    const __m512 ve2 = _mm512_scalef_ps(vp2, vn2);
    const __m512 ve3 = _mm512_scalef_ps(vp3, vn3);
    const __m512 ve4 = _mm512_scalef_ps(vp4, vn4);
    const __m512 ve5 = _mm512_scalef_ps(vp5, vn5);

    const __m512 vd0 = _mm512_add_ps(ve0, vone);
    const __m512 vd1 = _mm512_add_ps(ve1, vone);
    const __m512 vd2 = _mm512_add_ps(ve2, vone);
    const __m512 vd3 = _mm512_add_ps(ve3, vone);
    const __m512 vd4 = _mm512_add_ps(ve4, vone);
    const __m512 vd5 = _mm512_add_ps(ve5, vone);

    __m512 vf0 = _mm512_div_ps(ve0, vd0);
    __m512 vf1 = _mm512_div_ps(ve1, vd1);
    __m512 vf2 = _mm512_div_ps(ve2, vd2);
    __m512 vf3 = _mm512_div_ps(ve3, vd3);
    __m512 vf4 = _mm512_div_ps(ve4, vd4);
    __m512 vf5 = _mm512_div_ps(ve5, vd5);

    vf0 = _mm512_mask_sub_ps(vf0, _mm512_testn_epi32_mask(_mm512_castps_si512(vx0), vsign_mask), vone, vf0);
    vf1 = _mm512_mask_sub_ps(vf1, _mm512_testn_epi32_mask(_mm512_castps_si512(vx1), vsign_mask), vone, vf1);
    vf2 = _mm512_mask_sub_ps(vf2, _mm512_testn_epi32_mask(_mm512_castps_si512(vx2), vsign_mask), vone, vf2);
    vf3 = _mm512_mask_sub_ps(vf3, _mm512_testn_epi32_mask(_mm512_castps_si512(vx3), vsign_mask), vone, vf3);
    vf4 = _mm512_mask_sub_ps(vf4, _mm512_testn_epi32_mask(_mm512_castps_si512(vx4), vsign_mask), vone, vf4);
    vf5 = _mm512_mask_sub_ps(vf5, _mm512_testn_epi32_mask(_mm512_castps_si512(vx5), vsign_mask), vone, vf5);

    _mm512_storeu_ps(output, vf0);
    _mm512_storeu_ps(output + 16, vf1);
    _mm512_storeu_ps(output + 32, vf2);
    _mm512_storeu_ps(output + 48, vf3);
    _mm512_storeu_ps(output + 64, vf4);
    _mm512_storeu_ps(output + 80, vf5);
    output += 96;
  }
  for (; batch >= 16 * sizeof(float); batch -= 16 * sizeof(float)) {
    const __m512 vx = _mm512_loadu_ps(input);
    input += 16;

    const __m512 vz = _mm512_castsi512_ps(_mm512_or_epi32(_mm512_castps_si512(vx), vsign_mask));

    __m512 vn = _mm512_fmadd_ps(vz, vlog2e, vmagic_bias);
    const __m512 vl = _mm512_permutex2var_ps(vtable_lo, _mm512_castps_si512(vn), vtable_hi);
    vn = _mm512_sub_ps(vn, vmagic_bias);

    __m512 vt = _mm512_fmadd_ps(vn, vminus_ln2_hi, vz);
    vt = _mm512_fmadd_ps(vn, vminus_ln2_lo, vt);

    __m512 vp = _mm512_fmadd_ps(vt, vc2, vc1);
    vt = _mm512_mul_ps(vt, vl);
    vp = _mm512_fmadd_ps(vt, vp, vl);

    const __m512 ve = _mm512_scalef_ps(vp, vn);
    const __m512 vd = _mm512_add_ps(ve, vone);

    __m512 vf = _mm512_div_ps(ve, vd);

    vf = _mm512_mask_sub_ps(vf, _mm512_testn_epi32_mask(_mm512_castps_si512(vx), vsign_mask), vone, vf);

    _mm512_storeu_ps(output, vf);
    output += 16;
  }
  if XNN_UNLIKELY(batch != 0) {
    assert(batch >= 1 * sizeof(float));
    assert(batch <= 15 * sizeof(float));

    // Prepare mask for valid 32-bit elements (depends on batch).
    batch >>= XNN_LOG2_SIZEOF_FLOAT;
    const __mmask16 vmask = _cvtu32_mask16((uint32_t) ((UINT32_C(1) << batch) - UINT32_C(1)));

    const __m512 vx = _mm512_maskz_loadu_ps(vmask, input);
    const __m512 vz = _mm512_castsi512_ps(_mm512_or_epi32(_mm512_castps_si512(vx), vsign_mask));

    __m512 vn = _mm512_fmadd_ps(vz, vlog2e, vmagic_bias);
    const __m512 vl = _mm512_permutex2var_ps(vtable_lo, _mm512_castps_si512(vn), vtable_hi);
    vn = _mm512_sub_ps(vn, vmagic_bias);

    __m512 vt = _mm512_fmadd_ps(vn, vminus_ln2_hi, vz);
    vt = _mm512_fmadd_ps(vn, vminus_ln2_lo, vt);

    __m512 vp = _mm512_fmadd_ps(vt, vc2, vc1);
    vt = _mm512_mul_ps(vt, vl);
    vp = _mm512_fmadd_ps(vt, vp, vl);

    const __m512 ve = _mm512_scalef_ps(vp, vn);
    const __m512 vd = _mm512_add_ps(ve, vone);

    __m512 vf = _mm512_div_ps(ve, vd);

    vf = _mm512_mask_sub_ps(vf, _mm512_testn_epi32_mask(_mm512_castps_si512(vx), vsign_mask), vone, vf);

    _mm512_mask_storeu_ps(output, vmask, vf);
  }
}
