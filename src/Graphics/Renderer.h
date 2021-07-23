#pragma once

#include <map>
#include <string>

namespace Apex {

	class Texture;
	class BitMapFont;
	class Vec2;
	class Shader;

	class Renderer
	{
		std::map<std::string, Texture*>	m_loadedTextures;
		std::map<std::string, BitMapFont*>	m_loadedFonts;

	public:
		Renderer();
	    ~Renderer();

		void InitRender();

		void Push();
		void Pop();

		void Drawtext2D(const Vec2& drawMins, const std::string& asciiText, float cellHeight, const BitMapFont* font, float aspectScale, Shader shader);

		Texture* CreateOrGetTexture(const std::string& path);
		BitMapFont* CreateOrGetBitmapFont(const char* bitmapFontName);

		static void BeginLineLoop();
		static void BeginLineStrip();
		static void BeginPolygon();
		static void BeginQuads();

		static void End();
		static void Flush();
	};

}