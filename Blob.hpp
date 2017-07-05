#pragma once

#include "Util.hpp"
#include <vector>
#include <cstdint>
#include "flatbuffers/flatbuffers.h"

BEGIN_XE_NAMESPACE

class Blob
{
public:
	Blob(flatbuffers::DetachedBuffer buffer);
	Blob(const uint8_t *buffer, size_t size);
	Blob(const Blob &other);
	Blob(Blob &&other);
	const std::vector<uint8_t> &data() const { return _data; }
	const uint8_t *dataPtr() const { return &_data[0]; }
	const size_t size() const { return _data.size(); }

private:
	std::vector<uint8_t> _data;
};

END_XE_NAMESPACE
