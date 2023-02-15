/**
 * @file        TextDrawer.cpp
 * @author      your name (you@domain.com)
 * @brief       A drawer with text in it.
 * @version     0.1
 * @date        16-02-2023
 *
 * @copyright   Copyright (c) 2023
 */


#include "pch.h"

#include "LEDA_Graphics.h"
#include "TextDrawer.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iterator>
#include <unordered_map>

#include <ft2build.h>
#include FT_FREETYPE_H

// modified from https://learnopengl.com/In-Practice/Text-Rendering
// freetype character helper
class Character {

public:
    unsigned int textureid;
    glm::ivec2   size;
    glm::ivec2   bearing;
    unsigned int advance;

};

std::unordered_map<char, Character> characters;
unsigned int VAO, VBO;

void LEDA::initializeTextDrawer() {

    FT_Library ft;
    if (FT_Init_FreeType(&ft)) {
        LOG_WARNING("couldn't initialize the FreeType library");
        return;
    }
    
    std::string font_name = ""; // FileSystem::getPath("resources/fonts/Arial.ttf");
    if (font_name.empty()) {
        LOG_WARNING("failed to load font name");
        return;
    }
    
    FT_Face face;
    if (FT_New_Face(ft, font_name.c_str(), 0, &face)) {
        LOG_WARNING("failed to load font face");
        return;
    }
    else {
        // set the size of the character glyphs
        FT_Set_Pixel_Sizes(face, 0, 48);
        // disable byte-alignment restrictions
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
        // load the first 128 ASCII characters
        for (unsigned char c = 0; c < 128; c++) {
            if (FT_Load_Char(face, c, FT_LOAD_RENDER)) {
                LOG_WARNING(std::string("failed to load character glyph: ") + std::to_string(c));
                continue;
            }
            unsigned int texture;
            glGenTextures(1, &texture);
            glBindTexture(GL_TEXTURE_2D, texture);
            glTexImage2D(
                GL_TEXTURE_2D,
                0,
                GL_RED,
                face->glyph->bitmap.width,
                face->glyph->bitmap.rows,
                0,
                GL_RED,
                GL_UNSIGNED_BYTE,
                face->glyph->bitmap.buffer
            );
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            // memo (in unordered map)
            Character character = {
                texture,
                glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
                glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
                static_cast<unsigned int>(face->glyph->advance.x)
            };
            characters.insert(std::pair<char, Character>(c, character));
        }
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    // done!
    FT_Done_Face(face);
    FT_Done_FreeType(ft);

}

void LEDA::drawText(std::string string) {
    // wow
}

void LEDA::freeTextDrawer() {

}