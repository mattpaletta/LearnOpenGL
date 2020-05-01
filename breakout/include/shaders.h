//
//  shaders.h
//  shaders
//
//  Created by Matthew Paletta on 2020-04-29.
//
#pragma once

#include "embed.h"
EMBED_DECL(sprite_vert);
EMBED_DECL(sprite_frag);

embed::Resource sprite_v = sprite_vert();
embed::Resource sprite_f = sprite_frag();
