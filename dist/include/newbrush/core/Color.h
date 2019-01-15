﻿/*******************************************************
**	Color
**
**	颜色类
**	提供RGB颜色模式、HSV（与HSB是一样的）颜色模式、32位整型
**	和十六进制#RRGGBBAA字符串格式（如#FF00FFFF）的构建方式。
**	
**
**	可对各模式的参数进行设置和查询
**	RGB模式：R、G、B（整型参数范围为0~255，浮点参数为0.0~1.0）
**  SHV模式：S、H、B（S[0.0,360.0]、H[0.0,1.0]、B[0.0,1.0]
**	
**
**		潘荣涛
**	
********************************************************/
#pragma once
#include "../core/Def.h"

namespace nb{ namespace core{

class NB_API Color
{
public:
	//构建一个Color，它的argb为(255, 0, 0, 0)
	Color();

	//构建一个Color，它的argb为(255, r, g, b)
	Color(uint8_t r, uint8_t g, uint8_t b);

	//构建一个Color，它的argb为(a, r, g, b)
	Color(uint8_t a, uint8_t r, uint8_t g, uint8_t b);

	Color(const Color &other);
	~Color();

	void operator =(const Color &other);
	bool operator ==(const Color &other) const;
	bool operator !=(const Color &other) const;

	//整型argb是否合法，argb：[0~255]
	static bool isValidArgb(int a, int r, int g, int b);

	//浮点argb是否合法，argb：[0.0~1.0]
	static bool isValidArgbF(float a, float r, float g, float b);

	//HSV格式数据是否合法，h：[0.0~360.0]	s：[0.0~1.0]	v：[0.0~1.0]
	static bool isValidHsv(float h, float s, float v);

	//argb组成的32位整形数，格式化为0xAARRGGBB
	static Color fromInteger32(unsigned int argb);

	//HSV（色调、饱和度、亮度）格式的数据读入，h：[0.0~360.0]	s：[0.0~1.0]	v：[0.0~1.0]
	static Color fromHsv(float h, float s, float v);

	////屏蔽cmyk格式
	//Cmyk格式的数据格式
	//static Color FromCmyk(int c, int m, int y, int k);

	//浮点形式的argb，a、r、g、b范围0.0~1.0
	static Color fromRgbF(float r, float g, float b);
	static Color fromArgbF(float a, float r, float g, float b);

	//#AARRGGBB argb字符串
	//static Color FromArgbHexString(const String &sHex);

public:
	//alpha值
	uint8_t &alpha();
	uint8_t alpha() const;

	//red值
	uint8_t &red();
	uint8_t red() const;

	//green值
	uint8_t &green();
	uint8_t green() const;

	//blue值
	uint8_t &blue();
	uint8_t blue() const;

	//设置alpha值
	void setAlpha(uint8_t a);

	//设置red值
	void setRed(uint8_t r);

	//设置green值
	void setGreen(uint8_t g);

	//设置blue值
	void setBlue(uint8_t b);

	//设置rgb值
	void setRgb(uint8_t r, uint8_t g, uint8_t b);

	//设置argb值
	void setArgb(uint8_t a, uint8_t r, uint8_t g, uint8_t b);

	//alpha值的浮点形式（0.0-1.0)
	float alphaF() const;

	//red值的浮点形式（0.0-1.0)
	float redF() const;

	//green值的浮点形式（0.0-1.0)
	float greenF() const;

	//blue值的浮点形式（0.0-1.0)
	float blueF() const;

	//设置浮点形式alpha值
	void setAlphaF(float a);

	//设置浮点形式red值
	void setRedF(float r);

	//设置浮点形式green值
	void setGreenF(float g);

	//设置浮点形式blue值
	void setBlueF(float b);

	//设置浮点形式rgb值
	void setRgbF(float r, float g, float b);

	//设置浮点形式argb值
	void setArgbF(float a, float r, float g, float b);

	//色调
	float hue() const;

	//饱和度
	float saturation() const;

	//亮度
	float value() const;

	//设置色调
	void setHue(float h);

	//设置饱和度
	void setSaturation(float s);

	//设置亮度
	void setValue(float v);

	//设置色调、饱和度、亮度值
	void setHsv(float h, float s, float v);

	////屏蔽cmyk格式
	//void SetCmyk(int c, int m, int y, int k);
	//void GetCmyk(int *c, int *m, int *y, int *k);

	//void SetRgbaHexString(const String &sHex);
	//String GetRgbaHexString() const;

	//转换成32位整数，0xAARRGGBB
	void setInteger32(uint32_t argb);

