#include "Blob.hpp"

BEGIN_XE_NAMESPACE

Blob::Blob(flatbuffers::DetachedBuffer buffer) :
	Blob(buffer.data(), buffer.size())
{ }

Blob::Blob(const uint8_t *buffer, size_t size) : _data(buffer, buffer + size)
{ }

Blob::Blob(const Blob &other) : _data(other._data)
{ }

Blob::Blob(Blob &&other) : _data(std::move(other._data))
{ }

END_XE_NAMESPACE
