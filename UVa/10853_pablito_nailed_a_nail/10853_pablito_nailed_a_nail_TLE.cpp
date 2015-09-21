#include <cstdint>
#include <iostream>

using namespace std;

#define MIN(a, b) ((a) < (b) ? (a) : (b))

// 134217729 = 2^27 + 1
// 'turns' start from when the nail is at the bottom and go up. They are a
// possible length at which the nail can be
// if in turn i a moves: {0: a, 1: b} wins.
uint8_t amoves[134217729];
// if in turn i b moves: {0: b, 1: a} wins.
uint8_t bmoves[134217729];

// can have better average-case memory but not better worse-case memory

static uint8_t
_get_bit(uint8_t *arr, int i)
{
    return (arr[i/8] & (0x01 << (i%8))) >> (i%8);
}

static void
set_bit(uint8_t *arr, int i, uint8_t bit)
{
//    printf("Set bit %d to value %d\n", i, bit);
    arr[i/8] = (arr[i/8] & ~(0x01 << (i%8))) | (bit << (i%8));
//    printf("Bit %d has value %d\n", i, _get_bit(arr, i));
}

/* I miss partial application */
/* get correct bits from a and b without initializing the array */
int _amax, _bmax, _abmax_min;
static uint8_t
get_a_bit(int i)
{
    if(i <= _abmax_min) return 0;
    if(i <= _bmax) return 1;
    return _get_bit(amoves, i);
}
static uint8_t
get_b_bit(int i)
{
    if(i <= _abmax_min) return 0;
    if(i <= _amax) return 1;
    return _get_bit(bmoves, i);
}

static char
one_game(int l, int amin, int amax, int bmin, int bmax)
{
//    printf("l: %d; amin: %d; amax: %d; bmin: %d; bmax: %d;\n", l, amin, amax, bmin, bmax);
    if(l <= amax)
	return 'A';

    /* rolla: rolling sum of the bits of amoves from curpos-bmin to curpos-bmax. */
    int rolla, rollb, curpos;

    if(amax > bmax) {
	curpos = amax+1;
	rolla = 0;
	rollb = (curpos - amin) - bmax;
	if(rollb < 0) rollb = 0;
    } else if(amax < bmax) {
	curpos = bmax+1;
	rollb = 0;
	rolla = (curpos - bmin) - amax;
	if(rolla < 0) rolla = 0;
    } else {
	curpos = amax+1;
	rolla = rollb = 0;
    }
    uint8_t nexta, nextb;
    for(; curpos <= l; curpos++) {
	nexta = (rollb > 0 ? 0 : 1);
	nextb = (rolla > 0 ? 0 : 1);
//	printf("rolla: %d; rollb: %d; curpos: %d; nexta: %d; nextb: %d;\n", rolla, rollb, curpos, nexta, nextb);
	set_bit(amoves, curpos, nexta);
	set_bit(bmoves, curpos, nextb);
	rolla += nexta;
	rollb += nextb;
//	printf("ind1: %d, ind2: %d, b1 %d, b2 %d\n", curpos - bmax - bmin + 1, curpos - amax - amin + 1, get_a_bit(curpos - bmax - bmin + 1), get_b_bit(curpos - amax - amin + 1));
	rolla -= get_a_bit(curpos - bmax - bmin + 1);
	rollb -= get_b_bit(curpos - amax - amin + 1);
    }

    return nexta ? 'B' : 'A';
}


int
main()
{
    int l, amin, amax, bmin, bmax, N;
    cin >> N;
    for(; N>0; N--) {
	cin >> l >> amin >> amax >> bmin >> bmax;
	_amax = amax;
	_bmax = bmax;
	_abmax_min = MIN(amax, bmax);
	cout << one_game(l, amin, amax, bmin, bmax) << endl;
    }
    return 0;
}
