#pragma once
#include <map>
#include <string>
#include "BaseTypes.h"
//using namespace std;

enum eKeywordEnum {
	kwNone=0,//нет 
	kwIdent=1,
	//ключевые слова 1000+
	kwProgram =1000,
	kwVar = 1001,
	kwBegin = 1002,
	kwEnd = 1003,
	kwIf = 1004,
	kwThen = 1005,
	kwElse = 1006,
	kwAssign = 1007,
	kwWhile,
	kwDo,
	kwInteger,
	kwReal,
	kwChar,
	kwBoolean,
	//вспомогательные ключевые слова 
	kwhSemicolon = 2000, /* ; */
	kwhDot =2001, /*.*/
	kwhComma =2002, /* , */
	kwhColon = 2003, /*:*/
	//Операции
	kwoPlus =3000, /*+*/
	kwoMinus = 3001, /*-*/
	kwoSlash = 3002, /*/*/
	kwoMult =3003, /***/
	kwhLeftpar = 3004,  /*(*/
	kwhRightpar = 3005,  /*)*/
	kwoEqual=3006, /*=*/
	kwoLess = 3007, /*<*/
	kwoMore = 3008, /*>*/
};


namespace{
std::map<std::string, int > tableKeyWord{
	{ "program", kwProgram},
	{"var" ,kwVar},
	{"begin", kwBegin },
	{"end",kwEnd },
	{"if",kwIf},
	{"then",kwThen },
	{"else",kwElse },
	{":=", kwAssign},
	{"while", kwWhile},
	{"do", kwDo},
	{"integer", kwInteger},
	{"real", kwReal},
	{"boolean", kwBoolean},
	{"char", kwChar},
	//вспомогательные ключевые слова 
	{";",kwhSemicolon}, /* ; */
	{".",kwhDot }, /*.*/
	{",",kwhComma }, /* , */
	{":",kwhColon }, /*:*/
	{"(",kwhLeftpar } ,/* ( */
	{")",kwhRightpar} ,  /* ) */
	//Операции
	{"+",kwoPlus },/*+*/
	{"-",kwoMinus }, /*-*/
	{"/",kwoSlash}, /*/*/
	{"*",kwoMult }, /***/
	{"=",kwoEqual }, /*=*/
	{"<",kwoLess}, /*<*/
	{">",kwoMore }, /*>*/


};

std::map<int, std::string > tableKeyWordByInt{
	{ kwProgram, "program"},
	{ kwVar,"var"},
	{ kwBegin, "begin" },
	{kwEnd,"end" },
	{kwIf,"if"},
	{kwThen,"then" },
	{kwElse,"else" },
	{ kwAssign, ":="},
	{kwWhile,"while"},
	{ kwDo, "do"},
	{kwInteger,"integer" },
	{kwReal, "real" },
	{ kwBoolean, "boolean"},
	{kwChar, "char" },
	//вспомогательные ключевые слова 
	{kwhSemicolon, ";"}, /* ; */
	{kwhDot, "." }, /*.*/
	{kwhComma,"," }, /* , */
	{kwhColon, ":" }, /*:*/
	{kwhLeftpar, "(" } ,/* ( */
	{kwhRightpar, ")"} ,  /* ) */
	//Операции
	{kwoPlus, "+" },/*+*/
	{kwoMinus,"-" }, /*-*/
	{kwoSlash, "/"}, /*/*/
	{kwoMult, "*" }, /***/
	{kwoEqual,"=" }, /*=*/
	{kwoLess,"<"}, /*<*/
	{kwoMore,">" }, /*>*/

};

}
//std::map<std::string, int > tableKeyWord{
//	{ "program", kwProgram},
//	{"var" ,kwVar},
//	{"begin", kwBegin },
//	{"end",kwEnd },
//	{"if",kwIf},
//	{"then",kwThen },
//	{"else",kwElse },
//	//вспомогательные ключевые слова 
//	{";",kwhSemicolon}, /* ; */
//	{".",kwhDot }, /*.*/
//	{",",kwhComma }, /* , */
//	{":",kwhColon }, /*:*/
//	{"(",kwhLeftpar } ,/* ( */
//	{")",kwhRightpar} ,  /* ) */
//	//Операции
//	{"+",kwoPlus },/*+*/
//	{"-",kwoMinus }, /*-*/
//	{"/",kwoSlash}, /*/*/
//	{"-",kwoMult }, /***/
//
//};


//#define star              21    /***/
//#define slash             60    /*/*/
//#define equal_             16    /* = */
//#define comma             20    /* , */
//#define semicolon         14    /* ; */
//#define colon             5     /*:*/
//#define point             61    /*.*/
//#define arrow             62    /*^*/
//#define leftpar           9     /* ( */
//#define rightpar          4     /* ) */
//#define lbracket          11    /* [ */
//#define rbracket          12    /* ] */
//#define flpar             63    /* { */
//#define frpar             64    /* } */
//#define later             65    /* < */
//#define greater           66    /* > */
//#define laterequal        67    /* <= */
//#define greaterequal      68    /* >= */
//#define plus              70    /* + */
//#define minus             71    /* - */
//#define lcomment          72    /* (* */
//#define rcomment          73    /* *) */
//#define assign_            51    /* := */
//#define twopoints         74    /* .. */
//#define ident             2     /* идентификатор */
//#define floatc            82    /* вещественная константа*/
//#define intc              15    /* целая константа*/
//#define charc             83    /* символьная константа*/
//
////!!! Ключевые слова языка с окончанием sy
//#define ifsy 200
//#define dosy 201
//#define ofsy 202
//#define orsy 203
//#define insy 204
//#define tosy 205
//#define endsy 300
//#define varsy 301
//#define divsy 302
//#define andsy 303
//#define notsy 304
//#define forsy 305
//#define modsy 306
//#define nilsy 307
//#define setsy 308
//#define thensy 400
//#define elsesy 401
//#define casesy 402
//#define filesy 403
//#define gotosy 404
//#define typesy 405
//#define withsy 406
//#define beginsy 500
//#define whilesy 501
//#define arraysy 502
//#define constsy 503
//#define labelsy 504
//#define untilsy 505
//#define downtosy 600
//#define packedsy 601
//#define recordsy 602
//#define repeatsy 603
//#define programsy 700
//#define functionsy 800
//#define proceduresy 900
//
