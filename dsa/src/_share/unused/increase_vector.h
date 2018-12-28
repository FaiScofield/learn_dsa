/******************************************************************************************
 * Data Structures in C++
 * ISBN: 7-302-33064-6 & 7-302-33065-3 & 7-302-29652-2 & 7-302-26883-3
 * Junhui DENG, deng@tsinghua.edu.cn
 * Computer Science & Technology, Tsinghua University
 * Copyright (c) 2006-2013. All rights reserved.
 ******************************************************************************************/

#pragma once

#include "../vector/Vector.h"
#include "increase_elem.h"

template <typename T> void increase(Vector<T>& V) // ͳһ���������еĸ�Ԫ��
{  V.traverse(Increase<T>());  } //��Increase<T>()Ϊ�����������б���