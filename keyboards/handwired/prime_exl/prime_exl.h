/* Copyright 2018 Holten Campbell
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#include "quantum.h"

#define XXX KC_NO

#define LAYOUT( \
    k40, k50, k41, k51, k42, k52,    k43, k53, k44, k54, k45, k55,    k46, k56, k47, k57, k48, k58, \
    k30, k60, k31, k61, k32, k62,    k33, k63, k34, k64, k35, k65,    k36, k66, k37, k67, k38, k68, \
    k20, k70, k21, k71, k22, k72,    k23, k73, k24, k74, k25, k75,    k85, k26, k76, k27, k77, k28, k78, \
    k10, k80, k11, k81, k12, k82,    k13, k83, k14, k84,    k15,           k16,      k86, k17, k87, k18, \
    k00, k90, k01, k91, k02, k92 \
) { \
    { k00, k01, k02, XXX, XXX, XXX, XXX, XXX, XXX }, \
    { k10, k11, k12, k13, k14, k15, k16, k17, k18 }, \
    { k20, k21, k22, k23, k24, k25, k26, k27, k28 }, \
    { k30, k31, k32, k33, k34, k35, k36, k37, k38 }, \
    { k40, k41, k42, k43, k44, k45, k46, k47, k48 }, \
    { k50, k51, k52, k53, k54, k55, k56, k57, k58 }, \
    { k60, k61, k62, k63, k64, k65, k66, k67, k68 }, \
    { k70, k71, k72, k73, k74, k75, k76, k77, k78 }, \
    { k80, k81, k82, k83, k84, k85, k86, k87, XXX }, \
    { k90, k91, k92, XXX, XXX, XXX, XXX, XXX, XXX } \
}
