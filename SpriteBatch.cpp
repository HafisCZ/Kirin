#include "SpriteBatch.h"

#include <algorithm>

namespace Kirin {

	SpriteBatch::SpriteBatch() :
		_vbo(0),
		_vao(0)
	{

	}


	SpriteBatch::~SpriteBatch() {
	}

	void SpriteBatch::init() {
		createVertexArray();
	}

	void SpriteBatch::begin(GlyphSortType sortType) {
		_sortType = sortType;
		_renderBatches.clear();
		_glyphs.clear();
	}

	void SpriteBatch::end() {
		_glyphsPtrs.resize(_glyphs.size());
		for (int i = 0; i < _glyphs.size(); i++) {
			_glyphsPtrs[i] = &_glyphs[i];
		}

		sortGlyphs();
		createRenderBatches();
	}

	void SpriteBatch::draw(const glm::vec4& destRect, const glm::vec4& uvRect, GLuint texture, float depth, const ColorRGBA8& color) {
		_glyphs.emplace_back(destRect, uvRect, texture,depth, color);
	}

	void SpriteBatch::renderBatch() {
		glBindVertexArray(_vao);
		for (int i = 0; i < _renderBatches.size(); i++) {
			glBindTexture(GL_TEXTURE_2D, _renderBatches[i].texture);
			glDrawArrays(GL_TRIANGLES, _renderBatches[i].offset, _renderBatches[i].numVertices);
		}
		glBindVertexArray(0);
	}

	void SpriteBatch::createRenderBatches() {
		std::vector<Vertex> vertices;
		vertices.resize(_glyphs.size() * 6);
		if (_glyphs.empty()) {
			return;
		}

		int cv = 0, offset = 0;
		_renderBatches.emplace_back(offset, 6, _glyphsPtrs[0]->texture);
		vertices[cv++] = _glyphsPtrs[0]->topLeft;
		vertices[cv++] = _glyphsPtrs[0]->bottomLeft;
		vertices[cv++] = _glyphsPtrs[0]->bottomRight;
		vertices[cv++] = _glyphsPtrs[0]->bottomRight;
		vertices[cv++] = _glyphsPtrs[0]->topRight;
		vertices[cv++] = _glyphsPtrs[0]->topLeft;
		offset += 6;

		for (int cg = 1; cg < _glyphsPtrs.size(); cg++) {
			if (_glyphsPtrs[cg]->texture != _glyphsPtrs[cg - 1]->texture) {
				_renderBatches.emplace_back(offset, 6, _glyphsPtrs[cg]->texture);
			} else {
				_renderBatches.back().numVertices += 6;
			}

			vertices[cv++] = _glyphsPtrs[cg]->topLeft;
			vertices[cv++] = _glyphsPtrs[cg]->bottomLeft;
			vertices[cv++] = _glyphsPtrs[cg]->bottomRight;
			vertices[cv++] = _glyphsPtrs[cg]->bottomRight;
			vertices[cv++] = _glyphsPtrs[cg]->topRight;
			vertices[cv++] = _glyphsPtrs[cg]->topLeft;
			offset += 6;
		}

		glBindBuffer(GL_ARRAY_BUFFER, _vbo);
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), nullptr, GL_DYNAMIC_DRAW);
		glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(Vertex), vertices.data());
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void SpriteBatch::createVertexArray() {
		// Create and bind Vertex Array Object
		if (_vao == 0) glGenVertexArrays(1, &_vao);
		glBindVertexArray(_vao);

		// Create and bind Vertex Buffer Object
		if (_vbo == 0) glGenBuffers(1, &_vbo);
		glBindBuffer(GL_ARRAY_BUFFER, _vbo);

		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);

		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));
		glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void*)offsetof(Vertex, color));
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uv));

		glBindVertexArray(0);
	}

	void SpriteBatch::sortGlyphs() {
		switch (_sortType) {
			case GlyphSortType::BACK_TO_FRONT:
				std::stable_sort(_glyphsPtrs.begin(), _glyphsPtrs.end(), compareBackToFront);
				break;
			case GlyphSortType::FRONT_TO_BACK:
				std::stable_sort(_glyphsPtrs.begin(), _glyphsPtrs.end(), compareFrontToBack);
				break;
			case GlyphSortType::TEXTURE:
				std::stable_sort(_glyphsPtrs.begin(), _glyphsPtrs.end(), compareTexture);
				break;
		}
	}

	bool SpriteBatch::compareFrontToBack(Glyph *a, Glyph *b) {
		return (a->depth < b->depth);
	}

	bool SpriteBatch::compareBackToFront(Glyph *a, Glyph *b) {
		return (a->depth > b->depth);
	}

	bool SpriteBatch::compareTexture(Glyph *a, Glyph *b) {
		return (a->texture < b->texture);
	}
}