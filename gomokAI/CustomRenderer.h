#ifndef CUSTOMRENDERER_H
#define CUSTOMRENDERER_H
#include <SDL.h> 
#include <SDL_ttf.h>
#include <string>
using namespace std;
class CustomRenderer// ������Ʈ�� ���Ǵ� �簢���׸���,���׸���,���׸���,�ؽ�Ʈ �׸������� ĸ��ȭ�Ѵ�.
{
public:
	CustomRenderer();
	CustomRenderer(SDL_Renderer* renderer);
	void DrawEmptyCircle(int32_t centreX, int32_t centreY, int32_t radius);
	void DrawFilledCircle(int32_t centreX, int32_t centreY, int32_t radius);
	void ClearRenderer();
	void DrawRect(float x1,float y1, float width, float height);
	void DrawLine(float x1, float y1, float x2, float y2);
	void DrawText(string text, int x, int y, int fontSize,SDL_Color color);
	void DrawColorChange(SDL_Color color);
	void Render();
private:
	SDL_Renderer * renderer;
};
#endif