// #include <iostream>
// using namespace std;
// 
// typedef struct BiTNode
// {
// 	struct BiTNode* lchild;
// 	struct BiTNode* rchild;
// 	char data;
// }BiTNode;
//       
// BiTNode* BuildTree( char* exp, int s, int e )
// {
// 	if ( e - s == 1 )
// 	{
// 		BiTNode* p = ( BiTNode* ) malloc( sizeof( BiTNode ) );
// 		p->data = exp[s];
// 		p->lchild = p->rchild = nullptr;
// 		return p;
// 	}
// 	int c1 = -1, c2 = -1, c = 0;
// 	for ( int i = s; i < e; i++ )
// 	{
// 		switch ( exp[i] )
// 		{
// 		case '(':
// 			c++;
// 			break;
// 		case ')':
// 			c--;
// 			break;
// 		case '+':
// 		case '-':
// 			if (!c)
// 				c1 = i;
// 			break;
// 		case '*':
// 		case '/':
// 			if (!c)
// 				c2 = i;
// 			break;
// 		default:
// 			break;
// 		}
// 	}
// 	if ( c1 < 0 )
// 		c1 = c2;
// 	if ( c1 < 0 )
// 		return BuildTree( exp, s + 1, e - 1 );
// 	BiTNode* p = ( BiTNode* ) malloc( sizeof( BiTNode ) );
// 	p->data = exp[c1];
// 	p->lchild = BuildTree( exp, s, c1 );
// 	p->rchild = BuildTree( exp, c1 + 1, e );
// 	return p;
// }
// 
// void visit(BiTNode *T)
// {
// 	cout << T->data << " ";
// }
// 
// 
// #define MAXSIZE 100
// void LevelOrder( BiTNode *T )
// {
// 	BiTNode *Q[MAXSIZE]; int front = -1, rear = -1;
// 	if ( !T ) return;
// 	Q[++rear] = T;
// 	while ( front != rear )
// 	{
// 		BiTNode *p = Q[++front];
// 		visit( p );
// 		if ( p->lchild )
// 			Q[++rear] = p->lchild;
// 		if ( p->rchild )
// 			Q[++rear] = p->rchild;
// 	}
// }
// 
// int main()
// {
// 	char exp[] = "2+3*(4-1)-5/1"/*"a+b*(c-d)-e/f"*/;
// 	BiTNode *p = BuildTree( exp, 0, strlen( exp ) );
// 	LevelOrder( p );
// 	cout << endl;
// 	return 0;
// }
// 

#include <iostream>
#include <string>
#include <fstream>
using namespace std;

enum SymbolEnum
{
	// 标题枚举值在0~99范围
	title = 0,
	subtitle,
	newLine,
	nextLine,
	nextLevel,
	prevLevel,

	// 标点符号在100~
	colon = 100,

	comma,
	period,
	none
};

struct SYMBOL_ELEM
{
	int val;
	string symbol;
	int lvl;
	string data;
};

SYMBOL_ELEM st[]=
{
	// 标题都在0~99以内
	{ title, "标题",0,"\n★" },
// { "五角星",0,"\n★" },
// {"五角形",0,"\n★"},

/*{ "菱形",1,"\n  ◇" },*/
{ subtitle, "二级标题",1,"\n  ◇"},

// { "水平线",2,"\n    - " },
// { "横线",2,"\n    - " },
// { "横杠",2,"\n    - " },
// { "横岗",2,"\n    - " },
// { "横县",2,"\n    - " },
{ subtitle, "三级标题",2,"\n    - " },
{ subtitle, "四级标题",3,"\n      * " },
{ subtitle, "五级标题",4,"\n        #"},
{ newLine ,"新的一行",9,"\n" },
{ newLine ,"新的银行",9,"\n" },
{ newLine ,"新的也行",9,"\n"},
// 其他在100~999

{none, "[没有该级]",900,"[没有该级]"},
{ colon, "冒号",999,":" },
{ comma, "逗号",999,","},
{period,"句号",999,"."},
// special
{ nextLine,"下一行",999,"" },
// { "回车",999,"" },
// { "换行",999,"" },
{ prevLevel,"上一级",999,"" },
{ prevLevel,"像以及",999,"" },
{ nextLevel,"下一级",999,"" },

};


