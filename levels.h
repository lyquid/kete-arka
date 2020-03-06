#ifndef KETE_ARKA_LEVELS_H_
#define KETE_ARKA_LEVELS_H_

#include <string>

#include "config.h"

namespace k {

  struct ProtoLevel {
    const char*      name;
    const Background background;
    const BrickTypes layout[kLevelMaxRows * kLevelMaxColumns];
  };

  /*  - Level scaffold -
  {
    "LVL NAME", 
    k::Background::XXX
    { _, _, _, _, _, _, _, _, _, _, _,
      _, _, _, _, _, _, _, _, _, _, _,
      _, _, _, _, _, _, _, _, _, _, _,
      _, _, _, _, _, _, _, _, _, _, _,
      _, _, _, _, _, _, _, _, _, _, _,
      _, _, _, _, _, _, _, _, _, _, _,
      _, _, _, _, _, _, _, _, _, _, _,
      _, _, _, _, _, _, _, _, _, _, _,
      _, _, _, _, _, _, _, _, _, _, _,
      _, _, _, _, _, _, _, _, _, _, _,
      _, _, _, _, _, _, _, _, _, _, _,
      _, _, _, _, _, _, _, _, _, _, _,
      _, _, _, _, _, _, _, _, _, _, _,
      _, _, _, _, _, _, _, _, _, _, _,
      _, _, _, _, _, _, _, _, _, _, _ } 
    }
  */

