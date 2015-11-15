#include <iostream>
#include <stack>

using namespace std;

int N;
int blocks[25][25];
int num[25];
int pos[25];

void moveBlockToPos(int b, int p)
{
	int origpos = pos[b];
	--num[origpos];

	blocks[p][num[p]] = b;
	++num[p];
	pos[b] = p;
}

void moveBlocksOverBlockToOriginal(int b)
{
	int posb = pos[b];

	int numb = num[posb];
	for (int i = numb -1; i >= 0; --i)
	{
		int bi = blocks[posb][i];
		if (bi != b)
		{
			moveBlockToPos(bi, bi);
		}
		else
		{
			break;
		}
	}
}

void pileBlockInPosition(int b, int p)
{
	int posb = pos[b];

	stack<int> bbb;

	int numb = num[posb];
	for (int i = numb - 1; i >= 0; --i)
	{
		bbb.push(blocks[posb][i]);

		if (blocks[posb][i] == b)
			break;
	}

	while (!bbb.empty())
	{
		moveBlockToPos(bbb.top(), p);
		bbb.pop();
	}
}

void moveOnto(int b1, int b2)
{
	moveBlocksOverBlockToOriginal(b1);
	moveBlocksOverBlockToOriginal(b2);
	moveBlockToPos(b1, pos[b2]);
}

void moveOver(int b1, int b2)
{
	moveBlocksOverBlockToOriginal(b1);
	moveBlockToPos(b1, pos[b2]);
}

void pileOnto(int b1, int b2)
{
	moveBlocksOverBlockToOriginal(b2);
	pileBlockInPosition(b1, pos[b2]);
}

void pileOver(int b1, int b2)
{
	pileBlockInPosition(b1, pos[b2]);
}

void reset()
{
	for (int i = 0; i < 25; ++i)
	{
		pos[i] = i;
		num[i] = 1;
		blocks[i][0] = i;
	}
}

int main()
{
	string m1, m2;
	int b1, b2;

	while (cin >> N)
	{
		reset();

		while (cin >> m1)
		{
			if (m1 == "quit") break;

			cin >> b1 >> m2 >> b2;

			if (b1 != b2 && pos[b1] != pos[b2])
			{
				if (m1 == "move")
				{
					if (m2 == "onto")
					{
						moveOnto(b1, b2);
					}
					else if (m2 == "over")
					{
						moveOver(b1, b2);
					}
				}
				else if (m1 == "pile")
				{
					if (m2 == "onto")
					{
						pileOnto(b1, b2);
					}
					else if (m2 == "over")
					{
						pileOver(b1, b2);
					}
				}
			}
		}

		for (int i = 0; i < N; ++i)
		{
			cout << i << ":";

			for (int j = 0; j < num[i]; ++j)
			{
				cout << " " << blocks[i][j];
			}

			cout << "\n";
		}
	}

	return 0;
}