const SYMBOL_ELEM SymbolNone = { none, "[没有该级]", 900, "[没有该级]" };

SYMBOL_ELEM symbol_next( SYMBOL_ELEM sym )
{
	int lenST = sizeof( st ) / sizeof( SYMBOL_ELEM );
	for ( int i = 0; i < lenST; i++ )
		if ( st[i].lvl > sym.lvl )
			return st[i];
	return SymbolNone;
}

SYMBOL_ELEM symbol_prev( SYMBOL_ELEM sym )
{
	if ( sym.lvl <= 0 )
		return sym;
	int lenST = sizeof( st ) / sizeof( SYMBOL_ELEM );
	for ( int i = lenST-1; i >= 0; i-- )
		if ( st[i].lvl < sym.lvl )
			return st[i];
	return SymbolNone;
}

SYMBOL_ELEM symbol_match( char* pSource, bool& isMatch)
{
	isMatch = true;
	int lenST = sizeof( st ) / sizeof( SYMBOL_ELEM );
	bool flag = false;
	for ( int i = 0; i < lenST; i++ )
	{
		flag = true;
		int len = st[i].symbol.size();
		const char *p = st[i].symbol.c_str();
		char *pStr = pSource;
		while ( pStr && len--)
		{
			if ( *p != *pStr )
			{
				flag = false;
				break;
			}
			p++; pStr++;
		}
		if ( len != -1 )
			flag = false;
		if ( flag )
		{
			isMatch = flag;
			return st[i];
		}
	}
	isMatch = false;
	return SymbolNone;
}

int main()
{
	string fileInName = "C:\\Users\\yijia\\Desktop\\txtIn.txt";
	string fileOutName = "C:\\Users\\yijia\\Desktop\\txtOut.txt";
	ifstream fileIn;
	ofstream fileOut;
	fileIn.open( fileInName );
	fileOut.open( fileOutName );
	cout.rdbuf( fileOut.rdbuf() );

	if ( !fileIn)
	{
		wprintf( L"打开文件%s错误!\n", fileInName );
		return 0;
	}
	if ( !fileOut )
	{
		wprintf( L"打开文件%s错误!\n", fileOutName );
		return 0;
	}
	
	string str;
	SYMBOL_ELEM nextSymbol,prevSymbol,curSymbol;
	while ( getline( fileIn, str ) )
	{
		int lenStr = str.size();
		for ( int i = 0; i < lenStr; )
		{
			bool isMatch = false;
			SYMBOL_ELEM sym = symbol_match( &str[i] , isMatch);
			
			if ( isMatch )
			{
				if ( curSymbol.val == title && sym.val < 100 )
					cout << &curSymbol.data[1];
				switch ( sym.val )
				{
					case nextLine:
						cout << curSymbol.data;
						break;
					case nextLevel:
						curSymbol = symbol_next( curSymbol );
						cout << curSymbol.data;
						break;
					case prevLevel:
						curSymbol = symbol_prev( curSymbol );
						cout << curSymbol.data;
						break; 
					case title:
					case subtitle:
						curSymbol = sym;
						cout << sym.data;
						break;
					case colon:
						cout << sym.data;
						curSymbol = symbol_next( curSymbol );
						cout << curSymbol.data;
						break;
					case period:
					case comma:
						cout << sym.data;
						break;
					default:
						break;
				}
				i += sym.symbol.size();
			}
			else
				cout << str[i++];

		}
		cout << endl;
	}
	fileIn.close();
	fileOut.close();

	return 0;
}