#pragma once

#define IS_IN_SET(_item, _set) (_set.find(_item) != _set.end())
#define IS_SUBSET(_small,_big) (std::includes(_big.begin(), _big.end(), _small.begin(), _small.end()))
#define COPY_SET(_ori, _dest) (std::copy(_ori.begin(), _ori.end(), std::inserter(_dest, _dest.begin())))

#define FILL_VECTOR(_vt, _size, _item) {_vt.resize(_size); \
                                        std::fill(_vt.begin(), _vt.end(), _item);}
