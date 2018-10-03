#include <iostream>
using namespace std;

typedef struct BiTNode
{
	struct BiTNode* lchild;
	struct BiTNode* rchild;
	char data;
}BiTNode;
      
BiTNode* BuildTree( char* exp, int s, int e )
{
	if ( e - s == 1 )
	{
		BiTNode* p = ( BiTNode* ) malloc( sizeof( BiTNode ) );
		p->data = exp[s];
		p->lchild = p->rchild = nullptr;
		return p;
	}
	int c1 = -1, c2 = -1, c = 0;
	for ( int i = s; i < e; i++ )
	{
		switch ( exp[i] )
		{
		case '(':
			c++;
			break;
		case ')':
			c--;
			break;
		case '+':
		case '-':
			if (!c)
				c1 = i;
			break;
		case '*':
		case '/':
			if (!c)
				c2 = i;
			break;
		default:
			break;
		}
	}
	if ( c1 < 0 )
		c1 = c2;
	if ( c1 < 0 )
		return BuildTree( exp, s + 1, e - 1 );
	BiTNode* p = ( BiTNode* ) malloc( sizeof( BiTNode ) );
	p->data = exp[c1];
	p->lchild = BuildTree( exp, s, c1 );
	p->rchild = BuildTree( exp, c1 + 1, e );
	return p;
}

void visit(BiTNode *T)
{
	cout << T->data << " ";
}


#define MAXSIZE 100
void LevelOrder( BiTNode *T )
{
	BiTNode *Q[MAXSIZE]; int front = -1, rear = -1;
	if ( !T ) return;
	Q[++rear] = T;
	while ( front != rear )
	{
		BiTNode *p = Q[++front];
		visit( p );
		if ( p->lchild )
			Q[++rear] = p->lchild;
		if ( p->rchild )
			Q[++rear] = p->rchild;
	}
}

int main()
{
	char exp[] = "2+3*(4-1)-5/1"/*"a+b*(c-d)-e/f"*/;
	BiTNode *p = BuildTree( exp, 0, strlen( exp ) );
	LevelOrder( p );
	cout << endl;
	return 0;
}