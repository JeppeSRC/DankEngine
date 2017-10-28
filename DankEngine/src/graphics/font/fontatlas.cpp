#include "font.h"

namespace dank {

FontAtlas::FontAtlas(ftgl::texture_atlas_t* atlas) : Texture(atlas->id, atlas->width, atlas->height, false), atlas(atlas) {

}

FontAtlas::~FontAtlas() {
	texture_atlas_delete(atlas);
}

void FontAtlas::Bind(unsigned int slot) const {
	GL(glActiveTexture(GL_TEXTURE0 + slot));
	GL(glBindTexture(GL_TEXTURE_2D, textureID));
}

}