  constexpr ProtoLevel kProtoLevels[kMaxLevels] = {
    {
      "Som-hi", /* Level 01 */
      k::Background::Blue,
      { _, _, _, _, _, _, _, _, _, _, _,
        _, _, _, _, _, _, _, _, _, _, _,
        _, _, _, _, _, _, _, _, _, _, _,
        _, _, _, _, _, _, _, _, _, _, _,
        S, S, S, S, S, S, S, S, S, S, S,
        R, R, R, R, R, R, R, R, R, R, R,
        B, B, B, B, B, B, B, B, B, B, B,
        Y, Y, Y, Y, Y, Y, Y, Y, Y, Y, Y,
        P, P, P, P, P, P, P, P, P, P, P,
        G, G, G, G, G, G, G, G, G, G, G }
    },
    {
      "Escala ensopida", /* Level 02 */
      k::Background::Green,
      { _, _, _, _, _, _, _, _, _, _, _,
        _, _, _, _, _, _, _, _, _, _, _,
        O, _, _, _, _, _, _, _, _, _, _,
        O, L, _, _, _, _, _, _, _, _, _,
        O, L, G, _, _, _, _, _, _, _, _,
        O, L, G, B, _, _, _, _, _, _, _,
        O, L, G, B, R, _, _, _, _, _, _,
        O, L, G, B, R, O, _, _, _, _, _,
        O, L, G, B, R, O, L, _, _, _, _,
        O, L, G, B, R, O, L, G, _, _, _,
        O, L, G, B, R, O, L, G, B, _, _,
        O, L, G, B, R, O, L, G, B, R, _,
        S, S, S, S, S, S, S, S, S, S, O }
    },
    {
      "Serp ondulada", /* Level 03 */
      k::Background::BlueCircuit,
      { _, _, _, _, _, _, _, _, _, _, _,
        _, _, _, _, _, _, _, _, _, _, _,
        _, _, _, _, _, _, _, _, _, _, _,
        G, G, G, G, G, G, G, G, G, G, G,
        _, _, _, _, _, _, _, _, _, _, _,
        W, W, W, A, A, A, A, A, A, A, A,
        _, _, _, _, _, _, _, _, _, _, _, 
        R, R, R, R, R, R, R, R, R, R, R,
        _, _, _, _, _, _, _, _, _, _, _,
        A, A, A, A, A, A, A, A, W, W, W,
        _, _, _, _, _, _, _, _, _, _, _, 
        P, P, P, P, P, P, P, P, P, P, P,
        _, _, _, _, _, _, _, _, _, _, _,
        B, B, B, A, A, A, A, A, A, A, A,
        _, _, _, _, _, _, _, _, _, _, _, 
        B, B, B, B, B, B, B, B, B, B, B,
        _, _, _, _, _, _, _, _, _, _, _,
        A, A, A, A, A, A, A, A, B, B, B }
    },
    {
      "Columnes de Rossetta", /* Level 04 */
      k::Background::RedCircuit,
      { _, _, _, _, _, _, _, _, _, _, _,
        _, _, _, _, _, _, _, _, _, _, _,
        _, _, _, _, _, _, _, _, _, _, _,
        _, _, _, _, _, _, _, _, _, _, _,
        _, S, Y, G, P, _, Y, G, B, S, _,
        _, B, G, Y, R, _, G, Y, S, B, _,
        _, G, P, R, Y, _, B, S, Y, G, _, 
        _, Y, R, P, G, _, S, B, G, Y, _,
        _, R, Y, G, B, _, Y, G, P, R, _,
        _, P, G, Y, S, _, G, Y, R, P, _,
        _, G, B, S, Y, _, P, R, Y, G, _, 
        _, Y, S, B, G, _, R, P, G, Y, _,
        _, S, Y, G, P, _, Y, G, B, S, _,
        _, B, G, Y, R, _, G, Y, S, B, _,
        _, G, P, R, Y, _, B, S, Y, G, _, 
        _, Y, R, P, G, _, S, B, G, Y, _,
        _, R, Y, G, B, _, Y, G, P, R, _,
        _, P, G, Y, S, _, G, Y, R, P, _ }
    },
    {
      "L'invasor", /* Level 05 */
      k::Background::Blue,
      { _, _, _, _, _, _, _, _, _, _, _,
        _, _, _, _, _, _, _, _, _, _, _,
        _, _, _, Y, _, _, _, Y, _, _, _,
        _, _, _, _, Y, _, Y, _, _, _, _,
        _, _, _, _, Y, _, Y, _, _, _, _,
        _, _, _, S, S, S, S, S, _, _, _,
        _, _, _, S, S, S, S, S, _, _, _,
        _, _, S, S, R, S, R, S, S, _, _,
        _, _, S, S, R, S, R, S, S, _, _,
        _, S, S, S, S, S, S, S, S, S, _,
        _, S, S, S, S, S, S, S, S, S, _,
        _, S, _, S, S, S, S, S, _, S, _,
        _, S, _, S, _, _, _, S, _, S, _,
        _, S, _, S, _, _, _, S, _, S, _,
        _, _, _, _, S, _, S, _, _, _, _,
        _, _, _, _, S, _, S, _, _, _, _ }
    },
    {
      "Pont de Londres", /* Level 06 */
      k::Background::Green,
      { _, _, _, _, _, _, _, _, _, _, _,
        _, _, _, _, _, _, _, _, _, _, _,
        _, _, _, _, _, _, _, _, _, _, _,
        B, _, R, _, G, _, G, _, R, _, B,
        B, _, R, _, G, _, G, _, R, _, B,
        B, _, R, _, G, _, G, _, R, _, B,
        B, _, A, O, A, O, A, O, A, _, B,
        B, _, R, _, G, _, G, _, R, _, B,
        B, _, R, _, G, _, G, _, R, _, B,
        B, _, R, _, G, _, G, _, R, _, B,
        B, _, R, _, G, _, G, _, R, _, B,
        B, _, R, _, G, _, G, _, R, _, B,
        O, _, A, _, A, _, A, _, A, _, O,
        B, _, R, _, G, _, G, _, R, _, B }
    },
    {
      "Llaminadura poligonera", /* Level 07 */
      k::Background::BlueCircuit,
      { _, _, _, _, _, _, _, _, _, _, _,
        _, _, _, _, _, _, _, _, _, _, _,
        _, _, _, _, _, _, _, _, _, _, _,
        _, _, _, _, _, _, _, _, _, _, _,
        _, _, _, _, Y, L, B, _, _, _, _,
        _, _, _, Y, G, B, L, Y, _, _, _,
        _, _, _, L, B, G, Y, O, _, _, _,
        _, _, G, B, L, Y, G, R, O, _, _,
        _, _, B, G, Y, O, R, G, Y, _, _,
        _, _, L, Y, G, R, O, Y, G, _, _,
        _, _, Y, O, R, G, Y, L, B, _, _,
        _, _, G, R, O, Y, G, B, L, _, _,
        _, _, R, G, Y, L, B, G, Y, _, _,
        _, _, _, Y, G, B, L, Y, _, _, _,
        _, _, _, L, B, G, Y, O, _, _, _,
        _, _, _, _, L, Y, G, _, _, _, _ }
    },
    {
      "Papallona eteria", /* Level 08 */
      k::Background::RedCircuit,
      { _, _, _, _, _, _, _, _, _, _, _,
        _, _, _, _, _, _, _, _, _, _, _,
        _, _, _, _, _, _, _, _, _, _, _,
        _, A, _, _, A, _, A, _, _, A, _,
        _, A, A, _, _, _, _, _, A, A, _,
        _, _, _, _, _, O, _, _, _, _, _,
        _, _, _, _, A, G, A, _, _, _, _,
        _, _, A, _, _, Y, _, _, A, _, _,
        _, _, _, _, _, B, _, _, _, _, _,
        _, _, A, _, _, R, _, _, A, _, _,
        _, _, _, _, A, G, A, _, _, _, _,
        _, _, _, _, _, Y, _, _, _, _, _,
        _, A, A, _, _, _, _, _, A, A, _,
        _, A, _, _, A, _, A, _, _, A, _ }
    },
    {
      "Poals d'or", /* Level 09 */
      k::Background::Blue,
      { _, _, _, _, _, _, _, _, _, _, _,
        _, _, _, _, _, _, _, _, _, _, _,
        _, A, _, A, _, _, _, A, _, A, _,
        _, A, G, A, _, _, _, A, G, A, _,
        _, A, B, A, _, _, _, A, B, A, _,
        _, A, A, A, _, _, _, A, A, A, _,
        _, _, _, _, _, _, _, _, _, _, _,
        _, _, _, P, B, B, B, O, _, _, _,
        _, _, _, P, G, L, G, O, _, _, _,
        _, _, _, P, L, G, L, O, _, _, _,
        _, _, _, P, G, L, G, O, _, _, _,
        _, _, _, P, L, G, L, O, _, _, _,
        _, _, _, P, B, B, B, O, _, _, _ }
    },
    {
      "Bufar i fer ampolles", /* Level 10 */
      k::Background::Green,
      { _, A, _, _, _, _, _, _, _, _, _,
        _, _, _, _, _, _, _, _, _, _, _,
        _, A, _, _, _, _, _, _, _, _, _,
        _, A, _, _, _, _, _, _, _, _, _,
        _, A, _, _, _, _, B, _, _, _, _,
        _, A, _, _, _, B, L, B, _, _, _,
        _, A, _, _, B, L, B, L, B, _, _,
        _, A, _, B, L, B, S, B, L, B, _,
        _, A, _, _, B, L, B, L, B, _, _,
        _, A, _, _, _, B, L, B, _, _, _,
        _, A, _, _, _, _, B, _, _, _, _,
        _, A, _, _, _, _, _, _, _, _, _,
        _, A, _, _, _, _, _, _, _, _, _,
        _, A, _, _, _, _, _, _, _, _, _,
        _, A, _, _, _, _, _, _, _, _, _,
        _, A, A, A, A, A, A, A, A, A, A }
    },
    {
      "El bunquer insipid", /* Level 11 */
      k::Background::BlueCircuit,
      { _, _, _, _, _, _, _, _, _, _, _,
        _, _, _, _, _, _, _, _, _, _, _,
        _, _, _, _, _, _, _, _, _, _, _,
        _, _, _, _, _, _, _, _, _, _, _,
        _, S, S, S, S, S, S, S, S, S, _,
        _, S, _, _, _, _, _, _, _, S, _,
        _, S, _, S, S, S, S, S, _, S, _,
        _, S, _, S, _, _, _, S, _, S, _,
        _, S, _, S, _, S, _, S, _, S, _,
        _, S, _, S, _, _, _, S, _, S, _,
        _, S, _, S, S, S, S, S, _, S, _,
        _, S, _, _, _, _, _, _, _, S, _,
        _, S, S, S, S, S, S, S, S, S, _ }
    },
    {
      "Bany embussat", /* Level 12 */
      k::Background::RedCircuit,
      { _, _, _, _, _, _, _, _, _, _, _,
        _, _, _, _, _, _, _, _, _, _, _,
        A, A, A, A, A, A, A, A, A, A, A,
        _, _, _, _, A, _, _, _, A, O, _,
        _, A, G, _, A, _, _, _, A, _, _,
        _, A, _, _, A, _, A, _, A, _, _,
        _, A, _, _, A, _, A, _, A, _, _,
        _, A, _, _, A, G, A, _, A, _, _,
        _, A, _, O, A, _, A, B, A, _, _,
        _, A, _, _, A, R, A, _, A, _, _,
        _, A, _, _, A, _, A, _, A, _, _,
        _, A, _, _, A, _, A, _, A, _, _,
        _, A, L, _, _, _, A, _, _, _, _,
        _, A, _, _, _, _, A, _, _, _, O,
        _, A, A, A, A, A, A, A, A, A, A }
    },
    {
      "Parenceria d'imaginacio", /* Level 13 */
      k::Background::Blue,
      { _, _, _, _, _, _, _, _, _, _, _,
        _, _, _, _, _, _, _, _, _, _, _,
        _, _, _, _, _, _, _, _, _, _, _,
        _, _, _, _, _, _, _, _, _, _, _,
        _, O, O, _, W, W, W, _, O, O, _,
        _, W, W, _, O, O, O, _, W, W, _,
        _, B, B, _, R, R, R, _, B, B, _,
        _, P, P, _, G, G, G, _, P, P, _,
        _, G, G, _, P, P, P, _, G, G, _,
        _, R, R, _, B, B, B, _, R, R, _,
        _, O, O, _, W, W, W, _, O, O, _,
        _, W, W, _, O, O, O, _, W, W, _ }
    },
    {
      "Les primes linies", /* Level 14 */
      k::Background::Green,
      { _, _, _, _, _, _, _, _, _, _, _,
        _, _, _, _, _, _, _, _, _, _, _,
        _, _, _, _, _, _, _, _, _, _, _,
        R, S, S, S, S, S, S, S, S, S, R, 
        A, _, _, _, _, _, _, _, _, _, A,
        B, B, B, B, B, B, B, B, B, B, B,
        _, _, _, _, _, _, _, _, _, _, _,
        O, S, S, S, S, S, S, S, S, S, O,
        A, _, _, _, _, _, _, _, _, _, A,
        B, B, B, B, B, B, B, B, B, B, B,
        _, _, _, _, _, _, _, _, _, _, _,
        B, S, S, S, S, S, S, S, S, S, B,
        A, _, _, _, _, _, _, _, _, _, A,
        R, R, R, R, R, R, R, R, R, R, R,
        _, _, _, _, _, _, _, _, _, _, _,
        R, R, R, R, R, R, R, R, R, R, R,
        A, _, _, _, _, _, _, _, _, _, A }
    },
    {
      "Finestres '20", /* Level 15 */
      k::Background::BlueCircuit,
      { _, _, _, _, _, _, _, _, _, _, _,
        _, _, _, _, _, _, _, _, _, _, _,
        _, _, _, _, _, _, _, _, _, _, _,
        L, S, S, L, L, L, L, L, S, S, L,
        L, S, O, S, L, L, L, S, G, S, L,
        L, S, O, O, S, S, S, G, G, S, L,
        L, S, O, O, O, S, G, G, G, S, L,
        L, S, O, O, O, S, G, G, G, S, L,
        L, S, O, O, O, S, G, G, G, S, L,
        L, S, O, O, O, S, G, G, G, S, L,
        L, S, O, O, O, S, G, G, G, S, L,
        L, S, O, O, O, S, G, G, G, S, L,
        L, L, S, O, O, S, G, G, S, L, L,
        L, L, L, S, O, S, G, S, L, L, L,
        L, L, L, L, S, S, S, L, L, L, L }
    },
    {
      "Pit d'esquelet", /* Level 16 */
      k::Background::RedCircuit,
      { _, _, _, _, _, _, _, _, _, _, _,
        _, _, _, _, _, _, _, _, _, _, _,
        _, _, _, _, _, A, _, _, _, _, _,
        _, _, _, W, W, _, W, W, _, _, _,
        _, W, W, _, _, A, _, _, W, W, _,
        W, _, _, O, O, _, O, O, _, _, W,
        _, O, O, _, _, A, _, _, O, O, _,
        O, _, _, G, G, _, G, G, _, _, O,
        _, G, G, _, _, A, _, _, G, G, _,
        G, _, _, R, R, _, R, R, _, _, G,
        _, R, R, _, _, A, _, _, R, R, _,
        R, _, _, B, B, _, B, B, _, _, R,
        _, B, B, _, _, A, _, _, B, B, _,
        B, _, _, G, G, _, G, G, _, _, B,
        _, G, G, _, _, _, _, _, G, G, _,
        G, _, _, _, _, _, _, _, _, _, G }
    },
    {
      "Al maig tota cuca viu", /* Level 17 */
      k::Background::Blue,
      { _, _, _, _, _, _, _, _, _, _, _,
        _, _, _, _, _, _, _, _, _, _, _,
        _, _, _, _, _, S, _, _, _, _, _,
        _, _, _, B, B, S, G, G, _, _, _,
        _, _, B, B, W, W, W, G, G, _, _,
        _, B, B, W, W, W, W, W, G, G, _,
        _, B, B, W, W, W, W, W, G, G, _,
        _, B, B, W, W, W, W, W, G, G, _,
        _, S, _, S, _, S, _, S, _, S, _,
        _, _, _, _, _, S, _, _, _, _, _,
        _, _, _, _, _, S, _, _, _, _, _,
        _, _, _, A, _, A, _, _, _, _, _,
        _, _, _, A, A, A, _, _, _, _, _,
        _, _, _, _, A, _, _, _, _, _, _ }
    },
    {
      "Acropoli insubmisa", /* Level 18 */
      k::Background::Green,
      { _, _, _, _, _, _, _, _, _, _, _,
        _, _, _, _, _, _, _, _, _, _, _,
        _, _, _, _, _, _, _, _, _, _, _,
        O, _, A, Y, Y, Y, Y, Y, A, _, O,
        O, _, A, A, Y, Y, Y, A, A, _, O,
        O, _, A, _, A, Y, A, _, A, _, O,
        O, _, A, _, G, S, G, _, A, _, O,
        O, _, A, _, G, _, G, _, A, _, O,
        O, _, A, _, G, _, G, _, A, _, O,
        O, _, A, _, G, _, G, _, A, _, O,
        O, _, A, _, G, _, G, _, A, _, O,
        O, _, A, _, G, _, G, _, A, _, O,
        O, A, A, A, G, _, G, A, A, A, O }
    },
    {
      "I? H? Erra, ge, be!", /* Level 19 */
      k::Background::BlueCircuit,
      { _, _, _, _, _, _, _, _, _, _, _,
        _, _, _, _, _, _, _, _, _, _, _,
        _, _, _, _, _, _, _, _, _, _, _,
        _, _, A, A, A, A, A, A, A, _, _,
        _, _, G, R, B, A, B, R, G, _, _,
        _, _, G, R, B, A, B, R, G, _, _,
        _, _, G, R, B, A, B, R, G, _, _,
        _, _, G, R, B, A, B, R, G, _, _,
        _, _, G, R, B, A, B, R, G, _, _,
        _, _, G, R, B, A, B, R, G, _, _,
        _, _, G, R, B, A, B, R, G, _, _,
        _, _, A, A, A, A, A, A, A, _, _ }
    },
    {
      "El nan rosa", /* Level 20 */
      k::Background::RedCircuit,
      { _, _, _, _, _, _, _, _, _, _, _,
        _, _, _, _, _, _, _, _, _, _, _,
        _, _, _, _, _, _, _, _, _, _, _,
        G, A, O, A, L, A, G, A, P, A, O,
        P, A, S, A, S, A, S, A, S, A, L,
        _, _, P, _, _, _, _, _, _, _, _,
        _, A, _, A, P, A, _, A, _, A, _,
        _, A, _, A, _, A, P, A, _, A, _,
        _, A, _, A, _, A, _, A, P, A, _,
        _, _, _, _, _, _, _, _, _, _, _,
        _, A, _, A, _, A, P, A, _, A, _,
        _, A, _, A, P, A, _, A, _, A, _,
        _, _, P, A, _, A, _, A, _, _, _,
        P, _, _, _, _, A, _, _, _, _, _,
        _, _, _, _, _, _, _, _, _, _, _ }
    },
    {
      "Joier en joier", /* Level 21 */
      k::Background::Blue,
      { _, _, _, _, _, _, _, _, _, _, _,
        _, _, _, _, _, _, _, _, _, _, _,
        _, _, _, _, _, _, _, _, _, _, _,
        _, A, O, O, O, O, O, O, O, A, _,
        _, A, _, _, _, _, _, _, _, A, _,
        _, A, _, A, A, A, A, A, _, A, _,
        _, A, _, A, B, B, B, A, _, A, _,
        _, A, _, A, P, P, P, A, _, A, _,
        _, A, _, A, G, G, G, A, _, A, _,
        _, A, _, A, O, O, O, A, _, A, _,
        _, A, _, A, L, L, L, A, _, A, _,
        _, A, _, _, _, _, _, _, _, A, _,
        _, A, _, _, _, _, _, _, _, A, _,
        _, A, A, A, A, A, A, A, A, A, _ } 
    },
    {
      "Quatre indis", /* Level 22 */
      k::Background::Green,
      { _, _, _, _, _, _, _, _, _, _, _,
        _, _, _, _, _, _, _, _, _, _, _,
        _, _, _, _, _, _, _, _, _, _, _,
        O, O, O, O, O, O, O, O, O, O, O,
        _, _, _, _, _, _, _, _, _, _, _,
        R, A, _, A, R, R, R, A, _, A, R,
        R, A, _, A, R, R, R, A, _, A, R,
        R, A, _, A, R, R, R, A, _, A, R,
        R, A, _, A, R, R, R, A, _, A, R,
        _, _, _, _, _, _, _, _, _, _, _,
        W, W, W, W, W, W, W, W, W, W, W,
        W, W, W, W, W, W, W, W, W, W, W } 
    },
    {
      "Profund mar blau", /* Level 23 */
      k::Background::BlueCircuit,
      { _, _, _, _, _, _, _, _, _, _, _,
        _, _, _, _, _, _, _, _, _, _, _,
        B, B, B, B, B, B, B, B, B, B, B,
        _, _, _, _, _, _, _, _, _, _, _,
        S, S, S, _, S, S, S, _, S, S, S,
        S, G, S, _, S, G, S, _, S, G, S,
        S, S, S, _, S, S, S, _, S, S, S,
        _, _, _, _, _, _, _, _, _, _, _,
        _, _, S, S, S, _, S, S, S, _, _,
        _, _, S, R, S, _, S, R, S, _, _,
        _, _, S, S, S, _, S, S, S, _, _,
        _, _, _, _, _, _, _, _, _, _, _,
        S, S, S, _, S, S, S, _, S, S, S,
        S, B, S, _, S, B, S, _, S, B, S,
        S, S, S, _, S, S, S, _, S, S, S } 
    },
    {
      "Elasmobranqui gegant", /* Level 24 */
      k::Background::RedCircuit,
      { _, _, _, _, _, _, _, _, _, _, _,
        _, _, _, _, _, _, _, _, _, _, _,
        _, _, _, _, _, _, _, _, _, _, _,
        _, _, _, _, _, _, _, _, _, _, _,
        _, _, _, _, _, _, _, _, _, _, _,
        _, _, _, _, W, W, W, _, _, _, _,
        _, _, _, _, W, W, W, _, _, _, _,
        _, _, _, _, W, W, W, _, _, _, _,
        _, _, _, W, B, W, B, W, _, _, _,
        _, _, _, B, B, B, B, B, _, _, _,
        _, _, B, B, B, B, B, B, B, _, _,
        _, _, B, B, B, B, B, B, B, _, _,
        _, B, B, B, B, B, B, B, B, B, _,
        B, B, B, B, B, B, B, B, B, B, B } 
    },
    {
      "Palau del sulta", /* Level 25 */
      k::Background::Blue,
      { _, _, _, _, _, _, _, _, _, _, _,
        _, _, _, _, _, _, _, _, _, _, _,
        _, _, _, _, _, _, _, _, _, _, _,
        R, R, R, R, R, R, R, R, R, R, R,
        G, G, G, G, G, G, G, G, G, G, G,
        B, B, B, B, B, B, B, B, B, B, B,
        A, A, A, A, R, R, R, A, A, A, A,
        A, G, G, A, S, S, S, A, G, G, A,
        A, R, R, A, _, _, _, A, B, B, A,
        A, _, _, _, _, _, _, _, _, _, A,
        A, _, _, _, _, _, _, _, _, _, A,
        A, _, _, _, _, _, _, _, _, _, A,
        A, _, _, A, G, G, G, A, _, _, A,
        A, S, S, A, A, A, A, A, S, S, A } 
    },
    {
      "Flor de foc", /* Level 26 */
      k::Background::Green,
      { _, _, _, _, _, _, _, _, _, _, _,
        _, _, _, _, _, _, _, _, _, _, _,
        _, _, _, _, _, _, _, _, _, _, _,
        _, _, _, _, _, _, _, _, _, _, _,
        _, _, A, S, S, A, _, _, _, _, _,
        _, A, _, _, _, _, A, _, _, _, _,
        A, _, _, L, L, _, _, A, _, _, _,
        A, _, B, B, B, B, _, A, _, _, _,
        A, _, _, P, P, _, _, A, _, _, _,
        _, A, _, _, _, _, A, _, _, _, _,
        _, _, A, A, A, A, _, _, _, _, _ } 
    },
    {
      "Estat feixista", /* Level 27 */
      k::Background::BlueCircuit,
      { _, _, _, _, _, _, _, _, _, _, _,
        _, _, _, _, _, _, _, _, _, _, _,
        _, _, _, _, _, _, _, _, _, _, _,
        _, _, _, _, _, _, _, _, _, _, _,
        _, _, _, _, _, _, _, _, _, _, _,
        _, _, _, _, _, _, _, _, _, _, _,
        _, _, _, _, _, _, _, _, _, _, _,
        S, S, S, S, S, S, S, S, S, S, S,
        Y, Y, Y, Y, Y, Y, Y, Y, Y, Y, Y,
        S, S, S, S, S, S, S, S, S, S, S,
        _, _, _, _, _, _, _, _, _, _, _,
        S, S, S, S, S, S, S, S, S, S, S,
        R, R, R, R, R, R, R, R, R, R, R,
        S, S, S, S, S, S, S, S, S, S, S } 
    },
    {
      "Super dona", /* Level 28 */
      k::Background::RedCircuit,
      { _, _, _, _, _, _, _, _, _, _, _,
        _, _, _, _, _, _, _, _, _, _, _,
        _, _, _, _, _, _, _, _, _, _, _,
        B, B, B, B, B, B, B, B, B, B, B,
        B, A, A, A, P, A, P, A, A, A, B,
        B, A, _, _, _, _, _, _, _, A, B,
        B, A, P, _, _, _, _, _, P, A, B,
        B, A, P, P, _, _, _, P, P, A, B,
        _, B, A, P, P, _, P, P, A, B, _,
        _, _, B, A, P, P, P, A, B, _, _,
        _, _, _, B, A, P, A, B, _, _, _,
        _, _, _, _, B, P, B, _, _, _, _,
        _, _, _, _, _, B, _, _, _, _, _ } 
    },
    {
      "Moises al mar de l'amor", /* Level 29 */
      k::Background::Blue,
      { _, _, _, _, _, _, _, _, _, _, _,
        _, _, _, _, _, _, _, _, _, _, _,
        _, _, _, _, _, _, _, _, _, _, _,
        B, B, B, B, A, _, A, B, B, B, B,
        G, G, G, G, A, _, A, G, G, G, G,
        A, A, A, A, A, _, A, A, A, A, A,
        P, P, P, P, A, _, A, P, P, P, P,
        O, O, O, O, A, _, A, O, O, O, O,
        B, B, B, B, A, _, A, B, B, B, B,
        S, S, S, S, A, _, A, S, S, S, S,
        O, O, O, O, A, _, A, O, O, O, O,
        P, P, P, P, A, _, A, P, P, P, P,
        G, G, G, G, A, _, A, G, G, G, G } 
    },
    {
      "Cap abaix", /* Level 30 */
      k::Background::Green,
      { _, _, _, _, _, _, _, _, _, _, _,
        _, _, _, _, _, _, _, _, _, _, _,
        _, _, _, _, _, _, _, _, _, _, _,
        _, _, _, _, _, _, _, _, _, _, _,
        O, P, _, _, _, _, _, _, _, _, _,
        O, P, L, G, _, _, _, _, _, _, _,
        O, P, L, G, O, P, _, _, _, _, _,
        O, P, L, G, O, P, L, G, _, _, _,
        S, P, L, G, O, P, L, G, O, P, _,
        _, A, S, G, O, P, L, G, O, P, L,
        _, _, _, A, S, P, L, G, O, P, L,
        _, _, _, _, _, A, S, G, O, P, L,
        _, _, _, _, _, _, _, A, S, P, L,
        _, _, _, _, _, _, _, _, _, A, S } 
    },
    {
      "Hosti tu, quin pal!", /* Level 31 */
      k::Background::BlueCircuit,
      { _, _, _, _, _, _, _, _, _, _, _,
        _, _, _, _, _, _, _, _, _, _, _,
        _, _, _, _, _, _, _, _, _, _, _,
        B, _, R, _, G, _, P, _, B, _, R,
        S, _, S, _, S, _, S, _, S, _, S,
        _, G, _, R, _, B, _, O, _, G, _,
        _, S, _, S, _, S, _, S, _, S, _,
        O, _, B, _, R, _, G, _, P, _, B,
        S, _, S, _, S, _, S, _, S, _, S,
        _, P, _, G, _, R, _, B, _, O, _,
        _, S, _, S, _, S, _, S, _, S, _,
        G, _, O, _, B, _, R, _, G, _, P,
        S, _, S, _, S, _, S, _, S, _, S,
        _, B, _, P, _, G, _, R, _, B, _,
        _, S, _, S, _, S, _, S, _, S, _,
        R, _, G, _, O, _, B, _, R, _, G,
        S, _, S, _, S, _, S, _, S, _, S } 
    },
    {
      "U.S.C.S.S. Nostromo", /* Level 32 */
      k::Background::RedCircuit,
      { _, _, _, _, _, _, _, _, _, _, _,
        _, _, _, _, _, _, _, _, _, _, _,
        _, _, _, _, _, _, _, _, _, _, _,
        _, _, A, _, A, _, A, _, A, _, _,
        _, _, A, _, A, _, A, _, A, _, _,
        _, _, A, _, A, _, A, _, A, _, _,
        _, _, A, _, A, _, A, R, R, _, _,
        _, _, A, _, A, _, A, _, A, _, _,
        _, _, A, _, A, B, B, B, B, _, _,
        _, _, A, _, A, _, A, _, A, _, _,
        _, _, A, R, R, R, R, R, R, _, _,
        _, _, A, _, A, _, A, _, A, _, _,
        _, _, Y, Y, Y, Y, Y, Y, Y, _, _,
        _, _, S, S, S, S, S, S, S, _, _ }
    },
    {
      "Escurabutxaques", /* Level 33 */
      k::Background::Blue,
      { _, _, _, _, _, _, _, _, _, _, _,
        _, _, _, _, _, _, _, _, _, _, _,
        _, _, _, _, _, R, R, _, _, _, _,
        _, _, _, _, R, S, S, R, _, _, _,
        _, _, _, _, R, S, R, R, _, _, _,
        _, _, _, _, R, R, R, R, _, _, _,
        _, _, _, _, R, R, R, R, _, _, _,
        _, _, _, _, R, R, R, R, _, _, _,
        _, _, _, G, G, R, R, R, B, _, _,
        _, _, G, S, S, R, R, S, S, B, _,
        _, _, G, S, G, G, B, S, B, B, _,
        _, _, G, G, G, G, B, B, B, B, _,
        _, _, G, G, G, G, B, B, B, B, _,
        _, _, G, G, G, G, B, B, B, B, _,
        _, _, G, G, G, G, B, B, B, B, _,
        _, _, _, G, G, _, _, B, B, _, _ } 
    },
    {
      "Gelat de nabius", /* Level 34 */
      k::Background::Green,
      { _, _, _, _, _, _, _, _, _, _, _,
        _, _, _, _, _, _, _, _, _, _, _,
        _, _, _, _, _, _, _, _, _, _, _,
        _, _, _, _, _, _, L, L, L, _, _,
        _, _, _, _, _, _, L, L, P, _, _,
        _, _, _, _, _, L, L, P, P, P, _,
        _, _, _, _, _, L, L, L, P, B, _,
        _, _, _, _, _, L, L, L, L, B, _,
        _, _, _, _, A, L, L, L, L, B, _,
        _, _, _, _, O, B, L, L, B, B, _,
        _, _, _, _, O, O, B, B, B, _, _,
        _, _, _, A, O, A, B, B, B, _, _,
        _, _, _, O, O, O, O, _, _, _, _,
        _, _, A, O, A, O, _, _, _, _, _,
        _, _, O, O, O, O, _, _, _, _, _,
        _, _, O, O, O, _, _, _, _, _, _,
        _, O, O, O, _, _, _, _, _, _, _,
        _, O, O, _, _, _, _, _, _, _, _ } 
    },
    {
      "Flor de carn i sang", /* Level 35 */
      k::Background::BlueCircuit,
      { _, _, _, _, _, _, _, _, _, W, _,
        _, _, _, _, _, _, _, _, _, W, W,
        _, _, _, W, W, W, W, _, _, _, _,
        _, _, _, _, W, W, W, W, _, _, _,
        _, _, _, _, _, A, A, A, _, _, _,
        _, _, W, _, _, _, _, _, _, _, _,
        _, W, O, W, _, _, _, _, _, _, _,
        W, O, A, O, W, _, _, _, _, _, _,
        _, W, O, W, _, _, _, _, _, _, _,
        _, _, W, _, _, _, _, _, _, _, O,
        _, _, P, _, _, A, _, G, G, G, _,
        G, _, P, _, G, _, G, _, G, P, G,
        A, G, P, G, _, P, G, A, G, _, _,
        A, G, P, G, _, G, _, O, G, G, _,
        A, A, G, A, G, _, _, G, G, _, _ } 
    },
    {
      "Moai", /* Level 36 */
      k::Background::Moai,
      { _, _, _, _, _, _, _, _, _, _, _,
        _, _, _, _, _, _, _, _, _, _, _,
        _, _, _, _, _, _, _, _, _, _, _,
        _, _, _, _, _, _, _, _, _, _, _,
        _, _, _, _, _, _, _, _, _, _, _,
        _, _, _, _, _, _, _, _, _, _, _,
        _, _, _, _, _, _, _, _, _, _, _,
        _, _, _, _, _, S, _, _, _, _, _,
        _, _, _, _, _, _, _, _, _, _, _,
        _, _, _, _, _, _, _, _, _, _, _,
        _, _, _, _, _, _, _, _, _, _, _,
        _, _, _, _, _, _, _, _, _, _, _,
        _, _, _, _, _, _, _, _, _, _, _,
        _, _, _, _, _, _, _, _, _, _, _,
        _, _, _, _, _, _, _, _, _, _, _ } 
    }
  };
}

#endif // KETE_ARKA_LEVELS_H_