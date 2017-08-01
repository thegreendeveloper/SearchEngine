#include "WikiItem2.h"

WikiItem2::WikiItem2() {}

WikiItem2::WikiItem2(string s, Document * dcm, WikiItem2 * n)
{
	str = s;
	document = dcm;
	next = n;
}


WikiItem2::~WikiItem2() {}
