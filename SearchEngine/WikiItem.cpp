#include "WikiItem.h"

WikiItem::WikiItem() {}

WikiItem::WikiItem(string s, string dt, WikiItem * n)
{
	str = s;
	document_title = dt;
	next = n;
}


WikiItem::~WikiItem(){}