	//转换为整数
	uint32_t toInteger32() const;

	//判断颜色值是否相等
	bool equals(const Color &other) const;

public:
	static Color aliceBlue();
	static Color antiqueWhite();
	static Color aqua();
	static Color aquamarine();
	static Color azure();
	static Color beige();
	static Color bisque();
	static Color black();
	static Color blanchedAlmond();
	static Color bluePure();
	static Color blueViolet();
	static Color brown();
	static Color burlyWood();
	static Color cadetBlue();
	static Color chartreuse();
	static Color chocolate();
	static Color coral();
	static Color cornflowerBlue();
	static Color cornsilk();
	static Color crimson();
	static Color cyan();
	static Color darkBlue();
	static Color darkCyan();
	static Color darkGoldenrod();
	static Color darkGray();
	static Color darkGreen();
	static Color darkKhaki();
	static Color darkMagenta();
	static Color darkOliveGreen();
	static Color darkOrange();
	static Color darkOrchid();
	static Color darkRed();
	static Color darkSalmon();
	static Color darkSeaGreen();
	static Color darkSlateBlue();
	static Color darkSlateGray();
	static Color darkTurquoise();
	static Color darkViolet();
	static Color deepPink();
	static Color deepSkyBlue();
	static Color dimGray();
	static Color dodgerBlue();
	static Color firebrick();
	static Color floralWhite();
	static Color forestGreen();
	static Color fuchsia();
	static Color gainsboro();
	static Color ghostWhite();
	static Color gold();
	static Color goldenrod();
	static Color gray();
	static Color greenPure();
	static Color greenYellow();
	static Color honeydew();
	static Color hotPink();
	static Color indianRed();
	static Color indigo();
	static Color ivory();
	static Color khaki();
	static Color lavender();
	static Color lavenderBlush();
	static Color lawnGreen();
	static Color lemonChiffon();
	static Color lightBlue();
	static Color lightCoral();
	static Color lightCyan();
	static Color lightGoldenrodYellow();
	static Color lightGray();
	static Color lightGreen();
	static Color lightPink();
	static Color lightSalmon();
	static Color lightSeaGreen();
	static Color lightSkyBlue();
	static Color lightSlateGray();
	static Color lightSteelBlue();
	static Color lightYellow();
	static Color lime();
	static Color limeGreen();
	static Color linen();
	static Color magenta();
	static Color maroon();
	static Color mediumAquamarine();
	static Color mediumBlue();
	static Color mediumOrchid();
	static Color mediumPurple();
	static Color mediumSeaGreen();
	static Color mediumSlateBlue();
	static Color mediumSpringGreen();
	static Color mediumTurquoise();
	static Color mediumVioletRed();
	static Color midnightBlue();
	static Color mintCream();
	static Color mistyRose();
	static Color moccasin();
	static Color navajoWhite();
	static Color navy();
	static Color oldLace();
	static Color olive();
	static Color oliveDrab();
	static Color orange();
	static Color orangeRed();
	static Color orchid();
	static Color paleGoldenrod();
	static Color paleGreen();
	static Color paleTurquoise();
	static Color paleVioletRed();
	static Color papayaWhip();
	static Color peachPuff();
	static Color peru();
	static Color pink();
	static Color plum();
	static Color powderBlue();
	static Color purple();
	static Color redPure();
	static Color rosyBrown();
	static Color royalBlue();
	static Color saddleBrown();
	static Color salmon();
	static Color sandyBrown();
	static Color seaGreen();
	static Color seaShell();
	static Color sienna();
	static Color silver();
	static Color skyBlue();
	static Color slateBlue();
	static Color slateGray();
	static Color snow();
	static Color springGreen();
	static Color steelBlue();
	static Color tan();
	static Color teal();
	static Color thistle();
	static Color tomato();
	static Color transparent();
	static Color turquoise();
	static Color violet();
	static Color wheat();
	static Color white();
	static Color whiteSmoke();
	static Color yellow();
	static Color yellowGreen();
	
private:
	//返回值将被四舍五入，比如如果R计算为127.5，置为128
	static uint8_t argbF2Argb(float f);
	//返回结果将保持float的小数精度
	static float argb2ArgbF(uint8_t n);

	//rgbF与hsv的转换
	static void rgbF2Hsv(float r, float g, float b, float &h, float &s, float &v);
	static void hsv2RgbF(float h, float s, float v, float &r, float &g, float &b);


	uint8_t		m_Alpha;
	uint8_t		m_Red;
	uint8_t		m_Green;
	uint8_t		m_Blue;
};

}}
