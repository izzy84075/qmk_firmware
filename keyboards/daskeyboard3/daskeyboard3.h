/* Copyright 2017 skully <skullydazed@gmail.com>
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
#ifndef CLUEBOARD4_H
#define CLUEBOARD4_H

#include "quantum.h"


/*
-------     -------------------------  -------------------------  -------------------------  -------------------
| KH0 |     | KG2 | KF2 | KF4 | KF0 |  | KI1 | KA0 | KC4 | KC2 |  | KJ2 | KJ1 | KJ0 | KJ7 |  | KB1 | KB5 | KI5 |
-------     -------------------------  -------------------------  -------------------------  -------------------

-------------------------------------------------------------------------------------------  -------------------  -------------------------
| KH2 | KH1 | KG1 | KF1 | KE1 | KE2 | KD2 | KD1 | KA1 | KC1 | KL1 | KL2 | KA2 |    KJ4    |  | KK2 | KR2 | KN2 |  | KM6 | KK6 | KN6 | KN7 |
-------------------------------------------------------------------------------------------  -------------------  -------------------------
|  KH4   | KH5 | KG5 | KF5 | KE5 | KE4 | KD4 | KD5 | KA5 | KC5 | KL5 | KL4 | KA4 |  KJ3   |  | KM2 | KR1 | KN1 |  | KM5 | KK5 | KN5 |     |
-------------------------------------------------------------------------------------------  -------------------  ------------------| KR5 |
|   KG4   | KH3 | KG3 | KF3 | KE3 | KE0 | KD0 | KD3 | KA3 | KC3 | KL3 | KL0 |     KJ6     |                       | KM4 | KK4 | KN4 |     |
-------------------------------------------------------------------------------------------        -------        -------------------------
|     KQ4     | KH6 | KG6 | KF6 | KE6 | KE7 | KD7 | KD6 | KA6 | KC6 | KL7 |   KQ3         |        | KR0 |        | KM3 | KK3 | KN3 |     |
-------------------------------------------------------------------------------------------  -------------------  ------------------| KR3 |
|  KI2  |  KP4  |  KB0  |                KM0                      | KB7 | KO3 | KC7 | KI6 |  | KR7 | KM7 | KK7 |  |    KK0    | KN0 |     |
-------------------------------------------------------------------------------------------  -------------------  -------------------------
*/


// This a shortcut to help you visually see your layout.
// The first section contains all of the arguments
// The second converts the arguments into a two-dimensional array
#define KEYMAP(\
    KH0,      KG2, KF2, KF4, KF0,   KI1, KA0, KC4, KC2,   KJ2, KJ1, KJ0, KJ7,	KB1, KB5, KI5,                        \
    KH2, KH1, KG1, KF1, KE1, KE2, KD2, KD1, KA1, KC1, KL1, KL2, KA2,     KJ4,	KK2, KR2, KN2,	  KM6, KK6, KN6, KN7, \
	KH4,  KH5, KG5, KF5, KE5, KE4, KD4, KD5, KA5, KC5, KL5, KL4, KA4,    KJ3,	KM2, KR1, KN1,	  KM5, KK5, KN5, KR5, \
	KG4,   KH3, KG3, KF4, KE4, KE0, KD0, KD3, KA3, KC3, KL3, KL0,        KJ6,                     KM4, KK4, KN4,      \
	KQ4,    KH6, KG6, KF6, KE6, KE7, KD7, KD6, KA6, KC6, KL7,            KQ3,        KR0,         KM3, KK3, KN3, KR3, \
	KI2, KP4, KB0,               KM0,                     KB7, KO3, KC7, KI6,   KR7, KM7, KK7,    KK0,      KN0       \
) { \
    {	KR0,	KC_NO,	KC_NO,	KC_NO,	KN0,	KM0,	KL0,	KK0,	KJ0,	KC_NO,	KH0,	KC_NO,	KF0,	KE0,	KD0,	KC_NO,	KB0,	KA0 }, \
	{	KR1,	KC_NO,	KC_NO,	KC_NO,	KN1,	KC_NO,	KL1,	KC_NO,	KJ1,	KI1,	KH1,	KG1,	KF1,	KE1,	KD1,	KC1,	KB1,	KA1 }, \
	{	KR2,	KC_NO,	KC_NO,	KC_NO,	KN2,	KM2,	KL2,	KK2,	KJ2,	KI2,	KH2,	KG2,	KF2,	KE2,	KD2,	KC2,	KC_NO,	KA2 }, \
	{	KR3,	KQ3,	KC_NO,	KO3,	KN3,	KM3,	KL3,	KK3,	KJ3,	KC_NO,	KH3,	KG3,	KF3,	KE3,	KD3,	KC3,	KC_NO,	KA3 }, \
	{	KC_NO,	KQ4,	KP4,	KC_NO,	KN4,	KM4,	KL4,	KK4,	KJ4,	KC_NO,	KH4,	KG4,	KF4,	KE4,	KD4,	KC4,	KC_NO,	KA4 }, \
	{	KR5,	KC_NO,	KC_NO,	KC_NO,	KN5,	KM5,	KL5,	KK5,	KC_NO,	KI5,	KH5,	KG5,	KF5,	KE5,	KD5,	KC5,	KB5,	KA5 }, \
	{	KC_NO,	KC_NO,	KC_NO,	KC_NO,	KN6,	KM6,	KC_NO,	KK6,	KJ6,	KI6,	KH6,	KG6,	KF6,	KE6,	KD6,	KC6,	KC_NO,	KA6 }, \
	{	KR7,	KC_NO,	KC_NO,	KC_NO,	KN7,	KM7,	KL7,	KK7,	KJ7,	KC_NO,	KC_NO,	KC_NO,	KC_NO,	KE7,	KD7,	KC7,	KB7,	KC_NO }, \
}

#endif
